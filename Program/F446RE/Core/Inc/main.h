/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "app.h"
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
#define BUZZER_Pin GPIO_PIN_10
#define BUZZER_GPIO_Port GPIOB
#define LINE_LED_Pin GPIO_PIN_8
#define LINE_LED_GPIO_Port GPIOC
#define FAN_MOTOR_Pin GPIO_PIN_9
#define FAN_MOTOR_GPIO_Port GPIOC
#define LA_MOTOR_Pin GPIO_PIN_8
#define LA_MOTOR_GPIO_Port GPIOA
#define LB_MOTOR_Pin GPIO_PIN_9
#define LB_MOTOR_GPIO_Port GPIOA
#define RA_MOTOR_Pin GPIO_PIN_10
#define RA_MOTOR_GPIO_Port GPIOA
#define RB_MOTOR_Pin GPIO_PIN_11
#define RB_MOTOR_GPIO_Port GPIOA
#define BUTTON1_Pin GPIO_PIN_12
#define BUTTON1_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOD
#define BUTTON2_Pin GPIO_PIN_3
#define BUTTON2_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define BUTTON3_Pin GPIO_PIN_5
#define BUTTON3_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_6
#define LED3_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_7
#define LED4_GPIO_Port GPIOB
#define LED5_Pin GPIO_PIN_8
#define LED5_GPIO_Port GPIOB
#define LEDH_Pin GPIO_PIN_9
#define LEDH_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
