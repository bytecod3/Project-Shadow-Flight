#ifndef DAT_TYPES_H
#define DATA_TYPES_H

#include "data_types.h"
#include <stdint.h>
#include <stdio.h>

/* store the memory type data */
typedef struct {
	size_t free_heap;
	size_t min_ever_free_heap;
	size_t total_heap;

} PAYLOAD_rtos_memory_stats_type_t;

/* store the board sensor data */
typedef struct {
	float core_temperature;
	float ntc_onboard_temperature;
} PAYLOAD_sensor_data_t ;

#endif
