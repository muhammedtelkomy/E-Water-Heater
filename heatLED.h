/****************************************************************************
* Title                 :   Electric Heater
* Filename              :   heatLED.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   heatLED.h
 *  \brief  This file contains the control functions for the heat element LED.
 */

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifndef __HEATLED_H__
#define __HEATLED_H__

/**
 * heatLED_init()
 * 
 * @brief This function initializes the heat element LED hardware.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heatLED_init(void);

/**
 * heatLED_on()
 * 
 * @brief This function Checks whether the heat element LED is turned on or not if not it turns it on.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heatLED_on(void);

/**
 * heatLED_off()
 * 
 * @brief This function Checks whether the heat element LED is turned off or not if not it turns it off.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heatLED_off(void);

/**
 * heatLED_toggle()
 * 
 * @brief This function toggles the heat element LED state when called
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void heatLED_toggle(void);

#endif
/*** End of File **************************************************************/