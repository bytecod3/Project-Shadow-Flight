/**
 * This file implements the command engine functions
 * @author Edwin Mwiti
 * 24/01/26
 *
 */

#include "command_engine.h"

/* declare shared queues */
QueueHandle_t uart_command_queue = NULL;
QueueHandle_t uart_response_queue = NULL;

/* declare task handles */
TaskHandle_t uart_receive_command_task_handle = NULL;
TaskHandle_t uart_command_processor_task_handle = NULL;

/*
 * @brief create shared queues
 */
uint8_t command_engine_create_queues() {
	uint8_t queue_create_status = 0;

	// todo use JSON structured command
	uart_command_queue = xQueueCreate(5, sizeof(command));
	uart_response_queue = xQueueCreate(5, sizeof(uart_command_response));

	/* check if queue creation OK */
	if(uart_command_queue == NULL) {
		queue_create_status |= (1 << 0);
	}

	if(uart_response_queue == NULL) {
		queue_create_status |= (1 << 1);
	}

	/* 0 -> OK, 1, commandqueue_failed, 2 -> response_queue_failed, 3, all_failed */
	return queue_create_status;
}

/*
 * create tasks
 * todo: check task create status
 */
uint8_t command_engine_create_tasks() {
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
	//char rx_buffer[30];
	char tx_buffer[30];
	uint8_t d = 89;

	for(;;) {
		//HAL_UART_Receive

		/* simulate a response */
		sprintf(tx_buffer, "%d\r\n", d);
		HAL_UART_Transmit(&huart6, (uint8_t*)tx_buffer, strlen(tx_buffer), HAL_TX_TIMEOUT);

		vTaskDelay(pdMS_TO_TICKS(4));

	}
}

/* process the received command */
void uart_command_processor_task(void const* args) {

	for(;;) {
		vTaskDelay(pdMS_TO_TICKS(1));
	}

}

#endif

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

