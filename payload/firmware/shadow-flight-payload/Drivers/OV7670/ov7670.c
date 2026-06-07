/*
 * @file ov7670.c
 *
 * @date: Jun 5, 2026
 * @author: edwin
 */


#include <stdio.h>
#include <main.h>
#include <ov7670.h>
#include "stm32f4xx_hal.h"

#define QVGA_WIDTH 			(320)
#define QVGA_HEIGHT 		(240)

static DCMI_HandleTypeDef* sp_hdcmi;
static DMA_HandleTypeDef* sp_hdma_dcmi;
static I2C_HandleTypeDef* sp_hi2c;

static uint32_t s_dest_address_continous_mode;
static void(*s_cb_hsync)(uint32_t h);
static void(*s_cb_vsync)(uint32_t h);
static uint32_t s_current_h;
static uint32_t s_current_v;

/**
 * @brief write 8 bit data to camera module
 */
HAL_StatusTypeDef ov7670_i2c_write(uint8_t reg_addr, uint8_t data) {

	HAL_StatusTypeDef s;
	do {
		s = HAL_I2C_Mem_Write(
				sp_hi2c,
				OV7670_SLAVE_W_ADDRESS,
				reg_addr,
				I2C_MEMADD_SIZE_8BIT,
				&data,
				1,
				100
				);

	} while (s != HAL_OK && 0); // todo: add retry logic

	return s;
}

/**
 * @brief read 8-bit data from camera module
 */
HAL_StatusTypeDef ov7670_i2c_read(uint8_t reg_addr, uint8_t* data) {
	HAL_StatusTypeDef s;

	do {
		s = HAL_I2C_Mem_Read(
				sp_hi2c,
				OV7670_SLAVE_ADDRESS,
				reg_addr,
				I2C_MEMADD_SIZE_8BIT,
				data,
				1,
				1000

		);

		s = HAL_I2C_Master_Transmit(
				sp_hi2c,
				OV7670_SLAVE_ADDRESS,
				&reg_addr,
				1,
				100
				);

		s |= HAL_I2C_Master_Receive(
				sp_hi2c,
				OV7670_SLAVE_ADDRESS,
				reg_addr,
				I2C_MEMADD_SIZE_8BIT,
				100);

	} while (s != HAL_OK && 0); // todo: add definite retry logic

	return s;
}

/* function definitions */
void ov7670_init(DCMI_HandleTypeDef* p_hdcmi, DCMI_HandleTypeDef* p_hdma_dcmi, I2C_HandleTypeDef* p_hi2c) {
	sp_hdcmi = p_hdcmi;
	sp_hdma_dcmi = p_hdma_dcmi;
	sp_hi2c = p_hi2c;

	s_dest_address_continous_mode = 0;

	/* wake up the camera */
	HAL_GPIO_WritePin(CAM_RESET_GPIO_Port, CAM_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(CAM_RESET_GPIO_Port, CAM_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(100);



}





