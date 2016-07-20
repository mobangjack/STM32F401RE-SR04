#ifndef __TIM2_H__
#define __TIM2_H__

#include "stdint.h"

#define TIM2_PERIOD 0xFFFFFFFF
void TIM2_Config(void);

uint32_t Micros(void);
uint32_t Millis(void);
uint32_t Second(void);

#endif

