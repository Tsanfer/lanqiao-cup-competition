#include "common.h"

sbit RELAY_PIN=P0^4;
sbit BUZZ_PIN=P0^6;

void relayInit(void)
{
  hc138_drivers();
  RELAY_PIN=0;
  hc138_none();
}

void buzzInit(void)
{
  hc138_drivers();
  BUZZ_PIN=0;
  hc138_none();
}