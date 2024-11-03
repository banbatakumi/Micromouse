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
// #include "app.hpp"
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LINE_R_Pin GPIO_PIN_0
#define LINE_R_GPIO_Port GPIOC
#define LINE1_Pin GPIO_PIN_1
#define LINE1_GPIO_Port GPIOC
#define LINE2_Pin GPIO_PIN_2
#define LINE2_GPIO_Port GPIOC
#define LINE3_Pin GPIO_PIN_3
#define LINE3_GPIO_Port GPIOC
#define LINE4_Pin GPIO_PIN_0
#define LINE4_GPIO_Port GPIOA
#define LINE5_Pin GPIO_PIN_1
#define LINE5_GPIO_Port GPIOA
#define LINE6_Pin GPIO_PIN_2
#define LINE6_GPIO_Port GPIOA
#define LINE7_Pin GPIO_PIN_3
#define LINE7_GPIO_Port GPIOA
#define LINE8_Pin GPIO_PIN_4
#define LINE8_GPIO_Port GPIOA
#define LINE9_Pin GPIO_PIN_5
#define LINE9_GPIO_Port GPIOA
#define LINE10_Pin GPIO_PIN_6
#define LINE10_GPIO_Port GPIOA
#define LINE_L_Pin GPIO_PIN_7
#define LINE_L_GPIO_Port GPIOA
#define ENCODER_L_Pin GPIO_PIN_0
#define ENCODER_L_GPIO_Port GPIOB
#define ENCODER_R_Pin GPIO_PIN_1
#define ENCODER_R_GPIO_Port GPIOB
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
#define LED6_Pin GPIO_PIN_9
#define LED6_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
