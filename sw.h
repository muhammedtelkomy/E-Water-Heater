/****************************************************************************
* Title                 :   Switch
* Filename              :   sw.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   sw.h
 *  \brief  This file contains the control function definition for switches.
 */

#ifndef __SW_H__
#define __SW_H__

/******************************************************************************
* Constants
*******************************************************************************/
#define PRESSED     1
#define DEPRESSED   0

/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * @brief Initializes a selected switch
 *
 * @param <sw_msk> a mask for the initialized switches pins
 *
 * @return <void>
 */
void sw_init(unsigned char sw_msk);

/**
 * @brief checks a switch condition ( pressed / released )
 *
 * @param <sw> a mask for the switch pin
 *
 * @return <unsigned char (PRESSED / DEPRESSED)>
 */
unsigned char sw_is_pressed(unsigned char sw);

#endif
/*** End of File **************************************************************/