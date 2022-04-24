#include <stdint.h>
#include <string>

#include "app_main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "app_tasks.h"

uint8_t app_main()
{
    // At this point we call everything running in OS Layer

    TaskHandle_t led1_handle;
    TaskHandle_t led2_handle;

    xTaskCreate(Led1Task::run, "LED1", 100, NULL, 2, &led1_handle);
    xTaskCreate(Led2Task::run, "LED2", 100, NULL, 2, &led2_handle);

    vTaskStartScheduler();

    while (true)
    {
        // do fancy shit
    }
    return 0;
}
