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
uint8_t ADXL_initialize(ADXL345* device, I2C_HandleTypeDef* i2c_handle) {
	device->i2c_handle = i2c_handle;
	device->address = 0xA6;

	device->acceleration_buffer[0] = 0.0f;
	device->acceleration_buffer[1] = 0.0f;
	device->acceleration_buffer[2] = 0.0f;

	device->internal_temperature = 0.0f;
	device->test_byte = 0xAA;

	/* check device ID */
	uint8_t reg_data = 0;
	ADXL_read_single_register(device, DEVID_REG, &reg_data);

	if(reg_data == DEVICE_ID) {

		/* initialize device */
		/* set the ODR(output data rate) and digital filters: 25Hz data rate, 12.5 LPF Bandwidth */
		reg_data = 0x08;
		ADXL_write_register(device, BW_RATE, &reg_data);

		/* put the sensor in measurement mode */
		ADXL_write_register(device, POWER_CTL, &reg_data);
		return 1;

	} else {
		return 0; // todo: return error codes
	}

}

/**
 * @brief Read acceleration values
 */
void ADXL_read_acceleration(ADXL345* device) {
	uint8_t data[6];

	ADXL_read_multiple_registers(device, DATAX0, data, 6);

	/* combine values */
	int16_t raw_x = ( ( data[1] << 8) | data[0] );
	int16_t raw_y = ( ( data[3] << 8) | data[2] );
	int16_t raw_z = ( ( data[5] << 8) | data[4] );

	// convert to g
	device->acceleration_buffer[0] = raw_x * 0.0039;
	device->acceleration_buffer[1] = raw_y * 0.0039;
	device->acceleration_buffer[2] = raw_z * 0.0039;


	//int16_t acc_raw_signed[3]; // x, y, z
	//acc_raw_signed[0] = (uint16_t) ((reg_data[0] << 8) | (reg_data[1]));

	/**
	 * convert to g values
	 */
	//device->acceleration_buffer[0] = 0.000061035f * 9.81 * acc_raw_signed[0];

}

/**
 * @brief This function read a single register value
 */
//HAL_StatusTypeDef ADXL_read_single_register(ADXL345_instance device, uint8_t reg, uint8_t* data) {
//	return HAL_I2C_Mem_Read(device->i2c_handle, device->address, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
//}

void ADXL_read_single_register(ADXL345* device, uint8_t reg, uint8_t* data) {
	HAL_I2C_Mem_Read(device->i2c_handle, device->address, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

/**
 * @brief This function reads multiple registers
 */
HAL_StatusTypeDef ADXL_read_multiple_registers(ADXL345* device, uint8_t reg, uint8_t* data, uint8_t length) {
	return HAL_I2C_Mem_Read(device->i2c_handle, device->address, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);
}

/**
 * @brief This function writes to a single register
 */
HAL_StatusTypeDef ADXL_write_register(ADXL345* device, uint8_t reg, uint8_t* data) {
	return HAL_I2C_Mem_Write(device->i2c_handle, device->address, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
};




























