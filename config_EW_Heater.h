/****************************************************************************
* Title                 :   Electric Heater Configuration
* Filename              :   config_EW_Heater.h
* Author                :   Muhammed Elkomy
* Origin Date           :   08/07/2020
* Version               :   1.0.0
*
* Notes                 :   None
*******************************************************************************/
/** \file   config_EW_Heater.h
 *  \brief  This file contains all the configuration options for the electric
 *          heater application.
 */
#ifndef __CONFIG_EW_HEATER_H__
#define __CONFIG_EW_HEATER_H__
/******************************************************************************
* Configuration
*******************************************************************************/
/*****************************************************************************
 *
 *  Seven Segments Display Update
 *
 *****************************************************************************/
#define SSD_BLINK_PERIOD                    1000
#define SSD_TASK_PERIOD                     20
#define SSD_TASK_DELAY                      15
#define SSD_NUM                             2
/*****************************************************************************/


/*****************************************************************************
 *
 *  Temperature Configurations
 *
 *****************************************************************************/
#define INITIAL_TEMP                        60
#define MAX_SET_TEMP                        75
#define MIN_SET_TEMP                        35
#define TEMP_SET_STEP                       5
#define TEMP_ERROR_VAL                      5
#define TEMP_SENSOR_CH                      2
#define TEMP_SAVE_ADDRESS                   0x0009
#define TEMP_SENSE_TASK_PERIOD              100
#define TEMP_SENSE_TASK_DELAY               0
#define TEMP_CONTROL_TASK_PERIOD            100
#define TEMP_CONTROL_TASK_DELAY             5
#define TEMP_READINGS_AVG                   10
#define HEAT_LED_BLINK_TIME                 1000
/*****************************************************************************/

/*****************************************************************************
 *
 *  Temperature Setting
 *
 *****************************************************************************/
#define TEMP_SET_TASK_PERIOD                50
#define TEMP_SET_TASK_DELAY                 10
#define TEMP_SET_TIMEOUT                    5000
/*****************************************************************************/

/*****************************************************************************
 *
 *  Switches
 *
 *****************************************************************************/
#define PWR_TASK_PERIOD                     50
#define PWR_TASK_DELAY                      20
#define PWR_ON_TASKS_CNT                    2
#define PLUS_SW                             RB2
#define MINUS_SW                            RB1
#define PWR_SW                              RB0
#define NO_SW_NUM                           0
#define MINUS_SW_NUM                        1
#define PLUS_SW_NUM                         2
#define PWR_SW_NUM                          3
/*****************************************************************************/

#endif
/*** End of File **************************************************************/