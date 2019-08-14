#include <REG51.H>  
#include <intrins.h>
#include <absacc.h>
#include <stdio.h> 
#include <math.h> 
#include <string.h> 
#include "uart.h"
sfr P3M0 =0xb1;
sfr P3M1 =0xb2;
//#include "ds1302.c"
#define uchar unsigned char
#define uint  unsigned int
int second,minute,hour,day,month,week,year,zwc,fwc,wdc,bal,txt,wendu;
uchar xdata buf[64];
/*******************测试单片机STC12LE5A60S2******************************/
/*******************晶振 33MHz*******************************************/




/**************************************************************************
 - 功能描述：51单片机的串口初始化
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：无
 - 返回说明：无
 **************************************************************************/
void UART_Init()     
{
 PCON|=0x00; //PCON的最高位SMOD=1时波特率加倍 
 TMOD=0x20;  //时器1为方式2 初值自动装入 产生波特率
 TH1=0xf7;   //定时器初始为0XF7，晶振为33MHz，本函数实际产生的波特率为9600bps
 TL1=0xf7;	 //同上  f7
 SCON=0x50;	 //串口设置为方式1,REN=1,允许接收
 TR1=1;      //启动定时器1
 ES=1;       //使能串口接收中断，
// EA=1;     //打开所有中断
}

/**************************************************************************
 - 功能描述：51单片机的串口发送字节的函数
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：mydata:要发送的一个字节
 - 返回说明：无
 - 注：发送一个字节，是串口发送的基础操作
 **************************************************************************/
void UART_Send_Byte(unsigned char mydata)	
{
 ES=0;
 TI=0;
 SBUF=mydata;
 while(!TI);
 TI=0;
 ES=1;
}

/**************************************************************************
 - 功能描述：51单片机的串口发送字符串
 - 隶属模块：STC51串口操作
 - 函数属性：外部，使用户使用
 - 参数说明：s:指向字符串的指针
 - 返回说明：无
 **************************************************************************/
void UART_Send_Str(char *s)
{
 int i=0;
 while(s[i]!=0)
 {
 	UART_Send_Byte(s[i]);
 	i++;
 }
 
}
void UART_Send_END(void)
{
	 UART_Send_Byte(0xFF);
	 UART_Send_Byte(0xFF);
	 UART_Send_Byte(0xFF);
}
/*
void UART_Send_HEX(char *buff,char len)
{
	while(len--)
	UART_Send_Byte(*buff++);
}
*/
void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}


/*
void distime()					 //显示时间	   	
{				
			 	
				sprintf(buf,"t0.txt=\"%02d:%02d:%02d\"",hour,minute,second);
			    UART_Send_Str(buf);
				UART_Send_END();
                sprintf(buf,"t1.txt=\"20%02d年%d月%2d日\"",year,month,day);
				UART_Send_Str(buf);
				UART_Send_END();						
				if(week==1)
				{
				 	UART_Send_Str("t2.txt=\"星期一\"");
				    UART_Send_END();
				}
				if(week==2)
				{
				     UART_Send_Str("t2.txt=\"星期二\"");
				     UART_Send_END();
				 }
				if(week==3)
				{
				     UART_Send_Str("t2.txt=\"星期三\"");
				     UART_Send_END();
				 }
				if(week==4)
				{
				     UART_Send_Str("t2.txt=\"星期四\"");
				     UART_Send_END();
				 }
				if(week==5)
				{
				     UART_Send_Str("t2.txt=\"星期五\"");
				     UART_Send_END();
				 }
				if(week==6)
				{
				     UART_Send_Str("t2.txt=\"星期六\"");
				     UART_Send_END();
				 }
				if(week==7)	
				{
				     UART_Send_Str("t2.txt=\"星期六\"");
				     UART_Send_END();
				 }
					  
}
*/
void main(void)
{
 uint s=0;
 second=50;minute=48;hour=12;day=15;month=7;week=2;year=16;bal=0;txt=0;wendu=0;
 P3M0&= ~0X02;
 P3M1|=0X02;   //TX强上拉
 UART_Init();  //初始化串口，板上的晶振为33MHz，实际的波特率为9600bps 
 delayms(80);//等待屏幕初始化,建议50ms以上
 UART_Send_END();//发送一次结束符，清除上电产生的串口杂波数据  
 UART_Send_Str("page 0");
 UART_Send_END(); 
 delayms(2000);
   while(s<=100)
  {
  	s++;
	if(bal!=100)
	{
		bal++;
		txt++;
		delayms(50);
	 	sprintf(buf,"j0.val=%d",bal);
	 	UART_Send_Str(buf);
	 	UART_Send_END();
	 	sprintf(buf,"t2.txt=\"%d%%\"",txt);
	 	UART_Send_Str(buf);
	 	UART_Send_END();
	}
	else
	 {
		UART_Send_Str("page 1");
		UART_Send_END();
		//UART_Send_Str("t2.txt=\"星期\"");	
		//UART_Send_END();
		while(1)
		{
			for(second=0;second<60;second++) 
			{	
				delayms(1000);
		 		sprintf(buf,"t0.txt=\"%02d:%02d:%02d\"",hour,minute,second);
		 		UART_Send_Str(buf);
		 		UART_Send_END();
				UART_Send_Str("t2.txt=\"星期四\"");
				UART_Send_END();
				sprintf(buf,"t3.txt=\"%d\"",wendu);
	 			UART_Send_Str(buf);
	 			UART_Send_END();
				wendu++;
		 	}
		 		second=0;
				wendu=0;	
		 }
		
	 }
	

	}
	;
 

}


