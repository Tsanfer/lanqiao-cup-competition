#include "common.h"

#define LED P0

void ledInit(void)
{
  hc138_led();
  LED=0xff;
  hc138_none();
}

void led_on_N(uchar n)
{
  hc138_led();
  LED=n;
  hc138_none();
}

void led_on_all(void)
{
  hc138_led();
  LED=0x00;
  hc138_none();
}

void led_off(void)
{
  hc138_led();
  LED=0xff;
  hc138_none();
}