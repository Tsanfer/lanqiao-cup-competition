#include "common.h"

#define BIT P0
#define SEG P0

#define seg_tab_none 11
#define bit_tab_none 8

code uchar seg_tab[12]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};  //0~9,-,blank
code uchar bit_tab[9]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00};
uchar disp_val[8]={seg_tab_none,seg_tab_none,seg_tab_none,seg_tab_none,
                   seg_tab_none,seg_tab_none,seg_tab_none,seg_tab_none};

void dispscan(void)
{
  static uchar pointer=0;
  SEG=seg_tab[seg_tab_none];
  hc138_seg();
  SEG=seg_tab[disp_val[pointer]];
  hc138_none();
  BIT=bit_tab[bit_tab_none];
  hc138_bit();
  BIT=bit_tab[pointer];
  if(++pointer==8)
  {
    pointer=0;
  }
  hc138_none();
}