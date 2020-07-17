/****************************************************************************
* Title                 :   Electric Heater
* Filename              :   EW_Heater.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   Functions of This file can be configured from config_EW_Heater.h
*******************************************************************************/
/** \file   EW_Heater.h
 *  \brief  This file contains all the heater application functions and tasks.
 */

#ifndef __EW_HEATER_H__
#define __EW_HEATER_H__

/******************************************************************************
* Includes
*******************************************************************************/
#include "config_EW_Heater.h"
#include "sch.h"

/******************************************************************************
* Constants
* note: Task Creation Period and Delay differs from the task period and delay
*       Task Creation Period and Delay depends on the system tick and the actual
*       task delay and period
*******************************************************************************/
#define PWR_TASK_CREATION_PERIOD                PWR_TASK_PERIOD/SCH_TICK
#define PWR_TASK_CREATION_DELAY                 PWR_TASK_DELAY/SCH_TICK
#define TEMP_SENSE_TASK_CREATION_PERIOD         TEMP_SENSE_TASK_PERIOD/SCH_TICK
#define TEMP_SENSE_TASK_CREATION_DELAY          TEMP_SENSE_TASK_DELAY/SCH_TICK
#define TEMP_CONTROL_TASK_CREATION_PERIOD       TEMP_CONTROL_TASK_PERIOD/SCH_TICK
#define TEMP_CONTROL_TASK_CREATION_DELAY        TEMP_CONTROL_TASK_DELAY/SCH_TICK
#define SSD_TASK_CREATION_PERIOD                SSD_TASK_PERIOD/SCH_TICK
#define SSD_TASK_CREATION_DELAY                 SSD_TASK_DELAY/SCH_TICK
#define TEMP_SET_TASK_CREATION_PERIOD           TEMP_SET_TASK_PERIOD/SCH_TICK
#define TEMP_SET_TASK_CREATION_DELAY            TEMP_SET_TASK_DELAY/SCH_TICK

/*****************************************************************************
 *
 *  Seven Segments Display states
 *
 *****************************************************************************/
typedef enum{
    SSD1 = 1 ,SSD2 , SSD_Blinking
}SSD_STATE_ET;

typedef enum{
    TEMP_DISP_MODE,TEMP_SET_MODE
}DISP_MOD_T;
/*****************************************************************************/
/*****************************************************************************
 *
 *  Temperature states
 *
 *****************************************************************************/
typedef enum{
    NO_ENOUGH_READINGS  ,
    TEMP_CONTROL_OFF    ,
    COOLER_ON_STATE     ,
    HEATER_ON_STATE
}TEMP_CONT_T;
/*****************************************************************************/

/*****************************************************************************
 *
 *  Switch states
 *
 *****************************************************************************/
typedef enum{
    SW_DEPRESSED_STATE  ,
    SW_PRESSED_STATE    ,
    SW_SET_MODE_PRESSED_STATE
}SWITCH_STATES_ET;
/*****************************************************************************/

/*****************************************************************************
 *
 *  Power modes
 *
 *****************************************************************************/
typedef enum{
    POWER_OFF,POWER_ON
}PWR_MOD_T;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * SSD_UpdateDisp_Task()
 * 
 * @brief This is the task responsible for operating the seven segments display.
 *        A periodic function that is repeated every (n)ms for two displays
 *        every display is refreshed every (2*n)ms. Where n represents the refresh 
 *        period and can be changed from the config file. Two values are displayed
 *        (Temperature Reading / Temperature Setting value). At temperature Setting
 *        mode SSDs blinks every (m)s.Where m is the on/off time.
 *
 * @param <void> a periodic task called by the dispatcher that takes no arguments
 * @return <void>
 */
void SSD_UpdateDisp_Task(void);

/**
 * Temp_Sense_Task()
 * @brief This is the task responsible for sensing the temperature.
 *        A periodic function that is repeated every (n)ms, can be changed from
 *        configuration file.
 *        Temperature is saved at the static global variable "Temp" to be passed
 *        to other tasks.
 *
 * @param <void> a periodic task called by the dispatcher that takes no arguments
 * @return <void>
 */
void Temp_Sense_Task(void);

/**
 * Temp_Control_Task()
 * 
 * @brief This is the task responsible for controlling the temperature with the
 *        (Heater / Cooler) based on the average k temperature reading and the set temperature.
 *        A periodic function that is repeated every (n)ms, (n & k) can both be changed from
 *        configuration file.
 *        5 degrees celsius error allowed for the temperature.
 *
 * @param <void> a periodic task called by the dispatcher that takes no arguments
 * @return <void>
 */
void Temp_Control_Task(void);

/**
 * SetTemp_Task()
 * 
 * @brief This is the task responsible for setting the temperature with a step 
 *        of 5 degrees celsius within the range 35 - 75
 *        first plus or minus switch press enters the setting temperature mode.
 *        Temperature is saved to external EEPROM to be retrieved when the power is disconnected
 *        If there was no interaction with the switch for (n)ms setting mode is turned
 *        off and the display returns to displaying the temperature.
 *
 * @param <void> a periodic task called by the dispatcher that takes no arguments
 * @return <void>
 */
void SetTemp_Task(void);

/**
 * BTN_PwrOFF_Task()
 * 
 * @brief This is the task responsible for checking the power switch state and calling 
 *        the power off sequence.
 *        A periodic function that is repeated every (n)ms, n can be changed from
 *        configuration file.
 *        MCU shuts Down when the switch is pressed then released
 *
 * @param <void> a periodic task called by the dispatcher that takes no arguments
 * @return <void>
 */
void BTN_PwrOFF_Task(void);

/**
 * MC_init()
 * 
 * @brief This is a one time call function at the start to initialize all the
 * hardware used during the application.
 *
 * @param <void> an initialization task takes no arguments
 * @return <void>
 */
void MC_init(void);

/**
 * tasks_creation()
 * 
 * @brief This is a one time call function at the start to add all the application tasks
 *        to the scheduler buffer.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void tasks_creation(void);

/**
 * pwr_off()
 * 
 * @brief This is a one time-call function called to put MCU to sleep.
 *        ** note: at sleep mode all MCU ports and pins remain the same before sleeping
 *        ** so it should be turned off before going to sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void pwr_off(void);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void pwr_on(void);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void set_Desired_temperature(unsigned char val);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void inc_DTemp(unsigned char increase_val);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void dec_DTemp(unsigned char decrease_val);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
unsigned char get_Desired_temperature(void);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void set_pwr_mode(PWR_MOD_T val);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
PWR_MOD_T get_pwr_mode(void);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void set_op_mode(DISP_MOD_T val);

/**
 * pwr_on()
 * 
 * @brief This is a one time-call function called to initialize MCU after being in sleep mode.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
DISP_MOD_T get_op_mode(void);
#endif
/*** End of File **************************************************************/