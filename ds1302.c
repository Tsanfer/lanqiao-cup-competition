#include "common.h"

sbit CE=P1^3;
sbit SCLK=P1^7;
sbit I_O=P2^3;

uchar ds1302_time[7];
code uchar Init_time[7]={0x50,0x44,0x13,0x14,0x03,0x04,0x19};

void ds1302_write_byte(uchar dat)
{
	uchar mask=0x00;
	I_O=1;
	for(mask=0x01;mask;mask<<=1)
	{
		if(dat&mask)
		{
			I_O=1;
		}
		else
		{
			I_O=0;
		}
		SCLK=1;
		SCLK=0;
	}
	I_O=1;
}

uchar ds1302_read_byte(void)
{
	uchar mask=0x00,val=0;
	I_O=1;
	for(mask=0x01;mask;mask<<=1)
	{
		if(I_O)
		{
			val|=mask;
		}
		else
		{
			val&=~mask;
		}
		SCLK=1;
		SCLK=0;
	}
	return val;
}

void ds1302_single_write(uchar reg,uchar dat)
{
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(reg<<1|0x80);
	ds1302_write_byte(dat);
	CE=0;
}

uchar ds1302_single_read(uchar reg)
{
	static uchar val;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(reg<<1|0x81);
	val=ds1302_read_byte();
	CE=0;
	return val;
}

void ds1302_burst_write(uchar *dat)
{
	static uchar i;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(0xbe);
	for(i=0;i<8;i++)
	{
		ds1302_write_byte(dat[i]);
	}
	CE=0;
}

void ds1302_burst_read(uchar *dat)
{
	static uchar i;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(0xbf);
	for(i=0;i<8;i++)
	{
		dat[i]=ds1302_read_byte();
	}
	CE=0;
}

void ds1302Init(void)
{
	if(ds1302_single_read(0)&0x80)
	{
		ds1302_single_write(7,0x00);
		ds1302_burst_write(Init_time);
	}
}