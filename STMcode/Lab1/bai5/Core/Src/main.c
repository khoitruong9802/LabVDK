/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG_One(int num);
void display7SEG_Two(int num);
unsigned int buffer = 0x0000;
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int counter = 10;
  int reset_counter = 10;
  int time_7SEG1 = 3, time_7SEG2 = 5;
  int flag1, flag2; // red = 0 yellow = 1 green = 2
  while (1)
  {
	  if (counter == 7) {
		  time_7SEG1 = 2;
	  } else if (counter == 5) {
		  time_7SEG1 = 5;
	  } else if (counter == 0) {
		  time_7SEG1 = 3;
	  }
	  if (counter == 5) {
		  time_7SEG2 = 3;
	  } else if (counter == 2) {
		  time_7SEG2 = 2;
	  } else if (counter == 0) {
		  time_7SEG2 = 5;
	  }
	  if (counter <= 0) {
		  counter = reset_counter;
	  }
	  if (counter > 5) {
		  flag1 = 0;
	  } else if (counter > 2) {
		  flag1 = 2;
	  } else {
		  flag1 = 1;
	  }
	  if (counter > 7) {
		  flag2 = 2;
	  } else if (counter > 5) {
		  flag2 = 1;
	  } else {
		  flag2 = 0;
	  }
	  if (flag1 == 0) {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
	  } else if (flag1 == 1) {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, RESET);
	  } else if (flag1 == 2) {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, SET);
	  }
	  if (flag2 == 0) {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
	  } else if (flag2 == 1) {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, RESET);
	  } else if (flag2 == 2) {
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, SET);
	  }
	  display7SEG_One(time_7SEG1);
	  display7SEG_Two(time_7SEG2);
	  time_7SEG1--;
	  time_7SEG2--;
	  counter--;
	  HAL_Delay(1000);
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB3 PB4 PB5 PB6
                           PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG_One(int num) {
	buffer = buffer & 0xFF00;
	switch (num) {
		case 0:
			buffer += 0x0040; // 0100 0000
			break;
		case 1:
			buffer += 0x0079; // 0111 1001
			break;
		case 2:
			buffer += 0x0024; // 0010 0100
			break;
		case 3:
			buffer += 0x0030; // 0011 0000
			break;
		case 4:
			buffer += 0x0019; // 0001 1001
			break;
		case 5:
			buffer += 0x0012; // 0001 0010
			break;
		case 6:
			buffer += 0x0002; // 0000 0010
			break;
		case 7:
			buffer += 0x0078; // 0111 1000
			break;
		case 8:
			buffer += 0x0000; // 0000 0000
			break;
		case 9:
			buffer += 0x0010; // 0001 0000
			break;
		default:
			break;
	}
	GPIOB->ODR = buffer;
}
void display7SEG_Two(int num) {
	buffer = buffer & 0x00FF;
	switch (num) {
		case 0:
			buffer += 0x4000; // 0100 0000
			break;
		case 1:
			buffer += 0x7900; // 0111 1001
			break;
		case 2:
			buffer += 0x2400; // 0010 0100
			break;
		case 3:
			buffer += 0x3000; // 0011 0000
			break;
		case 4:
			buffer += 0x1900; // 0001 1001
			break;
		case 5:
			buffer += 0x1200; // 0001 0010
			break;
		case 6:
			buffer += 0x0200; // 0000 0010
			break;
		case 7:
			buffer += 0x7800; // 0111 1000
			break;
		case 8:
			buffer += 0x0000; // 0000 0000
			break;
		case 9:
			buffer += 0x1000; // 0001 0000
			break;
		default:
			break;
	}
	GPIOB->ODR = buffer;
}
/* USER CODE END 4 */

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

#ifdef  USE_FULL_ASSERT
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
