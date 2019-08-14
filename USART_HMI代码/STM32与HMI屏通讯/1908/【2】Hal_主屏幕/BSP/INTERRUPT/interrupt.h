#ifndef __INTERRUPT_H
#define __INTERRUPT_H
#include "main.h"
#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "tim.h"
#include "encoder.h"
#include "led.h"
#include "usart.h"

extern uint8_t Usart_hmi_Trasmt[20];
extern uint8_t Usart_hmi_Recv[20];
extern uint8_t Usart_opmv_itRecv[NUM];
extern uint8_t Usart_opmv_dmaRecv[NUM];
extern uint8_t Usart_opmv_Temp1[NUM];
extern uint8_t Usart_opmv_Temp2[NUM];

extern __IO int Encoder_value;
extern __IO u8 usart_hmicplt_flag;
extern __IO u8 usart_opmvcplt_flag;
extern uint8_t rx_len;
extern uint8_t recv_end_flag;
extern uint32_t tick,tick1,tick2,tick3;
extern  u8 openmv[NUM];	//´æÈ¡Êý¾Ý
extern 	 u8 state00;	
extern 	 u8 bit_number;	

void Interrupt_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void Openmv_Receive_Data(uint8_t data);

#endif
