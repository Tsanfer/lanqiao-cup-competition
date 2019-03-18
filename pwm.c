#include "common.h"

sbit PWM_PIN=P1^0;

void pwm(uchar dat)
{
	static uchar sw=0;
	if(++sw>dat)
	{
		PWM_PIN=1;
	}
	else
	{
		PWM_PIN=0;
	}
}