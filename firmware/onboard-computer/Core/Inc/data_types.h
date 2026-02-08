/*
 * data_types.h
 *
 *  Created on: Feb 5, 2026
 *      Author: emwit
 */

#ifndef INC_DATA_TYPES_H_
#define INC_DATA_TYPES_H_

#include "stdio.h"
#include "stdlib.h"

/* general defines */
#define HEAP_STATS_QUEUE_LENGTH		(10)
#define TASK_STATS_QUEUE_LENGTH		(10)


/* Hold the heap memory statistics */
typedef struct _heap_statistics {
	size_t free_heap;					///< what is the current free heap memory
	size_t minimum_ever_heap;			///< what is the lowest we have ever gone in terms of free memory
} heap_statistics_type_t;


#endif /* INC_DATA_TYPES_H_ */
