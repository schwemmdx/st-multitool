#include "drive_deamon.h"

#include "ff.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdbool.h"




void dd_init(driveDeamon_t* driveDeamon)
{
    
    do
    {
        driveDeamon->fatfs_result = f_mount(&driveDeamon->logical_drive,"/",1);

        if(driveDeamon->fatfs_result != FR_OK)
        {   
            driveDeamon->status = DRIVE_MOUNT_ERR;
            dd_error_handler();
        }
        else
        {
            driveDeamon->status = DRIVE_MOUNT_OK;
            FIL pFile;
            f_mkdir("/data");
            f_mkdir("/log");
            f_mkdir("/config");
            f_mkdir("/sys");
            f_mkdir("/dump");

            return;

        }

    }while(driveDeamon->fatfs_result != FR_OK);

    

}


   


void dd_runner(void * params)
{
    while(true)
    {
       
        vTaskDelay(5000);
    }
}

void dd_sizeinfo(driveDeamon_t* driveDeamon)
{
    DWORD free_clust;
    f_getfree("/",&free_clust,&driveDeamon->p_file_sys);

    //driveDeamon->free = driveDeamon->p_file_sys->free_clst * driveDeamon->p_file_sys->csize;
    //driveDeamon->total = (driveDeamon->p_file_sys->n_fatent -2) * driveDeamon->p_file_sys->csize;
    //driveDeamon->used = driveDeamon->total-driveDeamon->used;


}

float dd_convert_kib2mb(int kib_value)
{
    return 1024.0/100000 * kib_value;
}

void dd_error_handler(void)
{
    
    for (uint8_t i=0;i <10;i++) 
    {
        HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
        HAL_Delay(100);
    }
    
}