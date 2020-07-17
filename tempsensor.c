/****************************************************************************
* Title                 :   Temperature Sensor
* Filename              :   tempsensor.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   tempsensor.c
 *  \brief  This file contains the temperature sensor controls.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "tempsensor.h"
#include "adc.h"

/******************************************************************************
* Variables
*******************************************************************************/
static unsigned short Temp = 0;
static unsigned char ADC_CH = 0;

/******************************************************************************
* Functions
*******************************************************************************/
/*------------------------------------------------------------------*
 * temp_sensor_init()
 * This function initializes the temperature sensor pin as an ADC pin
 * by initializing the ADC peripheral and setting the channel for the sensor.
-*------------------------------------------------------------------*/
void temp_sensor_init( unsigned char ADCcanal )
{
    adc_init();
    ADC_CH = ADCcanal;
}

/*------------------------------------------------------------------*
 * temp_update()
 * This function updates the global variable (Temp) with the current sensor
 * reading after calculating the temp in celsius from the equation (((ADC return value)*100)/204).
-*------------------------------------------------------------------*/
void temp_update(void)
{
    Temp = ((adc_get(ADC_CH)*100)/204);
}
/*------------------------------------------------------------------*
 * get_temp()
 * This function gets the last temperature reading.
-*------------------------------------------------------------------*/
unsigned short get_temp(void)
{
    return Temp;
}
/*** End of File **************************************************************/