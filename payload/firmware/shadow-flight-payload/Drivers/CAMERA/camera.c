/*
 * camera.c
 *
 *  Created on: Jul 7, 2026
 *      Author: edwin
 */

#include "camera.h"

extern DCMI_HandleTypeDef hdcmi;
extern DMA_HandleTypeDef hdma_dcmi;
extern I2C_HandleTypeDef hi2c2;

/**
 * @brief initialize camera
 * @return 1 if initialization OK
 */
PAYLOAD_STATUS_T camera_init() {
	return ov7670_init(&hdcmi, &hdma, &hi2c2);
}


