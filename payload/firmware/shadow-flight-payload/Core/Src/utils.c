/**
* @brief Helper functions to use for payload file operations
* @author Edwin M.
*/

#include "utils.h"

/**
 * @brief Compile the SD card memory ad return size in MB
 */
struct memory_stats get_sd_size(unsigned long ttl_space, unsigned long free_space) {
	uint64_t ttl =  (ttl_space * 1024) / 1E6;
	uint64_t fre =  (free_space * 1024) / 1E6;

	struct memory_stats stats;
	stats.ttl_space_MB = ttl;
	stats.free_space_MB = fre;

	return stats;

}
