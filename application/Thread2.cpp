#include "Thread2.h"
#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "EventLogger.h"

void Thread2::run(void)
{   uint32_t i=0;
    while(1)
    {
        i++;
        this->dbg->info("Entered Thread 2 -"+std::to_string(i));
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(200);
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(200);
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(200);
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        HAL_Delay(200);
        vTaskDelay(500);
      
    }
}