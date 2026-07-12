/*
 * @file capture_control.c
 * @brief control image capture sequences and process
 *
 * @date Jul 10, 2026
 * @author edwin
 */

#include "state_machine.h"
#include "utils.h"
#include "storage.h"

extern payload_state_t payload_state;

/**
 * @brief Starts capture control system
 * This function is declared as an extern in main.c, and implemented here
 * for modularization
 */
void capture_control_task(void* argument){

	// check it in standby mode
	const char* s = payload_state_to_name(payload_state);
	myprintf("%s\r\n", s);

	/* =========== subsystem checks =============== */
	init_sd_card();

	// transition to next state

	for(;;) {

		// run state machine logic here
		vTaskDelay(pdMS_TO_TICKS(1500));

	}


}
