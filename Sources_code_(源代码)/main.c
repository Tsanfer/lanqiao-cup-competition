#include "common.h"

void SysInit(void)
{
	disp_val_none();
	Timer0Init();
	Timer1Init();
	Timer2Init();
	hc138Init();
	ledInit();
	buzzInit();
	relayInit();
	ds1302Init();
	//e2_reset();
	EA=1;
	ET0=1;
	ET1=1;
	IE2|=0x04;
}

void main(void)
{
	SysInit();
	while(1)
	{
		;
	}
}