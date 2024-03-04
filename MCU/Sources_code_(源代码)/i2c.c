#include "common.h"

sbit SCL=P2^0;
sbit SDA=P2^1;

void Delay5us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i);
}

void i2c_start(void)
{
	SDA=1;
	Delay5us();
	SCL=1;
	Delay5us();
	SDA=0;
	Delay5us();
	SCL=0;
	Delay5us();
}

void i2c_stop(void)
{
	SCL=0;
	Delay5us();
	SDA=0;
	Delay5us();
	SCL=1;
	Delay5us();
	SDA=1;
	Delay5us();
}

bit i2c_write_byte(uchar dat)
{
	bit ack=1;
	static uchar mask=0x00;
	SDA=1;
	Delay5us();
	for(mask=0x80;mask;mask>>=1)
	{
		SDA=dat&mask;
		Delay5us();
		SCL=1;
		Delay5us();
		SCL=0;
		Delay5us();
	}
	SDA=1;
	Delay5us();
	SCL=1;
	Delay5us();
	ack=SDA;
	SCL=0;
	Delay5us();
	return ack;
}

uchar i2c_read_byte_ack(void)
{
	static uchar mask=0x00,val=0;
	SDA=1;
	Delay5us();
	for(mask=0x80;mask;mask>>=1)
	{
		SCL=1;
		Delay5us();
		if(SDA)
			val|=mask;
		else
			val&=~mask;
		Delay5us();
		SCL=0;
		Delay5us();
	}
	SDA=1;
	Delay5us();
	SDA=0;
	Delay5us();
	SCL=1;
	Delay5us();
	SCL=0;
	Delay5us();
	return val;
}

uchar i2c_read_byte_nack(void)
{
	static uchar mask=0x00,val=0;
	SDA=1;
	Delay5us();
	for(mask=0x80;mask;mask>>=1)
	{
		SCL=1;
		Delay5us();
		if(SDA)
			val|=mask;
		else
			val&=~mask;
		Delay5us();
		SCL=0;
		Delay5us();
	}
	SDA=1;
	Delay5us();
	SCL=1;
	Delay5us();
	SCL=0;
	Delay5us();
	return val;
}

bit i2c_device(uchar dev,bit read)
{
	bit ack=1;
	dev<<=1;
	if(read)
		dev|=0x01;
	else
		dev&=0xfe;
	ack=i2c_write_byte(dev);
	return ack;
}

void adc_get(uchar *dat,uchar len)
{
	do{
		i2c_start();
		if(~i2c_device(0x48,0))
			break;
		i2c_stop();
	}while(1);
	i2c_write_byte(0x44);
	i2c_start();
	i2c_device(0x48,1);
	i2c_read_byte_ack();
	while(len-->1)
		*dat++=i2c_read_byte_ack();
	*dat=i2c_read_byte_nack();
	i2c_stop();
}

void dac_set(uchar dat)
{
	do{
		i2c_start();
		if(~i2c_device(0x48,0))
			break;
		i2c_stop();
	}while(1);
	i2c_write_byte(0x44);
	i2c_write_byte(dat);
	i2c_stop();
}

void e2_write(uchar word,uchar *dat,uchar len)
{
	do{
		i2c_start();
		if(~i2c_device(0x50,0))
			break;
		i2c_stop();
	}while(1);
	i2c_write_byte(word);
	while(len--)
		i2c_write_byte(*dat++);
	i2c_stop();
}

void e2_read(uchar word,uchar *dat,uchar len)
{
	do{
		i2c_start();
		if(~i2c_device(0x50,0))
			break;
		i2c_stop();
	}while(1);
	i2c_write_byte(word);
	i2c_start();
	i2c_device(0x50,1);
	while(len-->1)
		*dat++=i2c_read_byte_ack();
	*dat=i2c_read_byte_nack();
	i2c_stop();
}

//void e2_reset(void)
//{
//	static uchar i=0;
//	for(i=0;i<255;i++)
//	{
//		e2_write(i,0);
//	}
//}