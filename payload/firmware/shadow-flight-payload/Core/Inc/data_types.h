#ifndef DAT_TYPES_H
#define DATA_TYPES_H

#include <stdint.h>
#include <stdio.h>

#define PAYLOAD_MEMORY_QUEUE_LENGTH 		(15)
#define PAYLOAD_SENSOR_DATA_QUEUE_LENGTH	(15)
#define KILOBYTE_SIZE (1024.0F)		/* divisor for converting bytes to Kilobytes  */
#define MEMORY_CHECK_FREQ (5000)  	/* after how long should we sample the memory stats */

/* store the memory data in KB */
typedef struct _payload_stats{
	float free_heap;
	float min_ever_free_heap;
	float total_heap;

} PAYLOAD_rtos_memory_stats_type_t;

/* store the board sensor data */
typedef struct _sensor_data {
	float core_temperature;
	float ntc_onboard_temperature;
} PAYLOAD_sensor_data_t ;

/* compound data struct to hold all payload data */
typedef struct payload_data {
	PAYLOAD_rtos_memory_stats_type_t mem_data;
	PAYLOAD_sensor_data_t sensor_data;
} PAYLOAD_combined_data_t;


#endif
