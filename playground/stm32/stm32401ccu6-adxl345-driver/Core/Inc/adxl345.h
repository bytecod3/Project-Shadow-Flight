/*
 * adxl345.h
 *
 *  Created on: Aug 23, 2025
 *  Author: Edwin Mwiti
 */

#ifndef INC_ADXL345_H_
#define INC_ADXL345_H_

#include "stm32f4xx_hal.h"

/**
 * Register map and addresses
 *
 */
#define DEVID_REG			0x00		/*!< Device ID */
#define THRES_TAP			0x1D		/*!< Tap threshold */
#define OFSX				0x1E		/*!< x-axis offset */
#define OFSY				0x1F		/*!< y-axis offset */
#define OFSZ				0x20		/*!< z-axis offset */
#define DUR				0x21		/*!< tap duration */
#define LATENT 			0x22		/*!< tap latency */
#define WINDOW 			0x23		/*!< tap window */
#define THRESH_ACT 		0x24		/*!< activity threshold */
#define THESH_INACT 		0x25		/*!< inactivity threshold */
#define TIME_INACT 		0x26		/*!< inactivity time */
#define ACT_INACT_CTL 	0x27		/*!< axis enable control for activity and inactivity detection */
#define THRESH_FF 			0x28		/*!< free-fall threshold */
#define TIME_FF 			0x29		/*!< free-fall time */
#define TAP_AXES 			0x2A		/*!< axis control for single/double tap */
#define ACT_TAP_STATUS 	0x2B		/*!< source of single/double tap */
#define BW_RATE 			0x2C		/*!< data rate and power mode control */
#define POWER_CTL 			0x2D		/*!< power saving features control */
#define INT_ENABLE			0x22		/*!< interrupt enable control */
#define INT_MAP  			0x2F		/*!< winterrupt mapping control */
#define INT_SOURCE 		0x30		/*!< source of interrupts */
#define DATA_FORMAT 		0x31		/*!< dat format control */
#define DATAX0 			0x32		/*!< x axis data 0 */
#define DATAX1 			0x33		/*!< x axis data 1 */
#define DATAY0 			0x34		/*!< y axis data 0 */
#define DATAY1 			0x35		/*!< y axis data 1 */
#define DATAZ0 			0x36		/*!< z axis data 0 */
#define DATAZ1 			0x37		/*!< z axis data 1 */
#define FIFO_CTL 			0x38		/*!< fifo control */
#define FIFO_STATUS 		0x39		/*!< fifo status */

/* device ID*/
#define DEVICE_ID 0xE5

/* device I2C address */
#define ADXL345_ADDRESS 0x1D

/**
 * @brief This struct represents the ADXL345 object
 */
typedef struct {
	I2C_HandleTypedef* i2c_handle;
	float acceleration_buffer[3]; // x, y, z acceleration
	float internal_temperature;
} ADXL345;

typedef ADXL345* ADXL345_instance;

uint8_t initialize(ADXL345_instance, I2C_HandleTypeDef);
HAL_StatusTypeDef read_single_register(ADXL345_instance, uint8_t reg, uint8_t* data);
HAL_StatusTypeDef read_multiple_registers(ADXL345_instance, uint8_t reg, uint8_t* data, uint8_t length);
HAL_StatusTypeDef write_register(ADXL345_instance, uint8_t reg, uint8_t* data);
HAL_StatusTypedeDef read_acceleration(ADXL345_instance);
float get_internal_temperature(ADXL345_instance);



#endif /* INC_ADXL345_H_ */
