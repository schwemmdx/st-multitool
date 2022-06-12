#pragma once

#include <string>
#include <vector>
#include <map>
#include "ff.h"
#include "diskio.h"


#define MOUNT_INSTANT 1
#define MOUNT_DELAYED 0


#define DRIVE_MOUNT_OK  0
#define DRIVE_MOUNT_ERR 1
#define DRIVE_NO_INIT   2
#define DRIVE_MISSING   3



class DriveDeamon
{
    public:
    DriveDeamon(std::string mountPoint);
    std::string getSizeInfo(std::string drive,bool log=false);
    uint8_t getStatus(void);
    
    private:
    std::string mntPoint;
    FATFS fileSystem;
    FRESULT fs_status{FR_NOT_READY};
    uint8_t mntStatus{DRIVE_NO_INIT};
  
    float convertKib2Mb(int kibValue);
    void errorHandler(void);
    void createFolderStructure(void);



};