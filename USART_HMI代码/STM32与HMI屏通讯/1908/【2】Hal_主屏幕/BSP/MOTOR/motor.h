#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "tim.h"


#define PWMA   TIM1->CCR1    //倒立摆仅使用一路驱动 使用的A路
#define AIN1   PBout(12)     //倒立摆仅使用一路驱动 使用的A路
#define AIN2   PBout(13)     //倒立摆仅使用一路驱动 使用的A路


void Moto_Set_Pwm(TIM_HandleTypeDef*htimx,int channelx,int ccrx);
int Xianfu_Pwm(int Moto);
int myabs(int a);
void Motor_Init(void);
	


#endif
