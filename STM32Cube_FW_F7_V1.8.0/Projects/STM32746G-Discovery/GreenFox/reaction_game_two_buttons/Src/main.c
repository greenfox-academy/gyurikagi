/**
 ******************************************************************************
 * @file    Templates/Src/main.c
 * @author  MCD Application Team
 * @version V1.0.3
 * @date    22-April-2016
 * @brief   STM32F7xx HAL API Template project
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>

/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup Templates
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef uart_handle;

/* Private function prototypes -----------------------------------------------*/

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

static void SystemClock_Config(void);
static void Error_Handler(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);

void My_Delay(uint32_t Delay) {
	uint32_t tickstart = 0;
	tickstart = HAL_GetTick();
	while ((HAL_GetTick() - tickstart) < Delay) {
		if (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10) == 0 || HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9) == 0)
			return;
	}
}

void starting_led() {
	BSP_LED_On(LED_GREEN);
	My_Delay(500);
	BSP_LED_Off(LED_GREEN);
	My_Delay(500);

}

/*void flash_leds() {
	bool prevState = true;
	bool newState = true;
	while (prevState || !newState) {
		BSP_LED_On(led0);
		My_Delay(70);
		BSP_led (led0);
		HAL_Delay(70);
		prevState = newState;
		newState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == 0;
		counter = 0;
	}
}*/

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void) {

	// init buttons and leds:




	/* This project template calls firstly two functions in order to configure MPU feature
	 and to enable the CPU Cache, respectively MPU_Config() and CPU_CACHE_Enable().
	 These functions are provided as template implementation that User may integrate
	 in his application, to enhance the performance in case of use of AXI interface
	 with several masters. */

	/* Configure the MPU attributes as Write Through */
	MPU_Config();

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
	 - Configure the Flash ART accelerator on ITCM interface
	 - Configure the Systick to generate an interrupt each 1 msec
	 - Set NVIC Group Priority to 4
	 - Low Level Initialization
	 */
	HAL_Init();

	__HAL_RCC_GPIOF_CLK_ENABLE();

	GPIO_InitTypeDef butt1;
	butt1.Pin = GPIO_PIN_10;
	butt1.Mode = GPIO_MODE_INPUT;
	butt1.Pull = GPIO_PULLUP;
	butt1.Speed = GPIO_SPEED_HIGH;

	GPIO_InitTypeDef butt2;
	butt2.Pin = GPIO_PIN_9;
	butt2.Mode = GPIO_MODE_INPUT;
	butt2.Pull = GPIO_PULLUP;
	butt2.Speed = GPIO_SPEED_HIGH;

	GPIO_InitTypeDef led0;
	led0.Pin = GPIO_PIN_7;
	led0.Mode = GPIO_MODE_OUTPUT_PP;
	led0.Pull = GPIO_PULLDOWN;
	led0.Speed = GPIO_SPEED_HIGH;

	GPIO_InitTypeDef led1;
	led1.Pin = GPIO_PIN_6;
	led1.Mode = GPIO_MODE_OUTPUT_PP;
	led1.Pull = GPIO_PULLDOWN;
	led1.Speed = GPIO_SPEED_HIGH;

	GPIO_InitTypeDef led2;
	led2.Pin = GPIO_PIN_8;
	led2.Mode = GPIO_MODE_OUTPUT_PP;
	led2.Pull = GPIO_PULLDOWN;
	led2.Speed = GPIO_SPEED_HIGH;

	HAL_GPIO_Init(GPIOF, &led0);
	HAL_GPIO_Init(GPIOF, &led1);
	HAL_GPIO_Init(GPIOF, &led2);
	HAL_GPIO_Init(GPIOF, &butt1);
	HAL_GPIO_Init(GPIOF, &butt2);

	/* Configure the System clock to have a frequency of 216 MHz */
	SystemClock_Config();
	RNG_HandleTypeDef rnd;
	uint32_t rnd_num;
	rnd.Instance = RNG;
	HAL_RNG_Init(&rnd);
	HAL_RNG_GenerateRandomNumber(&rnd, &rnd_num);
	uint32_t rand_num = rnd_num % 10000 + 1;

	/* Add your application code here
	 */

//	BSP_LED_Init(LED_GREEN);
//	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	uart_handle.Init.BaudRate = 115200;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;

	BSP_COM_Init(COM1, &uart_handle);

	/* Output a message using printf function */
	printf("\n------------------WELCOME------------------\r\n");
	printf(
			"**********in STATIC reaction game**********\r\n\
		  \n Let's play a game! Are you ready?\n");

	uint32_t push_time;
	uint32_t start_time;
	uint32_t arr[2];

	while (1) {
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10) != 0 || HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9)!= 0) {
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
			My_Delay(500);
			HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
			My_Delay(500);

		}
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
		while (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10) != 1 || HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9)!= 1) {

		}

		for (int i = 0; i< 10; ++i){
				HAL_RNG_GenerateRandomNumber(&rnd, &rnd_num);
				rand_num = rnd_num % 10000 + 1;
				HAL_Delay(rand_num);
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET);
				start_time = HAL_GetTick();
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_RESET);
				if (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10)!=0){
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
					HAL_Delay(10000);
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET);
				} else if (HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9)!=0) {
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
					HAL_Delay(10000);
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
				}

		}




	}
/*	for (int j = 0; j < 2; ++j) {
		do {
			starting_led();
		} while (BSP_PB_GetState(BUTTON_KEY) == 0);

		BSP_LED_Off(LED_GREEN);
		while (BSP_PB_GetState(BUTTON_KEY) == 1) {

		}

		uint32_t avg_time = 0;
		for (int i = 0; i < 5; ++i) {
			HAL_RNG_GenerateRandomNumber(&rnd, &rnd_num);
			rand_num = rnd_num % 10000 + 1;
			HAL_Delay(rand_num);
			BSP_LED_On(LED_GREEN);
			start_time = HAL_GetTick();
			My_Delay(10000);
			push_time = HAL_GetTick();
			printf("Your time is %d msec.\n", (push_time - start_time));
			BSP_LED_Off(LED_GREEN);
			avg_time = avg_time + (push_time - start_time);
		}
		printf("Your average is: %d\n", avg_time / 5);
		arr[j] = avg_time;
		avg_time = 0;

		printf("Next player\n");
		HAL_Delay(200);


	}
	if (arr[0] < arr[1]) {
		printf("The winner is the first player\n");
	} else {
		printf("The winner is the second player\n");
	}*/
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
	HAL_UART_Transmit(&uart_handle, (uint8_t *) &ch, 1, 0xFFFF);

	return ch;
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000
 *            HCLK(Hz)                       = 216000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432
 *            PLL_P                          = 2
 *            PLL_Q                          = 9
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void) {
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* activate the OverDrive to reach the 216 Mhz Frequency */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void) {
	/* User may add here some code to deal with this error */
	while (1) {
	}
}

/**
 * @brief  Configure the MPU attributes as Write Through for SRAM1/2.
 * @note   The Base Address is 0x20010000 since this memory interface is the AXI.
 *         The Region Size is 256KB, it is related to SRAM1 and SRAM2  memory size.
 * @param  None
 * @retval None
 */
static void MPU_Config(void) {
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable the MPU */
	HAL_MPU_Disable();

	/* Configure the MPU attributes as WT for SRAM */
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.BaseAddress = 0x20010000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.SubRegionDisable = 0x00;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/* Enable the MPU */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void) {
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
