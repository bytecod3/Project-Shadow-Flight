/*
 * W25Qxx.h
 *
 *  Created on: Jun 19, 2025
 *      Author: Edwin
 */

#ifndef INC_W25QXX_H_
#define INC_W25QXX_H_

extern SPI_HandleTypeDef hspi3;

#define W25Q_SPI	hspi3

void W25Q_Delay(uint32_t time);
void cs_LOW(void);
void cs_HIGH(void);
void SPI_Write(uint8_t* data, uint8_t len);
void SPI_Read(uint8_t* data, uint8_t len);
void W25Q_Reset(void);
uint32_t W25Q_ReadID(void);


#endif /* INC_W25QXX_H_ */
