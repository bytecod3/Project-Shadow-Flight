/**
 * @brief This file creates a logger for debug functions
 * @file logger.h
 * @author Edwin M
 *
 */
#ifndef INC_LOGGER_H_
#define INC_LOGGER_H_

struct Logger{
	void print_to_uart();
	void print_to_file();
};


#endif /* INC_LOGGER_H_ */
