/**
* Helper functions and enums to use for payload operations
*
* @author Edwin M.
*
*/

#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <string.h>
#include <stm32f4xx_hal.h>
#include "cmsis_os.h"
#include <stdarg.h>

/**
 * These are defined in main.c
 */
extern UART_HandleTypeDef huart1;
extern SemaphoreHandle_t printf_mutex;

/**
 * custom return types
 */
typedef enum {
	PAYLOAD_STATUS_ERR 						= 0,
	PAYLOAD_STATUS_OK 						= 1,
	PAYLOD_STATUS_STORAGE_OK				= 2,
	PAYLOAD_STATUS_FILE_ERR 				= 3,
	PAYLOAD_STATUS_TIMEOUT 					= 4,
	PAYLOAD_STATUS_MEMORY_FAILURE 			= 5
} PAYLOAD_STATUS_T;

/* SD card file stats in MB */
struct memory_stats{
	uint64_t ttl_space_MB;
	uint64_t free_space_MB;
};

struct memory_stats get_sd_size(unsigned long ttl_space, unsigned long free_space);

/**
 * @brief redirect PrintF
 */
void myprintf(const char* fmt, ...);


#endif

