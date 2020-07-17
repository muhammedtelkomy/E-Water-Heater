/****************************************************************************
* Title                 :   Electric Heater
* Filename              :   EW_Heater.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   Functions of This file can be configured from config_EW_Heater.h
*******************************************************************************/
/** \file   EW_Heater.c
 *  \brief  This file contains all the heater application functions and tasks.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "i2c.h"
#include "eeprom_ext.h"
#include "adc.h"
#include "ssd.h"
#include "port.h"
#include "heater.h"
#include "cooler.h"
#include "heatLED.h"
#include "sw.h"
#include "tempsensor.h"
#include "ext_int.h"
#include "EW_Heater.h"
#include "sch.h"

/******************************************************************************
* Variables
*******************************************************************************/
/*------------------------------------------------------------------*
 * static unsigned char (DTemp) is the (Set/Desired) temperature used by:
 *          - SSD_UpdateDisp_Task()
 *          - Temp_Control_Task()
 *          - SetTemp_Task()
 * static DISP_MOD_T (OP_mode) is the current operating mode used by:
 *          - SetTemp_Task()
 *          - SSD_UpdateDisp_Task()
 * static PWR_MOD_T (pwr_mode) POWER_OFF = MCU was or currently in sleep mode
 *          - SSD_UpdateDisp_Task()
 *          - Temp_Control_Task()
-*------------------------------------------------------------------*/ 
static unsigned char DTemp = INITIAL_TEMP;
static PWR_MOD_T pwr_mode = POWER_OFF;
static DISP_MOD_T OP_mode = TEMP_DISP_MODE ;

/******************************************************************************
* Functions
*******************************************************************************/
/*------------------------------------------------------------------*
 * SSD_UpdateDisp_Task()
 * This is the task responsible for operating the seven segments display.
 * A periodic function that is repeated every (n)ms for two displays
 * every display is refreshed every (2*n)ms. Where n represents the refresh 
 * period and can be changed from the config file. Two values are displayed
 * (Temperature Reading / Temperature Setting value). At temperature Setting
 * mode SSDs blinks every (m)s.Where m is the on/off time.
 * 
 * SSD_UpdateDisp_Task Explained:
 *      - state machine with two states 
 *          * 1st state is responsible for getting the value displayed for the right SSD 
 *            and operating according to the operation mode.
 *          * 2nd state is responsible for getting the value displayed for the left SSD 
 *            and operating according to the operation mode and updating the counter as it is the last SSD.
 *      - every state is responsible for the next state transition 
 * This function is called by:
 *                              tasks_creation
 *                              SCH_Dispatch_Tasks
 * This function uses a non-reentrant model
-*------------------------------------------------------------------*/ 
void SSD_UpdateDisp_Task(void)
{  
    static SSD_STATE_ET state = SSD1 ;
    static unsigned char count = 0;
    unsigned char val = 0 , mode;  // the value to display on the 2 SSD 
    mode = get_op_mode();
    val = (mode==TEMP_DISP_MODE)?get_temp():DTemp;    // Decide which value to display 
    switch(state)
    {
        /* State to update the right SSD *************************************/
        
        case SSD1:
            ssd_write_data(val%10);     // get the the right digit of the two digit number and send it to data port
            /* Checking display mode (set temperature mode / current temperature reading) */
            if(mode == TEMP_DISP_MODE)
            {
                /* current temperature reading mode */
                ssd_en(SSD3_MSK);   // enable the third display on the board 
            }
            /* 
             * Checking that the display mode is (set temperature mode) with the blinking count greater than the value 
             * calculated by the task period and desired blinking rate and number of SSDs, so the SSD will turn off.
             *  */
            else if(mode == TEMP_SET_MODE && count > (SSD_BLINK_PERIOD/(SSD_TASK_PERIOD * SSD_NUM)))
            {
                ssd_off();      // turn off SSD
            }
            /* 
             * The display must be in set temperature mode with the blinking count is less than the time given 
             * so the SSD will turn on so that half of the count the SSDs are turned on and the other half they are off.
             */
            else
            {
                ssd_en(SSD3_MSK );  // turn on SSD
            } 
            state = SSD2;     // Move the state to the next SSD
            
            break;
        /*********************************************************************/
            
            
        /* State to update the second SSD ************************************/
            
        case SSD2:
            ssd_write_data(val/10);     // get the the left digit of the two digit number and send it to data port.
            /* Checking display mode */
            if(mode == TEMP_DISP_MODE)
            {
                ssd_en(SSD2_MSK );
            }
            /* Checking display mode and count */
            else if(mode == TEMP_SET_MODE && count > (SSD_BLINK_PERIOD/(SSD_TASK_PERIOD * SSD_NUM)))
            {
                ssd_off();       
                count ++;               // update blinking counter.
            }
            else
            {
                ssd_en(SSD2_MSK );
                count ++;               // update blinking counter.
            }
            state = SSD1;     // Move the state to the next SSD
            /* Check if the counter Exceeded the on/off time interval */
            if (count > (SSD_BLINK_PERIOD/(SSD_TASK_PERIOD)))    
            {
                count = 0;  // Reset the counter
            }
            break;
        /*********************************************************************/
    }
}

/*------------------------------------------------------------------*
 * Temp_Sense_Task()
 * This is the task responsible for sensing the temperature.
 * A periodic function that is repeated every (n)ms, can be changed from
 * configuration file.
 * Temperature is saved at the static global variable "Temp" to be passed
 * to other tasks.
-*------------------------------------------------------------------*/ 
void Temp_Sense_Task(void)
{   
    temp_update();    // Update the Temperature Readings
}

/*------------------------------------------------------------------*
 * Temp_Control_Task()
 * This is the task responsible for controlling the temperature with the
 * (Heater / Cooler) based on the average k temperature reading and the set temperature.
 * A periodic function that is repeated every (n)ms, (n & k) can both be changed from
 * configuration file.
 * 5 degrees celsius error allowed for the temperature.
 * 
 * Temp_Control_Task Explained:
 *      - state machine with four states 
 *          * NO_ENOUGH_READINGS * initial state takes no action until the average 
 *            temperature buffer is full.
 *          * TEMP_CONTROL_OFF * the state after NO_ENOUGH_READINGS state checks the 
 *            current temperature and the retrieved set temperature and decides what
 *            state will go next to reach the set temperature setting the temperature control mode.
 *          * COOLER_ON_STATE * state is responsible of controlling the cool element
 *            and moving to the HEATER_ON_STATE when the temperature exceeds the
 *            allowed error setting the temperature control mode.
 *          * HEATER_ON_STATE * state is responsible of controlling the heat element
 *            and moving to the COOLER_ON_STATE when the temperature exceeds the
 *            allowed error and setting the temperature control mode.
 *      - every state is responsible for the next state transition
-*------------------------------------------------------------------*/ 
void Temp_Control_Task(void)
{
    
    static unsigned short tmp[10] , avg_tmp , cnt = 0;
    static unsigned char ind = 0 ;
    static TEMP_CONT_T temp_cont_mode = NO_ENOUGH_READINGS;
    unsigned short avg_ind = 0;
    
    
    
    /*************************************************************************
     * Checking the previous power mode if this is the first time for the 
     * task to run after power on static variables must return to it's initial 
     * positions 
     *************************************************************************/
    if(get_pwr_mode() == POWER_OFF)
    {
        ind = 0;
        temp_cont_mode = NO_ENOUGH_READINGS;
        set_pwr_mode(POWER_ON);
    }
    /*************************************************************************/
    
    
    
    /* Getting the Average of the Temperature readings ***********************/
    tmp[ind] = get_temp();  // Get current temperature reading
    ind++;                  // Increase the buffer index
    ind%=TEMP_READINGS_AVG; // Reset the buffer if it reaches the end of the buffer
    avg_tmp = 0;            // Clear average readings value
    
        /* Add the buffer values to calculate the average to take a decision based on it */
    for(avg_ind = 0 ; avg_ind < TEMP_READINGS_AVG ; avg_ind++)
    {
        avg_tmp+=tmp[avg_ind];
    }
    avg_tmp /= TEMP_READINGS_AVG;   // Calculate the average of the readings
    /*************************************************************************/
    
    
    /* Check which mode currently working ************************************/
    switch (temp_cont_mode)
    {
        /* Not yet enough readings in the buffer ( initial state ) ***********/
        
        case NO_ENOUGH_READINGS:
            /* Checking if 10 readings in the buffer to start taking decision */
            if(ind < TEMP_READINGS_AVG - 1){
                temp_cont_mode = NO_ENOUGH_READINGS ; }    // Did not reach the 10 temperature readings to make a decision
            else{
                temp_cont_mode = TEMP_CONTROL_OFF;         // Buffer has 10 readings and can make a decision now
            }
            break;
        /*********************************************************************/    
            
            
        /* No temperature control mode ***************************************/
            
        case TEMP_CONTROL_OFF:
            
            /* 
             * Making sure that the retrieved temperature value is in between the
             * maximum and minimum set values and ranges, if not that means there
             * is an error and the temperature must be set to it's initial value
             * 60C.
             */
            if(DTemp > MAX_SET_TEMP || DTemp < MIN_SET_TEMP){
                DTemp = INITIAL_TEMP ; }
            /* 
             * Checking if the current average temperature readings is less or more than
             * the retrieved temperature.
             */
            
            if( avg_tmp < DTemp) {
                temp_cont_mode = HEATER_ON_STATE ; }    // Temperature is less than desired go to heating mode
            else{
                temp_cont_mode = COOLER_ON_STATE ; }    // Temperature is more than desired go to cooling mode
            heatLED_off();       // LED off             // Turn off Heat Element LED as it is not a heat or cool state
            break;
        /*********************************************************************/    
            
            
        /* Cooling mode ******************************************************/
            
        case COOLER_ON_STATE:
            heater_off();                       // Heater off
            cooler_on();                        // Cooler on    
            /* Check if the temperature exceeded the error allowed if so switch to heating */
            if(avg_tmp <= DTemp-TEMP_ERROR_VAL)
            {
                temp_cont_mode = HEATER_ON_STATE;   // Switch to heater mode
            }
            heatLED_on();       // LED on
            break; 
        /*********************************************************************/
            
            
        /* Heating mode ******************************************************/
        case HEATER_ON_STATE:
            cooler_off();                       // Cooler off
            heater_on();                        // Heater on
            cnt+=1;                             // increase cnt with one to control Heat element LED blinking time
            /* Check if the temperature exceeded the error allowed if so switch to cooling */
            if( avg_tmp >= DTemp + TEMP_ERROR_VAL)
            {
                temp_cont_mode = COOLER_ON_STATE;   // Switch to cooler mode
            }
            if(cnt > HEAT_LED_BLINK_TIME / TEMP_CONTROL_TASK_PERIOD)
            {
                cnt = 0;
                heatLED_toggle();
            }
            break;       
        /*********************************************************************/
    }
}

/*------------------------------------------------------------------*
 * SetTemp_Task()
 * This is the task responsible for setting the temperature with a step 
 * of 5 degrees celsius within the range 35 - 75
 * first plus or minus switch press enters the setting temperature mode.
 * Temperature is saved to external EEPROM to be retrieved when the power is disconnected
 * If there was no interaction with the switch for (n)ms setting mode is turned
 * off and the display returns to displaying the temperature.
 * 
 * SetTemp_Task Explained:
 *      - state machine with three states
 *          * SW_DEPRESSED_STATE           when the switch is depressed
 *          * SW_PRESSED_STATE             when the switch is pressed at normal mode
 *          * SW_SET_MODE_PRESSED_STATE    when the switch is pressed at setting temperature mode
 *      - each state is responsible for the state transition
-*------------------------------------------------------------------*/ 
void SetTemp_Task(void)
{
    static SWITCH_STATES_ET sw_state = SW_DEPRESSED_STATE ;
    static unsigned char count = 0 , BTN = NO_SW_NUM;
    unsigned char mode = get_op_mode();
    
    
    /* Checking the temperature mode *****************************************/
    if(get_pwr_mode() == POWER_OFF)
    {
        set_op_mode(TEMP_DISP_MODE);
        sw_state = SW_DEPRESSED_STATE;
        set_pwr_mode(POWER_ON);
    }
    
    
    /* Checking the temperature mode *****************************************/
    
    if(mode == TEMP_SET_MODE)
    {
        count += 1;     // Increase timeout count
        /* Checking the last switch press time */
        if(count > TEMP_SET_TIMEOUT/TEMP_SET_TASK_PERIOD)
        {
            // Time is out exit temperature display mode and go back to setting temperature mode
            set_op_mode(TEMP_DISP_MODE);
            count = 0;                      // Counter is reset for the next press
        }
    }
    /*************************************************************************/
    
    switch(sw_state)
    {
        /* switch is depressed at any mode ***********************************/
        
        case SW_DEPRESSED_STATE:
            /* Checking if either of the plus or minus switches are pressed */
            if(sw_is_pressed(PLUS_SW) == PRESSED || sw_is_pressed(MINUS_SW) == PRESSED)
            {
                /* Checking the operating mode */
                if(mode == TEMP_SET_MODE)
                {
                    /* Operating at setting temperature mode the next state is SW_SET_MODE_PRESSED_STATE */
                    sw_state = SW_SET_MODE_PRESSED_STATE; 
                    /* Check which button of the two is pressed */
                    if(sw_is_pressed(MINUS_SW) == PRESSED)
                    {
                        /* 
                         * Checking the allowed temperature boundaries and saving 
                         * the temperature to the EEPROM .
                         */
                        if(DTemp > MIN_SET_TEMP)  
                        {   DTemp -= TEMP_SET_STEP;
                            e2pext_w( TEMP_SAVE_ADDRESS , DTemp );
                        }
                    }
                    else
                    {
                        /* 
                         * Checking the allowed temperature boundaries and saving 
                         * the temperature to the EEPROM .
                         */
                        if(DTemp < MAX_SET_TEMP)  
                        {
                            DTemp += TEMP_SET_STEP;
                            e2pext_w( TEMP_SAVE_ADDRESS , DTemp );
                        }
                    }
                }
                else
                {
                    /* Operating at normal mode -first plus or minus press- the next state is SW_PRESSED_STATE */
                    sw_state = SW_PRESSED_STATE;
                }
                /* Checking which switch was pressed */
                if(sw_is_pressed(MINUS_SW) == PRESSED)
                {
                    BTN = MINUS_SW_NUM;
                }
                else
                {
                    BTN = PLUS_SW_NUM;
                }
                
            }
            break;
        /*********************************************************************/
            
            
        /* switch is pressed at normal mode **********************************/
        case SW_PRESSED_STATE:
            /* Checking if the switch pressed is the one released */
            if((sw_is_pressed(MINUS_SW) == DEPRESSED && BTN == MINUS_SW_NUM )|| ( sw_is_pressed(PLUS_SW) == DEPRESSED && BTN == PLUS_SW_NUM ))
            {
                /* 
                 * as the switch is released and the operating mode is normal mode
                 * hence this is the first switch application must enter setting temperature mode
                 */
                set_op_mode(TEMP_SET_MODE);
                sw_state = SW_DEPRESSED_STATE;
            }
            count = 0;                      // counter remains 0 while pressing one of the switches
            break;
        /*********************************************************************/
            
            
        /* switch is pressed at setting temperature mode *********************/
        case SW_SET_MODE_PRESSED_STATE:
            /* Check which switch is released at temperature setting mode */
            if(sw_is_pressed(MINUS_SW) == DEPRESSED && BTN == MINUS_SW_NUM)
            {
                sw_state = SW_DEPRESSED_STATE;
            }         
            if(sw_is_pressed(PLUS_SW) == DEPRESSED && BTN == PLUS_SW_NUM)
            {
                sw_state = SW_DEPRESSED_STATE;
            }
            count = 0;                          // counter remains 0 while pressing one of the switches
            break;
        /*********************************************************************/
    }
}

/*------------------------------------------------------------------*
 * pwr_off()
 * This is a one time-call function called to put MCU to sleep.
 * ** note: at sleep mode all MCU ports and pins remain the same before sleeping
 * ** so it should be turned off before going to sleep mode.
-*------------------------------------------------------------------*/
void pwr_off(void)
{
    ssd_off();          // Power off SSDs
    heatLED_off();      // Power off heat element LED
    heater_off();       // Power off heater element
    cooler_off();       // Power off cooler element
    sch_stop();         // Stop scheduler
    set_pwr_mode(POWER_OFF);
    /* 
     * Enable external interrupt as it is disabled while the application
     * is running as the open power on function is called in the external
     * interrupt function implementation.
     */
    ext_int_en();       
    asm("SLEEP");       // Put MCU to sleep mode
}

/*------------------------------------------------------------------*
 * pwr_on()
 * This is a one time-call function called to initialize MCU after being in sleep mode.
-*------------------------------------------------------------------*/
void pwr_on(void)
{
    set_op_mode(TEMP_DISP_MODE);  // Initialize display mode to start at temperature display mode
    ext_int_dis();              // Disable external interrupt to not interfere with power off function
    sch_start();                // Start schedulers as it was stopped at the power off sequence
}

/*------------------------------------------------------------------*
 * BTN_PwrOFF_Task()
 * This is the task responsible for checking the power switch state and calling 
 * the power off sequence.
 * A periodic function that is repeated every (n)ms, n can be changed from
 * configuration file.
 * MCU shuts Down when the switch is pressed then released
 * 
 * BTN_PwrOFF_Task Explained:
 *      - state machine with two states
 *          * SW_DEPRESSED_STATE           when the switch is depressed
 *          * SW_PRESSED_STATE             when the switch is pressed
 *      - each state is responsible for the state transition
-*------------------------------------------------------------------*/ 
void BTN_PwrOFF_Task(void)
{    
    static unsigned char state = 0;
    
    switch(state)
    {
        // Button is depressed
        case SW_DEPRESSED_STATE:
            /*
             * Checking if the button is pressed if so go to SW_Pressed_STATE
             */
            if(sw_is_pressed(PWR_SW) == PRESSED)
            {
                state = SW_PRESSED_STATE;
            }
            break;
        // Button is Pressed
        case SW_PRESSED_STATE:
            /* Wait until the switch is released then switch to SW_DEPRESSED_STATE and power off */
            if(sw_is_pressed(PWR_SW) == DEPRESSED)
            {
                state = SW_DEPRESSED_STATE;
                pwr_off();
            }
            break;
    }     
}



/*------------------------------------------------------------------*
 * MC_init()
 * This is a one time call function at the start to initialize all the hardware
 * used during the application
-*------------------------------------------------------------------*/ 
void MC_init(void)
{
    e2pext_init();                          // Initialize external EEPROM
    sw_init(PLUS_SW);                       // Initialize plus switch
    sw_init(MINUS_SW);                      // Initialize minus switch
    sw_init(PWR_SW);                        // Initialize power on/off switch
    cooler_init();                          // Initialize cooling element
    heater_init();                          // Initialize heating element
    ssd_init(SSD2_MSK);                     // Initialize 2nd seven segment display
    ssd_init(SSD3_MSK);                     // Initialize 3rd seven segment display
    heatLED_init();                         // Initialize heating element LED
    temp_sensor_init(TEMP_SENSOR_CH);       // Initialize temperature sensor
    sch_init();                             // Initialize scheduler
    init_ext_int();                         // Initialize external interrupt   
    DTemp = e2pext_r( TEMP_SAVE_ADDRESS );  // Retrieve saved temperature
}

/*------------------------------------------------------------------*
 * tasks_creation()
 * This is a one time call function at the start to add all the application tasks
 * to the scheduler buffer.
-*------------------------------------------------------------------*/ 
void tasks_creation(void)
{
    SCH_Add_Task( BTN_PwrOFF_Task , PWR_TASK_CREATION_DELAY , PWR_TASK_CREATION_PERIOD);
    SCH_Add_Task( Temp_Sense_Task , TEMP_SENSE_TASK_CREATION_DELAY , TEMP_SENSE_TASK_CREATION_PERIOD);
    SCH_Add_Task( Temp_Control_Task , TEMP_CONTROL_TASK_CREATION_DELAY , TEMP_CONTROL_TASK_CREATION_PERIOD);
    SCH_Add_Task( SSD_UpdateDisp_Task , SSD_TASK_CREATION_DELAY , SSD_TASK_CREATION_PERIOD);
    SCH_Add_Task( SetTemp_Task , TEMP_SET_TASK_CREATION_DELAY , TEMP_SET_TASK_CREATION_PERIOD);  
}

/*------------------------------------------------------------------*
 * set_op_mode(DISP_MOD_T val)
 * This function saves the current operation mode either TEMP_DISP_MODE or TEMP_SET_MODE
 * to a static global variable < OP_mode >
-*------------------------------------------------------------------*/
void set_op_mode(DISP_MOD_T val)
{
    OP_mode = val;
}

/*------------------------------------------------------------------*
 * set_Desired_temperature(unsigned char val)
 * This function saves the Set temperature to a static global variable < DTemp >
-*------------------------------------------------------------------*/
void set_Desired_temperature(unsigned char val)
{
    DTemp = val;
}

/*------------------------------------------------------------------*
 * set_pwr_mode(PWR_MOD_T val)
 * This function saves the current power mode either POWER_OFF or POWER_ON
 * to a static global variable < pwr_mode >
 * note:    this function must be called more than one time to change the power
 *          mode from OFF to ON as more than one function needs resetting some 
 *          of it's values at start
-*------------------------------------------------------------------*/
void set_pwr_mode(PWR_MOD_T val)
{
    static unsigned char cnt = PWR_ON_TASKS_CNT;
    if(val == POWER_ON)
    {
        cnt--;
        if(cnt == 0)
        {
           pwr_mode = val;
           cnt = PWR_ON_TASKS_CNT;
        }
    }
    else
    {
        pwr_mode = val;
    }
}

/*------------------------------------------------------------------*
 * DISP_MOD_T get_op_mode()
 * This function gets the current operating mode
-*------------------------------------------------------------------*/
DISP_MOD_T get_op_mode(void)
{
    return OP_mode;
}

/*------------------------------------------------------------------*
 * unsigned char get_Desired_temperature()
 * This function gets the current set temperature
-*------------------------------------------------------------------*/
unsigned char get_Desired_temperature(void)
{
    return DTemp;
}

/*------------------------------------------------------------------*
 * PWR_MOD_T get_pwr_mode()
 * This function gets the current power mode
-*------------------------------------------------------------------*/
PWR_MOD_T get_pwr_mode(void)
{
    return pwr_mode;
}

/*------------------------------------------------------------------*
 * inc_DTemp(unsigned char increase_val)
 * This function increases the set temperature by a given value
-*------------------------------------------------------------------*/
void inc_DTemp(unsigned char increase_val)
{
    DTemp += increase_val;
}

/*------------------------------------------------------------------*
 * dec_DTemp(unsigned char decrease_val)
 * This function decreases the set temperature by a given value
-*------------------------------------------------------------------*/
void dec_DTemp(unsigned char decrease_val)
{
    DTemp -= decrease_val;
}
/*** End of File **************************************************************/

