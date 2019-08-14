#ifndef __USART_HMI_H
#define __USART_HMI_H
#include "main.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include "led.h"
#include "string.h"


extern uint8_t Usart_hmi_Trasmt[20];
extern uint8_t Usart_hmi_Recv[20];
extern __IO u8 usart_hmicplt_flag;

extern __IO u8 usart_hmi_action;


void HMISendstart(void);
int HMIRead(void);
void HMIClose(int page);		
void HMISendPage(int page);
void HMI_task(void);


#endif
