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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "iwdg.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
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

	/*从CAN接收来的码位数据*/
	uint8_t CAN_Data_0 = 0x00;
	uint8_t CAN_Data_1 = 0x00;
	uint8_t CAN_Data_2 = 0x00;
	
	/*下位机控制标志位*/
	uint8_t Control_Flag = 0; 	//1 - 下位机控制 0 - 上位机控制
	uint16_t Set_Time = 0;		//控制离合器（合）置1的时间
	uint16_t Reset_Time = 0;	//控制离合器（合）置0的时间
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId Task_CANHandle;
osThreadId Task_FeedDogHandle;
osThreadId Task_GPIOHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void CanTask(void const * argument);
void FeedDogTask(void const * argument);
void GPIOControlTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 64);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Task_CAN */
  osThreadDef(Task_CAN, CanTask, osPriorityAboveNormal, 0, 128);
  Task_CANHandle = osThreadCreate(osThread(Task_CAN), NULL);

  /* definition and creation of Task_FeedDog */
  osThreadDef(Task_FeedDog, FeedDogTask, osPriorityNormal, 0, 64);
  Task_FeedDogHandle = osThreadCreate(osThread(Task_FeedDog), NULL);

  /* definition and creation of Task_GPIO */
  osThreadDef(Task_GPIO, GPIOControlTask, osPriorityHigh, 0, 64);
  Task_GPIOHandle = osThreadCreate(osThread(Task_GPIO), NULL);

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
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_CanTask */
/**
* @brief Function implementing the Task_CAN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_CanTask */
void CanTask(void const * argument)
{
  /* USER CODE BEGIN CanTask */
	
	osDelay(1000);
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
  /* Infinite loop */
  for(;;)
  {
	//对Data[0]的判断
//	if(CAN_Data_0 & 0x01){
//		HAL_GPIO_WritePin(DO_CON1_GPIO_Port, DO_CON1_Pin, GPIO_PIN_SET);
//	} else {
//		HAL_GPIO_WritePin(DO_CON1_GPIO_Port, DO_CON1_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x02){
//		HAL_GPIO_WritePin(DO_CON2_GPIO_Port, DO_CON2_Pin, GPIO_PIN_SET);
//	} else {
//		HAL_GPIO_WritePin(DO_CON2_GPIO_Port, DO_CON2_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x04){
//		HAL_GPIO_WritePin(DO_CON3_GPIO_Port, DO_CON3_Pin, GPIO_PIN_SET);
//	} else {                                     
//		HAL_GPIO_WritePin(DO_CON3_GPIO_Port, DO_CON3_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x08){
//		HAL_GPIO_WritePin(DO_CON4_GPIO_Port, DO_CON4_Pin, GPIO_PIN_SET);
//	} else {                                   
//		HAL_GPIO_WritePin(DO_CON4_GPIO_Port, DO_CON4_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x10){
//		HAL_GPIO_WritePin(DO_CON5_GPIO_Port, DO_CON5_Pin, GPIO_PIN_SET);
//	} else {                                  
//		HAL_GPIO_WritePin(DO_CON5_GPIO_Port, DO_CON5_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x20){
//		HAL_GPIO_WritePin(DO_CON6_GPIO_Port, DO_CON6_Pin, GPIO_PIN_SET);
//	} else {                                 
//		HAL_GPIO_WritePin(DO_CON6_GPIO_Port, DO_CON6_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x40){
//		HAL_GPIO_WritePin(DO_CON7_GPIO_Port, DO_CON7_Pin, GPIO_PIN_SET);
//	} else {                                   
//		HAL_GPIO_WritePin(DO_CON7_GPIO_Port, DO_CON7_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_0 & 0x80){
//		HAL_GPIO_WritePin(DO_CON8_GPIO_Port, DO_CON8_Pin, GPIO_PIN_SET);
//	} else {                                     
//		HAL_GPIO_WritePin(DO_CON8_GPIO_Port, DO_CON8_Pin, GPIO_PIN_RESET);
//	}
//	//对Data[1]的判断	
//	if(CAN_Data_1 & 0x01){
//		HAL_GPIO_WritePin(DO_CON9_GPIO_Port, DO_CON9_Pin, GPIO_PIN_SET);
//	} else {                                  
//		HAL_GPIO_WritePin(DO_CON9_GPIO_Port, DO_CON9_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x02){
//		HAL_GPIO_WritePin(DO_CON10_GPIO_Port, DO_CON10_Pin, GPIO_PIN_SET);
//	} else {                                   
//		HAL_GPIO_WritePin(DO_CON10_GPIO_Port, DO_CON10_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x04){
//		HAL_GPIO_WritePin(DO_CON11_GPIO_Port, DO_CON11_Pin, GPIO_PIN_SET);
//	} else {                                
//		HAL_GPIO_WritePin(DO_CON11_GPIO_Port, DO_CON11_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x08){
//		HAL_GPIO_WritePin(DO_CON12_GPIO_Port, DO_CON12_Pin, GPIO_PIN_SET);
//	} else {                                
//		HAL_GPIO_WritePin(DO_CON12_GPIO_Port, DO_CON12_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x10){
//		HAL_GPIO_WritePin(DO_CON13_GPIO_Port, DO_CON13_Pin, GPIO_PIN_SET);
//	} else {                                   
//		HAL_GPIO_WritePin(DO_CON13_GPIO_Port, DO_CON13_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x20){
//		HAL_GPIO_WritePin(DO_CON14_GPIO_Port, DO_CON14_Pin, GPIO_PIN_SET);
//	} else {                                 
//		HAL_GPIO_WritePin(DO_CON14_GPIO_Port, DO_CON14_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x40){
//		HAL_GPIO_WritePin(DO_CON15_GPIO_Port, DO_CON15_Pin, GPIO_PIN_SET);
//	} else {                                   
//		HAL_GPIO_WritePin(DO_CON15_GPIO_Port, DO_CON15_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_1 & 0x80){
//		HAL_GPIO_WritePin(DO_CON16_GPIO_Port, DO_CON16_Pin, GPIO_PIN_SET);
//	} else {                              
//		HAL_GPIO_WritePin(DO_CON16_GPIO_Port, DO_CON16_Pin, GPIO_PIN_RESET);
//	}
//	//对Data[2]的判断	
//	if(CAN_Data_2 & 0x01){
//		HAL_GPIO_WritePin(DO_CON17_GPIO_Port, DO_CON17_Pin, GPIO_PIN_SET);
//	} else {                                  
//		HAL_GPIO_WritePin(DO_CON17_GPIO_Port, DO_CON17_Pin, GPIO_PIN_RESET);
//	}
//	if(CAN_Data_2 & 0x02){
//		HAL_GPIO_WritePin(DO_CON18_GPIO_Port, DO_CON18_Pin, GPIO_PIN_SET);
//	} else {                                   
//		HAL_GPIO_WritePin(DO_CON18_GPIO_Port, DO_CON18_Pin, GPIO_PIN_RESET);
//	}
//	if(HAL_GPIO_ReadPin(DIN_GND1_GPIO_Port,DIN_GND1_Pin)==0){
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	}else if(HAL_GPIO_ReadPin(DIN_GND2_GPIO_Port,DIN_GND2_Pin)==0){
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	}else if(HAL_GPIO_ReadPin(DIN_GND3_GPIO_Port,DIN_GND3_Pin)==0){
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	}else if(HAL_GPIO_ReadPin(DIN_GND4_GPIO_Port,DIN_GND4_Pin)==0){
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	}else if(HAL_GPIO_ReadPin(DIN_GND5_GPIO_Port,DIN_GND5_Pin)==0){
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	}else if(HAL_GPIO_ReadPin(DIN_GND6_GPIO_Port,DIN_GND6_Pin)==0){
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//	}else 
//	{                                   
//		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
//	}

	ADC_Val_Buffer[0] = ADC_Filter(ADC_Buffer1,100,ADC1_Val_Buffer[0]);
	ADC_Val_Buffer[1] = ADC_Filter(ADC_Buffer2,100,ADC1_Val_Buffer[1]);
	osDelay(20);
  }
  /* USER CODE END CanTask */
}

/* USER CODE BEGIN Header_FeedDogTask */
/**
* @brief Function implementing the Task_FeedDog thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FeedDogTask */
void FeedDogTask(void const * argument)
{
  /* USER CODE BEGIN FeedDogTask */

  /* Infinite loop */
  for(;;)
  {
	HAL_IWDG_Refresh(&hiwdg);
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);	
		printf("ADC1: %d\r\n",ADC_Val_Buffer[0]);
		printf("ADC2: %d\r\n",ADC_Val_Buffer[1]);
	CAN_Transmit_1();
	osDelay(500);
  }
  /* USER CODE END FeedDogTask */
}

/* USER CODE BEGIN Header_GPIOControlTask */
/**
* @brief Function implementing the Task_GPIO thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GPIOControlTask */
void GPIOControlTask(void const * argument)
{
  /* USER CODE BEGIN GPIOControlTask */
  /* Infinite loop */
  for(;;)
  {
	if(Control_Flag){	//驱动器定时控制离合器（合）的开关
//		HAL_GPIO_WritePin(Output_52_GPIO_Port, Output_52_Pin, GPIO_PIN_RESET);
//		osDelay(Reset_Time);
//		HAL_GPIO_WritePin(Output_52_GPIO_Port, Output_52_Pin, GPIO_PIN_SET);
		osDelay(Set_Time);	
	
	}else{
		osDelay(100);	
	}
  }
  /* USER CODE END GPIOControlTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
