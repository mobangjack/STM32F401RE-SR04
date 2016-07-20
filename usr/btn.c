#include "main.h"

void Btn_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,  ENABLE);
    
	GPIO_BaseInit(GPIOC, GPIO_Pin_13, GPIO_Mode_IN, GPIO_Speed_2MHz, GPIO_OType_PP, GPIO_PuPd_UP);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
    EXTI_BaseInit(EXTI_Line13, EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);
	NVIC_BaseInit(EXTI15_10_IRQn, 2, 1, ENABLE);
    
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line13))
    {
		EXTI_ClearITPendingBit(EXTI_Line13);
		LED_TOGGLE();
    }
}

