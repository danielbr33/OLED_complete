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
#include "Oled/SSD1306.h"
#include "Interface/Interface_manager.h"
#include "spi.h"
#include "i2c.h"
#include "usart.h"
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
SSD1306* oled;
SSD1306* oled2;

/**** capacity related *****/
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId oledTaskHandle;
osThreadId interfaceTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of oledTask */
  osThreadDef(oledTask, StartOledTask, osPriorityBelowNormal, 0, 128);
  oledTaskHandle = osThreadCreate(osThread(oledTask), NULL);

  /* definition and creation of interfaceTask */
  osThreadDef(interfaceTask, StartInterfaceTask, osPriorityNormal, 0, 1024);
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
//	oled->oledInterruptDMA();
	oled2->oledInterrupt();
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
	Interface_manager* Interface1;
	Interface_manager* Interface2;

	SSD1306::gpio_struct  gpio_reset;
	gpio_reset.port = OLED_RESET_GPIO_Port;
	gpio_reset.pin= OLED_RESET_Pin;

	SSD1306::gpio_struct gpio_dc;
	gpio_dc.port = OLED_DC_GPIO_Port;
	gpio_dc.pin = OLED_DC_Pin;

	SSD1306::gpio_struct gpio_cs;
	gpio_cs.port = OLED_CS_GPIO_Port;
	gpio_cs.pin = OLED_CS_Pin;

	SSD1306::OledSettingsSPI oledSpiSettings;
	oledSpiSettings.cs.port = OLED_CS_GPIO_Port;
	oledSpiSettings.cs.pin = OLED_CS_Pin;

	oledSpiSettings.reset.port = OLED_RESET_GPIO_Port;
	oledSpiSettings.reset.pin = OLED_RESET_Pin;

	oledSpiSettings.dc.port = OLED_DC_GPIO_Port;
	oledSpiSettings.dc.pin = OLED_DC_Pin;

	oledSpiSettings.hspi = &hspi1;

	SSD1306::OledSettingsI2C i2c_settings;
	i2c_settings.address = 0x3C<<1;
	i2c_settings.hi2c = &hi2c1;


	oled = new SSD1306(oledSpiSettings);
	oled2 = new SSD1306(i2c_settings);

	oled->changeDMA(SSD1306::SET_ON);
	oled->init();
	HAL_Delay(5);
	oled2->changeDMA(SSD1306::SET_ON);
	oled2->init();
	HAL_Delay(5);
	Interface1=new Interface_manager(&huart3, oled);
	Interface2=new Interface_manager(&huart3, oled2);
  for(;;)
  {
	Interface2->interrupt();
    osDelay(100);
  }
  /* USER CODE END StartInterfaceTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
