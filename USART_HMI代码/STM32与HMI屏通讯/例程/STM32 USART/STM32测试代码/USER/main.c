/*********************************************************************************/	 
//STM32串口示例程序
//更多资料：www.tftmcu.taobao.com
//单片机STM32F103VCT6  外部晶振8MHZ  波特率：9600									  
/*********************************************************************************/	

#include "delay.h"
#include "sys.h"
#include "usart.h"	 
u8 idfind(u8 *buf,u8 *val,u8 len);
void HMISends(char *buf1);
void HMISendb(u8 buf);
void beepms(u16 va);
u8 key,beep;
void beepms(u16 va)
{
	beep=1;
	delay_ms(va);
	beep=0;
}

void HMISendstart(void)
	{
	 	delay_ms(200);
		HMISendb(0xff);
		delay_ms(200);
	}
						
int main(void)
 {	   	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	  	 //串口初始化为9600
	HMISendstart();          //为确保串口HMI正常通信
	{ 
		HMISends("cls RED");  //发送串口指令
		HMISendb(0xff);		  //发送结束符 0XFF 0XFF 0XFF
		delay_ms(1000);
    	HMISends("cls GREEN");
		HMISendb(0xff);
    	delay_ms(1000);
    	HMISends("cls BLUE");
		HMISendb(0xff);
		delay_ms(1000);
		HMISends("cls BLACK");
		HMISendb(0xff);
		delay_ms(1000);
		HMISends("page 4");
		HMISendb(0xff);
		HMISends("t0.txt=\"春风不度玉门关\"");
		HMISendb(0xff);
		HMISends("xstr 0,0,40,40,0,RED,BLACK,1,1,1,中国");//不建议使用这种指令去显示汉字，建议在上位机上输入你要显示的汉字
		HMISendb(0xff);	
	}
	while(1);
}
 
void HMISends(char *buf1)		  //字符串发送函数
{
	u8 i=0;
	while(1)
	{
	 if(buf1[i]!=0)
	 	{
			USART_SendData(USART1,buf1[i]);  //发送一个字节
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//等待发送结束
		 	i++;
		}
	 else 
	 return ;

		}
}


void HMISendb(u8 k)		         //字节发送函数
{		 
	u8 i;
	 for(i=0;i<3;i++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(USART1,k);  //发送一个字节
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//等待发送结束
		}
	 else 
	 return ;

	 } 
} 



