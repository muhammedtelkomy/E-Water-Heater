/****************************************************************************
* Title                 :   External EEPROM
* Filename              :   eeprom_ext.h
* Author                :   Luis Claudio Gambôa Lopes
* Origin Date           :   2011
*
* Notes                 :   None
*******************************************************************************/
/** \file   EW_Heater.h
 *  \brief  This file contains all the external EEPROM control functions.
 */
#ifndef __EEPROM_EXT_H__
#define __EEPROM_EXT_H__
/******************************************************************************
* Includes
*******************************************************************************/
#include <xc.h>

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
 * e2pext_init()
 * 
 * @brief This function initializes the external eeprom needed hardware.
 *
 * @param <void> none
 * @return <void>
 */
void e2pext_init(void);

/**
 * unsigned char e2pext_r(unsigned int addr);
 * 
 * @brief This function reads the data from the address(addr).
 *
 * @param <unsigned int addr> the eeprom address in which the data is saved.
 * @return <unsigned char>
 */
unsigned char e2pext_r(unsigned int addr);

/**
 * e2pext_w(unsigned int addr, unsigned char val);
 * 
 * @brief This function writes data(val) to address(addr).
 *
 * @param <unsigned int addr> the eeprom address in which the data will be saved in.
 * @param <unsigned char val> the data needed to be saved.
 * @return <void>
 */
void e2pext_w(unsigned int addr, unsigned char val);

#endif
/*** End of File **************************************************************/