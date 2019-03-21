#include "common.h"

static uchar page=1;
static uchar rxd_data=0;
static uchar temperature=0;
static uchar ds1302_time[7];
static uint sonic_distance=0;
static idata uchar e2_write_data[8]={0,1,2,3,4,5,6,7},e2_read_data[8];
static uchar adc_data[4];
static uchar dac_data=128;
static uchar trg_times,trg_clock,cont_clock;
static uchar pwm_clock,pwm_data=30;
static bit pwm_flag=0;
static uchar buzz=0;

void Timer0Init(void)		//10微秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xF7;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
}

void Timer1Init(void)		//50毫秒@11.0592MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x00;		//设置定时初值
	TH1 = 0x4C;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
}

void UartInit(void)		//2400bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR &= 0xFB;		//定时器2时钟为Fosc/12,即12T
	T2L = 0xA0;		//设定定时初值
	T2H = 0xFF;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
}
void trg_run(void)
{
	if(trg)
	{
		if(++trg_times==1)
		{
			trg_clock=0;
		}
		//buzz=1;
		switch(key_val)
		{
			case 1:page=1;break;
			case 2:page=2;break;
			case 3:page=3;break;
			case 4:page=4;break;
			case 5:page=5;break;
			case 6:page=6;break;
			case 7:page=7;break;
			case 8:page=8;break;
			case 9:page=9;break;
			case 10:page=10;break;
			case 11:page=11;break;
			case 12:page=12;break;
			case 13:page=13;break;
			case 14:page=14;break;
			case 15:page=15;break;
			case 16:page=16;break;
			default:break;
		}
	}
}
void trg_double_run(void)
{
	if(++trg_clock>=15)
	{
		trg_clock=0;
		trg_times=0;
	}
	if(trg_clock<15&&trg_times==2)
	{
		trg_clock=0;
		trg_times=0;
		disp_val_none();
		switch(key_val)
		{
			case 1:disp_val[0]=key_val;break;
			case 2:disp_val[0]=key_val;break;
			case 3:disp_val[0]=key_val;break;
			case 4:disp_val[0]=key_val;break;
			case 5:disp_val[0]=key_val;break;
			case 6:disp_val[0]=key_val;break;
			case 7:disp_val[0]=key_val;break;
			case 8:disp_val[0]=key_val;break;
			case 9:disp_val[0]=key_val;break;
			case 10:disp_val[0]=key_val;break;
			case 11:disp_val[0]=key_val;break;
			case 12:disp_val[0]=key_val;break;
			case 13:disp_val[0]=key_val;break;
			case 14:disp_val[0]=key_val;break;
			case 15:disp_val[0]=key_val;break;
			case 16:disp_val[0]=key_val;break;
			default:break;
		}
	}
}
void cont_run(void)
{
	if(cont)
	{
		if(++cont_clock>=20)
		{
			switch(key_val)
			{
				case 1:led_on_N(~key_val);break;
				case 2:led_on_N(~key_val);break;
				case 3:led_on_N(~key_val);break;
				case 4:led_on_N(~key_val);break;
				case 5:led_on_N(~key_val);break;
				case 6:led_on_N(~key_val);break;
				case 7:led_on_N(~key_val);break;
				case 8:led_on_N(~key_val);break;
				case 9:led_on_N(~key_val);break;
				case 10:led_on_N(~key_val);break;
				case 11:led_on_N(~key_val);break;
				case 12:led_on_N(~key_val);break;
				case 13:led_on_N(~key_val);break;
				case 14:led_on_N(~key_val);break;
				case 15:led_on_N(~key_val);break;
				case 16:led_on_N(~key_val);break;
				default:break;
			}
		}	
	}
	else
	{
		cont_clock=0;
		led_on_N(0xff);
	}
}
void buzz_run(void)
{
	if(buzz==1)
	{
		buzz=2;
		relay_off();
		buzz_on();
	}
	else if(buzz==2)
	{
		buzz=0;
		relay_off();
		buzz_off();
	}
}
void uart_run(void)
{
	disp_val_none();
	disp_val[0]=rxd_data%10;
	disp_val[1]=rxd_data%100/10;
	disp_val[2]=rxd_data/100;
}
void ds18b20_run(void)
{
	disp_val_none();
	temperature=ds18b20_get();
	disp_val[0]=0x0c;
	disp_val[1]=18;
	disp_val[2]=temperature%10;
	disp_val[3]=temperature/10;
}
void ds1302_HHMMSS_run(void)
{
	disp_val_none();
	ds1302_burst_read(ds1302_time);
	disp_val[0]=ds1302_time[0]&0x0f;
	disp_val[1]=ds1302_time[0]>>4&0x0f;
	disp_val[2]=17;
	disp_val[3]=ds1302_time[1]&0x0f;
	disp_val[4]=ds1302_time[1]>>4&0x0f;
	disp_val[5]=17;
	disp_val[6]=ds1302_time[2]&0x0f;
	disp_val[7]=ds1302_time[2]>>4&0x0f;
}
void ds1302_week_run(void)
{
	disp_val_none();
	ds1302_burst_read(ds1302_time);
	disp_val[0]=17;
	disp_val[1]=17;
	disp_val[2]=17;
	disp_val[3]=17;
	disp_val[4]=ds1302_time[5]&0x0f;
	disp_val[5]=17;
	disp_val[6]=17;
	disp_val[7]=17;
}

void ds1302_YYMMDD_run(void)
{
	disp_val_none();
	ds1302_burst_read(ds1302_time);
	disp_val[0]=ds1302_time[3]&0x0f;
	disp_val[1]=ds1302_time[3]>>4&0x0f;
	disp_val[2]=17;
	disp_val[3]=ds1302_time[4]&0x0f;
	disp_val[4]=ds1302_time[4]>>4&0x0f;
	disp_val[5]=17;
	disp_val[6]=ds1302_time[6]&0x0f;
	disp_val[7]=ds1302_time[6]>>4&0x0f;
}
void sonic_run(void)
{
	disp_val_none();
	sonic_distance=sonic_get();
	disp_val[0]=sonic_distance%10;
	disp_val[1]=sonic_distance%100/10;
	disp_val[2]=sonic_distance%1000/100;
	disp_val[3]=sonic_distance%10000/1000;
	disp_val[4]=sonic_distance/10000;
}


void e2_run(void)
{
	static uchar i=0;
	disp_val_none();
	e2_write(0x00,e2_write_data,sizeof(e2_write_data));
	e2_read(0x00,e2_read_data,sizeof(e2_read_data));
	disp_val[0]=e2_read_data[0]%10;
	disp_val[1]=e2_read_data[0]%100/10;
	disp_val[2]=e2_read_data[0]/100;
	disp_val[3]=e2_read_data[1]%10;
	disp_val[4]=e2_read_data[1]%100/10;
	disp_val[5]=e2_read_data[1]/100;
	disp_val[6]=e2_read_data[2]%10;
	disp_val[7]=e2_read_data[2]%100/10;
	for(i=0;i<sizeof(e2_write_data);i++)
	{
		e2_write_data[i]++;
	}
}

void adc_run(void)
{
	disp_val_none();
	adc_get(adc_data,sizeof(adc_data));
	disp_val[0]=adc_data[page-8]%10;
	disp_val[1]=adc_data[page-8]%100/10;
	disp_val[2]=adc_data[page-8]/100;
	disp_val[3]=0x11;
	disp_val[4]=page-8;
	disp_val[5]=0x0d;
	disp_val[6]=0x0a;
	disp_val[7]=0x11;
}

void dac_run(void)
{
	disp_val_none();
	dac_set(dac_data);
	adc_get(adc_data,sizeof(adc_data));
	disp_val[0]=adc_data[0]%10;
	disp_val[1]=adc_data[0]%100/10;
	disp_val[2]=adc_data[0]/100;
	disp_val[3]=0x11;
	disp_val[4]=0x0c;
	disp_val[5]=0x0a;
	disp_val[6]=0x0d;
	disp_val[7]=0x11;
}
void pwm_run(void)
{
	static uint clock=0;
	if(pwm_flag)
	{
		if(++pwm_clock<=pwm_data)
		{
			relay_off();
			buzz_off();
			motor_on();
		}
		else if(pwm_clock>pwm_data&&pwm_clock<=100)
		{
			relay_off();
			buzz_off();
			motor_off();
		}
		else
		{
			pwm_clock=0;
			if(++clock==1000)
			{
				clock=0;
				disp_val_none();
				disp_val[0]=0x11;
				disp_val[1]=0x11;
				disp_val[2]=0x11;
				disp_val[3]=pwm_data%10;
				disp_val[4]=pwm_data%100/10;
				disp_val[5]=pwm_data/100;
				disp_val[6]=0x11;
				disp_val[7]=0x11;
			}	
		}
	}
}
void Timer0_Routine(void) interrupt 1
{
	// 10us
	static uchar clock=0;
	TR0=0;
	if(++clock==100)
	{
		clock=0;
		disp_scan();
	}	
	pwm_run();
	TR0=1;
}

void Timer1_Routine(void) interrupt 3
{
	// 50ms
	static uint clock=0;
	TR1=0;
	key_scan();
	trg_run();
	trg_double_run();
	cont_run();
	relay_off();
	buzz_off();
	motor_off();
	buzz_run();
	if(++clock==20)
	{
		clock=0;
		switch(page)
		{
			case 1:pwm_flag=0;uart_run();break;
			case 2:pwm_flag=0;ds18b20_run();break;
			case 3:pwm_flag=0;ds1302_HHMMSS_run();break;
			case 4:pwm_flag=0;ds1302_week_run();break;
			case 5:pwm_flag=0;ds1302_YYMMDD_run();break;
			case 6:pwm_flag=0;sonic_run();break;
			case 7:pwm_flag=0;e2_run();break;
			case 8:pwm_flag=0;adc_run();break;
			case 9:pwm_flag=0;adc_run();break;
			case 10:pwm_flag=0;adc_run();break;
			case 11:pwm_flag=0;adc_run();break;
			case 12:pwm_flag=0;dac_run();break;
			case 13:pwm_flag=1;break;
			default:break;
		}
	}
	TR1=1;
}

void Uart(void) interrupt 4
{
	REN=0;
	if(RI)
	{
		RI=0;
		rxd_data=SBUF;
		SBUF=rxd_data;
	}
	if(TI)
	{
		TI=0;
	}
	REN=1;
}

//void Timer2_Routine(void) interrupt 12
//{
//	//50ms
//	AUXR&=0xef;
//	
//	AUXR|=0x10;
//}
