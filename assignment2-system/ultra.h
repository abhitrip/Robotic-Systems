/*
This Code defines function for sensor
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#ifndef ULTRA
#define ULTRA

#include "mbed.h"

int ultra_timer_duration();
float ultra_cal_distance(int duration);
void ultra_call_trigger();

#endif