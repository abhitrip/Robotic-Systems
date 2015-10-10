/*
This Code is for ULTRASONIC SENSOR integration with mbed 1768 with Polled IO
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathi; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"

DigitalIn echopin(p6);
DigitalOut triggerpin(p25);
Serial terminal(USBTX, USBRX);
Timer timer;


float cal_distance(float duration)
{
    return (duration/58.0);				//Distance = (Time/2)*340m/s = (Time/58) cm/s
}

int main()
{
    float duration = 0.0;
    float distance = 0.0;
    status = false;
    
    while(1) 
    {        
        triggerpin = 0;
        wait_us(1); 					// Wait for 1us for clean low pulse
        triggerpin = 1;
        wait_us(10);					// Trigger Pulse of 10us
        triggerpin = 0;                   
        
        while(!echopin);				//Poll echo pin for High
        timer.start();     				//start Timer   
        
        while(echopin);   				//Poll echo pin for low
        timer.stop();    				//Stop timer
        
        duration = (float)(timer.read_us());			//Read Timer Value = Echo High Time
        //terminal.printf("\n Timer Reading cm : %f \n", duration);
        
        distance = cal_distance(duration);				
        terminal.printf("\n Object Distance cm : %f \n", distance);
        
        timer.reset();					//Reset Timer            
        wait(1);						// Repeat Trigger after 1sec
    }
}
