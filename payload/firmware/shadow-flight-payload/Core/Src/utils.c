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

/**
 * @brief redirect PrintF
 */
void myprintf(const char* fmt, ...) {

	xSemaphoreTake(printf_mutex, portMAX_DELAY);
	{
		static char buffer[350];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buffer, sizeof(buffer), fmt, args);
		va_end(args);

		int len = strlen(buffer);
		HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, 200); // TODO define delay in header

	}
	xSemaphoreGive(printf_mutex);

}

/* translate payload status to name */
const char* payload_status_to_name(PAYLOAD_STATUS_T t) {
	switch (t) {
		case PAYLOAD_STATUS_ERR:
			return "PAYLOAD_STATUS_ERR\r\n";
		case PAYLOAD_STATUS_OK:
			return "PAYLOAD_STATUS_OK\r\n";
		case PAYLOD_STATUS_STORAGE_OK:
			return "PAYLOD_STATUS_STORAGE_OK\r\n";
		case PAYLOAD_STATUS_FILE_ERR:
			return "PAYLOAD_STATUS_FILE_ERR\r\n";
		case PAYLOAD_STATUS_TIMEOUT:
			return "PAYLOAD_STATUS_TIMEOUT\r\n";
		case PAYLOAD_STATUS_MEMORY_FAILURE:
			return "PAYLOAD_STATUS_MEMORY_FAILURE\r\n";
		default:
			return "Invalid PAYLOAD status\r\n";
	}
}

