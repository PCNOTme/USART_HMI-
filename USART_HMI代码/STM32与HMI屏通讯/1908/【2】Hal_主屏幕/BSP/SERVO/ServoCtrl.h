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
	float ServoSpeed; // ��ÿ��	
	float ServoAngleNow; // ��ǰ�Ƕ�
	uint32_t TimeLast;  // �ϴ����ýǶ�ʱ��
	uint32_t ServoAngleSet; // 0 ~ 180��
	uint8_t MaxAngleSet; // ������ýǶ�
	uint8_t MinAngleSet; // ��С���ýǶ�
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
// ���ö���ٶ� �Ƕ�
void setServo(ServoCtrl_t *ServoCtr,float Speed,uint8_t Angle);
uint32_t Angle2Pulse(float angle,uint8_t exchange);
float AngleRun(ServoCtrl_t *ServoCtr);



#endif

