#include "usart_hmi.h"

/*==============================
�������ܽ���
1.����ˢ�´������� HMISendstart��
2.���ҳ��ֱ����ʼ1....8����鵽���¡� HMIRead ��
3.��ʼ��Ӧ8����ʾ����
4.��ʾ����֮�󣬵��ö�Ӧ�Ľ���������HMIClose(page)��
5.ҳ��ص����˵���������һ��ѭ��

===============================*/


/**************************************************************************
�������ܣ�������ˢ��ҳ��
��ڲ�������
����  ֵ����
//uint8_t Usart_hmi_Trasmt[20]={0};
**************************************************************************/
void HMISendstart(void)
{
	LED1_ON;
//	BEEP_ON;
	HAL_Delay(100);
	memcpy(Usart_hmi_Trasmt,"page ��ҳ",100);
	HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,20,1000);		//������Usart_hmi_Trasmt���ݷ��ͳ�ȥ
	Usart_hmi_Trasmt[0]=0xff;
	HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
	HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
	HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
	LED1_OFF;
//	BEEP_OFF;
}


/**************************************************************************
�������ܣ������ѯ�������ж�������һ����ʾ����
��ڲ�������
����  ֵ�����յ���ָ��
**************************************************************************/
int HMIRead(void)		  //�ַ������ͺ���
{	
	if(usart_hmicplt_flag==1)
	{
		usart_hmicplt_flag=0;
		switch(Usart_hmi_Recv[0])
		{
			case 1:	usart_hmi_action=1;break;
			case 2:	usart_hmi_action=2;break;
			case 3:	usart_hmi_action=3;break;
			case 4:	usart_hmi_action=4;break;
			case 5:	usart_hmi_action=5;break;
			case 6:	usart_hmi_action=6;break;
			case 7:	usart_hmi_action=7;break;
			case 8:	usart_hmi_action=8;break;	
			default: break;
		}
		return usart_hmi_action;
	}
	else return 0;
}

/**************************************************************************
�������ܣ�����رպ��������һ�ζ�����ʾ֮���ϵͳ���йر�
��ڲ�������
����  ֵ�����յ���ָ��
**************************************************************************/
void HMIClose(int page)		 
{	
	//===============����һ���رյ�����ر��˶��ṹ�ȵȵĲ���===========//
		switch(page)
		{
			case 1:	HMISendPage(1);break;
			case 2:	HMISendPage(2);break;
			case 3:	HMISendPage(3);break;
			case 4:	HMISendPage(4);break;
			case 5:	HMISendPage(5);break;
			case 6:	HMISendPage(6);break;
			case 7:	HMISendPage(7);break;
			case 8:	HMISendPage(8);break;	
			default: break;
		}
}

/**************************************************************************
�������ܣ�������ѡ�������ҳ��
��ڲ�������
����  ֵ����
**************************************************************************/
void HMISendPage(int page)
{
	switch (page)
	{
		case 0:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ���˵�",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 1:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����1",150);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1500);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 2:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����2",150);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1500);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 3:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����3",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 4:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����4",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 5:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����5",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 6:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����6",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 7:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����7",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 8:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page ����8",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		default:break;
	}
}



/**************************************************************************
�������ܣ���������
��ڲ�������
����  ֵ����
**************************************************************************/
void HMI_task(void)
{
	int action;
	
	action=HMIRead();								//====��鴮�����Ƿ������񰴼�����,�Ӷ��ֱ�����8�������������֮��
	switch (action)
	{
		case 1:
		{	
			Beep_Flash(3,300);
		
		}break;
		
			case 2:
		{
			Beep_Flash(3,300);
		
		}break;	
		
		case 3:
		{
			Beep_Flash(3,300);
		
		}break;
		
		case 4:
		{
		
			Beep_Flash(3,300);
			
		}break;
	
		case 5:
		{
			Beep_Flash(3,300);
		
		}break;
		
		case 6:
		{
			Beep_Flash(3,300);
		
		}break;

		case 7:
		{
			Beep_Flash(3,300);
		
		}break;		

		case 8:
		{
			Beep_Flash(3,300);
		
		}break;	

		default:break;
	}
}
	
