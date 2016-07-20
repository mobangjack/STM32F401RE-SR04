#ifndef __USART2_H__
#define __USART2_H__

#include "stdint.h"

void USART2_Config(void);
void USART2_PrintChar(uint8_t ch);
void USART2_PrintBlock(uint8_t* pdata, uint8_t len);

#endif

