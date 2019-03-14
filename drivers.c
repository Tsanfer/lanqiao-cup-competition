#include "common.h"

sbit RELAY_PIN=P0^4;
sbit BUZZ_PIN=P0^6;

void relayInit(void)
{
	RELAY_PIN=0;
	hc138_drivers();
	hc138_none();
}

void relay_off(void)
{
	RELAY_PIN=0;
	hc138_drivers();
	hc138_none();
}

void buzzInit(void)
{
	BUZZ_PIN=0;
	hc138_drivers();
	hc138_none();
}

void buzz_on(void)
{	
	BUZZ_PIN=1;
	hc138_drivers();
	hc138_none();
}

void buzz_off(void)
{
	BUZZ_PIN=0;
	hc138_drivers();
	hc138_none();
}