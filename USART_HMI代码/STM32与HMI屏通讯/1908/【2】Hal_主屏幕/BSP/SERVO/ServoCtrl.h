#ifndef __servoctrl_H
#define __servoctrl_H

#include "main.h"
#include "stm32f1xx_hal.h"
//#include "usart.h"
#include "tim.h"

#define S1_OUT TIM_CHANNEL_1
#define S2_OUT TIM_CHANNEL_2
#define S3_OUT TIM_CHANNEL_3
#define S4_OUT TIM_CHANNEL_4
#define SxTime htim3
typedef struct 
{
	float ServoSpeed; // 度每秒	
	float ServoAngleNow; // 当前角度
	uint32_t TimeLast;  // 上次设置角度时间
	uint32_t ServoAngleSet; // 0 ~ 180°
	uint8_t MaxAngleSet; // 最大设置角度
	uint8_t MinAngleSet; // 最小设置角度
} ServoCtrl_t;

/*

*/
typedef struct 
{
	int32_t x;
	int32_t y;
	int32_t z;
	uint32_t speed;
}CoordinateSet_t;

extern ServoCtrl_t ServoCtrlS1;
extern ServoCtrl_t ServoCtrlS2;

extern CoordinateSet_t CoordinateSet;

void ServoCtrlInit(void);
void ServoCoordinateRun(void);
// 设置舵机速度 角度
void setServo(ServoCtrl_t *ServoCtr,float Speed,uint8_t Angle);
uint32_t Angle2Pulse(float angle,uint8_t exchange);
float AngleRun(ServoCtrl_t *ServoCtr);



#endif

