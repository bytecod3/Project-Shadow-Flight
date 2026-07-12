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
static inline int get_min(uint32_t a, uint32_t b) {
	if (a < b) return a;
	return b;
}

/* image dump file */
extern const char* image_dump_file;

/* sentinel guard file for system check */
extern const char* sentinel_file;

/**
 * @brief Initialise SD card
 * @return OK if successful
 */
PAYLOAD_STATUS_T init_sd_card();

/**
 * @brief Return the name of the SD card mount error as a string for easy debugging
 */
const char* sd_mount_status_to_name(FRESULT f);

#endif /* STORAGE_STORAGE_H_ */
