/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  * 496e7370697265642062792041706f6c6c6f20383a
  *
  * 496e2074686520626567696e6e696e6720476f64206372656174656420
  * 7468652068656176656e20616e64207468652065617274682ea416e642074686520
  * 65617274682077617320776974686f757420666f726d2c20616e6420766f69643b20616e6420
  * 6461726b6e657373207761732075706f6e207468652066616365206f6620
  * 74686520646565702e20416e642074686520537069726974206f6620476f6420
  * 6d6f7665642075706f6e207468652066616365206f6620
  * 746865207761746572732ea416e6420476f6420736169642c204c657420
  * 7468657265206265206c696768743a20616e6420746865726520
  * 776173206c696768742ea416e6420476f64207361772074686520
  * 6c696768742c20746861742069742077617320676f6f643a20616e6420
  * 476f64206469766964656420746865206c696768742066726f6d2074686520
  * 6461726b6e6573732e
  *
  * 416e6420476f642063616c6c656420746865206c69676874204461792c20616e6420
  * 746865206461726b6e6573732068652063616c6c6564204e696768742e20416e6420
  * 746865206576656e696e6720616e6420746865206d6f726e696e67207765726520
  * 746865206669727374206461792ea416e6420476f6420736169642c204c657420
  * 74686572652062652061206669726d616d656e7420696e20746865206d6964737420
  * 6f6620746865207761746572732c20616e64206c65742069742064697669646520
  * 746865207761746572732066726f6d20746865207761746572732ea416e6420
  * 476f64206d61646520746865206669726d616d656e742c20616e64206469766964656420
  * 74686520776174657273207768696368207765726520756e6465722074686520
  * 6669726d616d656e742066726f6d207468652077617465727320776869636820
  * 776572652061626f766520746865206669726d616d656e743a20616e6420697420
  * 77617320736f2ea416e6420476f642063616c6c65642074686520
  * 6669726d616d656e742048656176656e2e20416e642074686520
  * 6576656e696e6720616e6420746865206d6f726e696e67207765726520
  * 746865207365636f6e64206461792e
  *
  * 416e6420476f6420736169642c204c6574207468652077617465727320
  * 756e646572207468652068656176656e20626520676174686572656420
  * 746f67657468657220756e746f206f6e6520706c6163652c20616e6420
  * 6c65742074686520647279206c616e64206170706561723a20616e6420
  * 69742077617320736f2ea416e6420476f642063616c6c65642074686520
  * 647279206c616e642045617274683b20616e642074686520676174686572696e6720
  * 746f676574686572206f6620746865207761746572732063616c6c656420686520
  * 536561733a20616e6420476f642073617720746861742069742077617320676f6f642e
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "defines.h"
#include "filter_config.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;

osThreadId defaultTaskHandle;

/* USER CODE BEGIN PV */
osThreadId x_task_create_tasks_tsk_handle;
osThreadId x_task_dummy_data_tsk_handle;
osThreadId x_task_control_onboard_led_tsk_handle;
osThreadId x_task_control_onboard_buzzer_tsk_handle;
osThreadId x_task_get_watchdog_tsk_handle;
osThreadId x_task_core_fsm_monitor_tsk_handle;
osThreadId x_task_get_heap_memory_stats_tsk_handle;
osThreadId x_task_get_task_stats_tsk_handle;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */

/**
 * @fn void x_task_dummy_data(const void*)
 * @brief This function generates a fake dummy data values
 *
 * @param argument
 */
void x_task_dummy_data(void const* argument);

/**
 * @fn void x_task_create_tasks(const void*)
 * @brief This function creates all the tasks then self-deletes
 *
 * @param argument parameter to the task
 */
void x_task_create_tasks(void const* argument);

/**
 * @fn void x_task_control_onboard_led(const void*)
 * @brief This task controls the on-board LEDs depending on the state
 *
 * @param argument parameter to the task
 */
void x_task_control_onboard_led(void const* argument);

/**
 * @fn void x_task_control_onboard_buzzer(const void*)
 * @brief
 *
 * @param argument parameter to the task
 */
void x_task_control_onboard_buzzer(void const* argument);

/**
 * @fn void x_task_get_watchdog(const void*)
 * @brief
 *
 * @param argument
 */
void x_task_get_watchdog(void const* argument);

/**
 * @fn void x_task_core_fsm_monitor(const void*)
 * @brief This task monitors the current state of the device and calls relevant action
 *
 * @param argument
 */
void x_task_core_fsm_monitor(void const* argument);

/**
 * @fn void x_task_get_heap_memory_stats(const void*)
 * @brief This task collects the heap memory usage statistics
 *
 * @param argument parameter to the task
 */
void x_task_get_heap_memory_stats(void const* argument);

/**
 * @fn void x_task_get_task_stats(const void*)
 * @brief This task gets information about the tasks currently running
 *
 * @param argument
 */
void x_task_get_task_stats(void const* argument);

/**
 * @fn void x_task_read_acceleration(const void*)
 * @brief Thif task read the pure acceleration from the accelerometer
 *
 * @param argument parameter to the task
 */
void x_task_read_acceleration(void const* argument);

/**
 * @fn void x_task_read_imu(const void*)
 * @brief This task reads the inertial measurement unit
 *
 * @param argument
 */
void x_task_read_imu(void const* argument);

/**
 * @fn void x_task_read_magnetometer(const void*)
 * @brief This task reads the magnetometer/compass
 *
 * @param argument
 */
void x_task_read_magnetometer(void const* argument);

/**
 * @fn void x_task_read_temperature(const void*)
 * @brief This function reads the temperature from the onboard temperature sensor
 * on the OBC
 *
 * @param argument
 */
void x_task_read_temperature(void const* argument);

/**
 * @fn void x_task_sun_sensors(const void*)
 * @brief This function reads the light value from the sun sensors
 *
 * @param argument
 */
void x_task_sun_sensors(void const* argument);

/**
 * @fn void x_task_read_GPS(const void*)
 * @brief This function reads the GPS coordinates
 *
 * @param argument
 */
void x_task_read_GPS(void const* argument);

/**
 * @fn void x_task_data_dispatcher(const void*)
 * @brief This task sends the data to relevant queues
 *
 * @param argument
 */
void x_task_data_dispatcher(void const* argument);

/**
 * @fn void x_task_sensor_queue_notify(const void*)
 * @brief
 *
 * @param argument
 */
void x_task_sensor_queue_notify(void const* argument);

/**
 * @fn void x_task_kalman_filter(const void*)
 * @brief This task filters the sensor data using Kalman Filter
 *
 * @param argument
 */
void x_task_kalman_filter(void const* argument);

/**
 * @fn void x_task_median_filter(const void*)
 * @brief This function filters data using median filter
 *
 * @param argument
 */
void x_task_median_filter(void const* argument);

/**
 * @fn void x_task_moving_avg_filter(const void*)
 * @brief This task filters data using the moving average filter
 *
 * @param argument
 */
void x_task_moving_avg_filter(void const* argument);

/**
 * @fn void x_task_complementary_filter(const void*)
 * @brief This task filters data using complementary filter
 *
 * @param argument
 */
void x_task_complementary_filter(void const* argument);

/**
 * @fn void x_task_compose_telemetry_packet(const void*)
 * @brief This task arranged the telemetry data for transmission to ground
 *
 * @param argument
 */
void x_task_compose_telemetry_packet(void const* argument);

/**
 * @fn void x_task_transmit_telemetry(const void*)
 * @brief This task transmits telemetry packet to ground station
 *
 * @param argument
 */
void x_task_transmit_telemetry(void const* argument);

/**
 * @fn void x_task_check_fault(const void*)
 * @brief This task contantly monitors relevant thresholds to check for faults
 *
 * @param argument
 */
void x_task_check_fault(void const* argument);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */

  osThreadDef(dumm_data, x_task_dummy_data, osPriorityNormal, 0, 1024);			/// create all tasks
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);


  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USER_LED_GREEN_GPIO_Port, USER_LED_GREEN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPS_ACTIVATE_Pin|FLASH_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BTN_Pin */
  GPIO_InitStruct.Pin = USER_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USER_BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USER_LED_GREEN_Pin */
  GPIO_InitStruct.Pin = USER_LED_GREEN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USER_LED_GREEN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : GPS_ACTIVATE_Pin FLASH_CS_Pin */
  GPIO_InitStruct.Pin = GPS_ACTIVATE_Pin|FLASH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GPS_PPS_Pin MAG_INT_Pin */
  GPIO_InitStruct.Pin = GPS_PPS_Pin|MAG_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : MPU_INT_Pin ADCS_BOARD_DETECT_Pin EPS_BOARD_DETECT_Pin WATCHDOG_INT_Pin
                           COMMS_BOARD_DETECT_Pin */
  GPIO_InitStruct.Pin = MPU_INT_Pin|ADCS_BOARD_DETECT_Pin|EPS_BOARD_DETECT_Pin|WATCHDOG_INT_Pin
                          |COMMS_BOARD_DETECT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
