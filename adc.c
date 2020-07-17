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
/******************************************************************************
* Includes
*******************************************************************************/
#include <xc.h>
#include "adc.h"

/******************************************************************************
* Functions
*******************************************************************************/

/*------------------------------------------------------------------*
adc_init()
Initializes the ADC peripheral
-*------------------------------------------------------------------*/
void adc_init(void)
{
  ADCON1=0x06;
  ADCON1=0x02;
  ADCON0=0x41;  
}

/*------------------------------------------------------------------*
sch_init()
 * Gets the (canal) ADC channel reading
-*------------------------------------------------------------------*/
unsigned int adc_get(unsigned char canal)
{  
     switch(canal)
    {
      case 0:
        ADCON0=0x01;
        break;
      case 1:
        ADCON0=0x09;
        break;
      case 2:
        ADCON0=0x11;
        break;
      case 3:
        ADCON0=0x11;
        break;
      case 4:
        ADCON0=0x11;
        break;
      case 5:
        ADCON0=0x11;
        break;
    }   
     
    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}

/*------------------------------------------------------------------*
ADCON()
 * ADC Starting the conversion
-*------------------------------------------------------------------*/
void ADCON (void)
{
    ADCON0 |= 0x01;
}
/*** End of File **************************************************************/
