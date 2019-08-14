#include "usart_hmi.h"

/*==============================
函数功能介绍
1.首先刷新串口屏【 HMISendstart】
2.点击页面直到开始1....8被检查到按下【 HMIRead 】
3.开始对应8个演示动作
4.演示结束之后，调用对应的结束函数【HMIClose(page)】
5.页面回到主菜单，进入下一次循环

===============================*/


/**************************************************************************
函数功能：串口屏刷新页面
入口参数：无
返回  值：无
//uint8_t Usart_hmi_Trasmt[20]={0};
**************************************************************************/
void HMISendstart(void)
{
	LED1_ON;
//	BEEP_ON;
	HAL_Delay(100);
	memcpy(Usart_hmi_Trasmt,"page 主页",100);
	HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,20,1000);		//将数组Usart_hmi_Trasmt数据发送出去
	Usart_hmi_Trasmt[0]=0xff;
	HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
	HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
	HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
	LED1_OFF;
//	BEEP_OFF;
}


/**************************************************************************
函数功能：任务查询函数，判断启动哪一个演示动作
入口参数：无
返回  值：所收到的指令
**************************************************************************/
int HMIRead(void)		  //字符串发送函数
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
函数功能：任务关闭函数，完成一次动作演示之后对系统进行关闭
入口参数：无
返回  值：所收到的指令
**************************************************************************/
void HMIClose(int page)		 
{	
	//===============还有一波关闭电机，关闭运动结构等等的操作===========//
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
函数功能：串口屏选择回跳的页面
入口参数：无
返回  值：无
**************************************************************************/
void HMISendPage(int page)
{
	switch (page)
	{
		case 0:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 主菜单",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 1:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本1",150);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1500);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 2:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本2",150);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1500);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 3:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本3",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 4:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本4",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 5:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本5",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 6:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本6",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 7:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本7",100);
			HAL_UART_Transmit(&huart_hmi,Usart_hmi_Trasmt,strlen((char *)Usart_hmi_Trasmt),1000);
			Usart_hmi_Trasmt[0]=0xff;
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
			HAL_UART_Transmit(&huart_hmi,&Usart_hmi_Trasmt[0],1,100);
		}	break;
		
		case 8:
		{
			LED1_TOGGLE;
			memcpy(Usart_hmi_Trasmt,"page 基本8",100);
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
函数功能：任务处理函数
入口参数：无
返回  值：无
**************************************************************************/
void HMI_task(void)
{
	int action;
	
	action=HMIRead();								//====检查串口屏是否有任务按键按下,从而分别启动8个任务，启动完毕之后
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
	
