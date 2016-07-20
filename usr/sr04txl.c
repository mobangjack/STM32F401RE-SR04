#include "main.h"

SR04TXP txp;
void SR04TXL_TX(void)
{
	if(SR04_Update() == SUCCESS)
	{
		uint8_t id = SR04_Last();
		uint16_t data = SR04_Data(id);
		SR04TXP_Push(&txp, id, data);
		USART2_PrintBlock((uint8_t*)&txp, SR04TXP_SIZE());
		LED_TOGGLE();
	}
}

