/****************************************************************************
* Title                 :   Interrupt
* Filename              :   int.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   int.h
 *  \brief  This file contains the interrupt control function definitions.
 */

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifndef __INT_H__
#define __INT_H__

/**
 * Enable_Global_INT()
 * 
 * @brief Enables the global interrupt
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void Enable_Global_INT(void);

/**
 * Enable_Peripheral_INT()
 * 
 * @brief Enables the peripheral interrupt
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void Enable_Peripheral_INT(void);

/**
 * Disable_Global_INT()
 * 
 * @brief Disables the global interrupt
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void Disable_Global_INT(void);

/**
 * Disable_Perephiral_INT()
 * 
 * @brief Disable the peripheral interrupt
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void Disable_Perephiral_INT(void);
#endif
/*** End of File **************************************************************/