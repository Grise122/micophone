/**
  ******************************************************************************
  * @file    main.c
  * @author  SRA
  * @version v1.3.1
  * @date    17-Jul-2020
  * @brief   Main program body
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
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include <string.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @addtogroup X_CUBE_MEMSMIC1_Applications
  * @{
  */

/** @addtogroup Microphones_Acquisition
  * @{
  */

/** @defgroup MAIN
  * @{
  */

/** @defgroup MAIN_Exported_Variables
  * @{
  */
USBD_HandleTypeDef hUSBDDevice;
extern USBD_AUDIO_ItfTypeDef  USBD_AUDIO_fops;
SAI_HandleTypeDef            SaiHandle;
DMA_HandleTypeDef            hSaiDma;
UART_HandleTypeDef huart2;

/**
  * @}
  */

/** @defgroup MAIN_Private_Functions
  * @{
  */
/* Private function prototypes -----------------------------------------------*/
/**
  * @}
  */

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

/* 初始化 UART2 参数 */
void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* HAL 库底层初始化回调，配置时钟和 GPIO */
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART2)
  {
    /* 开启 UART2 和 GPIOD 的时钟 */
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    /* 配置 PD5 为 TX, PD6 为 RX (复用功能 AF7) */
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  }
}


int main(void)
{

  /* STM32F4xx HAL library initialization:
  - Configure the Flash prefetch, instruction and Data caches
  - Configure the Systick to generate an interrupt each 1 msec
  - Global MSP (MCU Support Package) initialization
  */
  HAL_Init();

  /* Enable Power Clock*/
  __HAL_RCC_PWR_CLK_ENABLE();
  /* enable USB power on Pwrctrl CR2 register */
  HAL_PWREx_EnableVddUSB();

  /* Configure the system clock */
  SystemClock_Config();

  BSP_LED_Init(LED2);
  BSP_LED_Off(LED2);
  BSP_LED_Init(LED1);
  BSP_LED_Off(LED1);

  /* Initialize USB descriptor basing on channels number and sampling frequency */
  USBD_AUDIO_Init_Microphone_Descriptor(&hUSBDDevice, AUDIO_IN_SAMPLING_FREQUENCY, AUDIO_IN_CHANNELS);
  /* Init Device Library */
  USBD_Init(&hUSBDDevice, &AUDIO_Desc, 0);
  /* Add Supported Class */
  USBD_RegisterClass(&hUSBDDevice, &USBD_AUDIO);
  /* Add Interface callbacks for AUDIO Class */
  USBD_AUDIO_RegisterInterface(&hUSBDDevice, &USBD_AUDIO_fops);
  /* Start Device Process */
  USBD_Start(&hUSBDDevice);

  /* Start audio acquisition and streaming */

#ifdef DISABLE_USB_DRIVEN_ACQUISITION
  Init_Acquisition_Peripherals(AUDIO_IN_SAMPLING_FREQUENCY, ACTIVE_MICROPHONES_MASK, AUDIO_IN_CHANNELS);
  Start_Acquisition();
#endif
  MX_USART2_UART_Init();
  uint32_t last_send_time = 0;
  while (1)
  {
	  if (HAL_GetTick() - last_send_time >= 1000)
	      {
	        char msg[] = "hello\r\n";
	        HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
	        last_send_time = HAL_GetTick();
	      }

  }
}

/* Private functions ---------------------------------------------------------*/


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
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif  /* USE_FULL_ASSERT */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
