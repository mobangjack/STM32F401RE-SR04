#include "main.h"

void TIM2_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_BaseInit(TIM2, 83, TIM_CounterMode_Up, TIM2_PERIOD, TIM_CKD_DIV1, 0);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	NVIC_BaseInit(TIM2_IRQn, 1, 0, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}

unsigned int Micros(void)
{
	return TIM2->CNT;
}

uint32_t Millis(void)
{
	return Micros()/1000;
}

uint32_t Second(void)
{
	return Millis()/1000;
}
