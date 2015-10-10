/*
This Code is for Motor integration with mbed 1768
Course: CSE291E ( Robotics/Embedded Systems)
Lab: 2
Last Modified: 08-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"

#define ON 1
#define OFF 0

#define MIN 0.001
#define MAX 0.01

#define WTIME 0.001				//Wait Time for motor Speed Control

DigitalOut motorpin1(p21);
DigitalOut motorpin2(p22);
DigitalOut motorpin3(p23);
DigitalOut motorpin4(p24);

int main() 
{
    while(1) 					// Motor Drive for Clockwise Rotation: (4,1)-->(1,2)-->(2,3)-->(3,4)-->(4,1)
    {
        motorpin1 = ON;
        wait(WTIME);
        motorpin4 = OFF;
        wait(WTIME);
        motorpin2 = ON;
        wait(WTIME);
        motorpin1 = OFF;
        wait(WTIME);        
        motorpin3 = ON;
        wait(WTIME);
        motorpin2 = OFF;
        wait(WTIME);
        motorpin4 = ON;
        wait(WTIME);
        motorpin3 = OFF;
        wait(WTIME);
    }
}