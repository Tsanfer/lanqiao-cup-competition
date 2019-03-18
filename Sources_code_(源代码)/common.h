#ifndef COMMON_H
#define COMMON_H

#include "stc15f2k60s2.h"
#include "intrins.h"

#define seg_tab_none 19
#define bit_tab_none 8

typedef unsigned char uchar;
typedef unsigned int uint;

extern uchar trg,cont,key_val;
extern uchar disp_val[8];
extern uchar ds1302_time[7];

extern void Timer0Init(void);
extern void Timer1Init(void);
extern void UartInit(void);
extern void Timer2Init(void);
extern void hc138Init(void);
extern void hc138_none(void);
extern void hc138_led(void);
extern void hc138_drivers(void);
extern void hc138_seg(void);
extern void hc138_bit(void);
extern void ledInit(void);
extern void led_on_N(uchar led);
extern void led_on_all(void);
extern void led_off(void);
extern void relayInit(void);
extern void relay_off(void);
extern void buzzInit(void);
extern void buzz_on(void);
extern void buzz_off(void);
extern void disp_scan(void);
extern void disp_val_none(void);
extern void key_scan(void);
extern uchar ds18b20_get(void);
extern void ds1302Init(void);
extern void ds1302_burst_read(uchar *val);
//extern void e2_reset(void);
extern void e2_read(uchar word,uchar *dat,uchar len);
extern void e2_write(uchar word,uchar *dat,uchar len);
extern void get_dac(uchar *dat,uchar len);
extern void set_dac(uchar dat);
extern uint sonic_distance(void);
extern void pwm(uchar dat);

#endif