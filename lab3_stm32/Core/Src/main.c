/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "softwaretimer.h"
#include "7led.h"
#include "button0.h"
#include "button1.h"
#include "button2.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  
	HAL_TIM_Base_Start_IT(&htim2);
	int tempvalue;
	int ledswitchingflag = 0;
	int mode = 1;
	int OnStartUp1 = 0;
	int OnStartUp2 = 0;
	int OnStartUp3 = 0;
	int OnStartUp4 = 1;
	int trafficlightred = 5;
	int trafficlightyellow = 2;
	int trafficlightgreen = 3;
	int status1 = 1;
	int status2 = 2;
	int value7A = trafficlightred;
	int value7B = trafficlightgreen;
	sevenledsetA(value7A%10);
	sevenledsetB(value7B%10);
	
	setTimer0(100);
	setTimer1(trafficlightred*100);
	setTimer2(trafficlightgreen*100);
	setTimer3(100);
	setTimer4(100);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	if (button0_trigger == 1)
	{
		button0_trigger = 0;
		mode++;
		if (mode > 4) mode = 1;
		if (mode == 2) OnStartUp2 = 1;
		if (mode == 3) OnStartUp3 = 1;
		if (mode == 4) OnStartUp4 = 1;
		if (mode == 1) OnStartUp1 = 1;
	}
	if (mode == 1)
	{
		if (OnStartUp1)
		{
			OnStartUp1 = 0;
			status1 = 1;
			status2 = 2;
			value7A = trafficlightred;
			value7B = trafficlightgreen;
			sevenledsetA(value7A%10);
			sevenledsetB(value7B%10);	
			
			setTimer0(100);
			setTimer1(trafficlightred*100);
			setTimer2(trafficlightgreen*100);
			setTimer3(100);
			setTimer4(100);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
		}
		if (trafficlightred == trafficlightgreen + trafficlightyellow)
		{
			if (timerflag0 == 1)
			{
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
				setTimer0(100);
			}
		}
		else 
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
		}
		switch(status1)
		{
			case 1:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
				if (timerflag1 == 1)
				{
					setTimer1(trafficlightgreen*100);
					status1 = 2;
				}
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
				if (timerflag1 == 1)
				{
					setTimer1(trafficlightyellow*100);
					status1 = 3;
				}
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
				if (timerflag1 == 1)
				{
					setTimer1(trafficlightred*100);
					status1 = 1;
				}
				break;
			default:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
				break;
		}
		switch(status2)
		{
			case 1:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
				if (timerflag2 == 1)
				{
					setTimer2(trafficlightgreen*100);
					status2 = 2;
				}
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
				if (timerflag2 == 1)
				{
					setTimer2(trafficlightyellow*100);
					status2 = 3;
				}
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
				if (timerflag2 == 1)
				{
					setTimer2(trafficlightred*100);
					status2 = 1;
				}
				break;
			default:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
				break;
		}
		if (timerflag3 == 1)
		{	
			value7A--;
			if (value7A == 0)
			{
				sevenledsetA(value7A%10);
				setTimer3(20);
			}
			if (value7A > 0)
			{
				sevenledsetA(value7A%10);
				setTimer3(100);
			}
			if (value7A < 0)
			{
				if (status1 == 2) {value7A = trafficlightgreen; sevenledsetA(value7A%10);}
				if (status1 == 3) {value7A = trafficlightyellow; sevenledsetA(value7A%10);}
				if (status1 == 1) {value7A = trafficlightred; sevenledsetA(value7A%10);}
				setTimer3(80);
			}
		}	
		if (timerflag4 == 1)
		{	
			value7B--;
			if (value7B == 0)
			{
				sevenledsetB(value7B%10);
				setTimer4(20);
			}
			if (value7B > 0)
			{
				sevenledsetB(value7B%10);
				setTimer4(100);
			}
			if (value7B < 0)
			{
				if (status2 == 2) {value7B = trafficlightgreen; sevenledsetB(value7B%10);}
				if (status2 == 3) {value7B = trafficlightyellow; sevenledsetB(value7B%10);}
				if (status2 == 1) {value7B = trafficlightred; sevenledsetB(value7B%10);}
				setTimer4(80);
			}
		}
	}
	if (mode == 2)
	{
		if (OnStartUp2)
		{
			OnStartUp2 = 0;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);

			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
			
			tempvalue = trafficlightred;
			sevenledsetA(tempvalue%10);
			ledswitchingflag = 0;
			sevenledsetB(2);
			setTimer0(50);
			setTimer1(25);
			setTimer2(50);
		}
		if (timerflag0 == 1)
		{
			//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
			setTimer0(50);
		}
		if (timerflag1 == 1)
		{
			if (ledswitchingflag == 0) 
			{
				ledswitchingflag = 1;
				sevenledsetA(tempvalue/10);
			}
			else
			{
				ledswitchingflag = 0;
				sevenledsetA(tempvalue%10);
			}
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_14);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
			setTimer1(25);
		}
		if (button1_trigger == 1)
		{
			button1_trigger = 0;
			tempvalue++;
			if (tempvalue >= 100)
			{
				tempvalue = 1;
			}
		}
		if (button1_trigger_long == 1)
		{
			if (timerflag2 == 1)
			{
				tempvalue++;
				if (tempvalue >= 100)
				{
					tempvalue = 1;
				}
				setTimer2(50);
			}
		}
		if (button2_trigger == 1)
		{
			button2_trigger = 0;
			trafficlightred = tempvalue;
		}
	}
	if (mode == 3)
	{
		if (OnStartUp3)
		{
			OnStartUp3 = 0;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
			
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
			
			tempvalue = trafficlightyellow;
			sevenledsetA(tempvalue%10);
			ledswitchingflag = 0;
			sevenledsetB(3);
			setTimer0(50);
			setTimer1(25);
			setTimer2(50);
		}
		if (timerflag0 == 1)
		{
			//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
			setTimer0(50);
		}
		if (timerflag1 == 1)
		{
			if (ledswitchingflag == 0) 
			{
				ledswitchingflag = 1;
				sevenledsetA(tempvalue/10);
			}
			else
			{
				ledswitchingflag = 0;
				sevenledsetA(tempvalue%10);
			}
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_14);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
			setTimer1(25);
		}
		if (button1_trigger == 1)
		{
			button1_trigger = 0;
			tempvalue++;
			if (tempvalue >= 100)
			{
				tempvalue = 1;
			}
		}
		if (button1_trigger_long == 1)
		{
			if (timerflag2 == 1)
			{
				tempvalue++;
				if (tempvalue >= 100)
				{
					tempvalue = 1;
				}
				setTimer2(50);
			}
		}
		if (button2_trigger == 1)
		{
			button2_trigger = 0;
			trafficlightyellow = tempvalue;
		}
	}
	if (mode == 4)
	{
		if (OnStartUp4)
		{
			OnStartUp4 = 0;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
			
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, 1);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
			
			tempvalue = trafficlightgreen;
			sevenledsetA(tempvalue%10);
			ledswitchingflag = 0;
			sevenledsetB(4);
			setTimer0(50);
			setTimer1(25);
			setTimer2(50);
		}
		if (timerflag0 == 1)
		{
			//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);
			setTimer0(50);
		}
		if (timerflag1 == 1)
		{
			if (ledswitchingflag == 0) 
			{
				ledswitchingflag = 1;
				sevenledsetA(tempvalue/10);
			}
			else
			{
				ledswitchingflag = 0;
				sevenledsetA(tempvalue%10);
			}
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_14);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
			setTimer1(25);
		}
		if (button1_trigger == 1)
		{
			button1_trigger = 0;
			tempvalue++;
			if (tempvalue >= 100)
			{
				tempvalue = 1;
			}
		}
		if (button1_trigger_long == 1)
		{
			if (timerflag2 == 1)
			{
				tempvalue++;
				if (tempvalue >= 100)
				{
					tempvalue = 1;
				}
				setTimer2(50);
			}
		}
		if (button2_trigger == 1)
		{
			button2_trigger = 0;
			trafficlightgreen = tempvalue;
		}
	}
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
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA13 PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 PB7 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	runTimer0();
	runTimer1();
	runTimer2();
	runTimer3();
	runTimer4();
	GetkeyInput0();
	GetkeyInput1();
	GetkeyInput2();
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
