/*
 * W25Qxx.h
 *
 *  Created on: Jun 19, 2025
 *      Author: Edwin
 */

#ifndef INC_W25QXX_H_
#define INC_W25QXX_H_

extern SPI_HandleTypeDef hspi3;

#define READ_DATA_3_BYTE_INSTR 					(0x03)
#define READ_DATA_4_BYTE_INSTR					(0x13)
#define FAST_READ_DATA_3_BYTE_INSTR				(0x0B)
#define FAST_READ_DATA_4_BYTE_INSTR				(0x0C)
#define ENABLE_WRITE							(0x06)
#define DISABLE_WRITE							(0x04)
#define ERASE_SECTOR_3_BYTE_INSTR				(0x20)
#define ERASE_SECTOR_4_BYTE_INSTR				(0x21)

#define W25Q_SPI	hspi3
#define NUM_BLOCKS	(32)

/**
 * @brief This function creates a short delay
 * @param time length to delay (ms)
 */
void external_flash_delay(uint32_t time);

/**
 * @brief This function pulls the chip select pin LOW
 */
void cs_low(void);

/**
 * @brief This function pulls the chip select pin HIGH
 */
void cs_high(void);

/**
 * @brief This function sends a byte to the flash memory
 * @param data pointer to byte data to write
 * @param len the number of bytes to write
 */
void external_flash_spi_write(uint8_t* data, uint8_t len);

/**
 * @brief This function reads bytes from the flash memory
 * @param data pointer to byte data to read
 * @param len the number of bytes to read
 */
void external_flash_spi_read(uint8_t* data, uint8_t len);

/**
 * @brief This function performs a flash memory reset
 */
void external_flash_reset(void);

/**
 * @brief This function enables writing to the flash memory
 */
void external_flash_enable_write(void);

/**
 * @brief This function disables writing to the flash memory
 */
void external_flash_disable_write(void);

/**
 * @brief This function read the flash memory ID
 */
uint32_t external_flash_read_ID(void);

/**
 * @brief This function reads data from a given address
 * @param start_page page number where we want to read from
 * @param offset byte offset within that page (0 - 255)
 * @param the number of bytes we want to read
 * @param buffer pointer to the array where the data will be stored
 */
void external_flash_read(uint32_t start_page, uint8_t offset, uint32_t size, uint8_t *buffer);

/**
 * @brief This function performs a sequential read of bytes from the memory
 *
 */
void external_flash_fast_read(uint32_t start_page, uint8_t offset, uint32_t size, uint8_t *buffer);

/**
 * @brief This function sets a sector of memory to 0xFF
 */
void external_flash_erase_sector(uint16_t num_sector);


uint8_t external_flash_test();


#endif /* INC_W25QXX_H_ */
