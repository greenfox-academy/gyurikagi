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
GPIO_InitTypeDef pb_up;
GPIO_InitTypeDef pb_down;
GPIO_InitTypeDef feedback;
GPIO_InitTypeDef gate;
TIM_HandleTypeDef timh;
TIM_OC_InitTypeDef output_compare_conf;
TIM_HandleTypeDef Tim2;
TIM_IC_InitTypeDef sICConfig;

volatile uint32_t timIntPeriod;

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

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */

void init_buttons ();
void init_feedback();
void Tim1_init_start();
void EXTI9_5_IRQHandler();
void EXTI15_10_IRQHandler();
void int_gate();
void Tim2_init_start();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


int main(void) {
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

	/* Configure the System clock to have a frequency of 216 MHz */
	SystemClock_Config();

	init_buttons ();
	init_feedback();
	Tim1_init_start();
	int_gate();

	BSP_LED_Init(LED_GREEN);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0x0F, 0x00);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 1, 1);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	/* Add your application code here
	 */

	uart_handle.Init.BaudRate = 115200;
	uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
	uart_handle.Init.StopBits = UART_STOPBITS_1;
	uart_handle.Init.Parity = UART_PARITY_NONE;
	uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_handle.Init.Mode = UART_MODE_TX_RX;

	BSP_COM_Init(COM1, &uart_handle);


	printf("\n-----------------WELCOME-----------------\r\n");
	printf("**********in STATIC interrupts WS**********\r\n\n");


	while (1) {

	}
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


void init_buttons (){
	__HAL_RCC_GPIOF_CLK_ENABLE();

	pb_down.Pin = GPIO_PIN_9;
	pb_down.Mode = GPIO_MODE_IT_RISING;
	pb_down.Pull = GPIO_PULLDOWN;
	pb_down.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOF, &pb_down);


	__HAL_RCC_GPIOF_CLK_ENABLE();
	pb_up.Pin = GPIO_PIN_10;
	pb_up.Mode = GPIO_MODE_IT_RISING;
	pb_up.Pull = GPIO_PULLDOWN;
	pb_up.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOF, &pb_up);
}


void init_feedback() {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	 feedback.Pin = GPIO_PIN_15;
	 feedback.Mode = GPIO_MODE_IT_RISING;
	 feedback.Pull = GPIO_NOPULL;
	 feedback.Speed = GPIO_SPEED_FAST;
	 HAL_GPIO_Init(GPIOA, &feedback);

}

void Tim1_init_start(){
	__HAL_RCC_TIM1_CLK_ENABLE();
	timh.Instance               = TIM1;
	timh.Init.Period            = 1000;
	timh.Init.Prescaler         = 50000;
	timh.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	timh.Init.CounterMode       = TIM_COUNTERMODE_UP;

	HAL_TIM_Base_Init(&timh);

	HAL_TIM_Base_Start(&timh);

	HAL_TIM_PWM_Init(&timh);

	output_compare_conf.OCMode = TIM_OCMODE_PWM1;
	output_compare_conf.Pulse = 0;

	HAL_TIM_PWM_ConfigChannel(&timh, &output_compare_conf, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&timh, TIM_CHANNEL_1);

}

void Tim2_init_start()
{	__HAL_RCC_TIM2_CLK_ENABLE();
	Tim2.Instance = TIM2;

	  Tim2.Init.Period            = 0xFFFF;
	  Tim2.Init.Prescaler         = 0;
	  Tim2.Init.ClockDivision     = 0;
	  Tim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
	  Tim2.Init.RepetitionCounter = 0;
	  Tim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if(HAL_TIM_IC_Init(&Tim2) != HAL_OK)
	  {
	  	    Error_Handler();
	  }
	  sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;
	  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
	  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;
	  sICConfig.ICFilter    = 0;
	  if(HAL_TIM_IC_ConfigChannel(&Tim2, &sICConfig, TIM_CHANNEL_1) != HAL_OK);
}

// button interrupt

void EXTI9_5_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
}

void EXTI15_10_IRQHandler()
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 if (GPIO_Pin == GPIO_PIN_10 && TIM1->CCR1 <= 900) {
	 TIM1->CCR1 +=100 ;
	 printf("%lu\n", TIM1->CCR1);
 } else if (GPIO_Pin == GPIO_PIN_9  && TIM1->CCR1 >= 100) {
	 TIM1->CCR1 -=100;
	 printf("%lu\n", TIM1->CCR1);
 }
}

void int_gate(){
	__HAL_RCC_GPIOA_CLK_ENABLE();

	 gate.Pin = GPIO_PIN_8;
	 gate.Mode = GPIO_MODE_AF_PP;
	 gate.Pull = GPIO_PULLDOWN;
	 gate.Speed = GPIO_SPEED_FAST;
	 gate.Alternate = GPIO_AF1_TIM1;

	HAL_GPIO_Init(GPIOA, &gate);
}

void TIM2_IRQHandler()
{
	
	HAL_TIM_IRQHandler(GPIO_PIN_15);
}

void HAL_TIM_IC_CaptureCallback(htim)
{
	
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
