#include "encoder.h"


/**************************************************************************
�������ܣ���������ʼ������
��ڲ�������
����  ֵ����
**************************************************************************/
void Encoder_Init(void)
{
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);	
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);	
}


/**************************************************************************
�������ܣ���λʱ���ȡ����������
��ڲ�������ʱ��
����  ֵ���ٶ�ֵ
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
�������ܣ���ʱ���ȡ��������������
��ڲ�������ʱ��
����  ֵ����������λ��
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

