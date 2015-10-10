#include "motor.h"

DigitalOut motorpin1(p21);
DigitalOut motorpin2(p22);
DigitalOut motorpin3(p23);
DigitalOut motorpin4(p24);

float delay = MIN;

void motor_set_delay(float t)
{
    delay = t;
}

void motor_initialize()
{
    motorpin1 = OFF;
    motorpin2 = OFF;
    motorpin3 = OFF;
    motorpin4 = OFF;
}

void motor_clockwise()
{
    motorpin1 = ON;
    wait(delay);
    motorpin4 = OFF;
    wait(delay);
    motorpin2 = ON;
    wait(delay);
    motorpin1 = OFF;
    wait(delay);        
    motorpin3 = ON;
    wait(delay);
    motorpin2 = OFF;
    wait(delay);
    motorpin4 = ON;
    wait(delay);
    motorpin3 = OFF;
    wait(delay);
}

void motor_anticlockwise()
{
    motorpin1 = ON;
    wait(delay);
    motorpin2 = OFF;
    wait(delay);
    motorpin4 = ON;
    wait(delay);
    motorpin1 = OFF;
    wait(delay);        
    motorpin3 = ON;
    wait(delay);
    motorpin4 = OFF;
    wait(delay);
    motorpin2 = ON;
    wait(delay);
    motorpin3 = OFF;
    wait(delay);
}