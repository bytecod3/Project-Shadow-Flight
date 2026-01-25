/**
 * command_engine.h
 * @author Edwin Mwiti
 * 24/01/26
 */

#ifndef INC_COMMAND_ENGINE_H_
#define INC_COMMAND_ENGINE_H_

#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
//#include "FreeRTOS.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

#define UART_TESTING_EN 					(1)			/* set to 0 to disable command testing via UART */
#define COMMAND_ENGINE_TASK_STACK_DEPTH  	(2048)
#define HAL_TX_TIMEOUT pdMS_TO_TICKS(100)

/* define our UART channel */
extern UART_HandleTypeDef command_engine_uart; /* to receive commands */
extern UART_HandleTypeDef huart6; /* to send responses to test PC */

/* command type */
extern char command[50];
extern char uart_command_response[50];

/* queue create status enum */
enum QUEUE_CREATE_STATUS {
	ALL_QUEUES_CREATED_OK = 0,
	UART_COMMAND_QUEUE_CREATE_FAILED = 1,
	UART_RESPONSE_QUEUE_CREATE_FAILED = 2,
	ALL_QUEUES_FAILED = 3
};

#if UART_TESTING_EN
	/* queues */
	extern QueueHandle_t uart_command_queue;
	extern QueueHandle_t uart_response_queue;

	/* tasks */
	extern TaskHandle_t uart_receive_command_task_handle;
	extern TaskHandle_t uart_command_processor_task_handle;
#endif


extern TaskHandle_t command_engine_processor_task_handle;
extern TaskHandle_t command_engine_tokenizer_task_handle;


/* FUNCTION PROTOTYPES */

/*
 * tasks prototypes
 */
void uart_receive_command_task(void const* args);
void uart_command_processor_task(void const* args);
void command_engine_processor_task(void const* args);
void command_engine_tokenizer_task(void const* args);

/*
 * create shared queues
 */
uint8_t command_engine_create_queues();

/* create tasks */
uint8_t command_engine_create_tasks();


/*
 * start the command engine
 */
void command_engine_start();


#endif /* INC_COMMAND_ENGINE_H_ */
