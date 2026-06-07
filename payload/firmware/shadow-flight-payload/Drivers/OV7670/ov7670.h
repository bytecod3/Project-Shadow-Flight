/*
 * @file ov7670.h
 *
 * @date: Jun 5, 2026
 * @author: edwin
 */

#ifndef OV7670_OV7670_H_
#define OV7670_OV7670_H_

#include <ov7670_regs.h>

#define OV7670_SLAVE_ADDRESS (0x42)  /* 42 for write */

/* settings and camera commands */
#define RESET_COMMAND (0x80)

void ov7670_init(DCMI_HandleTypeDef* p_hdcmi, DCMI_HandleTypeDef* p_hdma_dcmi, I2C_HandleTypeDef* p_hi2c);

void ov7670_config(uint32_t mode);

void ov7670_start_capture(uint32_t cap_mode, uint32_t dest_address);

void ov7670_stop_capture();

void ov7670_register_callback(void (*cb_hsync)(uint32_t h), void(*cb_vsync)(uint32_t v));

/* i2c functions */
HAL_StatusTypeDef ov7670_i2c_write(uint8_t reg_addr, uint8_t data);

HAL_StatusTypeDef ov7670_i2c_read(uint8_t reg_addr, uint8_t* data);

#endif /* OV7670_OV7670_H_ */
