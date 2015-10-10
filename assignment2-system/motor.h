/*
This Code defines motor functions
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#ifndef MOTOR
#define MOTOR

#include "mbed.h"

#define MIN 0.001
#define MAX 0.01
#define MID 0.005

#define ON 1
#define OFF 0

void motor_initialize(void);
void motor_clockwise();
void motor_anticlockwise();
void motor_set_delay(float t);

#endif