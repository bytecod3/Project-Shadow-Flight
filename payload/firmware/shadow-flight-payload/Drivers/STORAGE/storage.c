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
 * @brief Initialise SD card
 * @return OK if successful
 * This function will try to open and read a sentinel file
 * If read is okay a success event is returned and passed to capture control system
 * Sentinel file is created outside the cubesat, before the SD card is inserted into the system
 */
PAYLOAD_STATUS_T init_sd_card(){

	myprintf("Initializing payload SD card...\r\n");

	/* some variables for FatFS */
	FATFS FatFs;		// fat-fs handle
	FIL fil;			// file handle
	FRESULT fres;		// result after operations

	/* open the file system */
	fres = f_mount(&FatFs, "", 1);		// 1= mount now

	int retry_count = 0;
	uint32_t retry_delay = 1000;

	if(fres != FR_OK) {
	  myprintf("f_mount error (%s)", sd_mount_status_to_name(fres));

	  while(retry_count < MAX_RETRY_COUNT){

//			fres = f_mount(&FatFs, "", 1);
			myprintf("Retrying to mount SD card...\r\n");

//			if(fres == FR_OK) break;

//		if(fres != FR_OK) {
//			myprintf("Retrying to mount SD...\r\n");
//			retry_delay = get_min(1000 * 1 << retry_count, SD_CARD_MAX_RETRY_TIME); /* exponential back-off */
//			HAL_Delay(retry_delay);
//
//		} else {
//			break;
//		}

			retry_count++;
		}

	} else {
		myprintf("f_mount status (%s)", sd_mount_status_to_name(fres));
	}



//	/* get some SD card statistics */
//	DWORD free_clusters, free_sectors, total_sectors;
//	FATFS* get_free_fs;
//
//	fres = f_getfree("", &free_clusters, &get_free_fs);
//	if(fres != FR_OK) {
//	  myprintf("f_get free error (%i)\r\n", fres);
//	}
//
//	/* formula from CHANS documentation */
//	total_sectors = (get_free_fs->n_fatent - 2) * get_free_fs->csize;
//	free_sectors = free_clusters * get_free_fs->csize;
//
//	myprintf(
//		  "SD Card stats: \r\n%lu KB total drive space. \r\n%lu KB available. \r\n",
//		  total_sectors / 2,
//		  free_sectors / 2
//		  );
//
//	char mem[200] = {0};
//	struct memory_stats mem_stats = get_sd_size(total_sectors / 2, free_sectors / 2);
//	sprintf(mem,
//			"SD card space: Total: %lu MB, Free: %lu MB \r\n",
//			mem_stats.ttl_space_MB,
//			mem_stats.free_space_MB);
//
//	/* read the value of the sentinel file */
//	fres = f_open(&fil, sentinel_file, FA_READ);
//	int f_open_retry_count = 0 ;
//
//	if(fres !=FR_OK) {
//		myprintf("f_open error (%i)\r\n", fres);
//
//		while (f_open_retry_count < SENTINEL_FILE_OPEN_RETRY_COUNTER) {
//			fres = f_open(&fil, sentinel_file, FA_READ);
//			if(fres != FR_OK) break;
//
//			myprintf("Retrying to open sentinel file\r\n");
//			f_open_retry_count++;
//		}
//	}
//
//	/* try to open image dump file on SD card */
////	fres = f_open(&fil, image_dump_file, FA_READ);
////	int f_open_retry_count = 0;
////
////	if(fres != FR_OK) {
////	  myprintf("f_open error (%i)\r\n", fres);
////
////	  while(f_open_retry_count < IMAGE_DUMP_OPEN_RETRY_COUNTER) {
////		  fres = f_open(&fil, image_dump_file, FA_READ);
////		  if (fres != FR_OK) break;
////
////		  myprintf("Retrying to open image dump file...\r\n");
////		  f_open_retry_count++;
////
////	  }
////
////	  /* the file probably does not exist. Create it and retry opening */
////	  fres = f_open(&fil, image_dump_file, FA_WRITE | FA_CREATE_ALWAYS);
////	  if(fres != FR_OK) {
////		  myprintf("image file created OK.\r\n");
////	  } else {
////		  /* write a message to file */
////		  const char* genesis_msg = "Am going to store images\r\n";
////		  f_puts(genesis_msg, &fil);
////	  }
////
////	}
//
//	/* checking sentinel guard message */
//	BYTE readBuf[SENTINEL_GUARD_MSG_LENGTH];
//
//	TCHAR* res = f_gets((TCHAR*) readBuf, SENTINEL_GUARD_MSG_LENGTH, &fil);
//	if(res != 0) {
//	  myprintf("Checking Sentinel...Read string from sentinel file, contents: %s\r\b\n", readBuf);
//	} else {
//	  myprintf("f_gets error (%i)\r\n", fres);
//	}
//
//	/* close file */
//	f_close(&fil);

	myprintf("SD card initialization done\r\n");
	return PAYLOAD_STATUS_OK;
}

/**
 * @brief Return the name of the SD card mount error as a string for easy debugging
 */
const char* sd_mount_status_to_name(FRESULT f) {
	switch (f) {
		case FR_OK:
			return "SD mount success\r\n";

		case FR_DISK_ERR:
			return "A hard error occurred in the low level disk I/O layer\r\n";

		case FR_INT_ERR:
			return "Assertion failed\r\n";

		case FR_NOT_READY:
			return "The physical drive cannot work\r\n";

		case FR_NO_FILE:
			return "Could not find the file\r\n";

		case FR_NO_PATH:
			return "Could not find the path\r\n";

		case FR_INVALID_NAME:
			return "The path name format is invalid\r\n";

		case FR_DENIED:
			return "Access denied due to prohibited access or directory full\r\n";

		case FR_EXIST:
			return "Access denied due to prohibited access\r\n";

		case FR_INVALID_OBJECT:
			return "The file/directory object is invalid\r\n";

		case FR_WRITE_PROTECTED:
			return "The file/directory object is invalid\r\n";

		case FR_INVALID_DRIVE:
			return "The logical drive number is invalid \r\n";

		case FR_NOT_ENABLED:
			return "The volume has no work area\r\n";

		case FR_NO_FILESYSTEM:
			return "There is no valid FAT volume\r\n";

		case FR_MKFS_ABORTED:
			return "The f_mkfs() aborted due to any problem";

		case FR_TIMEOUT:
			return "Could not get a grant to access the volume within defined period\r\n";

		case FR_LOCKED:
			return "The operation is rejected according to the file sharing policy\r\n";

		case FR_NOT_ENOUGH_CORE:
			return "LFN working buffer could not be allocated\r\n";

		case FR_TOO_MANY_OPEN_FILES:
			return "Number of open files > _FS_LOCK\r\n";

		case FR_INVALID_PARAMETER:
			return "Given parameter is invalid\r\n";

		default:
			return "Invalid mount status \r\n";
	}
}





















