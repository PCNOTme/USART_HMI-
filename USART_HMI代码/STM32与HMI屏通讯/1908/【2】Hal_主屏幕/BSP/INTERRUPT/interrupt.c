#include "interrupt.h"

#define HEADER1	0xFF
#define HEADER2	0x55
#define ENDER  0xFD

int tt=0;
/**************************************************************************
�������ܣ��ж�ʼ������
��ڲ�������
����  ֵ����
**************************************************************************/
void Interrupt_Init(void)
{
//	HAL_TIM_Base_Start_IT(&htim1);
	HAL_UART_Receive_IT(&huart_hmi,&Usart_hmi_Recv[0],1);
//	__HAL_UART_ENABLE_IT(&huart_opmv, UART_IT_IDLE);//ʹ��idle�ж�
//	HAL_UART_Receive_DMA(&huart_opmv, Usart_opmv_dmaRecv,BUFFER_SIZE);
	HAL_UART_Receive_IT(&huart_opmv,&Usart_opmv_itRecv[0],5);
}


/**************************************************************************
�������ܣ��жϴ�����
��ڲ�������ʱ����
����  ֵ����
**************************************************************************/
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if (htim == (&htim1))
//	{
////			Encoder_value=Read_Encoder_Locat(4);
//	}
//}


/**************************************************************************
�������ܣ�����������жϴ�����
��ڲ�����������
����  ֵ����
**************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart_opmv)
	{
		LED1_TOGGLE;		
		for(int i=0;i<NUM;i++){Openmv_Receive_Data(Usart_opmv_itRecv[i]);	}	
		usart_opmvcplt_flag=1;
		HAL_UART_Receive_IT(&huart_opmv,&Usart_opmv_itRecv[0],NUM);
	}
	if(huart==&huart_hmi)
	{		
		usart_hmicplt_flag=1;
		HAL_UART_Receive_IT(&huart_hmi,&Usart_hmi_Recv[0],1);
	}

}



/**************************************************************************
�������ܣ�OpenMV�������ݴ�������HEADER1+HEADER2+����.....+ENDER��
��ڲ�������
����  ֵ����
**************************************************************************/
void Openmv_Receive_Data(uint8_t data)
{
//	if(recv_end_flag ==1)
//		{
////			printf("rx_len=%d\r\n",rx_len);//��ӡ���ճ���
////			HAL_UART_Transmit(&huart1,rx_buffer, rx_len,200);�������ݴ�ӡ����
//			for(uint8_t i=0;i<rx_len;i++)
//				{
//					Usart_opmv_dmaRecv[i]=0;//����ջ���
//				}
//			rx_len=0;//�������
//			recv_end_flag=0;//������ս�����־λ
//		HAL_UART_Receive_DMA(&huart_opmv, Usart_opmv_dmaRecv,BUFFER_SIZE);
//		}

//		
//============================================================================	
		
		if(state00==0&&data==HEADER1)
		{
			state00=1;
			openmv[bit_number++]=data;
		}
		else if(state00==1&&data==HEADER2)
		{
			state00=2;
			openmv[bit_number++]=data;
		}
		else if(state00==2)
		{
			openmv[bit_number++]=data;
			if(bit_number>=NUM-1)
			{
				state00=3;
			}
		}
		else if(state00==3)		//����Ƿ���ܵ�������־
		{
			if(data==ENDER)
			{
				openmv[bit_number++]=data;
				state00 = 0;
				bit_number=0;
			}
//			else if(data!=ENDER)
//			{
//			 state00 = 0;
//				for(int i=0;i<NUM;i++)
//				{
//					openmv[i]=0x00;
//				}           
//			}
		}    
		else
		{
			state00 = 0;
			bit_number=0;
			for(int i=0;i<NUM;i++)
			{
			 openmv[i]=0x00;
		 }
		}
}



