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
QueueHandle_t command_execution_response_queue = NULL;

/* declare task handles */
TaskHandle_t command_engine_receive_command_task_handle = NULL;
TaskHandle_t command_engine_command_processor_task_handle = NULL;

/* initialize DMA variables */
uint16_t dma_rx_indx = 0;		/* tracks the current DMA write index */
uint16_t dma_rx_xount = 0;		/* total number of DMA bytes received */
uint16_t last_dma_index  = 0;

/* declare buffers accordingly */
#if RECEIVE_BLOCKING
	char tx_buffer[MAX_UART_COMMAND_LENGTH];
	char rx_buffer[MAX_UART_COMMAND_LENGTH];
	uint8_t ch;
#elif RECEIVE_DMA
	char tx_dma_buffer[MAX_UART_DMA_COMMAND_LENGTH];
	char rx_dma_buffer[MAX_UART_DMA_COMMAND_LENGTH];
#endif

/* Semaphores for access control */
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

	raw_command_queue = xQueueCreate(5, sizeof(cubesat_command_t));							/* store the raw DMA command buffer */
	parsed_command_queue = xQueueCreate(5, sizeof(cubesat_command_t));						/* store the parsed command in cubesat_command format */
	command_execution_response_queue = xQueueCreate(5, sizeof(command_response_type_t)); 	/* store the command execution response/result */

	if(raw_command_queue == NULL) {				/* check if queue creation OK and set the right bit index for later checking */
		queue_create_status |= (1 << 0);
	}

	if(command_execution_response_queue == NULL) {
		queue_create_status |= (1 << 1);
	}

	if(command_execution_response_queue == NULL) {
		queue_create_status |= (1 << 2);

	}

	return queue_create_status;			/* 0 -> OK, 1, commandqueue_failed, 2 -> response_queue_failed, 3, all_failed */
}

/*
 * create tasks
 * todo: check task create status
 */
uint8_t command_engine_create_tasks() {

	uint8_t task_create_status = 0;

	osThreadDef(command_engine_receive_command, command_engine_receive_command_task, osPriorityHigh, 0, COMMAND_ENGINE_TASK_STACK_DEPTH);
	command_engine_receive_command_task_handle = osThreadCreate(osThread(command_engine_receive_command), NULL);

	osThreadDef(command_engine_command_processor, command_engine_command_processor_task, osPriorityHigh, 0, COMMAND_ENGINE_TASK_STACK_DEPTH);
	command_engine_command_processor_task_handle = osThreadCreate(osThread(command_engine_command_processor), NULL);

	/* check for successful task creation */
	if(command_engine_receive_command_task_handle == NULL) {
		task_create_status |= (1 << 0);
	}

	if(command_engine_command_processor_task_handle == NULL) {
		task_create_status |= (1 << 1);
	}

	return task_create_status;

}

/*
 * receive command from UART  and send to processing
 */
void command_engine_receive_command_task(void const* args) {
	raw_cubesat_command_t received_cmd;
	char cmd_str[MAX_COMMAND_LENGTH];
	char cmd_buffer[100];

	for(;;) {
		if(xQueueReceive(raw_command_queue, &received_cmd, pdMS_TO_TICKS(MAX_RAW_CMD_RECEIVE_WAIT)) == pdTRUE) {

			/* parse command */
			sprintf(cmd_str, "%s\r\n", received_cmd.command);
			HAL_UART_Transmit(&huart6, (uint8_t*)cmd_str, strlen(cmd_str), 100);

		}

		vTaskDelay(pdMS_TO_TICKS(1));
	}
}

/* process the received command */
void command_engine_command_processor_task(void const* args) {

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
			xQueueReceive(raw_command_queue, &recvd_raw_command, pdMS_TO_TICKS(100) );

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
	HAL_UART_Transmit(&huart6, (uint8_t*)"Initializing command engine..\r\n", strlen("Initializing command engine...\r\n"), 200);

	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t*) rx_dma_buffer, MAX_UART_DMA_COMMAND_LENGTH); /* initialize DMA receive command */
	__HAL_DMA_DISABLE_IT(huart1.hdmarx, DMA_IT_HT);
	command_engine_create_queues(); /* create queues */
	command_engine_create_tasks(); /* create tasks */
	HAL_UART_Transmit(&huart6, (uint8_t*)"Command engine initialized...\r\n", strlen("Command engine initialized..\r\n"), 200);

}

