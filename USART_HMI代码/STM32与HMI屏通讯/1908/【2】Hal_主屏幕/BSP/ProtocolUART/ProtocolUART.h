#ifndef __ProtocolUART_H__
#define __ProtocolUART_H__

#ifdef __cplusplus
 extern "C" {
#endif
	 
	 
#include "main.h"
#include "stdint.h"

#ifndef BYTE
typedef unsigned char	BYTE;
#endif
#ifndef UINT
typedef unsigned int	UINT;
#endif
#ifndef UINT16
typedef unsigned short  UINT16;
#endif

#ifndef MAKEWORD
#define MAKEWORD(low, high)		(((BYTE)(low)) | (((BYTE)(high)) << 8))
#endif


#ifndef TABLESIZE
#define TABLESIZE(table)    (sizeof(table)/sizeof(table[0]))
#endif

//#define PRO_SUPPORT_CHECK_SUM

/* SynchFrame DataLen Data  */
/*     2Byte 	2Byte  N Byte   */
// 无CheckSum情况下最小长度: 2 + 2 = 4

// 有CheckSum情况下最小长度: 2 + 2 + 1 = 5
// 无CheckSum情况下最小长度: 2 + 2 = 4

#ifdef PRO_SUPPORT_CHECK_SUM
#define DATA_PACKAGE_MIN_LEN		4
#else
#define DATA_PACKAGE_MIN_LEN		4
#endif

// 同步帧头
#define CMD_HEAD1	0xFF
#define CMD_HEAD2	0x55
#define DATA_LEN 256	// 数据块的最大长度，不要超过2K

// 数据块定义(用户有效数据)
#pragma pack(push,1)
typedef struct {
	// 用户自定义数据
	uint8_t    cmdID;		// 命令id
	uint32_t   data;     // 数据
} SProtocolData;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct {
	// 用户自定义数据
	uint16_t   X;		// 命令id
	uint16_t   Y;     // 数据
} Position_x_y;
#pragma pack(pop)

/**
 * 硬件发送函数 
 */
extern void protocolDataSend(const BYTE *pData, UINT len);
/**
 * 解析每一帧数据 协议解析回调函数
 */
extern void procParse(const BYTE *pData, UINT len);

// 协议解析函数 在串口空闲中断中运行
int parseProtocol(const BYTE *pData, UINT len);

// 协议发送函数
uint8_t sendProtocol(const BYTE *pData, int len);

#ifdef __cplusplus
}
#endif

#endif

