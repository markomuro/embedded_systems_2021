/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "joystick.h"
#include "stm32f429i_discovery_lcd.h"
#include "usart.h"
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
/* USER CODE BEGIN Variables */
SemaphoreHandle_t xSemaphore = NULL;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

extern void MX_USB_HOST_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
//uint16_t kogus;
uint16_t Radius = 10;
joy_data xy;
joy_data xy_mapped;
static const char pcTextForTask1[] = "Task1\n";
static const char pcTextForTask2[] = "Task2\n";

void vTask1(void *pvParameters){
	char* pcTaskName = ( char * ) pvParameters;
	for( ;; ) {
				if( xSemaphore != NULL )
						    {
						        /* See if we can obtain the semaphore.  If the semaphore is not
						        available wait 10 ticks to see if it becomes free. */
						        if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) )
						        {
						            /* We were able to obtain the semaphore and can now access the
						            shared resource. */
						        	Joy_Read(&xy);
						        	map_numbers(&xy,&xy_mapped);

						            /* We have finished accessing the shared resource.  Release the
						            semaphore. */
						            xSemaphoreGive( xSemaphore );
						        }

						    }
				uint8_t sendbuf[50];
				uint16_t pikkus = (uint16_t)sprintf(sendbuf, "JOY: %d %d \n", xy.x,xy.y);
				UartTask_sendData(sendbuf, pikkus);
				//HAL_Delay(5);
				taskYIELD();
	}
}

void vTask2(void *pvParameters){
	char* pcTaskName = ( char * ) pvParameters;
	for( ;; ) {
		BSP_LCD_Clear(LCD_COLOR_BLACK);
		BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
		BSP_LCD_DrawCircle(xy_mapped.x, xy_mapped.y,Radius);
		BSP_LCD_DrawCircle(xy_mapped.x, xy_mapped.y,8);
		BSP_LCD_DrawCircle(xy_mapped.x, xy_mapped.y,5);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DrawCircle(xy_mapped.x, xy_mapped.y,4);
		BSP_LCD_DrawCircle(xy_mapped.x, xy_mapped.y,3);
		BSP_LCD_DrawCircle(xy_mapped.x, xy_mapped.y,2);

		HAL_Delay(25);

		uint8_t sendbuf[50];
		uint16_t pikkus = (uint16_t)sprintf(sendbuf, "SCR: %d %d \n", xy.x,xy.y);
		UartTask_sendData(sendbuf, pikkus);

				/*if( xSemaphore != NULL )
						    {

						        if( xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) )
						        {

						        	BSP_LCD_Clear(LCD_COLOR_BLACK);
						        	BSP_LCD_DrawCircle(0.07*xy.x, 0.07*xy.y,Radius);
						        	HAL_Delay(30);

						            xSemaphoreGive( xSemaphore );
						        }
						    }*/
				//taskYIELD();
	}
}

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
	UartTaskInit();

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
	xSemaphore = xSemaphoreCreateMutex();
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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 4096);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  xTaskCreate(vTask1,"Task1",100,(void*)pcTextForTask1,1,NULL);
  xTaskCreate(vTask2,"Task2",100,(void*)pcTextForTask2,1,NULL);
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
