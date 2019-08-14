/*********************************************************************************/	 
//STM32液晶屏开发板示例程序
//技术支持:www.tjc1688.com
//深圳市淘晶驰电子有限公司									  
/*********************************************************************************/	 
#ifndef __SPI_H
#define __SPI_H
#include "sys.h"										  
void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

