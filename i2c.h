/****************************************************************************
* Title                 :   I2C
* Filename              :   i2c.h
* Author                :   Luis Claudio Gambôa Lopes
* Origin Date           :   2011
*
* Notes                 :   None
*******************************************************************************/
/** \file   I2C
 *  \brief  This file contains all the i2c peripheral control functions.
 */
#ifndef __I2C_H__
#define __I2C_H__
/******************************************************************************
* Includes
*******************************************************************************/
#include<xc.h>


/******************************************************************************
* Constants
*******************************************************************************/
#define ICLK PORTCbits.RC3
#define IDAT PORTCbits.RC4
#define TIDAT TRISCbits.TRISC4

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * i2c_init()
 * 
 * @brief This function initializes the i2c peripheral registers.
 *
 * @param <void>
 * @return <void>
 */
void i2c_init(void);

/**
 * i2c_start()
 * 
 * @brief This sends a start for starting the communication on the i2c bus.
 *
 * @param <void>
 * @return <void>
 */
void i2c_start(void);

/**
 * i2c_stop()
 * 
 * @brief This sends a stop for stopping the communication on the i2c bus.
 *
 * @param <void>
 * @return <void>
 */
void i2c_stop(void);

/**
 * i2c_wb(unsigned char val)
 * 
 * @brief This function writes data to the i2c connected device.
 *
 * @param <void>
 * @return <void>
 */
void i2c_wb(unsigned char val);

/**
 * unsigned char i2c_rb(unsigned char ack
 * 
 * @brief This function reads data from the i2c connected device.
 *
 * @param <void>
 * @return <void>
 */
unsigned char i2c_rb(unsigned char ack);

/**
 * delay()
 * 
 * @brief This function implements around one micro second delay.
 *
 * @param <void>
 * @return <void>
 */
void delay(void);

#endif
/*** End of File **************************************************************/