/*
 * @file storage.c
 * @brief This file implements storage services for payload
 *
 * @date Jul 11, 2026
 * @date edwin
 *
 */


#include "storage.h"

/* image dump file */
const char* image_dump_file = "img_dump.txt";

/* sentinel guard file for system check */
const char* sentinel_file = "sentinel.txt";

/**
 *@brief get the minimum of 2 uint32_t numbers
 */
static inline get_min(uint32_t a, uint32_t b) {
	if (a < b) return a;
	return b;
}

/**
 * @brief Initialise SD card
 * @return OK if successful
 * This function will try to open and read a sentinel file
 * If read is okay a success event is returned and passed to capture control system
 * Sentinel file is created outside the cubesat, before the SD card is inserted into the system
 */
PAYLOAD_STATUS_T init_sd_card(const char* img_file, const char* sentinel_file){

	myprintf("initializing payload SD card...\r\n");

	/* some variables for FatFS */
	FATFS FatFs;		// fat-fs handle
	FIL fil;			// file handle
	FRESULT fres;		// result after operations

	/* open the file system */
	fres = f_mount(&FatFs, "", 1);		// 1= mount now

	int retry_count = 0;
	uint32_t retry_delay = 1000;

	if(fres != FR_OK) {
	  myprintf("f_mount error (%i)\r\n", fres);

	  while(retry_count < MAX_RETRY_COUNT){

		fres = f_mount(&FatFs, "", 1);

		if(fres != FR_OK) {
			myprintf("Retrying to mount SD...\r\n");
			retry_delay = get_min(1000 * 1 << retry_count, SD_CARD_MAX_RETRY_TIME); /* exponential back-off */
			HAL_Delay(retry_delay);

		} else {
			break;
		}

		retry_count++;

		}

	}

	/* get some SD card statistics */
	DWORD free_clusters, free_sectors, total_sectors;
	FATFS* get_free_fs;

	fres = f_getfree("", &free_clusters, &get_free_fs);
	if(fres != FR_OK) {
	  myprintf("f_get free error (%i)\r\n", fres);
	  //while(1);
	}

	/* formula from CHANS documentation */
	total_sectors = (get_free_fs->n_fatent - 2) * get_free_fs->csize;
	free_sectors = free_clusters * get_free_fs->csize;

	myprintf(
		  "SD Card stats: \r\n%lu KiB total drive space. \r\n%lu KiB available. \r\n",
		  total_sectors / 2,
		  free_sectors / 2
		  );

	char mem[200] = {0};
	struct memory_stats mem_stats = get_sd_size(total_sectors / 2, free_sectors / 2);
	sprintf(mem,
			"SD card space: Total: %lu MB, Free: %lu MB \r\n",
			mem_stats.ttl_space_MB,
			mem_stats.free_space_MB);

	/* read the value of the sentinel file */
	fres = f_open(&fil, sentinel_file, FA_READ);
	int f_open_retry_count = 0 ;

	if(fres !=FR_OK) {
		myprintf("f_open error (%i)\r\n", fres);

		while (f_open_retry_count < SENTINEL_FILE_OPEN_RETRY_COUNTER) {
			fres = f_open(&fil, sentinel_file, FA_READ);
			if(fres != FR_OK) break;

			myprintf("Retrying to open sentinel file\r\n");
			f_open_retry_count++;
		}
	}

	/* try to open image dump file on SD card */
//	fres = f_open(&fil, image_dump_file, FA_READ);
//	int f_open_retry_count = 0;
//
//	if(fres != FR_OK) {
//	  myprintf("f_open error (%i)\r\n", fres);
//
//	  while(f_open_retry_count < IMAGE_DUMP_OPEN_RETRY_COUNTER) {
//		  fres = f_open(&fil, image_dump_file, FA_READ);
//		  if (fres != FR_OK) break;
//
//		  myprintf("Retrying to open image dump file...\r\n");
//		  f_open_retry_count++;
//
//	  }
//
//	  /* the file probably does not exist. Create it and retry opening */
//	  fres = f_open(&fil, image_dump_file, FA_WRITE | FA_CREATE_ALWAYS);
//	  if(fres != FR_OK) {
//		  myprintf("image file created OK.\r\n");
//	  } else {
//		  /* write a message to file */
//		  const char* genesis_msg = "Am going to store images\r\n";
//		  f_puts(genesis_msg, &fil);
//	  }
//
//	}

	/* checking sentinel guard message */
	BYTE readBuf[SENTINEL_GUARD_MSG_LENGTH];

	TCHAR* res = f_gets((TCHAR*) readBuf, 30, &fil);
	if(res != 0) {
	  myprintf("Read string from sentinel file, contents: %s\r\b\n", readBuf);
	} else {
	  myprintf("f_gets error (%i)\r\n", fres);
	}

	/* close file */
	f_close(&fil);
}

