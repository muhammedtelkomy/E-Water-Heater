/****************************************************************************
* Title                 :   I2C
* Filename              :   i2c.c
* Author                :   Luis Claudio Gambôa Lopes
* Origin Date           :   2011
*
* Notes                 :   None
*******************************************************************************/
/** \file   i2c.c
 *  \brief  This file contains all the i2c peripheral control functions.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "i2c.h"
 
/*------------------------------------------------------------------*
 * delay()
 * This function implements a one micro second delay.
-*------------------------------------------------------------------*/
void delay(void)
{
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
    asm("NOP");
}

/*------------------------------------------------------------------*
 * i2c_init()
 * This function initializes the i2c peripheral registers
-*------------------------------------------------------------------*/
void i2c_init(void)
{
  TIDAT=0;
  ICLK=1;
  IDAT=1;
}

/*------------------------------------------------------------------*
 * i2c_start()
 * This sends a start for starting the communication on the i2c bus.
-*------------------------------------------------------------------*/
void i2c_start(void)
{
  ICLK=1;
  IDAT=1;
  delay();
  IDAT=0;
  delay();
}

/*------------------------------------------------------------------*
 * i2c_stop()
 * This sends a stop for stopping the communication on the i2c bus.
-*------------------------------------------------------------------*/
void i2c_stop(void)
{
  ICLK=1;
  IDAT=0;
  delay();
  IDAT=1;
  delay();
}

/*------------------------------------------------------------------*
 * i2c_wb(unsigned char val)
 * This function writes data to the i2c connected device.
-*------------------------------------------------------------------*/
void i2c_wb(unsigned char val)
{
  unsigned char i;
  ICLK=0;
  for(i=0;i<8;i++)
  {
    IDAT=((val>>(7-i))& 0x01);
    ICLK=1;
    delay();
    ICLK=0;
  }	
  IDAT=1;
  delay();
  ICLK=1;
  delay();
  ICLK=0;
}

/*------------------------------------------------------------------*
 * unsigned char i2c_rb(unsigned char ack)
 * This function reads data from the i2c connected device.
-*------------------------------------------------------------------*/
unsigned char i2c_rb(unsigned char ack)
{
  char i;
  unsigned char ret=0;

  ICLK=0;
  TIDAT=1;
  IDAT=1;
  for(i=0;i<8;i++)
  {
    ICLK=1;
    delay();
    ret|=(IDAT<<(7-i));
    ICLK=0;
  }
  TIDAT=0;
  if(ack)
    IDAT=0;
  else
	IDAT=1;
  delay();
  ICLK=1;
  delay();
  ICLK=0;

  return ret;
}
/*** End of File **************************************************************/