#include "main.h"

void SR04TXP_Push(SR04TXP* txp, uint8_t id, uint16_t data)
{
	txp->header = SR04TXP_HEADER;
	txp->id = id;
	txp->data = data;
	CRC16Append((uint8_t*)txp, SR04TXP_SIZE(), SR04TXP_CRC16);
}

uint8_t SR04TXP_Pop(SR04TXP* txp, uint8_t* pBuf)
{
	if(pBuf[0] != SR04TXP_HEADER)
	{
		return 0;
	}
	if(!CRC16Check(pBuf, SR04TXP_SIZE(), SR04TXP_CRC16))
	{
		return 0;
	}
	memcpy(txp, pBuf, SR04TXP_SIZE());
	return 1;
}

