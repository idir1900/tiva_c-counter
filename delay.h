/*header file */
#include <stdint.h>

#ifndef __DELAY_H__
#define __DELAY_H__
void timer_delay(int time);
void my_time(int second);
unsigned long long int   my_count_wide(void);
int counter_up(int limit,int prescaler_up );
void wide_counter_down(unsigned long long int wlimit);
int counter_down(int start,int prescaler_down );
int my_count(void);

#endif

