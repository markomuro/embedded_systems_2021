/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "cmsis_os.h"
#include "stream_buffer.h"
//#include "FreeRTOS.h"

//extern SemaphoreHandle_t xSemaphore;

/* USER CODE BEGIN 0 */
SemaphoreHandle_t xSemaphore1 = NULL;
osThreadId uartTxTaskHandle;
StreamBufferHandle_t UartTxStreamBuffer = NULL; // other threads put data for sending here
uint8_t UartTxBuffer[32]; // copy data from streamBuffer for sending into here
volatile uint8_t UART_busy = 0;
static void UartTaskFn(void *argument);

void UartTaskInit() {
   UartTxStreamBuffer = xStreamBufferCreate(512, 1);

   osThreadDef(uartTxTask, UartTaskFn , osPriorityNormal, 0, 128);
   uartTxTaskHandle = osThreadCreate(osThread(uartTxTask), NULL);
   xSemaphore1 = xSemaphoreCreateMutex();
}

static void UartTaskFn(void *argument) {
   for (;;) {
      if (UART_busy == 1) {
         // Uart is busy transmitting, check back later
         // NOTE that UART_busy == 1 should rarely happen,
         // because the task waits for notification, if transmission is done,
         // and it should stay so until interrupt sets UART_busy to 0
         vTaskDelay(1);
         continue;
      }
      uint16_t bytesToSend = xStreamBufferReceive(UartTxStreamBuffer,
               (void *)UartTxBuffer, sizeof(UartTxBuffer), portMAX_DELAY);
      if (bytesToSend > 0) {
         UART_busy = 1;
         HAL_UART_Transmit_IT(&huart1, UartTxBuffer, bytesToSend);
         // block task until the existing data has been sent
         ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

      }
   }
}

void UartTask_sendData(uint8_t *data, uint16_t dataLength) {
   // kontrolli, kas bufferstreamis on piisavalt ruumi: xStreamBufferSpacesAvailable
	/*if (xStreamBufferSpacesAvailable(UartTxStreamBuffer) > dataLength){
		xStreamBufferSend(UartTxStreamBuffer);

	}*/
   // ja pane andmed puhvrisse: xStreamBufferSend
   // Mõtle, kas siia on vaja ka mutexit
	if( xSemaphore1 != NULL )
		{
			/* See if we can obtain the semaphore.  If the semaphore is not
			available wait 10 ticks to see if it becomes free. */
			if( xSemaphoreTake( xSemaphore1, ( TickType_t ) 10 ) )
			{
				/* We were able to obtain the semaphore and can now access the
				shared resource. */
				if (xStreamBufferSpacesAvailable(UartTxStreamBuffer) > dataLength){
						xStreamBufferSend(UartTxStreamBuffer, data, dataLength,( TickType_t ) 10);

				}

				/* We have finished accessing the shared resource.  Release the
				semaphore. */
				xSemaphoreGive( xSemaphore1 );
			}

		}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    UART_busy = 0;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    // wake the thread
    vTaskNotifyGiveFromISR(uartTxTaskHandle, &xHigherPriorityTaskWoken);
}


/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
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

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = STLINK_RX_Pin|STLINK_TX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, STLINK_RX_Pin|STLINK_TX_Pin);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
