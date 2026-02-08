

/**
 * @brief This file creates a logger for debug functions
 * @file logger.c
 * @author Edwin M
 *
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "logger.h"

/**
 * @brief receives which UART instance to print to
 * This function name is passed to init logger function
 * Default is Verbose Mode
 */
void print_to_uart(Logger* l, UART_HandleTypeDef* uart_inst){
//	HAL_UART_Transmit(uart_inst, (uint8_t*)"HELLO\r\n", strlen("HELLO\r\n"), LOGGER_UART_PRINT_WAIT);
//	if(uart_inst == &huart6) {
//		#if LOG_OBC
				char* uart_buffer[UART_LOG_BUFFER_SIZE] = {0};

				/* flush uart buffer */

				/* get heap statistics */
				heap_statistics_type_t lcl_heap_stats;
				xQueuePeek(heap_stats_queue, &lcl_heap_stats, QUEUE_FETCH_WAIT);

				/* compose buffer to send to UART */
				sprintf(uart_buffer,
						"Free heap: %ul, MinEverHeap: %ul\r\n",
						lcl_heap_stats.free_heap,
						lcl_heap_stats.minimum_ever_heap
						);

				HAL_UART_Transmit(uart_inst, (uint8_t*)uart_buffer, strlen(uart_buffer), LOGGER_UART_PRINT_WAIT);
				HAL_Delay(200);

//		#endif

//	}
}

/**
 * @brief This function initializes a logger instance
 * @param l Logger instance pointer
 * @param print_to_uart function pointer to print to uart function
 */
void logger_init(
		Logger* l,
		void (*print_to_uart_func)(Logger* l, UART_HandleTypeDef* uart_inst)
) {

	l->_log_to_uart = print_to_uart_func;

}

/**
 * @fn Logger logger_create*()
 * @brief Allocate memory for a logger struct
 *
 * @return pointer to allocated Logger memory
 */
Logger* logger_create(void) {
	Logger* l = (Logger*) malloc(sizeof(Logger));
	if(l != NULL) {

		logger_init(l, print_to_uart);

		return l;
	} else {
		return 0;
	}
}


