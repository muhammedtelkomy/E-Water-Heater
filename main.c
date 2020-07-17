/******************************************************************************
* Configuration
*******************************************************************************/
#ifdef _16F877A
#include"config_877A.h"
#endif

/******************************************************************************
* Includes
*******************************************************************************/
#include "EW_Heater.h"
#include "sch.h"
#include "xc.h"

/******************************************************************************
* Functions
*******************************************************************************/
/*
 * main() 
 * Called after power up or reset. The system is initialized then
 * enters sleep mode after wake up enters an endless for loop. The for loop
 * calls any continuous tasks and then checks if any of the periodic tasks are 
 * ready to run. Each periodic task is called when its timer interval is exceeded.
 */
void main() 
{
    MC_init();                      // Initializing MCU peripherals
    tasks_creation();               // Creating Electric Water Heater scheduler tasks
    pwr_off();                      // Power off MCU at start
    while(1)
    {
        SCH_Dispatch_Tasks();       // Run Task Dispatcher
    }
}
/*** End of File **************************************************************/