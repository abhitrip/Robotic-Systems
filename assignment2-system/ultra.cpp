#include "ultra.h"

DigitalOut trigger(p25);

float ultra_cal_distance(int duration)
{
    float range;
    range = (duration * 0.017);
    return(range);
}

void ultra_call_trigger()
{
    trigger = 0;
    wait_us(1);
    trigger = 1;
    wait_us(10);
    trigger = 0; 
    wait_us(2);   
}
    



