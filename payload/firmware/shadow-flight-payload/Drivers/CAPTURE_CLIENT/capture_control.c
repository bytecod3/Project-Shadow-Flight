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


	// file handles
	const char* fname = "IMG.txt";
	char img_fname_tstamped[13]; // todo: verify max allowed length
	FIL fil;
	FRESULT fres;

	// image timestamping
	uint32_t tm = 0;

	for(;;) {

		/////////////////// START CAPTURE
		myprintf("SNAPSHOT capture start\r\n");
		// inspect dcmi
		myprintf("DCMI state before start capture: %d\r\n", HAL_DCMI_GetState(&hdcmi));
		capture_control_start_capture();

		tm = HAL_GetTick(); // todo append time to fname

		// create a filename dynamically
		sprintf(img_fname_tstamped, "IMG_%lu.txt", tm);

//		fres =  f_open(&fil, img_fname_tstamped, FA_CREATE_NEW);
//		if(fres == FR_OK) {
//			myprintf("copying buffer to memory\r\n");
//			fputs(frame_buffer, &fil);
//
//			myprintf("Image written\r\n");
//		} else {
//			myprintf("img capture: %s\r\n",  sd_mount_status_to_name(fres));
//		}

		// todo: close the file

		capture_control_stop_capture();

		// inspect dcmi
		myprintf("DCMI state after stop: %d\r\n", HAL_DCMI_GetState(&hdcmi));

		// STOP CAPTURE

		// run state machine logic here
		vTaskDelay(pdMS_TO_TICKS(10));

	}


}
