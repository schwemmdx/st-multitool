#ifndef _SD_SPI_STM32_H743ZI_H_

#define _SD_SPI_STM32_H743ZI_H_



#include "stm32h7xx_hal.h"

#include "ff.h"
extern SPI_HandleTypeDef hspi1;

#define SD_SPI hspi1
#define SD_CS_PORT GPIOB
#define SD_CS_PIN  GPIO_PIN_5

#define SD_SPI_INIT_DIV 64
#define SD_SPI_RUN_DIV  8
#define SD_SPI_TIMEOUT_MS 5000


/*
These function need to be implemented target specific 
*/

/**
@brief: Sets the chip select pin for sd-card spi peripheral to low, 
in order to activate the spi transmission
*/
extern void SELECT(void);
/**
@brief: Releases the chip select pin for sd-spi peripheral  
*/
extern void DESELECT(void);
extern void xmit_spi(BYTE);
extern BYTE rcvr_spi(void);



#endif /* _SD_SPI_STM32_H743ZI_H_ */