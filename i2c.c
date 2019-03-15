//数据总线要释放
#include "common.h"

sbit SCL = P2^0; 
sbit SDA = P2^1;

void i2c_start()
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void i2c_stop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

bit i2c_write_byte(uchar dat)
{
	bit ack=1;
	uchar mask;
	SDA=1;
	for(mask=0x80;mask;mask>>=1)
	{
		SDA=mask&dat;
		SCL=1;
		SCL=0;
	}
	SDA=1;
	SCL=1;
	ack=SDA;
	SCL=0;
	return ack;
}

uchar i2c_read_byte_ack()
{
	uchar mask,val;
	SDA=1;
	for(mask=0x80;mask;mask>>=1)
	{
		if(SDA)
		{
			val|=mask;
		}	
		else
		{
			val&=~mask;
		}
		SCL=1;
		SCL=0;
	}
	SDA=0;
	SCL=1;
	SCL=0;
	return val;
}

uchar i2c_read_byte_nack()
{
	uchar mask,val;
	SDA=1;
	for(mask=0x80;mask;mask>>=1)
	{
		if(SDA)
		{
			val|=mask;
		}
		else
		{
			val&=~mask;
		}
		SCL=1;
		SCL=0;
	}
	SDA=1;
	SCL=1;
	SCL=0;
	return val;
}

bit i2c_device_address(uchar dev,bit read)
{
	// read:1 write:0
	static bit ack=1;
	dev<<=1;
	if(read)
	{
		dev|=0x01;
	}
	else
	{
		dev&=0xfe;
	}
	ack=i2c_write_byte(dev);
	return ack;
}

bit i2c_word_address(uchar word)
{
	static ack=1;
	ack=i2c_write_byte(word);
	return ack;
}

void e2_write(uchar word,uchar *dat,uchar len)
{
	do{
		i2c_start();
		if(~i2c_device_address(0x50,0))
		{
			break;
		}
		i2c_stop();
	}while(1);
	i2c_word_address(word);
	while(len)
	{
		i2c_write_byte(*dat++);
		len--;
	}
	i2c_stop();
}

void e2_read(uchar word,uchar *dat,uchar len)
{
	do{
		i2c_start();
		if(~i2c_device_address(0x50,0))
		{
			break;
		}
		i2c_stop();
	}while(1);
	i2c_word_address(word);
	i2c_start();
	i2c_device_address(0x50,1);
	while(len>1)
	{
		*dat++=i2c_read_byte_ack();
		len--;
	}
	*dat=i2c_read_byte_nack();
	len--;
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