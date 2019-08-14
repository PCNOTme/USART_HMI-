#include "key.h"

/**************************************************************************
函数功能：KEY中断标志位（上升沿触发）
入口参数：中断PIN脚 
返回  值：无
**************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin==KEY1_PIN){key_flag=1;}
	if(GPIO_Pin==KEY2_PIN){key_flag=1;}
}

