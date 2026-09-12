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
#include "cmsis_os.h"
#include "libjpeg.h"

extern payload_state_t payload_state;
static int s_next_frame_ready = 0;

// jpeg compression variables
#define JPEG_QUALITY 60    // must be between 1 - 100 (large = more memory)

static struct jpeg_compress_struct* sp_cinfo;  // pointer to main JPEG compressor object
static FIL *sp_fil;		// stores the compressed bytes
static struct jpeg_error_mgr* sp_jerr;			// pointer to the JPEG error handler
static JSAMPROW s_jsamprow[2] = 0;				// 2 pointers to image rows
static uint32_t s_jpeg_quality = JPEG_QUALITY;	// JPEG quality setting
static uint8_t* sp_line_buffer_rgb888;			// store the RGB888 pixel data

void capture_control_start_capture() {
	myprintf("\r\nCAPTURE_CONTROL: calling camera, starting capture...\r\n");
//	camera_stop_cap();

	PAYLOAD_STATUS_T a = camera_start_cap(CAMERA_CAP_SINGLE_FRAME, frame_buffer );
	myprintf("capture_control_start_capture: %s\r\n", payload_status_to_name(a) );

}

void capture_control_stop_capture() {
	camera_stop_cap();
}

// vsync callback
static void capture_control_cb_vsync(uint32_t frame){
	camera_stop_cap();
	s_next_frame_ready = 1;

	myprintf("CAPTURE_CONTROL: Frame event callback called");
}

// libjpeg error output function
static void capture_control_libjpeg_output_message(j_common_ptr cinfo) {
	char buffer[JMSG_LENGTH_MAX];
	(*cinfo->err->format_message)(cinfo, buffer);
	myprintf("%s\r\n", buffer;)
}

// encode JPEG
static int capture_control_encodeJPEG_frame() {
	int status = 1;

	sp_cinfo = pvPortMalloc(sizeof(struct jpeg_compress_struct));
	sp_jerr = pvPortMalloc(sizeof(struct jpeg_error_mgr));
	sp_line_buffer_rgb888 = pvPortMalloc(QQVGA_WIDTH * 3);

	// check created memory pointers
	if ( (sp_cinfo == 0) || (sp_jerr == 0) || (sp_line_buffer_rgb888 == 0) ) {
		myprintf("Not enough memory\r\n");
		vPortFree(sp_cinfo);
		vPortFree(sp_jerr);
		vPortFree(sp_line_buffer_rgb888);
		return 0;
	}

	/* prepare libjpeg */
	s_jsamprow[0] = sp_line_buffer_rgb888;
	sp_cinfo->err = jpeg_std_error(sp_jerr);
	sp_cinfo->err->output_message = capture_control_libjpeg_output_message;
	jpeg_create_compress(sp_cinfo);
	jpeg_stdio_dest(sp_cinfo, sp_fil);

	/* jpeg encode setting */
	sp_cinfo->image_width = QQVGA_WIDTH;
	sp_cinfo->image_height = QQVGA_HEIGHT;
	sp_cinfo->input_components = 3;
	sp_cinfo->in_color_space = JSC_RGB;
	jpeg_set_defaults(sp_cinfo);
	jpeg_set_quality(sp_cinfo, s_jpeg_quality, TRUE);
	jpeg_start_compress(sp_cinfo, TRUE);

	/* read pixel data from display and encode line by line */



	/* finalize libjpeg */
	jpeg_finish_compress(sp_cinfo);
	jpeg_destroy_compress(sp_cinfo);

	/* free memory */
	vPortFree(sp_cinfo);
	vPortFree(sp_jerr);
	vPortFree(sp_line_buffer_rgb888);

	return status;


}

/// single snap capture function
static int capture_control_single_snapshot() {
	myprintf("CAPTURE_CONTROL: Single capture start\r\n");
	char filename = "./IMG_GEN.jpg";

	// open file for writing
	FIL fil;
	FRESULT fres;
	fres =  f_open(&fil, filename, FA_WRITE | FA_CREATE_NEW);

	if(fres == FR_OK) {
		myprintf("Image file created\r\n");
	} else {
		myprintf("Img file failed: %s\r\n",  sd_mount_status_to_name(fres));
	}

	// encode to JPEG


	// write to file



	// close file after writing
	f_close(&fil);

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

	// register callback
	camera_register_callback(0, capture_control_cb_vsync);


	// file handles
	const char* fname = "IMG.txt";
	char img_fname_tstamped[13]; // todo: verify max allowed length
	FIL fil;
	FRESULT fres;

	// image timestamping
	uint32_t tm = 0;

	for(;;) {

		/////////////////// START CAPTURE
		// myprintf("SNAPSHOT capture start\r\n");
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
