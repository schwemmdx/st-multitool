#ifndef _DRIVE_DEAMON_H_
#define _DRIVE_DEAMON_H_

#include "stdint.h"
#include "ff.h"

#define DRIVE_MOUNT_ERR 1
#define DRIVE_MOUNT_OK 0


typedef struct
{
    uint8_t status;
    uint32_t total;
    uint32_t free;
    uint32_t used;
    FATFS logical_drive;
    FATFS* p_file_sys;
    FRESULT fatfs_result;
    
}driveDeamon_t;


void dd_init(driveDeamon_t*);
void dd_runner(void * );
void dd_sizeinfo(driveDeamon_t* );
float dd_convert_kib2mb(int );
void dd_error_handler(void);

 #endif /*_DRIVE_DEAMON_H_*/