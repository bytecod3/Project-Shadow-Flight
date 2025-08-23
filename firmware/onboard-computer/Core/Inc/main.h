/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_BTN_Pin GPIO_PIN_14
#define USER_BTN_GPIO_Port GPIOC
#define USER_LED_GREEN_Pin GPIO_PIN_15
#define USER_LED_GREEN_GPIO_Port GPIOC
#define GPS_ACTIVATE_Pin GPIO_PIN_0
#define GPS_ACTIVATE_GPIO_Port GPIOA
#define GPS_PPS_Pin GPIO_PIN_1
#define GPS_PPS_GPIO_Port GPIOA
#define MAG_INT_Pin GPIO_PIN_3
#define MAG_INT_GPIO_Port GPIOA
#define FLASH_CS_Pin GPIO_PIN_4
#define FLASH_CS_GPIO_Port GPIOA
#define MPU_INT_Pin GPIO_PIN_0
#define MPU_INT_GPIO_Port GPIOB
#define ADCS_BOARD_DETECT_Pin GPIO_PIN_1
#define ADCS_BOARD_DETECT_GPIO_Port GPIOB
#define EPS_BOARD_DETECT_Pin GPIO_PIN_2
#define EPS_BOARD_DETECT_GPIO_Port GPIOB
#define WATCHDOG_INT_Pin GPIO_PIN_15
#define WATCHDOG_INT_GPIO_Port GPIOB
#define GPS_RX_Pin GPIO_PIN_9
#define GPS_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_10
#define GPS_TX_GPIO_Port GPIOA
#define USART_DEBUG_TX_Pin GPIO_PIN_11
#define USART_DEBUG_TX_GPIO_Port GPIOA
#define USART_DBG_RX_Pin GPIO_PIN_12
#define USART_DBG_RX_GPIO_Port GPIOA
#define COMMS_BOARD_DETECT_Pin GPIO_PIN_5
#define COMMS_BOARD_DETECT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
