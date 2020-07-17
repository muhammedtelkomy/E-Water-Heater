/****************************************************************************
* Title                 :   Scheduler
* Filename              :   sch.h
* Author                :   Michael Pont in his book "Patterns for time-triggered embedded systems"
* Origin Date           :   2001
*
* Notes                 :   None
*******************************************************************************/
/** \file sch.h
 * \brief This module contains definitions for a task scheduler.
 */
#ifndef __SCH_H__
#define __SCH_H__
/******************************************************************************
* Constants
*******************************************************************************/
/**
 * Define the system tick interval in microseconds
 */
#define SCH_TICK                            5

/**
 * Define the system maximum number of tasks
 */
#define SCH_MAX_TASKS                       5

/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * Struct sTask
 * sTask structure is used to define the parameters required in order to
 * configure a task.
 */
typedef struct { 
    // Pointer to the task (must be a 'void (void)' function) 
    void (* pTask)(void); 
    // Delay (ticks) until the function will (next) be run // - see SCH_Add_Task() for further details 
    unsigned int Delay; 
    // Interval (ticks) between subsequent runs. // - see SCH_Add_Task() for further details 
    unsigned int Period; 
    // Incremented (by scheduler) when task is due to execute 
    unsigned char RunMe; 
} sTask;

/**
 * Enum SCH_E
 * SCH_E enumeration type is used to define the scheduling errors
 */
typedef enum 
{
    RETURN_ERROR,RETURN_NORMAL,ERROR_SCH_CANNOT_DELETE_TASK,ERROR_SCH_TOO_MANY_TASKS
}SCH_E;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
/**
 * sch_init()
 * 
 * @brief Initializes the scheduler tick time with 5ms 
 *        uses Timer 0 starts counting from 100 and overflows at 256
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void sch_init(void);

/**
 * sch_start()
 * 
 * @brief Enables the timer interrupt (starts scheduling)
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void sch_start(void);

/**
 * sch_stop()
 * 
 * @brief Disables the timer interrupt (stops scheduling)
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void sch_stop(void);

/**
 * SCH_Dispatch_Tasks()
 * 
 * @brief This is the 'dispatcher' function. When a task (function) is due to run,
          SCH_Dispatch_Tasks() will run it. This function must be called (repeatedly)
          from the main loop.
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void SCH_Dispatch_Tasks(void);

/**
 * SCH_Add_Task()
 * 
 * @brief Causes a task (function) to be executed at regular intervals or after 
 *        a user-defined delay
 *
 * @param <void> takes no arguments
 * @return <void>
 */
unsigned char SCH_Add_Task(void (* pFunction)(void), const unsigned int DELAY, const unsigned int PERIOD);

/**
 * SCH_Delete_Task()
 * 
 * @brief Disables all enabled SSDs and Clears the data port "d"
 *
 * @param <void> takes no arguments
 * @return <void>
 */
unsigned char SCH_Delete_Task(const unsigned char TASK_INDEX);

/**
 * SCH_Go_To_Sleep()
 * 
 * @brief Disables all enabled SSDs and Clears the data port "d"
 *
 * @param <void> takes no arguments
 * @return <void>
 */
void SCH_Go_To_Sleep(void) ;
#endif
/*** End of File **************************************************************/
