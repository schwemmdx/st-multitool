#pragma once

#include "ff.h"

#include "diskio.h"


#define MOUNT_INSTANT 1
#define MOUNT_DELAYED 0


#define DRIVE_MOUNT_OK  0
#define DRIVE_MOUNT_ERR 1
#define DRIVE_NO_INIT   2
#define DRIVE_MISSING   3



typedef struct 
{
    char* mntPoint;
    uint8_t mntStatus;
    FATFS fileSystem;
    FRESULT fs_status;
    uint8_t mntStatus;

}fk_DriveDeamon_t;

typedef struct 
{
    uint32_t total;
    uint32_t used;
    uint32_t free;
    
}fk_DriveSizeInfo_t;



void fk_initDriveDeamon(char* mountPoint,fk_DriveDeamon_t* pDeamon);
fk_DriveSizeInfo_t fk_getSpaceInfo(fk_DriveDeamon_t* pDeamon);
uint8_t fk_getDriveStatus(void);



float fk_convertKib2Mb(int kibValue);
void fk_DriveDeamonErrorHandler(void);
static void createFolderStructure(void);


