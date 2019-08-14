/*********************************************************************************/	 
//STM32液晶屏开发板示例程序
//技术支持:www.tjc1688.com
//深圳市淘晶驰电子有限公司									  
/*********************************************************************************/	 
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
#define beep PCout(12)// PE5	

void LED_Init(void);//初始化

		 				    
#endif
