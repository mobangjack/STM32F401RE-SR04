#include "main.h"

void Buzzer_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_BaseInit(GPIOA, GPIO_Pin_15, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
    
	BUZZER_OFF();
}


