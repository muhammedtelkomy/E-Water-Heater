/****************************************************************************
* Title                 :   Heating Element
* Filename              :   heater.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   heater.c
 *  \brief  This file contains the control functions for the heater element.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "port.h"
#include "heater.h"

/******************************************************************************
* Functions
*******************************************************************************/
/*------------------------------------------------------------------*
 * heater_init()
 * This function initializes the heating element hardware.
-*------------------------------------------------------------------*/ 
void heater_init(void)
{
    HEATER_IO_REG &= ~HEATER_MSK;
    HEATER_PORT &= ~HEATER_MSK;
}

/*------------------------------------------------------------------*
 * heater_on()
 * This function Checks whether the heater is turned on or not if not it turns it on.
-*------------------------------------------------------------------*/ 
void heater_on(void)
{
    if((HEATER_PORT&HEATER_MSK) == 0)
    {
        HEATER_PORT |= HEATER_MSK;
    }
}

/*------------------------------------------------------------------*
 * heater_off()
 * This function Checks whether the heater is turned off or not if not it turns it off.
-*------------------------------------------------------------------*/ 
void heater_off(void)
{
    if((HEATER_PORT&HEATER_MSK) != 0)
    {
        HEATER_PORT &= ~HEATER_MSK;
    }
}
/*** End of File **************************************************************/