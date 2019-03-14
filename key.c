#include "common.h"

#define KEY P3

uchar trg,cont,trg_row,trg_column,cont_row,cont_column,key_val;

void key_scan(void)
{
	uchar readdata=0x00,P42_val,P44_val;
	KEY=0x0f;
	P42=0;
	P44=0;
	P42_val=P42;
	P44_val=P44;
	P42_val=P42_val<<6&0x40;
	P44_val=P44_val<<7&0x80;
	readdata=KEY&0x3f|P42_val|P44_val;
	readdata^=0x0f;
	trg_row=readdata&(readdata^cont_row);
	cont_row=readdata;
	KEY=0xf0;
	P42=1;
	P44=1;
	P42_val=P42;
	P44_val=P44;
	P42_val=P42_val<<6&0x40;
	P44_val=P44_val<<7&0x80;
	readdata=KEY&0x3f|P42_val|P44_val;
	readdata^=0xf0;
	trg_column=readdata&(readdata^cont_column);
	cont_column=readdata;
	trg=trg_row|trg_column;
	cont=cont_row|cont_column;
	switch(trg)
	{
		case 0x81:key_val=1;break;
		case 0x41:key_val=2;break;
		case 0x21:key_val=3;break;
		case 0x11:key_val=4;break;
		case 0x82:key_val=5;break;
		case 0x42:key_val=6;break;
		case 0x22:key_val=7;break;
		case 0x12:key_val=8;break;
		case 0x84:key_val=9;break;
		case 0x44:key_val=10;break;
		case 0x24:key_val=11;break;
		case 0x14:key_val=12;break;
		case 0x88:key_val=13;break;
		case 0x48:key_val=14;break;
		case 0x28:key_val=15;break;
		case 0x18:key_val=16;break;
		default:break;
	}
	KEY=0xff;
}