#ifndef __SR04_H__
#define __SR04_H__

#include "base.h"

#define SR04_NUM 8
#define SPACING 8000 //spacing in micro second
#define MAX_CM 450
#define TIMEOUT 27000 //echo timeout: 450*58=26100 

typedef struct SR04
{
	IOPort trig;
	IOPort echo;
	uint8_t state;
	uint32_t startPulse;
	uint32_t endPulse;
	uint16_t data;
}SR04;

void SR04_Config(void);
uint8_t SR04_Update(void);
uint8_t SR04_Next(void);
uint8_t SR04_This(void);
uint8_t SR04_Last(void);
uint16_t SR04_Data(uint8_t index);

#endif

