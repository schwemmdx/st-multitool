#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

namespace Led1Task
{
    void run(void *params)
    {
        while (true)
        {
            HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
            vTaskDelay(250);
        }
    }
} // namespace Led1Task

namespace Led2Task
{
    void run(void *params)
    {
        while (true)
        {
            HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
            vTaskDelay(400);
        }
    }
} // namespace led2Task
