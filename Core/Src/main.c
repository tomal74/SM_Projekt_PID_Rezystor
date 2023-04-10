/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "onewire.h"
#include "ds18b20.h"

/* Include ARM math */
#include "arm_math.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* Choose PID parameters */
#define PID_PARAM_KP        100            /* Człon proporcjonalny - wzmocnienie */
#define PID_PARAM_KI        0.025        /* Człon całkujący - wzmocnienie*/
#define PID_PARAM_KD        20            /* Człon różniczkujący - wzmocnienie */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* Timery programowe */
uint16_t Timer1, Timer2;
float temperature;
/* Wypełnieienie sygnału sterującego - PWM */
uint16_t PWM_Duty;

/* bufor danych do transmisji danych z komputerem - uart3 */
uint8_t string_data[50];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t USART_Rx_temp_data[4];
uint8_t USART_set_temerature;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	//HAL_UART_Receive_IT(&huart3, &received_data, 1); //ponowne wlaczenie nasluchiwania uart3

	//	 uint8_t Data[40]; // Tablica przechowujaca wysylana wiadomosc.
	//	 uint16_t size = 0; // Rozmiar wysylanej wiadomosci
	//
	//	 size = sprintf(Data, "Odebrana wiadomosc: %s\n\r",Received);
	//
	//	 HAL_UART_Transmit_IT(&huart1, Data, size); // Rozpoczecie nadawania danych z wykorzystaniem przerwan

	sscanf(USART_Rx_temp_data, "T=%u", &USART_set_temerature);

	HAL_UART_Receive_IT(&huart3, USART_Rx_temp_data, 4); // Ponowne włączenie nasłuchiwania
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM4) {	// timer 4 - 100Hz
		uint16_t n;

		/* Timery programowe - funkcje nieblokujące

		 Timer1
		n = Timer1;
		if (n)
			Timer1 = --n;

		 Timer2
		n = Timer2;
		if (n)
			Timer2 = --n;
	}
}

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
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_TIM1_Init();
  MX_TIM10_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

	/* PID error */
	float pid_error;
	/* Duty cycle for PWM */
	float duty = 0;
	/* ARM PID Instance, float_32 format */
	arm_pid_instance_f32 PID;

	/* Set PID parameters */
	/* Set this for your needs */
	PID.Kp = PID_PARAM_KP; /* Proporcional */
	PID.Ki = PID_PARAM_KI; /* Integral */
	PID.Kd = PID_PARAM_KD; /* Derivative */

	/* Initialize PID system, float32_t format */
//	arm_pid_init_f32(&PID, 1);

	//HAL_UART_Receive_IT(&huart3, USART_Rx_temp_data, 4);

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //wlaczenie pwm - f = 1kHz (FCPU = 168MHz -> pres=999; autoreload=167
	TIM1->CCR1 = 0;  //poczatkowe wypelnienie PWM1 - dioda zielona BB

	HAL_TIM_Base_Start_IT(&htim4);	// start przerwan od timera 4 - 100Hz

	/* Inicjalizacja czujnika temperatury - ustawienie rozdzielczości na 12 bitów */
	DS18B20_Init(DS18B20_Resolution_12bits);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

		/* Komenda startu konwersji oraz odczytu z wszystkich czujników 18B20 na magistrali 1-Wire - co 30ms*/

		if (!Timer2) {
			/*		static temp = 0;

			 if(!temp)  DS18B20_ReadAll();
			 else DS18B20_StartAll();

			 if(++temp >= 2) temp = 0;
			 Timer2 = 3;*/

			DS18B20_ReadAll();
			DS18B20_StartAll();

			/* Odczyt temeratury z czujnika */
			for (uint8_t i = 0; i < DS18B20_Quantity(); i++) {
				if (DS18B20_GetTemperature(i, &temperature)) {
					/* Tu wpisz kod - gdy zostanie odczytana wartość temperatury z i-tego czujnika */
					temperature = temperature;
				}
			}

			Timer2 = 10;

		}

		/* Calculate PID here, argument is error */
		/* Output data will be returned, we will use it as duty cycle parameter */
		duty = arm_pid_f32(&PID, pid_error);

		/* Check overflow, duty cycle in percent */
		if (duty > 100) {
			duty = 100;
		} else if (duty < 0) {
			duty = 0;
		}

		/* Wysyłnie danych na UART co 0.5s (500ms) */
		if (!Timer1) {
			HAL_UART_Transmit_IT(&huart3, string_data,
					sprintf(string_data,
							"TEMPERATURA AKTUALNA = %f" "\n\r" "DUTY = %d" "\n\r\n\r",
							temperature, PWM_Duty));

			Timer1 = 50;
		}

		HAL_Delay(1);

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
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
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

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
