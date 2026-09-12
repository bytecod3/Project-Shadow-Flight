/* USER CODE BEGIN Header */
/**
 ******************************************************************************
  * File Name          : jdata_conf.h
  * Description        : This file provides header to "jdata_conf.h" module.
  *                      It implements also file based read/write functions.
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
#include "ff.h"

/*FreeRtos Api*/
#include "cmsis_os.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*This defines the memory allocation methods.*/
#define JMALLOC   pvPortMalloc
#define JFREE     vPortFree

/*This defines the File data manager type.*/
#define JFILE            FIL

size_t read_file (FIL  *file, uint8_t *buf, uint32_t sizeofbuf);
size_t write_file (FIL  *file, uint8_t *buf, uint32_t sizeofbuf) ;

#define JFREAD(file,buf,sizeofbuf)  \
read_file (file,buf,sizeofbuf)

#define JFWRITE(file,buf,sizeofbuf)  \
write_file (file,buf,sizeofbuf)

