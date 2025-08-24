/*
 * adxl345.c
 *
 *  Created on: Aug 23, 2025
 *      Author: Edwin Mwiti
 */

#include "adxl345.h"

/**
 * @brief This function initializes the ADXL345 object
 * @return 1 if init success, 0 if init fail
 */
uint8_t ADXL_initialize(ADXL345_instance device, I2C_HandleTypeDef* i2c_handle) {
	device->i2c_handle = i2c_handle;

	device->acceleration_buffer[0] = 0.0f;
	device->acceleration_buffer[1] = 0.0f;
	device->acceleration_buffer[2] = 0.0f;

	device->internal_temperature = 0.0f;

//	if(reg_data != DEVICE_ID) {
//		return 255;
//	} else {
//		return 1;
//	}

	uint8_t reg_data;

	/* set the ODR(output data rate) and digital filters: 25Hz data rate, 12.5 LPF Bandwidth  */
	reg_data = 0x08;
	ADXL_write_register(device, BW_RATE, &reg_data);

	/* put the sensor in measurement mode */
	ADXL_write_register(device, POWER_CTL, &reg_data);

	/**
	 * check device id, mems and part ID
	 */

	ADXL_read_single_register(device, DEVID_REG, &reg_data);

	return reg_data;

}

/**
 * @brief This function read a single register value
 */
HAL_StatusTypeDef ADXL_read_single_register(ADXL345_instance device, uint8_t reg, uint8_t* data) {
	return HAL_I2C_Mem_Read(device->i2c_handle, ADXL345_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

/**
 * @brief This function reads multiple registers
 */
HAL_StatusTypeDef ADXL_read_multiple_registers(ADXL345_instance device, uint8_t reg, uint8_t* data, uint8_t length) {
	return HAL_I2C_Mem_Read(device->i2c_handle, ADXL345_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);
}

/**
 * @brief This function writes to a single register
 */
HAL_StatusTypeDef ADXL_write_register(ADXL345_instance device, uint8_t reg, uint8_t* data) {
	return HAL_I2C_Mem_Write(device->i2c_handle, ADXL345_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
};




























