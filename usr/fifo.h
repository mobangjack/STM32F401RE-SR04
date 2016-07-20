#ifndef __FIFO_H__
#define __FIFO_H__

#include "stdint.h"

typedef struct FIFO
{
	uint8_t* buf;
	uint32_t size;
	uint32_t used_space;
	uint32_t free_space;
}FIFO;

FIFO* FIFO_Create(uint32_t size);
uint8_t FIFO_Push(FIFO* fifo, uint8_t* block, uint32_t size);
uint8_t FIFO_Pop(FIFO* fifo, uint8_t* block, uint32_t size);
uint8_t FIFO_IsFull(FIFO* fifo);
uint8_t FIFO_IsEmpty(FIFO* fifo);
uint32_t FIFO_GetUsedSpace(FIFO* fifo);
uint32_t FIFO_GetFreeSpace(FIFO* fifo);
void FIFO_Destroy(FIFO* fifo);

#endif
