/* 
This file containes the hardware specific driver functions 
in order to handle data-transfers beweeen the sd-card driver and the actual hardware. 

These functions need to be implemented for every hardware it shuld run on.

*/

#include "stm32h7xx_hal.h"
#include "ff.h"

#include "sd_spi_stm32h7xx.h"

void SELECT(void)
{
	HAL_GPIO_WritePin(SD_CS_PORT, SD_CS_PIN, GPIO_PIN_RESET);
}


void DESELECT(void)
{
	HAL_GPIO_WritePin(SD_CS_PORT, SD_CS_PIN, GPIO_PIN_SET);
}

void xmit_spi(BYTE Data)
{
	while (HAL_SPI_GetState(&SD_SPI) != HAL_SPI_STATE_READY);
	HAL_SPI_Transmit(&SD_SPI, (void*)&Data, 1, SD_SPI_TIMEOUT_MS);
}

BYTE rcvr_spi(void)
{
	unsigned char Dummy, Data;
	Dummy = 0xFF;
	Data = 0;
	while ((HAL_SPI_GetState(&SD_SPI) != HAL_SPI_STATE_READY))
	{
		asm("NOP");
	}
	HAL_SPI_TransmitReceive(&SD_SPI, &Dummy, &Data, 1, SD_SPI_TIMEOUT_MS);

	return Data;
}

DWORD sd_get_fattime(void) {

	return ((2007UL - 1980) << 25) // Year = 2007
	| (6UL << 21) // Month = June
			| (5UL << 16) // Day = 5
			| (11U << 11) // Hour = 11
			| (38U << 5) // Min = 38
			| (0U >> 1) // Sec = 0
	;

}
