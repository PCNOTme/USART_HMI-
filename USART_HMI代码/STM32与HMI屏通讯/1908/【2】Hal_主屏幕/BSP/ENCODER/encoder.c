#include "encoder.h"


/**************************************************************************
函数功能：编码器初始化函数
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);	
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);	
}


/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder_Speed(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT;TIM2 -> CNT=0; 	break;
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT; TIM4 -> CNT=0;break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}


/**************************************************************************
函数功能：总时间读取编码器计数个数
入口参数：定时器
返回  值：霍尔传感位置
**************************************************************************/
int Read_Encoder_Locat(u8 TIMX)
{
	int Encoder_TIM;    
		 switch(TIMX)
		 {
			 case 2:  Encoder_TIM= (short)TIM2 -> CNT;	break;
			 case 4:  Encoder_TIM= (short)TIM4 -> CNT;	break;	
			 default:  Encoder_TIM=0;
		 }
			return Encoder_TIM;
}

