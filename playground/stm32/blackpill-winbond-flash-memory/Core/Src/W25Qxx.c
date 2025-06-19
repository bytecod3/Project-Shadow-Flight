#include "main.h"
#include "W25Qxx.h"

void W25Q_Delay(uint32_t time) {
	HAL_Delay(time);
}

void cs_LOW(void) {
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);
}

void cs_HIGH(void) {
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);
}

void SPI_Write(uint8_t* data, uint8_t len) {
	HAL_SPI_Transmit(&W25Q_SPI, data, len, 2000);
}

void SPI_Read(uint8_t* data, uint8_t len) {
	HAL_SPI_Receive(&W25Q_SPI, data, len, 5000);
}

void W25Q_Reset(void) {
	uint8_t tData[2];

	tData[0] = 0x66; /* enable reset */
	tData[1] = 0x99; /* reset */

	cs_LOW();
	SPI_Write(tData, 2); /**/
	cs_HIGH();
	W25Q_Delay(100);
}

uint32_t W25Q_ReadID(void) {
	uint8_t tData = 0x9f;
	uint8_t rData[3]; /* MFN_ID:MEM_ID:CAPACITY_ID */

	cs_LOW();				/* activate memory */
	SPI_Write(&tData, 1);
	SPI_Read(rData, 3);
	cs_HIGH();

	return ((rData[0] << 16) | (rData[1] << 8) | rData[2]); /* MFN_ID:MEM_ID:CAPACITY_ID */
}
