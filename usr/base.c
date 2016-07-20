#include "base.h"

void IOPort_Init(IOPort* ioport, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd)
{
	GPIO_BaseInit(ioport->gpio, ioport->pin, mode, speed, otype, pupd);
}

void IOPort_Set(IOPort* ioport)
{
	GPIO_SetBits(ioport->gpio, ioport->pin);
}

void IOPort_Reset(IOPort* ioport)
{
	GPIO_ResetBits(ioport->gpio, ioport->pin);
}

uint8_t IOPort_Read(IOPort* ioport)
{
	return GPIO_ReadInputDataBit(ioport->gpio, ioport->pin);
}

void GPIO_BaseInit(GPIO_TypeDef* gpiox, u32 pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd)
{
	GPIO_InitTypeDef gpio;
	
	if(gpiox == GPIOA)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	if(gpiox == GPIOB)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	if(gpiox == GPIOC)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	if(gpiox == GPIOD)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	if(gpiox == GPIOE)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	if(gpiox == GPIOF)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	if(gpiox == GPIOG)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	if(gpiox == GPIOH)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	if(gpiox == GPIOI)
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
	
	gpio.GPIO_Pin = pin;
	gpio.GPIO_Mode = mode;
	gpio.GPIO_Speed = speed;
	gpio.GPIO_OType = otype;
	gpio.GPIO_PuPd = pupd;
	GPIO_Init(gpiox, &gpio);
}

void TIM_BaseInit(TIM_TypeDef* timx, u16 prescaler, u16 counter_mode, u32 period, u16 clock_division, u8 repetition_counter)
{
	TIM_TimeBaseInitTypeDef tim;
	tim.TIM_Prescaler = prescaler;
	tim.TIM_CounterMode = counter_mode;
	tim.TIM_Period = period;
	tim.TIM_ClockDivision = clock_division;
	tim.TIM_RepetitionCounter = repetition_counter;
	TIM_TimeBaseInit(timx,&tim);
}

void TIM_OC_BaseInit(TIM_TypeDef* timx, u8 channel, u16 mode, u16 optState, u16 optNewState, u32 pulse, u16 polarity, u16 newPolarity, u16 idleState, u16 newIdleState)
{
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = mode;
    oc.TIM_OutputState = optState;
    oc.TIM_OutputNState = optNewState;
    oc.TIM_Pulse = pulse;
    oc.TIM_OCPolarity = polarity;
    oc.TIM_OCNPolarity = newPolarity;
    oc.TIM_OCIdleState = idleState;
    oc.TIM_OCNIdleState = newIdleState;
	if(channel&0x01){
		TIM_OC1Init(timx,&oc);
		TIM_OC1PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel&0x02){
		TIM_OC2Init(timx,&oc);
		TIM_OC2PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel&0x04){
		TIM_OC3Init(timx,&oc);
		TIM_OC3PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel&0x08){
		TIM_OC4Init(timx,&oc);
		TIM_OC4PreloadConfig(timx,TIM_OCPreload_Enable);
	}
}

void NVIC_BaseInit(u8 channel, u8 preemption_priority, u8 subpriority, FunctionalState cmd)
{
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = channel;
	nvic.NVIC_IRQChannelPreemptionPriority = preemption_priority;
	nvic.NVIC_IRQChannelSubPriority = subpriority;
	nvic.NVIC_IRQChannelCmd = cmd;
	NVIC_Init(&nvic);
}

void USART_BaseInit(USART_TypeDef* usartx, u32 baudrate, u16 word_length, u16 stopbits, u16 parity, u16 mode, u16 flow_control, FunctionalState cmd)
{
	USART_InitTypeDef usart;
	usart.USART_BaudRate = baudrate;
	usart.USART_WordLength = word_length;
	usart.USART_StopBits = stopbits;
	usart.USART_Parity = parity;
	usart.USART_Mode = mode;
	usart.USART_HardwareFlowControl = flow_control;
	USART_Init(usartx, &usart);
	USART_Cmd(usartx, cmd);
}

void CAN_BaseInit(CAN_TypeDef* canx, u16 prescaler, u8 mode, u8 sjw, u8 bs1, u8 bs2, FunctionalState ttcm, FunctionalState abom, FunctionalState awum, FunctionalState nart, FunctionalState rflm, FunctionalState txfp)
{
	CAN_InitTypeDef can;
	can.CAN_Prescaler = prescaler;
	can.CAN_Mode = mode;
	can.CAN_SJW = sjw;
	can.CAN_BS1 = bs1;
	can.CAN_BS2 = bs2;
	can.CAN_TTCM = ttcm;
	can.CAN_ABOM = abom;
	can.CAN_AWUM = awum;
	can.CAN_RFLM = rflm;
	can.CAN_TXFP = txfp;
	CAN_Init(canx, &can);
}

void CAN_Filter_BaseInit(u16 id_high, u16 id_low, u16 mask_id_high, u16 mask_id_low, u16 fifo, u8 number, u8 mode, u8 scale, FunctionalState cmd)
{
	CAN_FilterInitTypeDef can_filter;
	can_filter.CAN_FilterIdHigh = id_high;
	can_filter.CAN_FilterIdLow = id_low;
	can_filter.CAN_FilterMaskIdHigh = mask_id_high;
	can_filter.CAN_FilterMaskIdLow = mask_id_low;
	can_filter.CAN_FilterFIFOAssignment = fifo;
	can_filter.CAN_FilterNumber = number;
	can_filter.CAN_FilterMode = mode;
	can_filter.CAN_FilterScale = scale;
	can_filter.CAN_FilterActivation = cmd;
	CAN_FilterInit(&can_filter);
}

void DMA_BaseInit(DMA_Stream_TypeDef* DMAy_Streamx, u32 channel, u32 pba, u32 mba, u32 dir, u32 bufSize)
{
	DMA_InitTypeDef dma;
	dma.DMA_Channel = channel;
	dma.DMA_PeripheralBaseAddr = pba;
	dma.DMA_Memory0BaseAddr = mba;
	dma.DMA_DIR = dir;
	dma.DMA_BufferSize = bufSize;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_VeryHigh;
	dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	dma.DMA_MemoryBurst = DMA_Mode_Normal;
	dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMAy_Streamx,&dma);
}

void EXTI_BaseInit(u32 line, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger, FunctionalState cmd)
{
	EXTI_InitTypeDef exti;
	exti.EXTI_Line = line;
	exti.EXTI_Mode = mode;
	exti.EXTI_Trigger = trigger;
	exti.EXTI_LineCmd = cmd;
	EXTI_Init(&exti);
}

