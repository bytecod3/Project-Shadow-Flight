/*
 * @file storage.c
 * @brief This file implements storage services for payload
 *
 * @date Jul 11, 2026
 * @date edwin
 *
 */

#ifndef STORAGE_STORAGE_H_
#define STORAGE_STORAGE_H_

#include "stm32f4xx_hal.h"
#include "utils.h"
#include "fatfs.h"

#define SD_CARD_MAX_RETRY_TIME 					(10000)			/* max time for exponential back-off retry, see usage */
#define MAX_RETRY_COUNT							(50)
#define IMAGE_DUMP_OPEN_RETRY_COUNTER 			(50)
#define SENTINEL_FILE_OPEN_RETRY_COUNTER 		(50)
#define SENTINEL_GUARD_MSG_LENGTH				(30)

/**
 *@brief get the minimum of 2 uint32_t numbers
 */
static inline get_min(uint32_t a, uint32_t b);

/* image dump file */
const char* image_dump_file;

/* sentinel guard file for system check */
const char* sentinel_file;

/**
 * @brief Initialise SD card
 * @return OK if successful
 */
PAYLOAD_STATUS_T init_sd_card(const char* img_file, const char* sentinel_file);

#endif /* STORAGE_STORAGE_H_ */
