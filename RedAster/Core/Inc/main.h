/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PYRO_FIRE_CH1_Pin GPIO_PIN_3
#define PYRO_FIRE_CH1_GPIO_Port GPIOE
#define PYRO_FIRE_CH2_Pin GPIO_PIN_4
#define PYRO_FIRE_CH2_GPIO_Port GPIOE
#define NOSE_DETECT_Pin GPIO_PIN_13
#define NOSE_DETECT_GPIO_Port GPIOC
#define SICURA_Pin GPIO_PIN_2
#define SICURA_GPIO_Port GPIOF
#define OGIVA_GPIO_Pin GPIO_PIN_3
#define OGIVA_GPIO_GPIO_Port GPIOF
#define SW_RAMPA_Pin GPIO_PIN_4
#define SW_RAMPA_GPIO_Port GPIOF
#define EN_NEOPIXEL_RING_Pin GPIO_PIN_5
#define EN_NEOPIXEL_RING_GPIO_Port GPIOF
#define EN_NEOPIXEL_MCU_Pin GPIO_PIN_6
#define EN_NEOPIXEL_MCU_GPIO_Port GPIOF
#define BUZZER_Pin GPIO_PIN_9
#define BUZZER_GPIO_Port GPIOF
#define EN_SERVO_Pin GPIO_PIN_10
#define EN_SERVO_GPIO_Port GPIOF
#define EN_PYRO_Pin GPIO_PIN_3
#define EN_PYRO_GPIO_Port GPIOC
#define PYRO_IN_CH1_Pin GPIO_PIN_5
#define PYRO_IN_CH1_GPIO_Port GPIOC
#define PYRO_IN_CH2_Pin GPIO_PIN_0
#define PYRO_IN_CH2_GPIO_Port GPIOB
#define LED_MCU_6_Pin GPIO_PIN_1
#define LED_MCU_6_GPIO_Port GPIOB
#define BTN_DOWN_Pin GPIO_PIN_13
#define BTN_DOWN_GPIO_Port GPIOF
#define BTN_UP_Pin GPIO_PIN_14
#define BTN_UP_GPIO_Port GPIOF
#define BTN_OK_Pin GPIO_PIN_15
#define BTN_OK_GPIO_Port GPIOF
#define LED_MCU_7_Pin GPIO_PIN_0
#define LED_MCU_7_GPIO_Port GPIOG
#define LED_MCU_5_Pin GPIO_PIN_10
#define LED_MCU_5_GPIO_Port GPIOE
#define MODE_SEL_1_Pin GPIO_PIN_12
#define MODE_SEL_1_GPIO_Port GPIOE
#define MODE_SEL_0_Pin GPIO_PIN_15
#define MODE_SEL_0_GPIO_Port GPIOE
#define CS_MAG_Pin GPIO_PIN_10
#define CS_MAG_GPIO_Port GPIOD
#define CS_EXT_MAG_Pin GPIO_PIN_14
#define CS_EXT_MAG_GPIO_Port GPIOD
#define CS_WINBOND_Pin GPIO_PIN_15
#define CS_WINBOND_GPIO_Port GPIOD
#define CS_MS56_P_Pin GPIO_PIN_2
#define CS_MS56_P_GPIO_Port GPIOG
#define CS_BMI088_ACC_P_Pin GPIO_PIN_3
#define CS_BMI088_ACC_P_GPIO_Port GPIOG
#define CS_BMI088_GYR_P_Pin GPIO_PIN_4
#define CS_BMI088_GYR_P_GPIO_Port GPIOG
#define CS_ICM_P_Pin GPIO_PIN_5
#define CS_ICM_P_GPIO_Port GPIOG
#define CS_BMP585_HI_Pin GPIO_PIN_6
#define CS_BMP585_HI_GPIO_Port GPIOG
#define CS_BMP585_STA_Pin GPIO_PIN_7
#define CS_BMP585_STA_GPIO_Port GPIOG
#define CS_H3LIS_Pin GPIO_PIN_8
#define CS_H3LIS_GPIO_Port GPIOG
#define SERVO_MAIN_Pin GPIO_PIN_6
#define SERVO_MAIN_GPIO_Port GPIOC
#define SERVO_DROGUE_Pin GPIO_PIN_7
#define SERVO_DROGUE_GPIO_Port GPIOC
#define SERVO_AERO_Pin GPIO_PIN_8
#define SERVO_AERO_GPIO_Port GPIOC
#define SERVO_CH4_Pin GPIO_PIN_9
#define SERVO_CH4_GPIO_Port GPIOC
#define CLK_32k_OUT_Pin GPIO_PIN_8
#define CLK_32k_OUT_GPIO_Port GPIOA
#define SD_DETECT_Pin GPIO_PIN_10
#define SD_DETECT_GPIO_Port GPIOA
#define CS_MS56_B_Pin GPIO_PIN_2
#define CS_MS56_B_GPIO_Port GPIOD
#define CS_BMI088_ACC_B_Pin GPIO_PIN_3
#define CS_BMI088_ACC_B_GPIO_Port GPIOD
#define CS_BMI088_GYR_B_Pin GPIO_PIN_4
#define CS_BMI088_GYR_B_GPIO_Port GPIOD
#define CS_ICM_B_Pin GPIO_PIN_5
#define CS_ICM_B_GPIO_Port GPIOD
#define LED_MCU_4_Pin GPIO_PIN_13
#define LED_MCU_4_GPIO_Port GPIOG
#define LED_MCU_3_Pin GPIO_PIN_14
#define LED_MCU_3_GPIO_Port GPIOG
#define LED_MCU_2_Pin GPIO_PIN_15
#define LED_MCU_2_GPIO_Port GPIOG
#define LED_MCU_1_Pin GPIO_PIN_4
#define LED_MCU_1_GPIO_Port GPIOB
#define NEOPIXEL_CH1_RING_Pin GPIO_PIN_8
#define NEOPIXEL_CH1_RING_GPIO_Port GPIOB
#define NEOPIXEL_CH2_Pin GPIO_PIN_9
#define NEOPIXEL_CH2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
