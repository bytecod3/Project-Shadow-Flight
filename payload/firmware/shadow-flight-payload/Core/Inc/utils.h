/**
* Helper functions to use for payload file operations
@author Edwin M.
*/

#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

/* SD card file stats in MB */
struct memory_stats{
	uint64_t ttl_space_MB;
	uint64_t free_space_MB;
};

struct memory_stats get_sd_size(unsigned long ttl_space, unsigned long free_space);

#endif
