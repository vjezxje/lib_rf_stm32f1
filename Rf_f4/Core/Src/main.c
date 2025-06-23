/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "nrf24l01p.h"
#include "nrf24l01.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define TRANSMITTER
//#define RECEIVER

#define RECEIVER_2
//#define TRANSMITTER_2

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t rx_data[NRF24L01P_PAYLOAD_LENGTH] = {0};
uint8_t tx_data[NRF24L01P_PAYLOAD_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7};

#ifdef RECEIVER_2
uint8_t rx_data[32];
uint8_t RxNumber = 5;

#endif

#ifdef TRANSMITTER_2
uint8_t tx_data[32] = "Hello World\n";
#endif
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
  MX_SPI1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
	#ifdef RECEIVER
		nrf24l01p_rx_init(2500, _1Mbps);
	#endif

	#ifdef TRANSMITTER
		nrf24l01p_tx_init(2500, _1Mbps);
    #endif

	#ifdef RECEIVER_2
		uint8_t RxAddress0[5] = {0x78, 0x78, 0x78, 0x78, 0x78};
		uint8_t RxAddress1[5] = {0xB3, 0xB4, 0xB5, 0xB6, 0xCD};
		uint8_t RxAddress2 = 0xF3;
		uint8_t RxAddress3 = 0xF2;
		uint8_t RxAddress4 = 0xF4;
		uint8_t RxAddress5 = 0xF1;

		NRF24L01_RxInit(50, NRF24L01_DATA_RATE_1MBPS, 2000);
		NRF24L01_SetRxAddress(NRF24L01_RX_ADDRESS_P0, RxAddress0, 2000);
		NRF24L01_SetRxAddress(NRF24L01_RX_ADDRESS_P1, RxAddress1, 2000);
		NRF24L01_SetRxAddress(NRF24L01_RX_ADDRESS_P2, &RxAddress2, 2000);
		NRF24L01_SetRxAddress(NRF24L01_RX_ADDRESS_P3, &RxAddress3, 2000);
		NRF24L01_SetRxAddress(NRF24L01_RX_ADDRESS_P4, &RxAddress4, 2000);
		NRF24L01_SetRxAddress(NRF24L01_RX_ADDRESS_P5, &RxAddress5, 2000);

	#endif
	#ifdef TRANSMITTER_2
		uint8_t TxAddress1[5] = {0xB3, 0xB4, 0xB5, 0xB6, 0xCD};

		NRF24L01_TxInit(50, NRF24L01_DATA_RATE_1MBPS, 2000);

		NRF24L01_SetTxAddress(TxAddress1, 2000);
	#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		#ifdef RECEIVER
		  // Nothing to do
	  	  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		#endif
		#ifdef TRANSMITTER

		  for(int i= 0; i < 8; i++)
		  {
			  tx_data[i]++;
		  }
		  nrf24l01p_tx_transmit(tx_data);
		  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		#endif
///////////////////////////////////////////////////////
		#ifdef RECEIVER_2

		#endif
		#ifdef TRANSMITTER_2
				NRF24L01_TxTransmit(tx_data, 2000);
		#endif
		HAL_Delay(100);
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == NRF24L01P_IRQ_PIN_NUMBER)
	{
		#ifdef RECEIVER
				nrf24l01p_rx_receive(rx_data);
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		#endif

		#ifdef TRANSMITTER
				nrf24l01p_tx_irq();
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		#endif
	}
	#ifdef RECEIVER_2
		if(GPIO_Pin == NRF24L01_IRQ_GPIO_PIN)
		{
			NRF24L01_RxReceive(rx_data, &RxNumber, 4000);
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		}
	#endif
	#ifdef TRANSMITTER_2
		if(GPIO_Pin == NRF24L01_IRQ_GPIO_PIN)
		{
			NRF24L01_TxIRQHandle(2000);
		}
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_14);
	#endif
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
