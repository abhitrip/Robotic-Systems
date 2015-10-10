/*
This Code defines function for sensor
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

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
    



