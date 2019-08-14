#ifndef __ENCODER_H
#define __ENCODER_H
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "tim.h"

void Encoder_Init(void);
int Read_Encoder_Speed(u8 TIMX);
int Read_Encoder_Locat(u8 TIMX);


#endif
