#ifndef __UART_H__
#define __UART_H__

//UART Ïà¹Øº¯Êý------------------------

void UART_Init();
void UART_Send_Byte(unsigned char mydata);
void UART_Send_Str(char *s);
void UART_Send_Enter();
void u32tostr(unsigned long dat,char *str);
unsigned long strtou32(char *str);
void UART_Put_Num(unsigned long dat);
void UART_Put_Inf(char *inf,unsigned long dat);
void binary(unsigned char dat);

//UART----END-------------------------------
#endif