/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#define Timer2TicksMax 500
#define BoardLight_Pin GPIO_PIN_13
#define BoardLight_GPIO_Port GPIOC
#define ReceiverOn_Pin GPIO_PIN_14
#define ReceiverOn_GPIO_Port GPIOC
#define Relay3_Pin GPIO_PIN_15
#define Relay3_GPIO_Port GPIOC
#define Relay1_Pin GPIO_PIN_1
#define Relay1_GPIO_Port GPIOA
#define ProximitySensor2_Pin GPIO_PIN_5
#define ProximitySensor2_GPIO_Port GPIOA
#define ProximitySensor1_Pin GPIO_PIN_6
#define ProximitySensor1_GPIO_Port GPIOA
#define MovingSensor1_Pin GPIO_PIN_7
#define MovingSensor1_GPIO_Port GPIOA
#define Relay6_Pin GPIO_PIN_0
#define Relay6_GPIO_Port GPIOB
#define Relay2_Pin GPIO_PIN_1
#define Relay2_GPIO_Port GPIOB
#define Relay8_Pin GPIO_PIN_2
#define Relay8_GPIO_Port GPIOB
#define Relay4_Pin GPIO_PIN_10
#define Relay4_GPIO_Port GPIOB
#define Relay5_Pin GPIO_PIN_11
#define Relay5_GPIO_Port GPIOB
#define Button4_Pin GPIO_PIN_4
#define Button4_GPIO_Port GPIOB
#define Button3_Pin GPIO_PIN_5
#define Button3_GPIO_Port GPIOB
#define Button2_Pin GPIO_PIN_6
#define Button2_GPIO_Port GPIOB
#define Button1_Pin GPIO_PIN_7
#define Button1_GPIO_Port GPIOB
#define Led1_Pin GPIO_PIN_8
#define Led1_GPIO_Port GPIOB
#define Relay7_Pin GPIO_PIN_9
#define Relay7_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
