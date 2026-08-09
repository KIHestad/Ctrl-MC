/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

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
#define BTN_DEV_BOARD_Pin GPIO_PIN_13
#define BTN_DEV_BOARD_GPIO_Port GPIOC
#define SW_IS_Pin GPIO_PIN_3
#define SW_IS_GPIO_Port GPIOA
#define SW_CSN_Pin GPIO_PIN_4
#define SW_CSN_GPIO_Port GPIOA
#define SW_SCLK_Pin GPIO_PIN_5
#define SW_SCLK_GPIO_Port GPIOA
#define SW_MISO_Pin GPIO_PIN_6
#define SW_MISO_GPIO_Port GPIOA
#define SW_MOSI_Pin GPIO_PIN_7
#define SW_MOSI_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_6
#define LED_GPIO_Port GPIOC
#define BTN_10_Pin GPIO_PIN_8
#define BTN_10_GPIO_Port GPIOA
#define BTN_9_Pin GPIO_PIN_9
#define BTN_9_GPIO_Port GPIOA
#define FDCAN1_WAKE_UP_Pin GPIO_PIN_10
#define FDCAN1_WAKE_UP_GPIO_Port GPIOA
#define BTN_8_Pin GPIO_PIN_15
#define BTN_8_GPIO_Port GPIOA
#define BTN_7_Pin GPIO_PIN_10
#define BTN_7_GPIO_Port GPIOC
#define BTN_6_Pin GPIO_PIN_3
#define BTN_6_GPIO_Port GPIOB
#define BTN_5_Pin GPIO_PIN_4
#define BTN_5_GPIO_Port GPIOB
#define BTN_4_Pin GPIO_PIN_5
#define BTN_4_GPIO_Port GPIOB
#define BTN_3_Pin GPIO_PIN_6
#define BTN_3_GPIO_Port GPIOB
#define BTN_2_Pin GPIO_PIN_7
#define BTN_2_GPIO_Port GPIOB
#define BTN_1_Pin GPIO_PIN_9
#define BTN_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
