#ifndef __KEY_H
#define __KEY_H	 
#include "main.h"
#include "stm32f1xx_hal.h"
#include "led.h"
 
#define KEY1 PCin(14)
#define KEY2 PCin(15)

#define KEY1_PIN 		GPIO_PIN_14
#define KEY2_PIN 		GPIO_PIN_15

extern __IO u8 key_flag;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif 
