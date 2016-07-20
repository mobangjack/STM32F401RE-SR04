#include "main.h"

int main(void)
{
	USART2_Config();
	LED_Config();
	Btn_Config();
	Buzzer_Config();
	SR04_Config();
	TIM2_Config();
	
	while(1)
	{
		SR04TXL_TX();
	}
}
