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