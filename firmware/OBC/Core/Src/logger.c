

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
	if(uart_inst == &huart6) {
#if ENABLE_LOG
		#if LOG_OBC
				char uart_buffer[UART_LOG_BUFFER_SIZE] = {0};

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

		#endif
#endif

	}
}

/**
 * @fn void print_to_uart_msg(Logger*, UART_HandleTypeDef*)
 * @brief
 *
 * @param l Logger isntance
 * @param uart_inst uart to use for printing
 * @param msg message to print
 */
void print_to_uart_msg(Logger* l, UART_HandleTypeDef* uart_inst, const char* msg) {
	if(uart_inst == &huart6) {
		#if ENABLE_LOG
			if (msg != NULL) {
				HAL_UART_Transmit(&huart6, (uint8_t*)msg, strlen(msg), LOGGER_UART_PRINT_WAIT);
			}
		#endif
	}
}



/**
 * @brief This function initializes a logger instance
 * @param l Logger instance pointer
 * @param print_to_uart function pointer to print to uart function
 */
void logger_init(
		Logger* l,
		void (*print_to_uart_func)(Logger* l, UART_HandleTypeDef* uart_inst),
		void (*print_to_uart_single)(Logger* l, UART_HandleTypeDef* uart_inst, const char* msg)
) {

	l->_log_to_uart = print_to_uart_func;
	l->_log_to_uart_msg = print_to_uart_single;

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

		logger_init(l, print_to_uart, print_to_uart_msg);

		return l;
	} else {
		return 0;
	}
}


