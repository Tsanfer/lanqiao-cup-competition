#include "common.h"

#define HC138 P2

void hc138Init(void)
{
  HC138&=0x1f;
}

void hc138_none(void)
{
  HC138&=0x1f;
}

void hc138_led(void)
{
  HC138&=0x1f;
  HC138|=0x80;
}

void hc138_drivers(void)
{
  HC138&=0x1f;
  HC138|=0xa0;
}

void hc138_bit(void)
{
  HC138&=0x1f;
  HC138|=0xc0;
}

void hc138_seg(void)
{
  HC138&=0x1f;
  HC138|=0xe0;
}