#ifndef SD_STM32_HEADER
#define SD_STM32_HEADER

#include "ff.h"
#include "ffconf.h"
#define _READONLY FF_FS_READONLY
/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure  (Platform dependent)                */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 10ms                        */

void sdcard_systick_timerproc(void);

extern DRESULT sd_disk_ioctl(BYTE, BYTE,void*);
extern DSTATUS sd_disk_status (BYTE);
extern DSTATUS sd_disk_initialize(BYTE);
extern DRESULT sd_disk_write(BYTE,const BYTE*,DWORD,UINT);
extern DRESULT sd_disk_read(BYTE,BYTE*,DWORD,UINT);
#endif

