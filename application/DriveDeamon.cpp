
#include <string>

#include "DriveDeamon.h"
#include "ff.h"
#include "main.h"

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"


DriveDeamon::DriveDeamon(std::string mountPoint)
{   
    this->fs_status = f_mount(&this->fileSystem,this->mntPoint.c_str(),MOUNT_INSTANT);

    if(this->fs_status == FR_OK)
    {
        this->mntStatus = DRIVE_MOUNT_OK;
        this->createFolderStructure();
    }
    else
    {
        this->mntStatus = DRIVE_MOUNT_ERR;
        this->errorHandler();
    }
   
}
void DriveDeamon::createFolderStructure(void)
{
     
    f_mkdir((this->mntPoint+"data").c_str());
    f_mkdir((this->mntPoint+"log").c_str());
    f_mkdir((this->mntPoint+"config").c_str());
    f_mkdir((this->mntPoint+"sys").c_str());
    f_mkdir((this->mntPoint+"dump").c_str());
}

void DriveDeamon::errorHandler(void)
{
    //this is typically reached in case no drive is available
    while(true)
    {
        HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
        HAL_Delay(150);
        //UART tell that drive is missing
    }
}