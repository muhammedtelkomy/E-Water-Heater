/****************************************************************************
* Title                 :   Scheduler
* Filename              :   sch.c
* Author                :   Michael Pont in his book "Patterns for time-triggered embedded systems"
* Origin Date           :   2001
*
* Notes                 :   None
*******************************************************************************/
/** \file sch.c
 * \brief This module contains code implementation for a task scheduler.
 */

/******************************************************************************
* Includes
*******************************************************************************/
#include "pic16f877a.h"
#include "sch.h"
#include <stdio.h>
#include <stdint.h>

/******************************************************************************
* Variables
*******************************************************************************/
static sTask SCH_tasks_G[SCH_MAX_TASKS];
static unsigned char Error_code_G = 0;

/******************************************************************************
* Functions
*******************************************************************************/

/*------------------------------------------------------------------*
sch_init()
Initializes the scheduler tick time with 5ms uses Timer 0 starts counting from
100 and overflows at 256
-*------------------------------------------------------------------*/
void sch_init(void)
{
    unsigned int i;
    for (i = 0; i < SCH_MAX_TASKS; i++) 
    {   
        SCH_Delete_Task(i); 
    }
    Error_code_G = 0;
    /* Timer 0 initialization */
    /* Set the prescaler with a division 64 for 5ms Tick configurations */
    PS0 = 1;                    
    PS1 = 0;                    
    PS2 = 1;                    
    PEIE = 1;                   // Enable Pherephiral interrupt
    GIE = 1;                    // Enable General interrupt
    TMR0 = 0;                   // clear Timer0 count
}

/*------------------------------------------------------------------*
SCH_Add_Task()
Enables the timer interrupt (starts scheduling)
-*------------------------------------------------------------------*/
void sch_start(void)
{
    TMR0IE = 1;                 // Enable Timer 0 interrupt to start scheduling
}

/*------------------------------------------------------------------*
SCH_Add_Task()
Disables the timer interrupt (stops scheduling)
-*------------------------------------------------------------------*/
void sch_stop(void)
{
    TMR0IE = 0;                 // Disable Timer 0 interrupt to stop scheduling
}

/*------------------------------------------------------------------*
SCH_Add_Task()
Causes a task (function) to be executed at regular intervals or after a user-defined delay
-*------------------------------------------------------------------*/ 
unsigned char SCH_Add_Task(void (* pFunction)(void), const unsigned int DELAY, const unsigned int PERIOD) 
{ 
    unsigned char Index = 0;
    // First find a gap in the array (if there is one) 
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) 
    { 
        Index++; 
    } 
    // Have we reached the end of the list? 
    if (Index == SCH_MAX_TASKS) 
    { 
        // Task list is full 
        // // Set the global error variable 
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
    // Also return an error code 
        return SCH_MAX_TASKS; 
    }
    // If we're here, there is a space in the task array 
    SCH_tasks_G[Index].pTask  = pFunction;
    SCH_tasks_G[Index].Delay  = DELAY; 
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].RunMe  = 0;
    
    return Index; // return position of task (to allow later deletion) 
}

/*------------------------------------------------------------------*
SCH_Dispatch_Tasks()
This is the 'dispatcher' function. When a task (function) is due to run,
SCH_Dispatch_Tasks() will run it. This function must be called (repeatedly)
from the main loop.
-*------------------------------------------------------------------*/ 
void SCH_Dispatch_Tasks(void) 
{ 
    unsigned char Index;
    // Dispatches (runs) the next task (if one is ready) 
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) 
    { 
        if (SCH_tasks_G[Index].RunMe > 0) 
        { 
            (SCH_tasks_G[Index].pTask)(); // Run the task
            SCH_tasks_G[Index].RunMe -= 1; // Reset / reduce RunMe flag
            // Periodic tasks will automatically run again // - if this is a 'one shot' task, remove it from the array 
            if (SCH_tasks_G[Index].Period == 0) 
            { 
                SCH_Delete_Task(Index); 
            } 
        }
    }
// The scheduler enters idle mode at this point 
    SCH_Go_To_Sleep(); 
}

/*------------------------------------------------------------------*
SCH_Delete_Task(const unsigned char TASK_INDEX)
 * Deletes a task with index TASK_INDEX
-*------------------------------------------------------------------*/ 
unsigned char SCH_Delete_Task(const unsigned char TASK_INDEX) 
{ 
    unsigned char Return_code;
    if (SCH_tasks_G[TASK_INDEX].pTask == 0) 
    { 
        // No task at this location... // 
        // Set the global error variable 
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
        // ...also return an error code 
        Return_code = RETURN_ERROR; 
    } 
    else 
    { 
        Return_code = RETURN_NORMAL; 
    } 
    SCH_tasks_G[TASK_INDEX].pTask = 0x0000; 
    SCH_tasks_G[TASK_INDEX].Delay = 0; 
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;
return Return_code; // return status 
}

/*------------------------------------------------------------------*
SCH_Go_To_Sleep(const unsigned char TASK_INDEX)
 * Enters idle mode
-*------------------------------------------------------------------*/ 
void SCH_Go_To_Sleep(void) 
{ 
    asm("SLEEP");    // Enter idle mode
}
/*** End of File **************************************************************/