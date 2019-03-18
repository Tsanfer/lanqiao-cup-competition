#include "common.h"

sbit TX=P1^0;
sbit RX=P1^1;

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}

void sonic_emit(void)
{
	uchar i=8;
	while(i--)
	{
		TX=1;
		Delay10us();
		TX=0;
		Delay10us();
	}
}

uint sonic_echo(void)
{
	static uint distance=0;
	TL1 = 0x00;
	TH1 = 0x00;
	TF1=0;
	TR1 = 1;
	while(RX&&~TF1);
	TR1 = 0;
	if(TF1)
	{
		TF1=0;
		distance=9999;
		return distance;
	}
	else
	{
		distance=TH1;
		distance<<=8;
		distance|=TL1;
	}
	TL1 = 0x00;
	TH1 = 0x4C;
	distance=(uint)(distance*0.017);//distance=time*velocity/2
	return distance;
}
uint sonic_distance(void)
{
	static uint distance=0;
	sonic_emit();
	distance=sonic_echo();
	return distance;
}