#ifndef __cmd_H__
#define __cmd_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "cmsis_os.h"


extern osThreadId cmdTaskHandle;
//extern ringbuff_t uartrxbuff,uarttxbuff;


#define MotionUP   0x01
#define MotionSTOP 0x00
#define MotionDOWN 0x02

/* 发送命令 */
#define Send_1  0x01
#define Send_2  0x02
#define Send_3  0x03

/* 接收命令 */
#define Rec_Position    0x01
#define Rec_2						0x02
#define Rec_3					  0x03
#define Rec_4  					0x04
#define Rec_5  					0x05
#define Rec_6    				0x06
#define Rec_7    				0x07
#define Rec_8    		    0x08  // P  I 参数
#define Rec_9   			  0x09  // D 和 PID更新标志
#define Rec_10   		    0x0a  // P  I 参数
#define Rec_11   				0x0b  // D 和 PID更新标志
#define Rec_12    	    0x0c

#define Rec_13   			  0xFE  // MCU复位
#define Rec_14   			  0xFF

void cmd_init(void);

#ifdef __cplusplus
}
#endif

#endif
