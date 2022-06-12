#include <stdint.h>
#include <string>

#include "app_main.h"
#include "Thread2.h"
#include "Thread1.h"
#include "DriveDeamon.h"
#include "EventLogger.h"


extern "C"
{
    #include "main.h"
    #include "FreeRTOS.h"
    #include "task.h"

}


uint8_t app_main()
{   
    /*
    driveDeamon_t drive;
    dd_init(&drive);
    */
    DriveDeamon mainDrive("/");

    EventLogger dbg("/log");  
    
    Thread1 task1("Test1",3,512,&dbg);
    Thread2 task2("Test2",3,512,&dbg);
    
    vTaskStartScheduler();

    while(true)
    {   
        
       
    }

    
    return 0;
}

