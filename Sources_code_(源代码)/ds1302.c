#include "common.h"

sbit CE=P1^3;
sbit SCLK=P1^7;
sbit I_O=P2^3;

uchar ds1302_init_time[7]={0x50,0x52,0x20,0x19,0x03,0x02,0x19};

void ds1302_write_byte(uchar dat)
{
	static uchar mask=0x00;
	I_O=1;
	for(mask=0x01;mask;mask<<=1)
	{
		I_O=dat&mask;
		SCLK=1;
		SCLK=0;
	}
	I_O=1;
}

uchar ds1302_read_byte(void)
{
	static uchar mask=0x00,val=0;
	I_O=1;
	for(mask=0x01;mask;mask<<=1)
	{
		if(I_O)
			val|=mask;
		else
			val&=~mask;
		SCLK=1;
		SCLK=0;
	}
	I_O=1;
	return val;
}

void ds1302_address(uchar reg,bit read)
{
	reg=reg<<1|0x80;
	if(read)
		reg|=0x01;
	else
		reg&=0xfe;
	ds1302_write_byte(reg);
}

void ds1302_single_write(uchar reg,uchar dat)
{
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_address(reg,0);
	ds1302_write_byte(dat);
	CE=0;
}

uchar ds1302_single_read(uchar reg)
{
	static uchar val=0;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_address(reg,1);
	val=ds1302_read_byte();
	CE=0;
	return val;
}

void ds1302_burst_write(uchar *dat)
{
	static uchar i=0;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(0xbe);
	for(i=0;i<8;i++)
	{
		ds1302_write_byte(*dat++);
	}
	CE=0;
}

void ds1302_burst_read(uchar *dat)
{
	static uchar i=0;
	SCLK=0;
	I_O=0;
	CE=1;
	ds1302_write_byte(0xbf);
	for(i=0;i<8;i++)
	{
		*dat++=ds1302_read_byte();
	}
	CE=0;
}

void ds1302Init(void)
{
	ds1302_single_write(0x07,0x00);
	if(ds1302_single_read(0x00)&0x80)
		ds1302_burst_write(ds1302_init_time);
}
