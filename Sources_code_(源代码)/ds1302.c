#include "common.h"

sbit CE=P1^3;
sbit SCLK=P1^7;
sbit I_O=P2^3;

uchar ds1302_time[7];
code uchar Inittime[]={0x05,0x20,0x19,0x23,0x02,0x06,0x19};

void ds1302_write_byte(uchar dat)
{
	uchar i=0x00;
	for(i=0x01;i;i<<=1)
	{
		SCLK=0;
		if(dat&i)
		{
			I_O=1;
		}
		else
		{
			I_O=0;
		}
		SCLK=1;
	}
	I_O=1;
}

uchar ds1302_read_byte(void)
{
	uchar i=0x00,val=0x00;
	for(i=0x01;i;i<<=1)
	{
		SCLK=0;
		if(I_O)
		{
			val|=i;
		}
		SCLK=1;
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
	uchar val;
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
	uchar i=0;
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

void ds1302_burst_read(uchar *val)
{
	uchar i=0;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(0xbf);
	for(i=0;i<8;i++)
	{
		val[i]=ds1302_read_byte();
	}
	CE=0;
}

void ds1302Init(void)
{
	CE=0;
	SCLK=0;
	if(ds1302_single_read(0)&0x80)
	{
		ds1302_single_write(7,0x00);
		ds1302_burst_write(Inittime);
	}
}