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
* Function Prototypes
*******************************************************************************/
#ifndef __SSD_H__
#define __SSD_H__
/**
 * ssd_init()
 * 
 * @brief Initializes SSD_MSK of the SSD on the board
 *
 * @param <SSD_MSK> a mask for the SSD to initialize
 * @return <void>
 */
void ssd_init(unsigned char SSD_MSK);

/**
 * ssd_write_data()
 * 
 * @brief Writes the value sent to SSD data port.
 *
 * @param <value> the value to be written on the SSD
 * @return <void>
 */
void ssd_write_data(unsigned char value);

/**
 * ssd_en()
 * 
 * @brief Enables specific SSD_MSK SSD
 *
 * @param <SSD_MSK> a mask for the SSD to enable
 * @return <void>
 */
void ssd_en(unsigned char SSD_MSK);

/**
 * ssd_off()
 * 
 * @brief Disables all enabled SSDs and Clears the data port "d"
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void ssd_off(void);

#endif
/*** End of File **************************************************************/
