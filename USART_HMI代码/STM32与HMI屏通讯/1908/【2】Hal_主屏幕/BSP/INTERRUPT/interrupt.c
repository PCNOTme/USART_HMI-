#include "interrupt.h"

#define HEADER1	0xFF
#define HEADER2	0x55
#define ENDER  0xFD

int tt=0;
/**************************************************************************
函数功能：中断始化函数
入口参数：无
返回  值：无
**************************************************************************/
void Interrupt_Init(void)
{
//	HAL_TIM_Base_Start_IT(&htim1);
	HAL_UART_Receive_IT(&huart_hmi,&Usart_hmi_Recv[0],1);
//	__HAL_UART_ENABLE_IT(&huart_opmv, UART_IT_IDLE);//使能idle中断
//	HAL_UART_Receive_DMA(&huart_opmv, Usart_opmv_dmaRecv,BUFFER_SIZE);
	HAL_UART_Receive_IT(&huart_opmv,&Usart_opmv_itRecv[0],5);
}


/**************************************************************************
函数功能：中断处理函数
入口参数：定时器数
返回  值：无
**************************************************************************/
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//	if (htim == (&htim1))
//	{
////			Encoder_value=Read_Encoder_Locat(4);
//	}
//}


/**************************************************************************
函数功能：串口屏完成中断处理函数
入口参数：串口数
返回  值：无
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
函数功能：OpenMV串口数据处理函数【HEADER1+HEADER2+数据.....+ENDER】
入口参数：无
返回  值：无
**************************************************************************/
void Openmv_Receive_Data(uint8_t data)
{
//	if(recv_end_flag ==1)
//		{
////			printf("rx_len=%d\r\n",rx_len);//打印接收长度
////			HAL_UART_Transmit(&huart1,rx_buffer, rx_len,200);接收数据打印出来
//			for(uint8_t i=0;i<rx_len;i++)
//				{
//					Usart_opmv_dmaRecv[i]=0;//清接收缓存
//				}
//			rx_len=0;//清除计数
//			recv_end_flag=0;//清除接收结束标志位
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
		else if(state00==3)		//检测是否接受到结束标志
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



