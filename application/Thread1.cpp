#include "Thread1.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "EventLogger.h"

void Thread1::run(void)
{   uint32_t i=0;
    while(1)
    {
        i++;
        this->dbg->info("Entered Thread 1 -"+std::to_string(i));
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        HAL_Delay(100);
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        HAL_Delay(100);
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        HAL_Delay(100);
        HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
        HAL_Delay(100);
        vTaskDelay(200);
      
    }
}