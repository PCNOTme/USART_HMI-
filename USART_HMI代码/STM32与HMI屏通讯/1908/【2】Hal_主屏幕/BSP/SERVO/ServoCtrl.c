#include "servoctrl.h"
#include <string.h>
#include "arm_math.h"
#include <math.h>

#define LIMIT( x,min,max ) ( (x) < (min)  ? (min) : ( (x) > (max) ? (max) : (x) ) ) //大小限制

#define TEST (0)
ServoCtrl_t ServoCtrlS1;
ServoCtrl_t ServoCtrlS2;

uint32_t Angle2Pulse(float angle,uint8_t exchange); 
float AngleRun(ServoCtrl_t *ServoCtr);

void ServoCtrlInit(void) 
{
	/* 初始化舵机*/
	ServoCtrlS1.MinAngleSet = 0;
	ServoCtrlS1.MaxAngleSet = 150;
	ServoCtrlS1.ServoAngleSet = 0;
	ServoCtrlS1.ServoAngleNow = 0;
	ServoCtrlS1.ServoSpeed = 30;

	ServoCtrlS2.MinAngleSet = 0;
	ServoCtrlS2.MaxAngleSet = 180;
	ServoCtrlS2.ServoAngleSet = 0;
	ServoCtrlS2.ServoAngleNow = 0;
	ServoCtrlS2.ServoSpeed = 30;
	
	CoordinateSet.speed = 30;
	
	__HAL_TIM_SET_COMPARE(&SxTime,S1_OUT,Angle2Pulse(AngleRun(&ServoCtrlS1),1));
	__HAL_TIM_SET_COMPARE(&SxTime,S2_OUT,Angle2Pulse(AngleRun(&ServoCtrlS2),1));

	HAL_TIM_PWM_Start_IT(&SxTime,S1_OUT);
	HAL_TIM_PWM_Start_IT(&SxTime,S2_OUT);
  
}

#if TEST 
uint32_t plues;
#endif


CoordinateSet_t CoordinateSet;
/*
			Y
			^
			|
			|
		__Z|_______> X
      |
	两轴云台控制
*/


void ServoCoordinateRun(void)
{
	float z_temp;
	float angle1,angle2;
	/* X Y 轴舵机 */
	if(CoordinateSet.y < 0) CoordinateSet.y = 0;
	angle2 = atan2f(CoordinateSet.x,CoordinateSet.y) * 180.f / PI;
	ServoCtrlS2.ServoAngleSet = 90.f - angle2;
	/* Z 轴舵机 */
	z_temp = CoordinateSet.x * CoordinateSet.x + CoordinateSet.y * CoordinateSet.y;
	arm_sqrt_f32(z_temp,&z_temp);
	angle1 = atan2f(z_temp,CoordinateSet.z) * 180.f / PI;
	ServoCtrlS1.ServoAngleSet = angle1;
	/* 舵机速度设置 度每秒 */
	ServoCtrlS1.ServoSpeed = CoordinateSet.speed;
	ServoCtrlS2.ServoSpeed = CoordinateSet.speed;
}


// 设置舵机速度 角度
void setServo(ServoCtrl_t *ServoCtr,float Speed,uint8_t Angle) // 度每秒	
{
	ServoCtr->ServoSpeed = Speed;
	ServoCtr->ServoAngleSet = Angle;
}

/* angle 角度 exchange 设置反方向为0度 */
uint32_t Angle2Pulse(float angle,uint8_t exchange)
{
	#define MaxPulse 2500.f
	#define MinPulse 500.f
	if(angle > 180.f ) return 0;
	if(exchange)
		return  (uint32_t)((180 - angle)*((MaxPulse - MinPulse)/180.f)+MinPulse);
	else
		return (uint32_t)(angle*((MaxPulse - MinPulse)/180.f)+MinPulse);
}


/* 角度控制 速度控制 */
float AngleRun(ServoCtrl_t *ServoCtr)
{
	float temp;
	
	if(ServoCtr->ServoAngleSet > ServoCtr->MaxAngleSet) // 判断是不是在该舵机设置范围内
	{
		ServoCtr->ServoAngleSet = ServoCtr->MaxAngleSet;
	}
	else if(ServoCtr->ServoAngleSet < ServoCtr->MinAngleSet)
	{
		ServoCtr->ServoAngleSet = ServoCtr->MinAngleSet;
	}
	
	if(ServoCtr->ServoAngleSet == ServoCtr->ServoAngleNow)
	{
		ServoCtr->TimeLast = HAL_GetTick(); // 保存当前时间
		return ServoCtr->ServoAngleSet;
	}
	else
	{
		temp = HAL_GetTick() - ServoCtr->TimeLast; // 获取当前时间之差
		temp = 1000.f / temp; //  计算当前设置数值
		ServoCtr->TimeLast = HAL_GetTick(); // 保存当前时间
		temp = (float)ServoCtr->ServoSpeed / temp;
		
		if(ServoCtr->ServoAngleSet > ServoCtr->ServoAngleNow)
		{	
			temp = ServoCtr->ServoAngleNow + temp;	
			if(temp >= ServoCtr->ServoAngleSet) 
				ServoCtr->ServoAngleNow = ServoCtr->ServoAngleSet;	
			else
				ServoCtr->ServoAngleNow = temp;
		}
		else
		{
			temp = ServoCtr->ServoAngleNow - temp;
			if(temp <= ServoCtr->ServoAngleSet) 
				ServoCtr->ServoAngleNow = ServoCtr->ServoAngleSet;	
			else
				ServoCtr->ServoAngleNow = temp;
		}
		return ServoCtr->ServoAngleNow;
	}
}


// pwm 脉冲中断 使舵机运动更流畅 
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	 if(htim == &SxTime)
	 {
		 if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		 {			 
			  #if TEST 
			  __HAL_TIM_SET_COMPARE(&SxTime,S1_OUT,plues);
			  #else
				__HAL_TIM_SET_COMPARE(&SxTime,S1_OUT,Angle2Pulse(AngleRun(&ServoCtrlS1),1));
			  #endif
		 }
		 if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		 {
			 __HAL_TIM_SET_COMPARE(&SxTime,S2_OUT,Angle2Pulse(AngleRun(&ServoCtrlS2),0));
		 }		
	 }
} 
 
 /**************************************/
 
 

