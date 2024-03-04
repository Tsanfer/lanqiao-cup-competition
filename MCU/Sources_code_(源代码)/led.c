#include "common.h"

#define LED P0

void ledInit(void)
{
	LED=0xff;
	hc138_led();
	hc138_none();
}

void led_on_N(uchar led)
{
	LED=led;
	hc138_led();
	hc138_none();
}
