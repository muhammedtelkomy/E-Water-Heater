/****************************************************************************
* Title                 :   External EEPROM
* Filename              :   eeprom_ext.c
* Author                :   Luis Claudio Gambôa Lopes
* Origin Date           :   2011
*
* Notes                 :   None
*******************************************************************************/
/** \file   EW_Heater.c
 *  \brief  This file contains all the external EEPROM control functions.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "i2c.h"
#include"eeprom_ext.h"

/******************************************************************************
* Functions
*******************************************************************************/
/*------------------------------------------------------------------*
 * e2pext_init()
 * This function initializes the external eeprom needed hardware.
-*------------------------------------------------------------------*/
void e2pext_init(void)
{
    TRISC &= ~0x08;
    i2c_init();
}

/*------------------------------------------------------------------*
 * unsigned char e2pext_r(unsigned int addr)
 * This function reads the data from the address(addr).
-*------------------------------------------------------------------*/
unsigned char e2pext_r(unsigned int addr)
{
  unsigned char ret;
  unsigned char ah;
  unsigned char al;

  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;
  i2c_start();	
  if(ah)
  {
    i2c_wb(0xA2);
  }
  else
  {
    i2c_wb(0xA0);
  }
  i2c_wb(al);

  i2c_start();
  if(ah)
  {
    i2c_wb(0xA3);
  }
  else
  {
    i2c_wb(0xA1);
  }
  ret=i2c_rb(1);
  i2c_stop();

  return ret;	
}

/*------------------------------------------------------------------*
 * e2pext_w(unsigned int addr, unsigned char val)
 * This function writes data(val) to address(addr).
-*------------------------------------------------------------------*/
void e2pext_w(unsigned int addr, unsigned char val)
{
  unsigned int tmp;
  unsigned char ah;
  unsigned char al;
  unsigned char nt;

  tmp=val;
  ah=(addr&0x0100)>>8;
  al=addr&0x00FF;
  nt=0;

  do
  {
    i2c_start();
    if(ah)
    { 
      i2c_wb(0xA2);
    }
    else
    {
      i2c_wb(0xA0);
    }
    i2c_wb(al);
    i2c_wb(tmp);
    i2c_stop();

    nt++;
  }
  while((tmp != e2pext_r(addr))&&(nt < 10));
}
/*** End of File **************************************************************/