/****************************************************************************
* Title                 :   Cooler
* Filename              :   cooler.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   cooler.h
 *  \brief  This file contains the control functions for the cooler element.
 */

#ifndef __COOLER_H__
#define __COOLER_H__
/******************************************************************************
* Functions
*******************************************************************************/
/**
 * cooler_init()
 * 
 * @brief This function initializes the cooling element hardware.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void cooler_init(void);

/**
 * cooler_on()
 * 
 * @brief This function Checks whether the cooler is turned on or not if not it turns it on.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void cooler_on(void);

/**
 * cooler_off()
 * 
 * @brief This function Checks whether the cooler is turned off or not if not it turns it off.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void cooler_off(void);

#endif
/*** End of File **************************************************************/