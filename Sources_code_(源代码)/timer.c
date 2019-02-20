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
  static uchar disp,val[8]={seg_tab_none,seg_tab_none,seg_tab_none,seg_tab_none,
														seg_tab_none,seg_tab_none,seg_tab_none,seg_tab_none};
  TR0=0;
	if(++clock==1000)
	{
		clock=0;
		for(disp=0;disp<8;disp++)
		{
			switch(disp)
			{
				case 0:
				{
					disp_val[disp]=val[disp];
				}break;
				case 1:
				{
					disp_val[disp]=val[disp];
				}break;
				case 2:
				{
					disp_val[disp]=val[disp];
				}break;
				case 3:
				{
				disp_val[disp]=val[disp];
				}break;
				case 4:
				{
					disp_val[disp]=val[disp];
				}break;
				case 5:
				{
					disp_val[disp]=val[disp];
				}break;
				case 6:
				{
					disp_val[disp]=val[disp];
				}break;
				case 7:
				{
					disp_val[disp]=val[disp];
				}break;
				default:break;
			}
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
      case 1:break;
      case 2:break;
      case 3:break;
      case 4:break;
      case 5:break;
      case 6:break;
      case 7:break;
      case 8:break;
      case 9:break;
      case 10:break;
      case 11:break;
      case 12:break;
      case 13:break;
      case 14:break;
      case 15:break;
      case 16:break;
      default:break;
    }
  }
  TR1=1;
}