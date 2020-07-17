/****************************************************************************
* Title                 :   Cooler
* Filename              :   cooler.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   cooler.c
 *  \brief  This file contains the control functions for the cooler element.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "port.h"
#include "cooler.h"

/*------------------------------------------------------------------*
 * cooler_init()
 * This function initializes the cooling element hardware.
-*------------------------------------------------------------------*/ 
void cooler_init(void)
{
    COOLER_IO_REG &= ~COOLER_MSK;
    COOLER_PORT &= ~COOLER_MSK;
}

/*------------------------------------------------------------------*
 * cooler_on()
 * This function Checks whether the cooler is turned on or not if not it turns it on.
-*------------------------------------------------------------------*/ 
void cooler_on(void)
{
    if((COOLER_PORT&COOLER_MSK) == 0)
    {
        COOLER_PORT |= COOLER_MSK;
    }
}

/*------------------------------------------------------------------*
 * cooler_off()
 * This function Checks whether the cooler is turned off or not if not it turns it off.
-*------------------------------------------------------------------*/
void cooler_off(void)
{
    if((COOLER_PORT&COOLER_MSK) != 0)
    {
        COOLER_PORT &= ~COOLER_MSK;
    }
}
/*** End of File **************************************************************/