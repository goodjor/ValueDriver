/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "adc.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DIN_GND3_Pin GPIO_PIN_2
#define DIN_GND3_GPIO_Port GPIOE
#define DIN_GND4_Pin GPIO_PIN_3
#define DIN_GND4_GPIO_Port GPIOE
#define DIN_GND5_Pin GPIO_PIN_4
#define DIN_GND5_GPIO_Port GPIOE
#define DIN_GND6_Pin GPIO_PIN_5
#define DIN_GND6_GPIO_Port GPIOE
#define DO_CON12_Pin GPIO_PIN_4
#define DO_CON12_GPIO_Port GPIOA
#define DO_CON11_Pin GPIO_PIN_5
#define DO_CON11_GPIO_Port GPIOA
#define DO_CON10_Pin GPIO_PIN_6
#define DO_CON10_GPIO_Port GPIOA
#define DO_CON9_Pin GPIO_PIN_7
#define DO_CON9_GPIO_Port GPIOA
#define DO_CON8_Pin GPIO_PIN_8
#define DO_CON8_GPIO_Port GPIOE
#define DO_CON7_Pin GPIO_PIN_9
#define DO_CON7_GPIO_Port GPIOE
#define DO_CON6_Pin GPIO_PIN_10
#define DO_CON6_GPIO_Port GPIOE
#define DO_CON5_Pin GPIO_PIN_11
#define DO_CON5_GPIO_Port GPIOE
#define DO_CON4_Pin GPIO_PIN_12
#define DO_CON4_GPIO_Port GPIOE
#define DO_CON3_Pin GPIO_PIN_13
#define DO_CON3_GPIO_Port GPIOE
#define DO_CON2_Pin GPIO_PIN_14
#define DO_CON2_GPIO_Port GPIOE
#define DO_CON1_Pin GPIO_PIN_15
#define DO_CON1_GPIO_Port GPIOE
#define DO_CON13_Pin GPIO_PIN_8
#define DO_CON13_GPIO_Port GPIOD
#define DO_CON14_Pin GPIO_PIN_9
#define DO_CON14_GPIO_Port GPIOD
#define DO_CON15_Pin GPIO_PIN_10
#define DO_CON15_GPIO_Port GPIOD
#define DO_CON16_Pin GPIO_PIN_11
#define DO_CON16_GPIO_Port GPIOD
#define DO_CON17_Pin GPIO_PIN_12
#define DO_CON17_GPIO_Port GPIOD
#define DO_CON18_Pin GPIO_PIN_13
#define DO_CON18_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOD
#define DIN_GND1_Pin GPIO_PIN_0
#define DIN_GND1_GPIO_Port GPIOE
#define DIN_GND2_Pin GPIO_PIN_1
#define DIN_GND2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
extern uint16_t ADC1_Val_Buffer[2];
extern uint16_t ADC_Val_Buffer[2];
extern uint16_t ADC_Buffer1[100];
extern uint16_t ADC_Buffer2[100];
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
