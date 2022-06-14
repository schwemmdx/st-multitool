

#include "drive_deamon.h"
#include "ff.h"
#include "main.h"

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_gpio.h"

#include "string.h"


void fk_initDriveDeamon(char* mountPoint,fk_DriveDeamon_t* pDeamon)
{
    
    pDeamon->fs_status = f_mount(&pDeamon->fileSystem,mountPoint,0);
    if(pDeamon->fs_status == FR_OK)
    {
        pDeamon->mntPoint = mountPoint;
        pDeamon->mntStatus = DRIVE_MOUNT_OK;
        createFolderStructure();

    }
    else
    {
        pDeamon->mntPoint = NULL;
        pDeamon->mntStatus = DRIVE_MOUNT_ERR;
    }
    
}

static void createFolderStructure(void,fk_DriveDeamon_t* pDeamon)
{
    char logs[]= "logs";
    char config[]="config";
    char data[] = "data";
    char sys[] = "sys";

    char dummy[20];
    memset(dummy,0,sizeof(dummy));
    strcat(dummy,pDeamon->mntPoint);
    strcat(dummy,logs);
    f_mkdir(dummy);
}

fk_DriveSizeInfo_t fk_getSizeInfo(fk_DriveDeamon_t* pDeamon)
{
    fk_DriveSizeInfo_t sInfo;
    DWORD nClust=0;
    FATFS* dummyFS;
    f_getfree(pDeamon->mntPoint,&nClust,&dummyFS);
    //More calulations need to be done
    sInfo.free = dummyFS->free_clst;
    sInfo.total = dummyFS->fsize;
    return sInfo;
}

/*
void fwk_InitLogger( const char* mountPoint)
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
*/