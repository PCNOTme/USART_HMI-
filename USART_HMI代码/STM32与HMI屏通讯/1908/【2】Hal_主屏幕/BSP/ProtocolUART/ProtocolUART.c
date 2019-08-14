#include "ProtocolUART.h"



#ifndef LOBYTE
#define LOBYTE(l)           ((BYTE)(l))
#endif

#ifndef HIBYTE
#define HIBYTE(l)           ((BYTE)(l >> 8))
#endif

uint8_t getCheckSum(const uint8_t *pData, int len) {
	int sum = 0;
	for (int i = 0; i < len; ++i) {
		sum += pData[i];
	}

	//return (uint8_t) (~sum + 1);
		return (uint8_t)sum&0xff;
}

/**
 * 功能：解析协议
 * 参数：pData 协议数据，len 数据长度
 * 返回值：实际解析协议的长度
 */

//uint8_t cheak = 0;

int parseProtocol(const BYTE *pData, UINT len) 
{
	UINT remainLen = len;	// 剩余数据长度
	UINT dataLen;	// 数据包长度
	UINT frameLen;	// 帧长度

	/**
	 * 以下部分需要根据协议格式进行相应的修改，解析出每一帧的数据
	 */
	while (remainLen >= DATA_PACKAGE_MIN_LEN) 
		{
		// 找到一帧数据的数据头
		while ((remainLen >= 2) && ((pData[0] != CMD_HEAD1) || (pData[1] != CMD_HEAD2))) {
			pData++;
			remainLen--;
			continue;
		}

		if (remainLen < DATA_PACKAGE_MIN_LEN) {
			break;
		}
		
		dataLen = MAKEWORD(pData[3], pData[2]);
		if (dataLen != sizeof(SProtocolData)) {
			//LOGE("The data length is inconsistent!!!");
			//LOGE("dataLen:%d, frameLen:%d", remainLen - DATA_PACKAGE_MIN_LEN, sizeof(SProtocolData));
		}
		//dataLen = pData[4];
		frameLen = dataLen + DATA_PACKAGE_MIN_LEN;
		if (frameLen > remainLen) {
			// 数据内容不全
			break;
		}

		// 打印一帧数据，需要时在CommDef.h文件中打开DEBUG_PRO_DATA宏
#ifdef DEBUG_PRO_DATA
		for (UINT i = 0; i < frameLen; ++i) {
			LOGD("%x ", pData[i]);
		}
		LOGD("\n");
#endif
		// 支持checksum校验，需要时在CommDef.h文件中打开PRO_SUPPORT_CHECK_SUM宏
#ifdef PRO_SUPPORT_CHECK_SUM
		// 检测校验码
//		cheak=getCheckSum(pData, frameLen - 1);
		if (getCheckSum(pData, frameLen - 1) == pData[frameLen - 1]) {
			// 解析一帧数据
			procParse(pData, frameLen);
		} else {
			//LOGE("CheckSum error!!!!!!\n");
		}
#else
		// 解析一帧数据
		procParse(pData, frameLen);
#endif

		pData += frameLen;
		remainLen -= frameLen;
	}
	return len - remainLen;
}

/**
 * 需要根据协议格式进行拼接，以下只是个模板
 */
uint8_t sendProtocol(const BYTE *pData, int len) {
	BYTE dataBuf[DATA_LEN + DATA_PACKAGE_MIN_LEN];
	// 判断数据长度是否超出限制
	if (len > DATA_LEN) {
		//LOGE("The data length over the limit!!!");
		return 1;
	}

	dataBuf[0] = CMD_HEAD1;
	dataBuf[1] = CMD_HEAD2;			// 同步帧头

	dataBuf[2] = HIBYTE(len);
	dataBuf[3] = LOBYTE(len);
	UINT frameLen = 4;

	// 数据
	for (int i = 0; i < len; ++i) {
		dataBuf[frameLen] = pData[i];
		frameLen++;
	}

#ifdef PRO_SUPPORT_CHECK_SUM
	// 校验码
	//extern BYTE getCheckSum(const BYTE *pData, int len);
	dataBuf[frameLen] = getCheckSum(dataBuf, frameLen);
	frameLen++;
#endif
	protocolDataSend(dataBuf,frameLen);
	return 0;
}


