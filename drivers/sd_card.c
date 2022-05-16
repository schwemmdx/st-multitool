#include "sd_spi_drv.h"
#include "diskio.h"



DSTATUS disk_initialize (BYTE pdrv)
{
    return STA_NOINIT;
}

DSTATUS disk_status (BYTE pdrv)
{
    return STA_NOINIT;
}
DRESULT disk_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count)
{
    return STA_NOINIT;
}
DRESULT disk_write (BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count)
{
    return STA_NOINIT;
}
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff)
{
    return STA_NOINIT;
}