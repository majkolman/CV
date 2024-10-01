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
static void MPU_Initialize(void);
static void MPU_Config(void);
void start_timer();
void stop_timer();
uint32_t get_time();
void start_utripanje();
void stop_utripanje();
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

DMA_HandleTypeDef dma1_struct = {0};
UART_HandleTypeDef uart;

int cas_DMA;
int cas_UART;
int bool;
#define SIZE 40*1024 // 32*1024
uint8_t source[SIZE];
uint8_t destination[SIZE];

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

	  for(int i = 0; i < SIZE; i++){
		  source[i] = i;
	  }
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  __HAL_RCC_GPIOD_CLK_ENABLE();

     GPIO_InitTypeDef initD = {0};
     initD.Pin = GPIO_PIN_3;
     initD.Mode = GPIO_MODE_OUTPUT_PP;
     initD.Pull = GPIO_NOPULL;
     initD.Speed = GPIO_SPEED_FREQ_LOW;
     HAL_GPIO_Init(GPIOD, &initD);

     __HAL_RCC_GPIOJ_CLK_ENABLE();

     GPIO_InitTypeDef initJ = {0};
     initJ.Pin = GPIO_PIN_2;
     initJ.Mode = GPIO_MODE_OUTPUT_PP;
     initJ.Pull = GPIO_NOPULL;
     initJ.Speed = GPIO_SPEED_FREQ_LOW;
     HAL_GPIO_Init(GPIOJ, &initJ);

     __HAL_RCC_GPIOI_CLK_ENABLE();

     GPIO_InitTypeDef initI = {0};
     initI.Pin = GPIO_PIN_13;
     initI.Mode = GPIO_MODE_OUTPUT_PP;
     initI.Pull = GPIO_NOPULL;
     initI.Speed = GPIO_SPEED_FREQ_LOW;
     HAL_GPIO_Init(GPIOI, &initI);

     HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
     HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_2, GPIO_PIN_SET);
     HAL_GPIO_WritePin(GPIOI, GPIO_PIN_13, GPIO_PIN_SET);

  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef init_structure;
  init_structure.Pin = GPIO_PIN_10 | GPIO_PIN_11;
  init_structure.Mode = GPIO_MODE_AF_PP;
  init_structure.Pull = GPIO_NOPULL;
  init_structure.Speed = GPIO_SPEED_FREQ_LOW;
  init_structure.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOB, &init_structure);

  __HAL_RCC_USART3_CLK_ENABLE();
  uart.Instance = USART3;
  uart.Init.BaudRate = 115200;
  uart.Init.WordLength = UART_WORDLENGTH_8B;
  uart.Init.StopBits = UART_STOPBITS_1;
  uart.Init.Parity = UART_PARITY_NONE;
  uart.Init.Mode = UART_MODE_TX_RX;
  uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  HAL_UART_Init(&uart);




  __HAL_RCC_DMA1_CLK_ENABLE();

  dma1_struct.Instance = DMA1_Stream0;
  dma1_struct.Init.Request = DMA_REQUEST_USART3_TX;
  dma1_struct.Init.Direction = DMA_MEMORY_TO_PERIPH;
  dma1_struct.Init.PeriphInc = DMA_PINC_DISABLE;
  dma1_struct.Init.MemInc = DMA_MINC_ENABLE;
  dma1_struct.Init.PeriphDataAlignment = DMA_MDATAALIGN_BYTE;
  dma1_struct.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  dma1_struct.Init.Mode = DMA_NORMAL;
  dma1_struct.Init.Priority = DMA_PRIORITY_LOW;
  dma1_struct.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  dma1_struct.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
  HAL_DMA_Init(&dma1_struct);


  __HAL_LINKDMA(&uart, hdmatx, dma1_struct);
  start_timer();
  HAL_UART_Transmit(&uart, source, sizeof(source), HAL_MAX_DELAY);
  stop_timer();
  cas_UART = get_time();
  //cas brez DMA je 3558450
  //cas z DMA je pa 3558261

  start_timer();
  HAL_UART_Transmit_DMA(&uart, source, sizeof(source));

  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 5);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);


  start_utripanje();
  while(bool == 1){
	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_3);
	  HAL_Delay(50);
  }


  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* MPU Configuration */
void DMA1_Stream0_IRQHandler(void) {
  // dma1_struct je struktura tipa DMA_HandleTypeDef
    HAL_DMA_IRQHandler(&dma1_struct);
  // preverimo da se je prenos uspešno zaključil
  if (dma1_struct.State == HAL_DMA_STATE_READY) {
    // v primeru uspešnega prenosa
    // se znajdemo tu
	  stop_timer();
	  cas_DMA = get_time();
	  stop_utripanje();
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOJ, GPIO_PIN_2, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOI, GPIO_PIN_13, GPIO_PIN_SET);
  }
}
void start_utripanje(){
	bool = 1;
}
void stop_utripanje(){
	bool = 0;
}

void start_timer() {
  __HAL_RCC_TIM2_CLK_ENABLE();
  TIM_HandleTypeDef timer = {0};
  timer.Instance = TIM2;
  timer.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer.Init.Period = 100000000;
  timer.Init.Prescaler = 64 -1;
  HAL_TIM_Base_Init(&timer);

  HAL_TIM_Base_Start(&timer);
  __HAL_TIM_SetCounter(&timer, 0);
}

void stop_timer() {
  TIM_HandleTypeDef timer = {0};
  timer.Instance = TIM2;
  HAL_TIM_Base_Stop(&timer);
}

uint32_t get_time() {
  TIM_HandleTypeDef timer = {0};
  timer.Instance = TIM2;
  return __HAL_TIM_GetCounter(&timer);
}


void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

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
