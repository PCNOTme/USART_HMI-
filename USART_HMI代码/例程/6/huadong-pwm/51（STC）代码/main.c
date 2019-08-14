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
sbit swich=P1^3;

uchar uart_dat[32]=0;
idata long  count_num=0;
uchar uart_num=0;
uchar endflag = 0;
uchar comm_dat[32];
uchar comm_len=0;
uchar k=0;
signed char PWM=0;
bit   new_en=0;
uchar ButtonFlag = 0;


uchar xdata gettxtval[64];
unsigned long getnumval=0; 
uchar xdata Tx_comm[64];
/*******************���Ե�Ƭ��STC12LE5A60S2******************************/
/*******************���� 33MHz*******************************************/


void MEMCOPY(uchar *dest,uchar *src,uint len)
{
	while(len--)
	{
		*dest++ = *src++;
	}
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڳ�ʼ��
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵������
 - ����˵������
 **************************************************************************/
void UART_Init()     
{
 PCON|=0x00; //PCON�����λSMOD=1ʱ�����ʼӱ� 
 TMOD=0x20;  //ʱ��1Ϊ��ʽ2 ��ֵ�Զ�װ�� ����������
 TH1=0xf7;   //��ʱ����ʼΪ0XF7������Ϊ33MHz��������ʵ�ʲ����Ĳ�����Ϊ9600bps
 TL1=0xf7;	 //ͬ��  f7
 
 TH0=(65536-50000)/256;
 TL0=(65536-50000)%256;

 SCON=0x50;	 //��������Ϊ��ʽ1,REN=1,�������
 TR1=1;      //������ʱ��1
 TR0=1;      //������ʱ��0
 ET0=1;		 //ʹ�ܶ�ʱ��T0�ж�
 ES=1;       //ʹ�ܴ��ڽ����жϣ�
 EA=1;       //�������ж�
}


void timer0()interrupt  1//��ʱ���жϺ���
{
	TH0=0xFF;//(65536-50000)/256;
 	TL0=0x00;//(65536-50000)%256;
	//swich=~swich; 
	if(k<PWM)
	swich = 0;
	if((k<=100)&&(k>PWM))
	swich = 1;
	if(k>=100)
	k=0;
	k++;


}

void uart_get_int(void) interrupt  4//�����жϽ��պ���
{
    uchar a=0;
	
	if(RI==1)
	{	   
		RI = 0; 
		a = SBUF;
		uart_dat[uart_num] = a;
		uart_num++;
		if(a==0xff)
		{
			endflag++;
			if(endflag == 3)
			{
				comm_len = uart_num;
				MEMCOPY(comm_dat,uart_dat,comm_len);
				uart_num = 0;
				endflag = 0;
			}
		}  
		else
		{
			endflag = 0;	
		}
	}
	UART_Init();
}

/**************************************************************************
 - ����������51��Ƭ���Ĵ��ڷ����ֽڵĺ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����mydata:Ҫ���͵�һ���ֽ�
 - ����˵������
 - ע������һ���ֽڣ��Ǵ��ڷ��͵Ļ�������
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
 - ����������51��Ƭ���Ĵ��ڷ����ַ���
 - ����ģ�飺STC51���ڲ���
 - �������ԣ��ⲿ��ʹ�û�ʹ��
 - ����˵����s:ָ���ַ�����ָ��
 - ����˵������
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

void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}

void TouchEventReturn(void)
{
	switch(comm_dat[1])
	{
	case 0:
		//ҳ��0���ݴ���
		if(comm_dat[2]==1)
		{
			//ȷ����ǰ���¿ؼ�IDΪ1
			if(comm_dat[3]==0x01)
			{
				//ȷ���¼�Ϊ�����¼�
				ButtonFlag	= ~ButtonFlag;
				if(ButtonFlag)
				{
			  UART_Send_Str("q0.picc=1");
					  UART_Send_END();
					  swich = 0;
				}
				else
				{
					UART_Send_Str("q0.picc=0");
					UART_Send_END();
					swich = 1;
				}
			}
		}
		break;
	case 1:
		//ҳ��1���ݴ���
		break;
	case 2:
		//ҳ��2���ݴ���
		break;
	default:
		break;	
	}
}

void StringValueReturn(void)
{
	if(comm_len > 60)
		return;
	MEMCOPY(&gettxtval[0],&comm_dat[1],comm_len-1);	//�����ַ�����ͬ
	gettxtval[comm_len-1]=0;						//�����ַ���������־

}

void NumberValueReturn(void)
{
	getnumval  = ((unsigned long)comm_dat[4]) << 24;
	getnumval += ((unsigned long)comm_dat[3]) << 16;
	getnumval += ((unsigned long)comm_dat[2]) << 8;
	getnumval += (unsigned long)comm_dat[1];
}

void main(void)
{
 uint s=0;
 uchar flag = 1;
 P3M0&= ~0X02;
 P3M1|=0X02;   //TXǿ����
 
 UART_Init();  //��ʼ�����ڣ����ϵľ���Ϊ33MHz��ʵ�ʵĲ�����Ϊ9600bps 
 delayms(80);  //�ȴ���Ļ��ʼ��,����50ms����
 UART_Send_END();//����һ�ν�����������ϵ�����Ĵ����Ӳ�����  
 UART_Send_Str("page 0");
 UART_Send_END(); 
 delayms(2000);
// UART_Send_Str("t0.txt=\"40\"");
UART_Send_END();
  PWM=0;
  while(1)
  {
	if(comm_len)
	{
		switch(comm_dat[0])
		{
		case 0x65:		
			//���������¼�����
			TouchEventReturn();
			break;
		case 0x70:
			//�ַ����������ݷ���
			StringValueReturn();
			break;
		case 0x71:
			//16�������ͱ������ݷ���
			NumberValueReturn();
			PWM = (signed char)getnumval;
			if(PWM < 0)
			{
				PWM = 0;
			}
			else if(PWM > 100)
			{
				PWM = 100;
			}
			sprintf(Tx_comm,"t0.txt=\"%d\"",(unsigned int)PWM);
			UART_Send_Str(Tx_comm);
			UART_Send_END();
			break;
			//���ٴδ��������¼�����
		default:
		break;
		}
		comm_len = 0;
	}
   }
 while(1)
 {	
 	if(flag)
	{
 		
		PWM+=5;
		if(PWM >= 100)
		{
			flag = 0;
			PWM = 99;
		}
		delayms(500);
	}
	else
	{
		 PWM -= 5;
		 if(PWM <= 0)
		 {
		 	PWM = 1;
			flag = 1;
		 }
		 delayms(500);
	}
 }
/*   while(1)
  {
	if(comm_len)
	{
		switch(comm_dat[0])
		{
		case 0x65:		//���������¼�����
			if(comm_dat[1]==0)
			{
				//ȷ��ҳ��IDΪ0
				if(comm_dat[2]==1)
				{
					//ȷ����ǰ���¿ؼ�IDΪ1
					if(comm_dat[3]==0x01)
					{
						//ȷ���¼�Ϊ�����¼�
						ButtonFlag	= ~ButtonFlag;
						if(ButtonFlag)
						{
							  UART_Send_Str("s0.picc=1");
							  UART_Send_END();
							  swich = 0;
						}
						else
						{
							UART_Send_Str("s0.picc=0");
							UART_Send_END();
							swich = 1;
						}
					}
				}
			}
		break;
		//���ٴδ��������¼�����
		default:
		break;
		}
		comm_len = 0;
	}
   }

 
*/
}


