#include "common.h"

static uchar page=1;

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
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

void Timer2Init(void)		//50毫秒@11.0592MHz
{
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0x00;		//设置定时初值
	T2H = 0x4C;		//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
}

void Timer0_Routine(void) interrupt 1
{
	//1ms
	TR0=0;
	disp_scan();
	TR0=1;
}

void Timer1_Routine(void) interrupt 3
{
	//50ms
	static uchar i=0,temperature,cont_clock;
	static uchar e2_write_data[8]={0,1,2,3,4,5,6,7},e2_read_data[8];
	TR1=0;
	if(++cont_clock==20)
	{
		cont_clock=0;
		if(page==1)
		{
			disp_val_none();
			e2_read(0x00,e2_read_data,sizeof(e2_read_data));
			disp_val[0]=e2_read_data[0]%10;
			disp_val[1]=e2_read_data[0]%100/10;
			disp_val[2]=e2_read_data[0]/100;
			disp_val[3]=e2_read_data[1]%10;
			disp_val[4]=e2_read_data[1]%100/10;
			disp_val[5]=e2_read_data[1]/100;
			disp_val[6]=e2_read_data[2]%10;
			disp_val[7]=e2_read_data[2]%100/10;
			e2_write(0,e2_write_data,sizeof(e2_write_data));
			for(i=0;i<sizeof(e2_write_data);i++)
			{
				e2_write_data[i]+=1;
			}
		}
		else if(page==2)
		{
			disp_val_none();
			temperature=ds18b20_get();
			disp_val[0]=0x0c;
			disp_val[1]=0x12;
			disp_val[2]=temperature%10;
			disp_val[3]=temperature/10;
		}
		else if(page==3)
		{	
			disp_val_none();
			ds1302_burst_read(ds1302_time);
			disp_val[0]=ds1302_time[0]&0x0f;
			disp_val[1]=ds1302_time[0]>>4&0x0f;
			disp_val[2]=0x11;
			disp_val[3]=ds1302_time[1]&0x0f;
			disp_val[4]=ds1302_time[1]>>4&0x0f;
			disp_val[5]=0x11;
			disp_val[6]=ds1302_time[2]&0x0f;
			disp_val[7]=ds1302_time[2]>>4&0x0f;
		}
	}
	TR1=1;
}

void Timer2_Routine(void) interrupt 12
{
	//50ms
	static uchar cont_clock,buzz,trg_times,trg_clock;
	AUXR&=0xef;
	key_scan();
	if(trg)
	{
		if(++trg_times==1)
		{
			trg_clock=0;
		}
		//buzz=1;
		switch(key_val)
		{
			case 1:disp_val[7]=4;break;
			case 2:disp_val[7]=5;break;
			case 3:disp_val[7]=6;break;
			case 4:disp_val[7]=7;break;
			case 5:disp_val[7]=8;break;
			case 6:disp_val[7]=9;break;
			case 7:disp_val[7]=10;break;
			case 8:disp_val[7]=11;break;
			case 9:disp_val[7]=12;break;
			case 10:disp_val[7]=13;break;
			case 11:disp_val[7]=14;break;
			case 12:disp_val[7]=15;break;
			case 13:disp_val[7]=16;break;
			case 14:disp_val[7]=17;break;
			case 15:disp_val[7]=18;break;
			case 16:disp_val[7]=19;break;
			default:break;
		}
	}
	if(++trg_clock>=15)
	{
			trg_times=0;
	}
	if(trg_clock<15&&trg_times==2)
	{
		trg_clock=0;
		trg_times=0;
		switch(key_val)
		{
			case 1:disp_val[6]=1;break;
			case 2:disp_val[6]=2;break;
			case 3:disp_val[6]=3;break;
			case 4:disp_val[6]=4;break;
			case 5:disp_val[6]=5;break;
			case 6:disp_val[6]=6;break;
			case 7:disp_val[6]=7;break;
			case 8:disp_val[6]=8;break;
			case 9:disp_val[6]=9;break;
			case 10:disp_val[6]=10;break;
			case 11:disp_val[6]=11;break;
			case 12:disp_val[6]=12;break;
			case 13:disp_val[6]=13;break;
			case 14:page=3;break;
			case 15:page=2;break;
			case 16:page=1;break;
			default:break;
		}
	}
	if(cont)
	{
		if(++cont_clock>=20)
		{
			switch(key_val)
			{
				case 1:led_on_N(~4);break;
				case 2:led_on_N(~5);break;
				case 3:led_on_N(~6);break;
				case 4:led_on_N(~7);break;
				case 5:led_on_N(~8);break;
				case 6:led_on_N(~9);break;
				case 7:led_on_N(~10);break;
				case 8:led_on_N(~11);break;
				case 9:led_on_N(~12);break;
				case 10:led_on_N(~13);break;
				case 11:led_on_N(~14);break;
				case 12:led_on_N(~15);break;
				case 13:led_on_N(~16);break;
				case 14:led_on_N(~17);break;
				case 15:led_on_all();break;
				case 16:led_off();break;
				default:break;
			}
		}
	}
	else
	{
		cont_clock=0;
		led_off();
	}
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
	AUXR|=0x10;
}