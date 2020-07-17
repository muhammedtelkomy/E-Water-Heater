/****************************************************************************
* Title                 :   SSD
* Filename              :   ssd.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file ssd.h
 * \brief This module contains definitions for a seven-segment display.
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "ssd.h"
#include "port.h"
/******************************************************************************
* Constants
*******************************************************************************/
/* const char table[16] is an array of 16 elements for LED representation for every digit on the SSD in hexadecimal */
static const char table[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x58,0x5E,0x79,0x71};

/******************************************************************************
* Functions
*******************************************************************************/
/*------------------------------------------------------------------*
 * ssd_init(unsigned char SSD_MSK)
 * Initializes SSD_MSK of the SSD on the board
-*------------------------------------------------------------------*/ 
void ssd_init(unsigned char SSD_MSK)
{
    TRISA &= ~SSD_MSK;          // initialize SSD enable pin as an output
    TRISD &= ~0xFF;             // initialize data port as output
    SSD_DATA_PORT &= ~0xFF;     // clear data port
    
}

/*------------------------------------------------------------------*
 * ssd_write_data()
 * Writes the value sent to SSD data port which is port d
-*------------------------------------------------------------------*/ 
void ssd_write_data(unsigned char value)
{
    SSD_DATA_PORT = table[ value ];
}

/*------------------------------------------------------------------*
 * ssd_en()
 * Enables specific SSD_MSK SSD
-*------------------------------------------------------------------*/ 
void ssd_en(unsigned char SSD_MSK)
{
    SSD_EN_PORT &= ~SSD_ALL_MSK;
    SSD_EN_PORT |= SSD_MSK;
}

/*------------------------------------------------------------------*
 * ssd_off()
 * Disables all enabled SSDs and Clears the data port "d"
-*------------------------------------------------------------------*/ 
void ssd_off(void)
{
    SSD_EN_PORT &= ~SSD_ALL_MSK;
    SSD_DATA_PORT &= ~0xFF;
}
/*** End of File **************************************************************/
