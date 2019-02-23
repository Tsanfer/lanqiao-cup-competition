#include "common.h"

void Timer0Init(void)       //1??@11.0592MHz
{
  AUXR &= 0x7F;     //?????12T??
  TMOD &= 0xF0;     //???????
  TL0 = 0x66;       //??????
  TH0 = 0xFC;       //??????
  TF0 = 0;      //??TF0??
  TR0 = 1;      //???0????
}

void Timer1Init(void)       //50??@11.0592MHz
{
  AUXR &= 0xBF;     //?????12T??
  TMOD &= 0x0F;     //???????
  TL1 = 0x00;       //??????
  TH1 = 0x4C;       //??????
  TF1 = 0;      //??TF1??
  TR1 = 1;      //???1????
}

void Timer0_Routine(void) interrupt 1
{
  //1ms
  static uint clock;
	static uchar select,temp;
	TR0=0;
	if(++clock==1000)
  {
    clock=0;
		if(++select==1)
		{
			ds1302_burst_read(ds1302_time);
			disp_val_none();
			disp_val[0]=ds1302_time[0]&0x0f;
			disp_val[1]=ds1302_time[0]>>4&0x0f;
			disp_val[2]=0x11;
			disp_val[3]=ds1302_time[1]&0x0f;
			disp_val[4]=ds1302_time[1]>>4&0x0f;
			disp_val[5]=0x11;
			disp_val[6]=ds1302_time[2]&0x0f;
			disp_val[7]=ds1302_time[2]>>4&0x0f;
		}
		else
		{
			select=0;
			temp=ds18b20_get();
			disp_val_none();
			disp_val[0]=0x0c;
			disp_val[1]=0x12;
			disp_val[2]=temp%10;
			disp_val[3]=temp/10;
		}
	}
	dispscan();
  TR0=1;
}

void Timer1_Routine(void) interrupt 3
{
  //50ms
  TR1=0;
  keyscan();
  if(trg)
  {
    switch(key_val)
    {
      case 1:led_on_all();break;
      case 2:break;
      case 3:break;
      case 4:break;
      case 5:break;
      case 6:led_on_N(0xaa);break;
      case 7:break;
      case 8:break;
      case 9:break;
      case 10:break;
      case 11:led_on_N(0x55);break;
      case 12:break;
      case 13:break;
      case 14:break;
      case 15:break;
      case 16:led_off();break;
      default:break;
    }
  }
  TR1=1;
}