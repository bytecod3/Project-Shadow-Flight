/**
 * This file implements the command engine functions
 * @author Edwin Mwiti
 * 24/01/26
 *
 */

#include "command_engine.h"

/* declare shared queues */
QueueHandle_t raw_command_queue = NULL;
QueueHandle_t parsed_command_queue = NULL;
QueueHandle_t uart_response_queue = NULL;

/* declare task handles */
TaskHandle_t uart_receive_command_task_handle = NULL;
TaskHandle_t uart_command_processor_task_handle = NULL;

/* initialise DMA variables */
uint16_t rx_dma_indx = 0;
uint16_t rx_dma_count = 0;

/* declare buffers accordingly */
#if RECEIVE_BLOCKING
	char tx_buffer[MAX_UART_COMMAND_LENGTH];
	char rx_buffer[MAX_UART_COMMAND_LENGTH];
	uint8_t ch;
#elif RECEIVE_DMA
	char tx_dma_buffer[MAX_UART_DMA_COMMAND_LENGTH];
	char rx_dma_buffer[MAX_UART_DMA_COMMAND_LENGTH];
#endif

/* Sempahores for access control */
SemaphoreHandle_t command_queue_semaphore = NULL;

/**
 * create binary semaphores
 */
void command_engine_create_semaphores() {
	command_queue_semaphore = xSemaphoreCreateBinary();
	if(command_queue_semaphore == NULL) {
		/* todo: return sth event and log it */
	}
}

/*
 * @brief create shared queues
 */
uint8_t command_engine_create_queues() {
	uint8_t queue_create_status = 0;

	// todo use JSON structured command
	raw_command_queue = xQueueCreate(5, sizeof(rx_dma_buffer));			/* store the raw dma command buffer */
	parsed_command_queue = xQueueCreate(5, sizeof(cubesat_command));	/* store the parsed command in cubesat_command format */
	uart_response_queue = xQueueCreate(5, sizeof(uart_command_response));

	/* check if queue creation OK */
	if(raw_command_queue == NULL) {
		queue_create_status |= (1 << 0);
	}

	if(uart_response_queue == NULL) {
		queue_create_status |= (1 << 1);
	}

	// todo: check for parsed command queue creation

	/* 0 -> OK, 1, commandqueue_failed, 2 -> response_queue_failed, 3, all_failed */
	return queue_create_status;
}

/*
 * create tasks
 * todo: check task create status
 */
uint8_t command_engine_create_tasks() {

	/* initialize the DMA receive callback */

	uint8_t task_create_status = 0;

//#if UART_TESTING_EN
	osThreadDef(uart_receive_command, uart_receive_command_task, osPriorityNormal, 0, COMMAND_ENGINE_TASK_STACK_DEPTH);
	uart_receive_command_task_handle = osThreadCreate(osThread(uart_receive_command), NULL);

	osThreadDef(uart_command_processor, uart_command_processor_task, osPriorityNormal, 0, COMMAND_ENGINE_TASK_STACK_DEPTH);
	uart_command_processor_task_handle = osThreadCreate(osThread(uart_command_processor), NULL);

	/* do the check */
	if(uart_receive_command_task_handle == NULL) {
		task_create_status |= (1 << 0); // todo: create proper bit masks
	}

	if(uart_command_processor_task_handle == NULL) {
		task_create_status |= (1 << 1);
	}

//#endif

	return task_create_status;

}

#if UART_TESTING_EN

/*
 * receive command from uart and send to processing
 */
void uart_receive_command_task(void const* args) {
	char* m = "========Shadow Flight Command Engine========\r\n";
	HAL_UART_Transmit(&huart1, (uint8_t*)m, strlen(m), pdMS_TO_TICKS(100));

	/* initialize DMA receive command */
	HAL_UARTEx_ReceiveToIdle_DMA(&huart6, (uint8_t*) rx_dma_buffer, MAX_UART_DMA_COMMAND_LENGTH);
	// todo: disable DMA half interrupt task here

#endif

	for(;;) {

#if RECEIVE_BLOCKING
		/* build the received command string */
		uint8_t indx = 0;
		while(indx < MAX_UART_COMMAND_LENGTH) {
			HAL_UART_Receive(&huart6, &ch ,1 , HAL_RX_TIMEOUT);
			if(ch == '\n') break;

			rx_buffer[indx++] = ch;
		}

		/* null terminate the received character */
		rx_buffer[indx] = '\0';

		/* simulate a response */
		if(indx > 0) {
			HAL_UART_Transmit(&huart6, (uint8_t*)rx_buffer, strlen(rx_buffer), HAL_TX_TIMEOUT);
			HAL_UART_Transmit(&huart6, (uint8_t*)"\r\n", 2, 500);
		}
#elif RECEIVE_DMA

#endif

		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

/* process the received command */
void uart_command_processor_task(void const* args) {

	for(;;) {
		vTaskDelay(pdMS_TO_TICKS(1));
	}

}

/**
 * @fn void command_engine_start()
 * @brief
 *
 */
void command_engine_parse_raw_string_task(void* args) {
	char recvd_raw_command[MAX_COMMAND_LENGTH];

	for(;;) {

		/* receive from raw commands queue */
		if(xSemaphoreTake(command_queue_semaphore, pdMS_TO_TICKS(0)) == pdPASS) {
			xQueueReceive(&raw_command_queue, &recvd_raw_command, pdMS_TO_TICKS(100) );

			/* debug */
			HAL_UART_Transmit(&huart1, (uint8_t*)recvd_raw_command, rx_dma_indx, pdMS_TO_TICKS(100));

			xSemaphoreGive(command_queue_semaphore);

		}

		vTaskDelay(pdMS_TO_TICKS(1));
	}

}

/*
 * start the command engine
 */
void command_engine_start() {
	/* create semaphores and mutexes */

	/* create queues */
	command_engine_create_queues();

	/* create tasks */
	command_engine_create_tasks();

}

