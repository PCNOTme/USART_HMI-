#ifndef __LED_H
#define __LED_H
#include "main.h"
#include "stm32f1xx_hal.h"

#define BEEP PBout(8) 
#define LED1 PBout(9) 
#define LED2 PCout(13) 
#define BEEP_PORT 	 GPIOB
#define BEEP_PIN		GPIO_PIN_8
#define LED1_PORT 	 GPIOA
#define LED1_PIN		GPIO_PIN_4
#define LED2_PORT 	 GPIOC
#define LED2_PIN 		GPIO_PIN_13


//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入
/////////////////////////////////////////////////////////////////
#define BEEP_ON   		HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_SET);		//注意LED灯的电路状态，该板LED灯接VCC
#define BEEP_OFF			HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_RESET);
#define BEEP_TOGGLE		HAL_GPIO_TogglePin(BEEP_PORT,BEEP_PIN);

#define LED1_ON   		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);		//注意LED灯的电路状态，该板LED灯接VCC
#define LED1_OFF			HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_SET);
#define LED1_TOGGLE		HAL_GPIO_TogglePin(LED1_PORT,LED1_PIN);

#define LED2_ON   		HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_SET);			//电路状态同LED1相反
#define LED2_OFF			HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_RESET);
#define LED2_TOGGLE		HAL_GPIO_TogglePin(LED2_PORT,LED2_PIN);

void Led_Flash(u8 n,u16 time);
void Led1_Flash(u8 n,u16 time);
void Led2_Flash(u8 n,u16 time);
void Beep_Flash(u8 n,u16 time);
#endif

