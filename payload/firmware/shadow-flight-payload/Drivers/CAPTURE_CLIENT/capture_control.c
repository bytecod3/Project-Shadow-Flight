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
#include "camera.h"

extern payload_state_t payload_state;

void capture_control_start_capture() {
	camera_stop_cap();

	PAYLOAD_STATUS_T a = camera_start_cap(CAMERA_CAP_SINGLE_FRAME, frame_buffer );
	myprintf("capture_control_start_capture: %s\r\n", payload_status_to_name(a) );

}

void capture_control_stop_capture() {
	camera_stop_cap();
}

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
	PAYLOAD_STATUS_T t = init_sd_card();
	myprintf("PAYLOAD_STATUS: %s\r\n", payload_status_to_name(t));

	// todo: transition to next state
	PAYLOAD_STATUS_T camera_init_s = camera_init();
	myprintf("PAYLOAD_STATUS: %s\r\n", payload_status_to_name(camera_init_s));

	myprintf("SNAPSHOT capture start\r\n");
	capture_control_start_capture();

	uint32_t tm = HAL_GetTick(); // todo append time to fname
	const char* fname = "img000.txt";

	FIL fil;
	FRESULT fres;

	fres =  f_open(&fil, fname, FA_WRITE);
	if(fres == FR_OK) {
		myprintf("copying buffer to memory\r\n");
		fputs(frame_buffer, &fil);

		myprintf("Image written\r\n");
	} else {
		myprintf("img capture: %s\r\n",  sd_mount_status_to_name(fres));
	}

	capture_control_stop_capture();

	for(;;) {

		// run state machine logic here
		vTaskDelay(pdMS_TO_TICKS(1500));

	}


}
