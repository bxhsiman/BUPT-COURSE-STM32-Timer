/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define BEEP_Pin GPIO_PIN_0
#define BEEP_GPIO_Port GPIOA
#define BTN_0_Pin GPIO_PIN_1
#define BTN_0_GPIO_Port GPIOA
#define BTN_0_EXTI_IRQn EXTI1_IRQn
#define TIMER_Pin GPIO_PIN_2
#define TIMER_GPIO_Port GPIOA
#define LED_EN5_Pin GPIO_PIN_4
#define LED_EN5_GPIO_Port GPIOA
#define LED_EN4_Pin GPIO_PIN_5
#define LED_EN4_GPIO_Port GPIOA
#define LED_EN3_Pin GPIO_PIN_6
#define LED_EN3_GPIO_Port GPIOA
#define LED_D_Pin GPIO_PIN_7
#define LED_D_GPIO_Port GPIOA
#define LED_E_Pin GPIO_PIN_0
#define LED_E_GPIO_Port GPIOB
#define LED_F_Pin GPIO_PIN_1
#define LED_F_GPIO_Port GPIOB
#define LED_A_Pin GPIO_PIN_2
#define LED_A_GPIO_Port GPIOB
#define LED_C_Pin GPIO_PIN_10
#define LED_C_GPIO_Port GPIOB
#define LED_P_Pin GPIO_PIN_11
#define LED_P_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_12
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_13
#define LED_B_GPIO_Port GPIOB
#define LED_EN2_Pin GPIO_PIN_14
#define LED_EN2_GPIO_Port GPIOB
#define LED_EN1_Pin GPIO_PIN_15
#define LED_EN1_GPIO_Port GPIOB
#define LED_EN0_Pin GPIO_PIN_8
#define LED_EN0_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
