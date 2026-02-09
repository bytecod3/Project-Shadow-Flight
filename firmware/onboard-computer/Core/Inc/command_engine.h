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
#define RECEIVE_DMA			(1)
#define RECEIVE_BLOCKING	(0)

#define COMMAND_ENGINE_TASK_STACK_DEPTH  	(1024)

#define MAX_UART_COMMAND_LENGTH			(100)				/* maximum data for UART blocking buffer */
#define MAX_UART_DMA_COMMAND_LENGTH		(200)				/* maximum data for UART DMA buffer */
#define MAX_COMMAND_LENGTH	(30)							/* long can a parsed command be ? */

extern uint16_t rx_dma_indx;
extern uint16_t rx_dma_count;

extern char tx_dma_buffer[];
extern char rx_dma_buffer[];

#define HAL_TX_TIMEOUT pdMS_TO_TICKS(200)
#define HAL_RX_TIMEOUT pdMS_TO_TICKS(200)

/* define our UART channel */
extern UART_HandleTypeDef command_engine_uart; /* to receive commands */
extern UART_HandleTypeDef huart6; /* to receive commands from PC */
extern UART_HandleTypeDef huart1; /* temporary debug uart1 -> reserved for GPS */

/* command type */
extern char command[50];
extern char uart_command_response[50];

/* command structure */
typedef enum {
	IMMEDIATE = 0,
	SCHEDULED = 1
} command_type_t;

typedef struct {
	command_type_t cmd_type;
	char command[MAX_COMMAND_LENGTH];
} cubesat_command;


/* queue create status enum */
enum QUEUE_CREATE_STATUS {
	ALL_QUEUES_CREATED_OK = 0,
	UART_COMMAND_QUEUE_CREATE_FAILED = 1,
	UART_RESPONSE_QUEUE_CREATE_FAILED = 2,
	ALL_QUEUES_FAILED = 3
};

#if UART_TESTING_EN
	/* queues */
	extern QueueHandle_t raw_command_queue;
	extern QueueHandle_t parsed_command_queue;
	extern QueueHandle_t uart_response_queue;

	/* tasks */
	extern TaskHandle_t uart_receive_command_task_handle;
	extern TaskHandle_t uart_command_processor_task_handle;
#endif

/* sempahores for access control */
extern SemaphoreHandle_t command_queue_semaphore;

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
 * create binary semaphores
 */
void command_engine_create_semaphores();

/*
 * create shared queues
 */
uint8_t command_engine_create_queues();

/* create tasks */
uint8_t command_engine_create_tasks();

void command_engine_parse_raw_string(char const* raw_command);

/*
 * start the command engine
 */
void command_engine_start();


#endif /* INC_COMMAND_ENGINE_H_ */
