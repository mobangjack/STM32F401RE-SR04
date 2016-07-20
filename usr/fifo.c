#include "fifo.h"
#include "stdlib.h"
#include "string.h"

FIFO* FIFO_Create(uint32_t size)
{
	FIFO* fifo = NULL;
	uint8_t* buf = (uint8_t*)malloc(sizeof(uint8_t)*size);
	if(buf == NULL)
	{
		return NULL;
	}
	fifo = (FIFO*)malloc(sizeof(FIFO));
	if(fifo == NULL)
	{
		free(buf);
		return NULL;
	}
	fifo->buf = buf;
	fifo->size = size;
	fifo->used_space = 0;
	fifo->free_space = size;
	return fifo;
}

uint8_t FIFO_Push(FIFO* fifo, uint8_t* block, uint32_t size)
{
	if(fifo->free_space >= size)
	{
		memcpy(fifo->buf+fifo->used_space, block, size);
		fifo->used_space += size;
		fifo->free_space -= size;
		return 1;
	}
	else if(fifo->size <= size)
	{
		memcpy(fifo->buf, block+size-fifo->size, fifo->size);
		fifo->used_space = fifo->size;
		fifo->free_space = 0;
		return 1;
	}
	else
	{
		uint32_t count = fifo->size - size;
		uint8_t* tmp = (uint8_t*)malloc(count);
		if(tmp == NULL)
			return 0;
		memcpy(tmp, fifo->buf + fifo->used_space - count, count);
		memcpy(fifo->buf, tmp, count);
		memcpy(fifo->buf + count, block, size);
		free(tmp);
		fifo->used_space = fifo->size;
		fifo->free_space = 0;
		return 1;
	}
}

uint8_t FIFO_Pop(FIFO* fifo, uint8_t* block, uint32_t size)
{
	if(fifo->used_space < size)
	{
		return 0;
	}
	else if(fifo->used_space == size)
	{
		memcpy(block, fifo->buf, size);
		fifo->used_space = 0;
		fifo->free_space = fifo->size;
		return 1;
	}
	else
	{
		uint32_t count = fifo->used_space - size;
		uint8_t* tmp = (uint8_t*)malloc(count);
		if(tmp == NULL)
			return 0;
		memcpy(tmp, fifo->buf+size, count);
		memcpy(block, fifo->buf, size);
		memcpy(fifo->buf, tmp, count);
		free(tmp);
		fifo->used_space -= size;
		fifo->free_space += size;
		return 1;
	}
}

uint8_t FIFO_IsFull(FIFO* fifo)
{
	return fifo->free_space == 0;
}

uint8_t FIFO_IsEmpty(FIFO* fifo)
{
	return fifo->used_space == 0;
}

uint32_t FIFO_GetUsedSpace(FIFO* fifo)
{
	return fifo->used_space;
}

uint32_t FIFO_GetFreeSpace(FIFO* fifo)
{
	return fifo->free_space;
}

void FIFO_Destroy(FIFO* fifo)
{
	free(fifo);
	fifo = NULL;
}

