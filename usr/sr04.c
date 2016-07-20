#include "main.h"

static volatile uint8_t index = 0;

SR04 sr04[SR04_NUM] = {
	
	{
		PC3,
		PC0,
		ON,
		0,
		0,
		0
	},
	{
		PC2,
		PC1,
		ON,
		0,
		0,
		0
	},
	{
		PC9,
		PC8,
		ON,
		0,
		0,
		0
	},
	{
		PB8,
		PC6,
		ON,
		0,
		0,
		0
	},
	{
		PB9,
		PC5,
		ON,
		0,
		0,
		0
	},
	{
		PA8,
		PB1,
		ON,
		0,
		0,
		0
	},
	{
		PB10,
		PB15,
		ON,
		0,
		0,
		0
	},
	{
		PB4,
		PB14,
		ON,
		0,
		0,
		0
	}
	
};
	
void SR04_Config(void)  
{  
	for(index = 0; index < SR04_NUM; index++)
	{
		IOPort_Init(&sr04[index].trig, GPIO_Mode_OUT, GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
		IOPort_Init(&sr04[index].echo, GPIO_Mode_IN,  GPIO_Speed_100MHz, GPIO_OType_PP, GPIO_PuPd_NOPULL);
	}
	index = 0;
}

uint8_t SR04_Next(void)
{
	index++;
	index%=SR04_NUM;
	return index;
}

#define SUCCESS 1
#define FAILED 0
#define CHECK_OVERFLOW(dt) if(dt<0)dt = dt+TIM2_PERIOD;

uint8_t SR04_Update(void)
{
	uint32_t t = Micros();
	int64_t dt = t - sr04[index].endPulse;
	if(sr04[index].state == OFF) 
	{
		SR04_Next();
		return FAILED;
	}
	CHECK_OVERFLOW(dt);
	if(dt < SPACING)
	{
		//printf("spacing not enough!\n");
		return FAILED;
	}
	IOPort_Reset(&sr04[index].trig);//clear all pins
	delay_us(2);
	IOPort_Set(&sr04[index].trig);//trig TTL > 10us
	delay_us(10);
	IOPort_Reset(&sr04[index].trig);
	t = Micros();
	while(!IOPort_Read(&sr04[index].echo))//wait for rising edge
	{
		dt = Micros() - t;
		CHECK_OVERFLOW(dt);
		if(dt > TIMEOUT)
		{
			SR04_Next();
			//printf("wait for rising edge time out!time=%lld\n",dt);
			return FAILED;
		}
	}
	sr04[index].startPulse = Micros();//echo pulse start time point
	t = Micros();
	while(IOPort_Read(&sr04[index].echo))//wait for falling edge
	{
		dt = Micros() - t;
		CHECK_OVERFLOW(dt);
		if(dt > TIMEOUT)
		{
			SR04_Next();
			//printf("wait for falling edge time outtime=%lld\n",dt);
			return FAILED;
		}
	}
	sr04[index].endPulse = Micros();//echo pulse stop time point
	dt = sr04[index].endPulse - sr04[index].startPulse;
	CHECK_OVERFLOW(dt);
	sr04[index].data = dt / 58.0f;
	SR04_Next();
	//printf("SR04 Update Done!\n");
	return SUCCESS;
}

uint8_t SR04_This(void)
{
	return index;
}

uint8_t SR04_Last(void)
{
	return index==0?7:index-1;
}

uint16_t SR04_Data(uint8_t index)
{
	return sr04[index].data;
}

