/*
 * camera.c
 *
 *  Created on: Jul 7, 2026
 *      Author: edwin
 */

#include "camera.h"



/**
 * @brief initialize camera
 * @return 1 if initialization OK
 */
PAYLOAD_STATUS_T camera_init() {
	return ov7670_init(&hdma_dcmi, &hdcmi, &hi2c2);
}

/**
 * @brief Configure camera capture mode
 * @param mode Mode to use to capture image. Continuous or single frame
 */
PAYLOAD_STATUS_T camera_config(uint32_t mode) {
	uint32_t ov7670_mode;

	switch (mode) {
	case CAMERA_MODE_QVGA_RGB565:
		ov7670_mode = CAMERA_MODE_QVGA_RGB565;
		break;
	case CAMERA_MODE_QVGA_YUV:
		ov7670_mode = CAMERA_MODE_QVGA_YUV;
		break;
	default:
		printf("Capture mode not supported\r\n");
		return PAYLOAD_STATUS_ERR;
	}

	return ov7670_config(ov7670_mode);

}

/**
 * @brief start frame capture
 * @param cap_mode Mode to use to capture image. Continuous or single frame
 * @param dest_handle where to route the frame data to
 */
PAYLOAD_STATUS_T camera_start_cap(uint32_t cap_mode, void* dest_handle) {
	uint32_t ov7670_cap_mode;

	switch(cap_mode){
	case CAMERA_CAP_CONTINOUS:
		ov7670_cap_mode = CAMERA_CAP_CONTINOUS;
		break;
	case CAMERA_CAP_SINGLE_FRAME:
		ov7670_cap_mode = CAMERA_CAP_SINGLE_FRAME;
		break;
	default:
		printf("Capture mode %ld is not supported\r\n", cap_mode);
		return PAYLOAD_STATUS_ERR;
	}

	return ov7670_start_capture(ov7670_cap_mode, dest_handle);

}

/**
 * @brief Stop frame capture
 */
PAYLOAD_STATUS_T camera_stop_cap() {
	return ov7670_stop_capture();
}

/**
 * @brief Register call-backs used for handling vertical and horizontal sync events
 */
PAYLOAD_STATUS_T camera_register_callback(void(*cbHSYnc)(uint32_t h), void (*cbVSync)(uint32_t v)) {
	ov7670_register_callback(cbHSYnc, cbVSync);
}
















