#ifndef _SD_SPI_DRV_H_
#define _SD_SPI_DRV_H_

// sd_spi_drv uses the functions from fatfs's diskio.h

#include "diskio.h"


DSTATUS sd_init (BYTE pdrv);
DSTATUS sd_status (BYTE pdrv);
DRESULT sd_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count);
DRESULT sd_write (BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count);
DRESULT sd_ioctl (BYTE pdrv, BYTE cmd, void* buff);

#endif /* _SD_SPI_DRV_H_ */