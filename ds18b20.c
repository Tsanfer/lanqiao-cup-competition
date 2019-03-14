#include "common.h"

sbit DQ=P1^4;

void Delay50us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 1;
	j = 134;
	do
	{
		while (--j);
	} while (--i);
}

void Delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void ds18b20Init(void)
{
	DQ=0;
	Delay500us();
	DQ=1;
	Delay50us();
	while(~DQ)
	{
		;
	}
}

void ds18b20_write(uchar dat)
{
	uchar mask=0x00;
	for(mask=0x01;mask;mask<<=1)
	{
		DQ=0;
		DQ=dat&mask;
		Delay50us();
		Delay50us();
		DQ=1;
	}
}

uchar ds18b20_read(void)
{
	uchar mask=0x00,val=0;
	for(mask=0x01;mask;mask<<=1)
	{
		DQ=0;
		DQ=1;
		if(DQ)
		{
			val=val|mask;
		}
		else
		{
			val=val&~mask;
		}
		Delay50us();
		Delay50us();
	}
	return val;
}

uchar ds18b20_get(void)
{
	uchar temp[2],val=0;
	ds18b20Init();
	ds18b20_write(0xcc);
	ds18b20_write(0x44);
	ds18b20Init();
	ds18b20_write(0xcc);
	ds18b20_write(0xbe);
	temp[0]=ds18b20_read();
	temp[1]=ds18b20_read();
	val=temp[0]>>4&0x0f|temp[1]<<4&0xf0;
	return val;
}