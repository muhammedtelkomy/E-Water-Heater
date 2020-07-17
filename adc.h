/****************************************************************************
* Title                 :   ADC
* Filename              :   adc.c
* Author                :   Luis Claudio Gambôa Lopes
* Origin Date           :   2011
*
* Notes                 :   None
*******************************************************************************/
/** \file   adc.c
 *  \brief  This file contains all the adc periphral functions.
 */

#ifndef __ADC_H__
#define __ADC_H__
/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * sch_init()
 * 
 * @brief Initializes the ADC peripheral
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void adc_init(void);

/**
 * sch_init()
 * 
 * @brief Gets the (canal) ADC channel reading
 *
 * @param <unsigned char canal> ADC Channel
 * @return <unsigned int> the ADC conversion value
 */
unsigned int adc_get(unsigned char canal);

#endif
/*** End of File **************************************************************/