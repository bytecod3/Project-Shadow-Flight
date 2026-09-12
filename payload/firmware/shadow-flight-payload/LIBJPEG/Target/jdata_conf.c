/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * File Name          : jdata_conf.c
  * Description        : This file implements LibJPEG file based read/write functions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
**/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

/*FatFS is chosen for File storage*/
#include "jdata_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

size_t read_file (FIL  *file, uint8_t *buf, uint32_t sizeofbuf)
{
static size_t BytesReadfile ;
f_read (file, buf , sizeofbuf, &BytesReadfile);
return BytesReadfile;
}

size_t write_file (FIL  *file, uint8_t *buf, uint32_t sizeofbuf)
{
static size_t BytesWritefile;
f_write (file, buf , sizeofbuf, &BytesWritefile);
return BytesWritefile;
}

