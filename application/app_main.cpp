#include <stdint.h>
#include <string>

#include "app_main.h"

#include "EventLogger.h"

extern "C"
{
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drive_deamon.h"
}

#include <string.h>
#include <stdio.h>


#include "Thread2.h"
#include "Thread1.h"



uint8_t app_main()
{   
    driveDeamon_t drive;
    dd_init(&drive);
    EventLogger dbg("/log");  
    
    Thread1 task1("Test1",3,512,&dbg);
    Thread2 task2("Test2",3,512,&dbg);
    
    vTaskStartScheduler();

    while(true)
    {   
        
       
    }

    
    return 0;
}

