#ifndef __BUZZER_H__
#define __BUZZER_H__

void Buzzer_Config(void);

#define  BUZZER_OFF()       GPIO_ResetBits(GPIOA, GPIO_Pin_15)
#define  BUZZER_ON()        GPIO_SetBits(GPIOA, GPIO_Pin_15)
#define  BUZZER_TOGGLE()    GPIO_ToggleBits(GPIOA, GPIO_Pin_15)
#define  BUZZER_STATE()     GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_15)

#endif
