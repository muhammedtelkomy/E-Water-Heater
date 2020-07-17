/****************************************************************************
* Title                 :   Interrupt
* Filename              :   int.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   int.c
 *  \brief  This file contains the interrupt control functions and the ISR
 *          function Implementation.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <xc.h>
#include "int.h"
#include "sch.h"
#include "ext_int.h"
#include "EW_Heater.h"

/******************************************************************************
* Variables
*******************************************************************************/
extern sTask SCH_tasks_G[SCH_MAX_TASKS];        // related to scheduler ISR implementation
extern unsigned char Error_code_G;              // related to scheduler ISRimplementation

/*------------------------------------------------------------------*
 * Enable_Global_INT()
 * Enables the global interrupt
-*------------------------------------------------------------------*/ 
void Enable_Global_INT(void)
{
    GIE = 1;
}

/*------------------------------------------------------------------*
 * Enable_Peripheral_INT()
 * Enables the peripheral interrupt
-*------------------------------------------------------------------*/ 
void Enable_Peripheral_INT(void)
{
    PEIE = 1;
}

/*------------------------------------------------------------------*
 * Disable_Global_INT()
 * Disables the global interrupt
-*------------------------------------------------------------------*/
void Disable_Global_INT(void)
{
    GIE = 0;
}

/*------------------------------------------------------------------*
 * Disable_Peripheral_INT()
 * Disable the peripheral interrupt
-*------------------------------------------------------------------*/
void Disable_Perephiral_INT(void)
{
    PEIE = 1;
}

/*------------------------------------------------------------------*
 * __interrupt() ISR()()
 * ISR function implementation
-*------------------------------------------------------------------*/
void __interrupt() ISR()
{   PORTE |= 0x01;
    /*------------------------------------------------------------------*
     * This is the scheduler ISR. It is called at a rate determined by the timer settings in the 'init' function.
     * This version is triggered by Timer 2 interrupts: timer is automatically reloaded.
    -*------------------------------------------------------------------*/ 
    if(TMR0IF==1)
    {
        TMR0 = 100;
        TMR0IF = 0;
        unsigned char Index;
        for (Index = 0; Index < SCH_MAX_TASKS ; Index++) 
        {
        // Check if there is a task at this location 
            if (SCH_tasks_G[Index].pTask) { 
                if (SCH_tasks_G[Index].Delay == 0) 
                { 
                    // The task is due to run 
                    SCH_tasks_G[Index].RunMe += 1; // Inc. the 'RunMe' flag
                        if (SCH_tasks_G[Index].Period) 
                        { 
                            // Schedule periodic tasks to run again 
                            SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period; 
                        } 
                } 
                else { 
                    // Not yet ready to run: just decrement the delay 
                    SCH_tasks_G[Index].Delay -= 1; 
                } 
            } 
        }
    }
    /*------------------------------------------------------------------*
     * This is the external interrupt ISR. It is called when the device in sleep mode
     * at the rising edge if the switch.
    -*------------------------------------------------------------------*/ 
    if (INTF==1)            //External Interrupt detected
    {
        clear_int_flag();   // Clear external interrupt flag
        ext_int_dis();      // disable External Interrupt
        pwr_on();           // Start power on sequence
    }
    PORTE &= ~0x01;
}
/*** End of File **************************************************************/