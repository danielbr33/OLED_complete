/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
#include "Oled/SSD1306.h"
#include "Interface/Interface_manager.h"
#include "stdlib.h"
#include "cstring"
#include "string.h"
#include "stdio.h"
#include "stm32f4xx_hal.h"
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
extern Interface_manager* Interface1;
extern Interface_manager* Interface2;
extern SSD1306* oled;
extern SSD1306* oled2;

FATFS fs;  // file system
FIL fil; // File
FRESULT fresult;  // result
FILINFO fno;
UINT br, bw;  // File read/write count
/**** capacity related *****/
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId sd_taskHandle;
osThreadId oledTaskHandle;
osThreadId interfaceTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void send_uart (char *string)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)string, strlen (string), HAL_MAX_DELAY);  //TODO change uart
}

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartSDTask(void const * argument);
void StartOledTask(void const * argument);
void StartInterfaceTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
extern "C" void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

extern "C" void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
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
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 256);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of sd_task */
  osThreadDef(sd_task, StartSDTask, osPriorityNormal, 0, 256);
  sd_taskHandle = osThreadCreate(osThread(sd_task), NULL);

  /* definition and creation of oledTask */
  osThreadDef(oledTask, StartOledTask, osPriorityBelowNormal, 0, 256);
  oledTaskHandle = osThreadCreate(osThread(oledTask), NULL);

  /* definition and creation of interfaceTask */
  osThreadDef(interfaceTask, StartInterfaceTask, osPriorityBelowNormal, 0, 256);
  interfaceTaskHandle = osThreadCreate(osThread(interfaceTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
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
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSDTask */
/**
* @brief Function implementing the sd_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSDTask */
void StartSDTask(void const * argument)
{
  /* USER CODE BEGIN StartSDTask */

	char* read_data;
	char buffer[100];
	char name[20];
	uint32_t size;
	uint8_t width=7;
	uint8_t height=10;
	//sprintf(name, "Font%dx%d.txt", width, height);
	sprintf(name, "Font11x18.txt");

	fresult = f_mount(&fs, (const TCHAR*)"/", 1);
	if (fresult != FR_OK) send_uart ("ERROR!!! in mounting SD CARD...\n\n");
	else send_uart("SD CARD mounted successfully...\n");


	/**** check whether the file exists or not ****/
	fresult = f_stat (name, &fno);
	if (fresult != FR_OK) 	{
		char *buf = (char*)malloc(100*sizeof(char));
		sprintf (buf, "ERRROR!!! *%s* does not exists\n\n", name);
		send_uart (buf);
		free(buf);
	}
	else {
		/* Open file to read */
		fresult = f_open(&fil, name, FA_READ);
		if (fresult != FR_OK) {
			char *buf = (char*)malloc(100*sizeof(char));
			sprintf (buf, "ERROR!!! No. %d in opening file *%s*\n\n", fresult, name);
			send_uart(buf);
			free(buf);
	  	}

	  	/* Read data from the file
	  	 * 		* see the function details for the arguments */
		size = f_size(&fil);
	  	read_data = (char*)malloc(size);
	  	fresult = f_read (&fil,read_data, size, &br);
	  	char *buf = (char*)malloc(100*sizeof(char));
	  	sprintf(buf, "%s", read_data);
	  	//HAL_Delay(100);
	  	send_uart(buf);
	  	free(buf);
	 	if (fresult != FR_OK) {
			char *buf = (char*)malloc(100*sizeof(char));
	 		free(read_data);
	  	 	sprintf (buf, "ERROR!!! No. %d in reading file *%s*\n\n", fresult, name);
	  	  	send_uart(buf);
	  	  	free(buf);
		}

  		else  {
  			free(read_data);

  			/* Close file */
  			fresult = f_close(&fil);
  			if (fresult != FR_OK) {
  				char *buf = (char*)malloc(100*sizeof(char));
  				sprintf (buf, "ERROR!!! No. %d in closing file *%s*\n\n", fresult, name);
  				send_uart(buf);
  				free(buf);
  			}
  			else
  			{
  				char *buf = (char*)malloc(100*sizeof(char));
  				sprintf (buf, "File *%s* CLOSED successfully\n", name);
  				send_uart(buf);
  				free(buf);
  			}
  		}
	}


	fresult = f_mount(NULL, (const TCHAR*)"/", 1);
	if (fresult == FR_OK) send_uart ("SD CARD UNMOUNTED successfully...\n\n\n");
	else send_uart("ERROR!!! in UNMOUNTING SD CARD\n\n\n");
  /* Infinite loop */
  for(;;)
  {
	osDelay(2000);
  }
  /* USER CODE END StartSDTask */
}

/* USER CODE BEGIN Header_StartOledTask */
/**
* @brief Function implementing the oledTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOledTask */
void StartOledTask(void const * argument)
{
  /* USER CODE BEGIN StartOledTask */
  /* Infinite loop */
  for(;;)
  {
	oled->SPI_Interrupt_DMA();
	oled2->SPI_Interrupt_DMA();
	osDelay(50);
  }
  /* USER CODE END StartOledTask */
}

/* USER CODE BEGIN Header_StartInterfaceTask */
/**
* @brief Function implementing the interfaceTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInterfaceTask */
void StartInterfaceTask(void const * argument)
{
  /* USER CODE BEGIN StartInterfaceTask */
  /* Infinite loop */
  for(;;)
  {
	Interface2->interrupt();
    osDelay(50);
  }
  /* USER CODE END StartInterfaceTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
