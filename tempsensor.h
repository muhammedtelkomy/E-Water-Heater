/****************************************************************************
* Title                 :   Temperature Sensor
* Filename              :   tempsensor.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   tempsensor.h
 *  \brief  This file contains the temperature sensor controls.
 */

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifndef __TEMPSENSOR_H__
#define __TEMPSENSOR_H__

/**
 * temp_sensor_init()
 * 
 * @brief This function initializes the temperature sensor pin as an ADC pin
 *        by initializing the ADC peripheral and setting the channel for the sensor.
 *
 * @param <ADCcanal> takes no arguments
 * @return <void>
 */
void temp_sensor_init( unsigned char ADCcanal );

/**
 * temp_update()
 * 
 * @brief This function updates the global variable (Temp) with the current sensor
 *        reading after calculating the temp in celsius from the equation
 *        (((ADC return value)*100)/204).
 *
 * @param <void> 
 * @return <void>
 */
void temp_update(void);

/**
 * get_temp()
 * 
 * @brief This function gets the last temperature reading.
 *
 * @param <void> takes no arguments
 * @return <unsigned short>
 */
unsigned short get_temp(void);
#endif
/*** End of File **************************************************************/