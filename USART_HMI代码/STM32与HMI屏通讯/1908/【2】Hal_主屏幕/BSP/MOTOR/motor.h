#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "tim.h"


#define PWMA   TIM1->CCR1    //�����ڽ�ʹ��һ·���� ʹ�õ�A·
#define AIN1   PBout(12)     //�����ڽ�ʹ��һ·���� ʹ�õ�A·
#define AIN2   PBout(13)     //�����ڽ�ʹ��һ·���� ʹ�õ�A·


void Moto_Set_Pwm(TIM_HandleTypeDef*htimx,int channelx,int ccrx);
int Xianfu_Pwm(int Moto);
int myabs(int a);
void Motor_Init(void);
	


#endif
