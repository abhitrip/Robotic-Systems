/*
This Code is for STEPPER MOTOR integration with mbed 1768 with direction control on Serial Port
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"
#define WTIME 0.001		// Wait Time for motor speed control
#define ON 1
#define OFF 0

Serial terminal(USBTX, USBRX);	//Keyboard Input

DigitalOut motorpin1(p21);
DigitalOut motorpin2(p22);
DigitalOut motorpin3(p23);
DigitalOut motorpin4(p24);

void clockwise()			//Function for Clockwise Rotation: (4,1)-->(1,2)-->(2,3)-->(3,4)-->(4,1)
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

void anticlockwise() 	//Function for Anti-Clockwise Rotation: (2,1)-->(4,1)-->(4,3)-->(3,2)-->(2,1)
{
    motorpin1 = ON;
    wait(WTIME);
    motorpin2 = OFF;
    wait(WTIME);
    motorpin4 = ON;
    wait(WTIME);
    motorpin1 = OFF;
    wait(WTIME);        
    motorpin3 = ON;
    wait(WTIME);
    motorpin4 = OFF;
    wait(WTIME);
    motorpin2 = ON;
    wait(WTIME);
    motorpin3 = OFF;
    wait(WTIME);
}

int main()
{
    int input = 0;
    
    while(1) 
    {        
        
		//User Input Serial
		terminal.printf("\n Enter Choice [1 (clockwise), 0 (anti-clockwise)] : \n");
        terminal.scanf("%d", &input);
        terminal.printf("\n%d\n", input);
        fflush(stdin);
        
        motorpin1 = OFF;
        motorpin2 = OFF;
        motorpin3 = OFF;
        motorpin4 = OFF;   

        if(input)								//If Input =1, Rotate Clockwise
        {
            while(!terminal.readable())			// Check for Serial Input
            {
                clockwise();
            }
        }
        else										//else, Rotate Anti-Clockwise (Optimistic Code)
        {
            while(!terminal.readable())				// Check for Serial Input
            {
                anticlockwise();
            }
        }        
    }
}
