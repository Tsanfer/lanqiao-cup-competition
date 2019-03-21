#include "common.h"

sbit TX=P1^0;
sbit RX=P1^1;

uchar sonic_times=8;

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

void sonic_emit(uchar times)
{
	// 50KHz
	while(times--)
	{
		TX=1;
		Delay10us();
		TX=0;
		Delay10us();
	}
}

uint sonic_echo(void)
{
	static uchar tl,th;
	static uint distance,time;
	tl=TL1;
	th=TH1;
	TH1=0x00;
	TL1=0x00;
	TF1=0;
	TR1=1;
	while(RX&&~TF1);
	TR1=0;
	if(TF1)
	{
		TF1=0;
		distance=9999;
		return distance;
	}
	else
	{
		time=TH1;
		time<<=8;
		time|=TL1;
	}
	TH1=th;
	TL1=tl;
	distance=(uint)(time*0.017); // x=t*v=time/1000000*340*100/2
	return distance;
}

uint sonic_get(void)
{
	static uint distance=0;
	sonic_emit(sonic_times);
	distance=sonic_echo();
	return distance;
}
