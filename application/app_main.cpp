#include <stdint.h>
#include <string>

#include "app_main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "app_tasks.h"

extern "C" {
#include "ff.h"
#include "main.h"
}

#include <string.h>
#include <stdio.h>

void indicate_state(FRESULT);

uint8_t app_main()
{
    // At this point we call everything running in OS Layer
    
    TaskHandle_t led1_handle;
    TaskHandle_t led2_handle;

    xTaskCreate(Led1Task::run, "LED1", 100, NULL, 2, &led1_handle);
    xTaskCreate(Led2Task::run, "LED2", 100, NULL, 2, &led2_handle);

    FATFS fs;  // file system
    FIL fil; // File
    FRESULT result;
    FILINFO fno;

    UINT br, bw;  // File read/write count

  
    FATFS *pfs;
    DWORD fre_clust;
    uint32_t total, free_space;

    result=f_mount(&fs, "/", 1);

	f_getfree("/", &fre_clust, &pfs);
	total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);

  	
    result = f_open(&fil, "/debug.log", FA_OPEN_ALWAYS | FA_READ | FA_WRITE | FA_OPEN_APPEND);

  
  	char buf[80];
    f_puts("[INFO] Started Application sucessfully", &fil);

  
  	result = f_close(&fil);

    f_mkdir("/data");
    result = f_open(&fil,"/data/useless_data.csv", FA_OPEN_ALWAYS|FA_READ |FA_WRITE);
    for(uint8_t i=0;i<100;i++ )
    {
        sprintf(buf,"%d,%d\n",i,2*i);
        f_puts(buf,&fil);
    }
    f_close(&fil);
    vTaskStartScheduler();

    while (true)
    {
        indicate_state(result);
        // do fancy shit
    }
    return 0;
}

void indicate_state(FRESULT result)
{
    if(result == FR_NOT_READY)
    {
        while(true)
        {
            HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
            HAL_GPIO_TogglePin(SD_CS_GPIO_Port,SD_CS_Pin);
            HAL_Delay(100);
            
        }
    }
    else
    {
        HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,GPIO_PIN_SET);

    }
    
}
