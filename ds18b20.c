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
	while(~DQ);
}

void write_byte(uchar val)
{
	uchar i=0x00;
	for(i=0x01;i;i<<=1)
	{
		DQ=0;
		DQ=val&i;
		Delay50us();
		Delay50us();
		DQ=1;
	}
}

uchar read_byte()
{
	uchar i=0x00,val=0;
	for(i=0x01;i;i<<=1)
	{
		DQ=0;
		DQ=1;
		if(DQ)val=val|i;
		Delay50us();
		Delay50us();
	}
	return val;
}

uchar ds18b20_get(void)
{
	static uchar temp[2]={0x00,0x00},val;
	ds18b20Init();
	write_byte(0xcc);
	write_byte(0x44);
	ds18b20Init();
	write_byte(0xcc);
	write_byte(0xbe);
	temp[0]=read_byte();
	temp[1]=read_byte();
	val=temp[0]>>4&0x0f|temp[1]<<4&0xf0;
	return val; //such as 27
}