#include "main.h"

FIFO* usart2fifo = NULL;
void USART2_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	
	GPIO_BaseInit(GPIOA, GPIO_Pin_2, GPIO_Mode_AF, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	
	USART_BaseInit(USART2, 115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, USART_Mode_Tx|USART_Mode_Rx, USART_HardwareFlowControl_None, ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_BaseInit(USART2_IRQn, 1, 0, ENABLE);
	
	if(usart2fifo == NULL)
	{
		usart2fifo = FIFO_Create(100);
	}
}

void USART2_PrintChar(uint8_t ch)
{    
    FIFO_Push(usart2fifo, &ch, 1);
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    
}

void USART2_PrintBlock(uint8_t* pdata, uint8_t len)
{
	FIFO_Push(usart2fifo, pdata, len);
    USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
}

int fputc(int ch, FILE* file)
{
	while (USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	USART_SendData(USART2, (uint8_t)ch);
	return ch;
}

void USART2_IRQHandler(void)
{  
    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {   
		while(!FIFO_IsEmpty(usart2fifo))
		{
			uint8_t data = 0;
			FIFO_Pop(usart2fifo, &data, 1);
			while (USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
			USART_SendData(USART2, data);
		}
		USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
    }else if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
		uint8_t data = USART_ReceiveData(USART2);
	}
}

