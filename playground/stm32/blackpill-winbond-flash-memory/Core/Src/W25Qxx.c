#include "main.h"
#include "W25Qxx.h"

void external_flash_delay(uint32_t time) {
	HAL_Delay(time);
}

void cs_low(void) {
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_RESET);
}

void cs_high(void) {
	HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);
}

void external_flash_spi_write(uint8_t* data, uint8_t len) {
	HAL_SPI_Transmit(&W25Q_SPI, data, len, 2000);
}

void external_flash_spi_read(uint8_t* data, uint8_t len) {
	HAL_SPI_Receive(&W25Q_SPI, data, len, 5000);
}

void external_flash_reset(void) {
	uint8_t tData[2];

	tData[0] = 0x66; /* enable reset */
	tData[1] = 0x99; /* reset */

	cs_low();
	external_flash_spi_write(tData, 2); /**/
	cs_high();
	external_flash_delay(100);
}

uint32_t external_flash_read_ID(void) {
	uint8_t tData = 0x9f;
	uint8_t rData[3]; /* MFN_ID:MEM_ID:CAPACITY_ID */

	cs_low();				/* activate memory */
	external_flash_spi_write(&tData, 1);
	external_flash_spi_read(rData, 3);
	cs_high();

	return ((rData[0] << 16) | (rData[1] << 8) | rData[2]); /* MFN_ID:MEM_ID:CAPACITY_ID */
}

/**
 * @brief This function reads data from a given address
 * @param start_page page number where we want to read from
 * @param offset byte offset within that page (0 - 255)
 * @param the number of bytes we want to read
 * @param buffer pointer to the array where the data will be stored
 */
void external_flash_read(uint32_t start_page, uint8_t offset, uint32_t size, uint8_t *buffer) {
	uint8_t t_data[5];
	uint32_t mem_addr = (start_page * 256) + offset;

	/* if chip size is less 256 Mbits, use 24-bit address, else use 32-bit address */
	if( NUM_BLOCKS < 512) {
		t_data[0] = READ_DATA_3_BYTE_INSTR;
		t_data[1] = (mem_addr >> 16) & 0xFF;	/* MSB */
		t_data[2] = (mem_addr >> 8) & 0xFF;
		t_data[3] = (mem_addr) & 0xFF; /* LSB */

	} else {
		t_data[0] = READ_DATA_4_BYTE_INSTR;
		t_data[1] = (mem_addr >> 24) & 0xFF;
		t_data[2] = (mem_addr >> 16) & 0xFF;
		t_data[3] = (mem_addr >> 8) & 0xFF;
		t_data[4] = (mem_addr) & 0xFF;
	}

	/* send it */
	cs_low();
	if(NUM_BLOCKS < 512) {
		external_flash_spi_write(t_data, 4);
	} else {
		external_flash_spi_write(t_data, 5);
	}

	/* read the stored data */
	external_flash_spi_read(buffer, size);

	cs_high();

}


void external_flash_fast_read(uint32_t start_page, uint8_t offset, uint32_t size, uint8_t *buffer) {
	uint8_t t_data[6];
	uint32_t mem_addr = (start_page * 256) + offset;

	/* if chip size is less 256 Mbits, use 24-bit address, else use 32-bit address */
	if( NUM_BLOCKS < 512) {
		t_data[0] = FAST_READ_DATA_3_BYTE_INSTR;
		t_data[1] = (mem_addr >> 16) & 0xFF;	/* MSB */
		t_data[2] = (mem_addr >> 8) & 0xFF;
		t_data[3] = (mem_addr) & 0xFF; /* LSB */
		t_data[4] = 0;

	} else {
		t_data[0] = FAST_READ_DATA_4_BYTE_INSTR;
		t_data[1] = (mem_addr >> 24) & 0xFF;
		t_data[2] = (mem_addr >> 16) & 0xFF;
		t_data[3] = (mem_addr >> 8) & 0xFF;
		t_data[4] = (mem_addr) & 0xFF;
		t_data[5] = 0;
	}

	/* send it */
	cs_low();
	if(NUM_BLOCKS < 512) {
		external_flash_spi_write(t_data, 5);
	} else {
		external_flash_spi_write(t_data, 6);
	}

	/* read the stored data */
	external_flash_spi_read(buffer, size);

	cs_high();
}

/**
 * @brief This function enables writing to the flash memory
 * Write is automatically disabled after power-up
 */
void external_flash_enable_write(void) {
	uint8_t t_data = ENABLE_WRITE;
	cs_low();
	external_flash_spi_write(&t_data, 1);
	cs_high();
	external_flash_delay(5);
}

/**
 * @brief This function disables writing to the flash memory
 */
void external_flash_disable_write(void) {
	uint8_t t_data = DISABLE_WRITE;
	cs_low();
	external_flash_spi_write(&t_data, 1);
	cs_high();
	external_flash_delay(5);
}

/**
 * @brief This function sets a sector of memory to 0xFF
 */
void external_flash_erase_sector(uint16_t num_sector) {
	uint8_t t_data[6];
	uint32_t mem_addr = num_sector * 16 * 256;

	external_flash_enable_write();

	if (NUM_BLOCKS < 512) {
		t_data[0] = ERASE_SECTOR_3_BYTE_INSTR;
		t_data[1] = (mem_addr >> 16) & 0xFF; /* MSB */
		t_data[2] = (mem_addr >> 8) & 0xFF;
		t_data[3] = (mem_addr) & 0xFF; /* LSB */

		cs_low();
		external_flash_spi_write(t_data, 4);
		cs_low();

	} else {
		t_data[0] = ERASE_SECTOR_4_BYTE_INSTR;
		t_data[1] = (mem_addr >> 24) & 0xFF; /* MSB */
		t_data[2] = (mem_addr >> 16) & 0xFF;
		t_data[3] = (mem_addr >> 8) & 0xFF;
		t_data[4] = (mem_addr) & 0xFF; /* LSB */

		cs_low();
		external_flash_spi_write(t_data, 5);
		cs_low();
	}

	external_flash_delay(450); /* sector erase takes ~400ms*/

	external_flash_disable_write();

}














































