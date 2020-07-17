/****************************************************************************
* Title                 :   External Interrupt
* Filename              :   ext_int.c
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   ext_int.c
 *  \brief  This file contains external interrupt controls.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include <xc.h>
#include "ext_int.h"
#include "int.h"
#include "port.h"

/******************************************************************************
* Function Prototypes
*******************************************************************************/
/*------------------------------------------------------------------*
 * init_ext_int()
 * Initializes external interrupt at PORTB pin 0
-*------------------------------------------------------------------*/ 
void init_ext_int(void)
{
    EXT_INT_IO_REG |= EXT_INT_PIN_MSK;
    nRBPU = 1;
    INTEDG = 1;
    Enable_Peripheral_INT();
    Enable_Global_INT();
}

/*------------------------------------------------------------------*
 * ext_int_en()
 * Enables the external interrupt
-*------------------------------------------------------------------*/ 
void ext_int_en(void)
{
    INTE = 1;
}

/*------------------------------------------------------------------*
 * ext_int_dis()
 * Disables the external interrupt
-*------------------------------------------------------------------*/ 
void ext_int_dis(void)
{
    INTE = 0;
}

/*------------------------------------------------------------------*
 * clear_int_flag()
 * Clears the external interrupt flag
-*------------------------------------------------------------------*/ 
void clear_int_flag(void)
{
    INTF = 0;  
}
/*** End of File **************************************************************/