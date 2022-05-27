#include <stdint.h>
#include <string>

#include "app_main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "app_tasks.h"



#include <string.h>
#include <stdio.h>

uint8_t app_main()
{
    // At this point we call everything running in OS Layer
    
    TaskHandle_t led1_handle;
    TaskHandle_t led2_handle;

    xTaskCreate(Led1Task::run, "LED1", 100, NULL, 2, &led1_handle);
    xTaskCreate(Led2Task::run, "LED2", 100, NULL, 2, &led2_handle);
/*
    FATFS fs;  // file system
    FIL fil; // File
    FILINFO fno;
    FRESULT fresult;  // result
    UINT br, bw;  // File read/write count

  
    FATFS *pfs;
    DWORD fre_clust;
    uint32_t total, free_space;

    fresult = f_mount(&fs, "/", 1);
	f_getfree("", &fre_clust, &pfs);
	total = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
	free_space = (uint32_t)(fre_clust * pfs->csize * 0.5);

  	
    fresult = f_open(&fil, "file1.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

  
  	char buf[80];
    sprintf(buf,"Data in File");
      f_puts("This data is from the FILE1.txt. And it was written using ...f_puts... ", &fil);

  
  	fresult = f_close(&fil);
*/
    vTaskStartScheduler();

    while (true)
    {
        // do fancy shit
    }
    return 0;
}
