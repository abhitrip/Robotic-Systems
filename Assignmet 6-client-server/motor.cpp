/*
This Code is for RADAR SYSTEM: MOTOR API.
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 5
Last Modified: 05-Nov-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathi; Pulkit Bhatnagar
University of California, San Diego
*/
#include "motor.h"
#include "mbed.h"
#include "queue.h"

#define MIN 0.001
#define MAX 0.01
#define MID 0.005

#define ON 1
#define OFF 0

float delay = MIN;
bool flag = false;
bool direction = false;     //Anticlockwise
int count = 0;

DigitalOut motorpin1(p21);
DigitalOut motorpin2(p22);
DigitalOut motorpin3(p23);
DigitalOut motorpin4(p24);

Ticker ti;
signed int angle=26;            //Start from 90deg N

void motor_attachticker()
{
    if(flag)
    {
        flag = false;
        
        if(direction)                       //Rotate anticlockwise
        {
            for (int i = 0 ; i< 5; i++) {
            motor_clockwise();
            }
            angle--;                        
        }
        else                                //Rotate Clockwise
        {
            for (int i = 0 ; i< 5; i++) {
            motor_anticlockwise();
            }
            angle++;

        }
    }
}

//Motor Initialization
void motor_init(float t)
{
    delay=t;
    ti.attach(motor_attachticker, 0.01);
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

//Direction sweep 0-180deg
int motor_rotate()
{
    if(angle>=52 || angle<=0)
    {
        if(direction){            
        direction = false;
        }
        else {
        direction = true;
        }
    }    

    flag = true;
       //printf("\nAngle:%d",angle);
      // printf("\nDirection:%d",direction);
    return angle;
 
}



int scan_at_head () //Scan at heading at 15deg only
{
    if(angle>=10 || angle<=0)
    {
        if(direction){            
        direction = false;
        }
        else {
        direction = true;
        }
    }    

    flag = true;
    return angle;
 
}