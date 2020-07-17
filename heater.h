/****************************************************************************
* Title                 :   Heating Element
* Filename              :   heater.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   heater.h
 *  \brief  This file contains the control functions for the heater element.
 */

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifndef __HEATER_H__
#define __HEATER_H__

/**
 * heater_init()
 * 
 * @brief This function initializes the heating element hardware.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heater_init(void);

/**
 * heater_on()
 * 
 * @brief This function Checks whether the heater is turned on or not if not it turns it on.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heater_on(void);

/**
 * heater_off()
 * 
 * @brief This function Checks whether the heater is turned off or not if not it turns it off.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heater_off(void);

#endif
/*** End of File **************************************************************/