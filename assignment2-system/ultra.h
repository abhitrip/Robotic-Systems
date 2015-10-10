#ifndef ULTRA
#define ULTRA

#include "mbed.h"

int ultra_timer_duration();
float ultra_cal_distance(int duration);
void ultra_call_trigger();

#endif