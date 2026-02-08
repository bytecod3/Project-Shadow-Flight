

/**
 * @brief This file creates a logger for debug functions
 * @file logger.c
 * @author Edwin M
 *
 */

struct Logger{
	void (*print_to_uart)(void);
	void (*print_to_file)(void);
};

