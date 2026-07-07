/*
 * camera.h
 *
 *  Created on: Jul 7, 2026
 *      Author: edwin
 */

#ifndef CAMERA_CAMERA_H_
#define CAMERA_CAMERA_H_

#include "utils.h"
#include "ov7670.h"

#define CAMERA_MODE_QVGA_RGB565 0
#define CAMERA_MODE_QVGA_YUV 1

#define CAMERA_CAP_CONTINOUS	0
#define CAMERA_CAP_SINGLE_FRAME	1

PAYLOAD_STATUS_T camera_init();
PAYLOAD_STATUS_T camera_config(uint32_t mode);
PAYLOAD_STATUS_T camera_start_cap(uint32_t cap_mode, void* dest_handle);
PAYLOAD_STATUS_T camera_stop_cap();
PAYLOAD_STATUS_T camera_register_callback(void(*cbHSYnc)(uint32_t h), void (*cbVSync)(uint32_t v));


#endif /* CAMERA_CAMERA_H_ */
