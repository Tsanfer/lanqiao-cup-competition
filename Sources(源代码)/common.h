#ifndef COMMON_H
#define COMMON_H

#include "stc15f2k60s2.h"

typedef unsigned char uchar;
typedef unsigned int uint;

#define seg_tab_none 11
#define bit_tab_none 8

extern uchar disp_val[8];
extern uchar trg,cont,key_val;

extern void Timer0Init(void);
extern void Timer1Init(void);
extern void hc138Init(void);
extern void hc138_none(void);
extern void hc138_led(void);
extern void hc138_drivers(void);
extern void hc138_bit(void);
extern void hc138_seg(void);
extern void ledInit(void);
extern void led_on_N(uchar n);
extern void led_on_all(void);
extern void led_off(void);
extern void relayInit(void);
extern void buzzInit(void);
extern void dispscan(void);
extern void keyscan(void);

#endif