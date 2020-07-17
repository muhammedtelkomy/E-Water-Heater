/****************************************************************************
* Title                 :   Electric Heater Port
* Filename              :   port.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   any change of the hardware components should be changed here accordingly.
*******************************************************************************/
/** \file   port.h
 *  \brief  This file contains all the port configurations for the electric heater app.
 */

#ifndef __PORT_H__
#define __PORT_H__

/******************************************************************************
* Includes
*******************************************************************************/
#include <xc.h>

/******************************************************************************
* Constants
*******************************************************************************/
/*****************************************************************************
 *
 *  External Interrupt
 *
 *****************************************************************************/
#define EXT_INT_IO_REG     TRISB
#define EXT_INT_PORT       PORTB
#define EXT_INT_PIN_MSK    0x01

/*****************************************************************************
 *
 *  Seven Segments Display
 *
 *****************************************************************************/
#define SSD_DATA_IO_REG TRISD
#define SSD_EN_IO_REG   TRISA
#define SSD_DATA_PORT   PORTD
#define SSD_EN_PORT     PORTA

#define SSD1_MSK        0x04
#define SSD2_MSK        0x08
#define SSD3_MSK        0x10
#define SSD4_MSK        0x20
#define SSD_ALL_MSK     0x3C
/*****************************************************************************/

/*****************************************************************************
 *
 *  Heat LED
 *
 *****************************************************************************/
#define HEAT_LED_IO_REG TRISB
#define HEAT_LED_PORT   PORTB
#define HEAT_LED_MSK    0x80
/*****************************************************************************/

/*****************************************************************************
 *
 *  Heater
 *
 *****************************************************************************/
#define HEATER_IO_REG TRISC
#define HEATER_PORT   PORTC
#define HEATER_MSK    0x20
/*****************************************************************************/

/*****************************************************************************
 *
 *  Cooler
 *
 *****************************************************************************/
#define COOLER_IO_REG TRISC
#define COOLER_PORT   PORTC
#define COOLER_MSK    0x04
/*****************************************************************************/

/*****************************************************************************
 *
 *  Push Buttons
 *
 *****************************************************************************/
#define SW_IO_REG     TRISB
#define SW_PORT       PORTB
#define SW0_MSK       0x01
#define SW1_MSK       0x02
#define SW2_MSK       0x04
#define SW3_MSK       0x08
#define SW4_MSK       0x10
#define SW5_MSK       0x21
#define SW6_MSK       0x40
#define SW7_MSK       0x80
#define PULLUP        nRBPU

/*****************************************************************************/
#endif
/*** End of File **************************************************************/