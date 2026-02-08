/*
 * @file defines.h
 * @brief Contains arbitrary definitions
 * @date Oct 8, 2025
 * @author Edwin Mwiti
 */

#ifndef INC_DEFINES_H_
#define INC_DEFINES_H_

#define SPACECRAFT_ID	 				(0x3FF)		 		///< self-assigned space-craft ID (1023)
#define FRAME_MAX_SIZE					(256)				///< maximum size of CCSDS packet

#define HAL_UART_PRINT_WAIT_TIME		(200)				///< HUART delay time for printing
#define ONBOARD_LED_BLINK_INTERVAL		(200)				///< Blink time for on-board LED

#define QUEUE_FETCH_WAIT				(0)					///< Time to wait when fetching data from queue

#endif /* INC_DEFINES_H_ */
