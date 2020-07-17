/****************************************************************************
* Title                 :   Switch
* Filename              :   sw.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   sw.c
 *  \brief  This file contains the control functions for switches.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "sw.h"
#include "port.h"

/******************************************************************************
* Functions
*******************************************************************************/
/* Here we assume all the switches are on the same port */
/*------------------------------------------------------------------*
 * sw_init()
 * This function initializes the selected pin to work as a switch internally pulled up.
-*------------------------------------------------------------------*/
void sw_init(unsigned char sw_msk)
{
    SW_IO_REG |= sw_msk;
    PULLUP = 0; //Pull up pin is active low so it must be cleared
}

/*------------------------------------------------------------------*
 * sw_is_pressed(unsigned char sw)
 * This function checks a passed switch state (PRESSED / DEPRESSED) and returns 
 * the state.
-*------------------------------------------------------------------*/
unsigned char sw_is_pressed(unsigned char sw)
{
    if( sw == 0 )
    {
        return PRESSED;
    }
    else
    {
        return DEPRESSED;
    }
}
/*** End of File **************************************************************/