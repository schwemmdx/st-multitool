#pragma once

extern "C"
{
  #include "FreeRTOS.h"
  #include "task.h"
}

#include "EventLogger.h"

class Thread 
{

public:
  class EventLogger* dbg;

  Thread(char const*name, unsigned portBASE_TYPE priority,
           unsigned portSHORT stackDepth=configMINIMAL_STACK_SIZE, class EventLogger* pEvent=nullptr) 
           {
             xTaskCreate(&taskfun, name, stackDepth, this, priority, &handle);
             this->dbg = pEvent;

           }
  ~Thread()
  {
    vTaskDelete(handle);
  }

  virtual void run(void)
  {
    while(1)
    {
      vTaskDelay(1000);
    }
  }
 
 private:
    
    xTaskHandle handle;  
    static void taskfun(void* parm) 
    {
      static_cast<Thread *>(parm)->run();
    }

};