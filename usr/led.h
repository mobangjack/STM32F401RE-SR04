#ifndef __LED_H__
#define __LED_H__

void LED_Config(void);

#define  LED_OFF()       GPIO_ResetBits(GPIOA, GPIO_Pin_5)
#define  LED_ON()        GPIO_SetBits(GPIOA, GPIO_Pin_5)
#define  LED_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_5)
#define  LED_STATE()     GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_5)

#endif
