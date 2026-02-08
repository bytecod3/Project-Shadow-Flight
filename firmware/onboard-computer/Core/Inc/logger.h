/**
 * @brief This file creates a logger
 * @file logger.h
 * @author Edwin M
 * @date 8th February 2026
 *
 */
#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

#include "stm32f4xx_hal.h"
#include "defines.h"
#include "data_types.h"
#include "string.h"

/* enable disable logging from various subsystems */
#define ENABLE_LOG						(1) 				///< set to 1 to enable global logging
#define LOG_OBC							(1)					///< set to 1 to enable debugging from OBC
#define LOG_EPS							(0)
#define LOG_COMMS						(0)
#define LOG_ADCU						(0)


#define UART_LOG_BUFFER_SIZE			(50)				///< UART buffer length for printing items to UART
#define LOGGER_UART_PRINT_WAIT			(100)				///< how long to wait during blocking UART debug

/* Define the USART you will use for debugging here */
extern UART_HandleTypeDef huart6;

/**
 * @brief This struct represents a Logger instance
 */
typedef struct Logger Logger;
struct Logger {
	void (*_log_to_uart)(Logger* l, UART_HandleTypeDef* uart_inst);		///< prints to UART
	void (*_log_to_uart_msg)(Logger* l, UART_HandleTypeDef* uart_inst, const char* msg); ///< print a single message to uart

};

/**
 * @brief receives which UART instance to print to
 * This function name is passed to init logger function
 */
void print_to_uart(Logger* l, UART_HandleTypeDef* uart_inst);

/**
 * @fn void print_to_uart_msg(Logger*, UART_HandleTypeDef*)
 * @brief
 *
 * @param l Logger isntance
 * @param uart_inst uart to use for printing
 * @param msg message to print
 */
void print_to_uart_msg(Logger* l, UART_HandleTypeDef* uart_inst, const char* msg);

/**
 * @brief Constructor. This function initializes a logger instance
 * @param l Logger instance pointer
 * @param print_to_uart function pointer to print to uart function
 */
void logger_init(
		Logger* l,
		void (*print_to_uart_func)(Logger* l, UART_HandleTypeDef* uart_inst),
		void (*print_to_uart_single)(Logger* l, UART_HandleTypeDef* uart_inst, const char* msg)
);


/**
 * @fn Logger logger_create*()
 * @brief Allocate memory for a logger struct
 *
 * @return pointer to allocated Logger memory
 */
Logger* logger_create(void);


#endif /* INC_LOGGER_H_ */
