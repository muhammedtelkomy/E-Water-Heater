/****************************************************************************
* Title                 :   Heating Element LED
* Filename              :   heatLED.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   heatLED.c
 *  \brief  This file contains the control functions for the heat element LED.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "port.h"
#include "heatLED.h"

/******************************************************************************
* Functions
*******************************************************************************/
/*------------------------------------------------------------------*
 * heatLED_init()
 * This function initializes the heat element LED hardware.
-*------------------------------------------------------------------*/ 
void heatLED_init(void)
{
    
    HEAT_LED_IO_REG &= ~HEAT_LED_MSK;
    HEAT_LED_PORT &= ~HEAT_LED_MSK;
}

/*------------------------------------------------------------------*
 * heatLED_on()
 * This function Checks whether the heat element LED is turned on or not if not it turns it on.
-*------------------------------------------------------------------*/
void heatLED_on(void)
{
    if((HEAT_LED_PORT&HEAT_LED_MSK) == 0)
    {
        HEAT_LED_PORT |= HEAT_LED_MSK;
    }
}

/*------------------------------------------------------------------*
 * heatLED_off()
 * This function Checks whether the heat element LED is turned off or not if not it turns it off.
-*------------------------------------------------------------------*/
void heatLED_off(void)
{
    if((HEAT_LED_PORT&HEAT_LED_MSK) != 0)
    {
        HEAT_LED_PORT &= ~HEAT_LED_MSK;
    }
}

/*------------------------------------------------------------------*
 * heatLED_toggle()
 * This function toggles the heat element LED state when called
-*------------------------------------------------------------------*/
void heatLED_toggle(void)
{
    HEAT_LED_PORT ^= HEAT_LED_MSK;
}
/*** End of File **************************************************************/