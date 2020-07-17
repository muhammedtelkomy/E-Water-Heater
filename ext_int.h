/****************************************************************************
* Title                 :   External Interrupt
* Filename              :   ext_int.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   ext_int.h
 *  \brief  This file contains external interrupt controls.
 */

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifndef __EXT_INT_H__
#define __EXT_INT_H__

/**
 * init_ext_int()
 * 
 * @brief Initializes external interrupt at PORTB pin 0
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void init_ext_int(void);

/**
 * ext_int_en()
 * 
 * @brief Enables the external interrupt
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void ext_int_en(void);

/**
 * ext_int_dis()
 * 
 * @brief Disables the external interrupt
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void ext_int_dis(void);

/**
 * clear_int_flag()
 * 
 * @brief Clears the external interrupt flag
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void clear_int_flag(void);

#endif
/*** End of File **************************************************************/