#include "main.h"

void delay_ms(u32 t)
{
	int i;
	for(i=0;i<t;i++)
	{
		int a=42000;
		while(a--);
	}
}

void delay_us(u32 t)
{
	int i;
	for(i=0;i<t;i++)
	{
		int a=40;
		while(a--);
	}
}




