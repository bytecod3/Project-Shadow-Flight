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
uint8_t initialize(ADXL345_instance device, I2C_HandleTypeDef i2c_handle) {
	device->i2c_handle = i2c_handle;

	device->acceleration_buffer[0] = 0.0f;
	device->acceleration_buffer[1] = 0.0f;
	device->acceleration_buffer[2] = 0.0f;

	device->internal_temperature = 0.0f;

	HAL_StatusTypeDef status;

	/**
	 * check device, mems and part ID
	 */
	uint8_t reg_data;
	status = read_single_register(device, DEVID_REG, &reg_data);

	if(reg_data != DEVICE_ID) {
		return 255;
	}

	/* set the ODR(output data rate) and digital filters:  */

}


/**
 * @brief This function read a single register value
 */
HAL_StatusTypeDef read_single_register(ADXL345_instance device, uint8_t reg, uint8_t* data) {
	return HAL_I2C_Mem_Read(device->i2c_handle, ADXL345_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

/**
 * @brief This function reads multiple registers
 */
HAL_StatusTypeDef read_multiple_registers(ADXL345_instance device, uint8_t reg, uint8_t* data, uint8_t length) {
	return HAL_I2C_Mem_Read(device->i2c_handle, ADXL345_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);
}

/**
 * @brief This function writes to a single register
 */
HAL_StatusTypeDef write_register(ADXL345_instance, uint8_t reg, uint8_t* data) {
	return HAL_I2C_Mem_Write(device->i2c_handle, ADXL345_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
};




























