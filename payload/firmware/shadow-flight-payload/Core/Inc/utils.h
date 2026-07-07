/**
* Helper functions and enums to use for payload file operations
*
* @author Edwin M.
*
*/

#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

/* return types for various functions */
typedef enum {
	PAYLOAD_STATUS_ERR 						= 0,
	PAYLOAD_STATUS_OK 						= 1,
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

#endif
