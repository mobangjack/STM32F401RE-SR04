#ifndef __SR04TXP_H__
#define __SR04TXP_H__

#ifdef __cplusplus
extern "C"
{
#endif
	
#include "stdint.h"

#define SR04TXP_HEADER 0x00
#define SR04TXP_CRC16  0x7000
	
#pragma pack(1)
typedef struct SR04TXP
{
	uint8_t header : 8;
	uint8_t id : 8;
	uint16_t data : 16;
	uint16_t check_sum : 16;
}SR04TXP;

#define SR04TXP_SIZE() sizeof(SR04TXP)
	
void SR04TXP_Push(SR04TXP* txp, uint8_t id, uint16_t data);
uint8_t SR04TXP_Pop(SR04TXP* txp, uint8_t* pBuf);

#ifdef __cplusplus
}
#endif
	
#endif
