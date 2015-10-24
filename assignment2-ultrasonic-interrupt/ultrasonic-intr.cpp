/*
This Code is for ULTRASONIC SENSOR integration with mbed 1768 with Interrupt
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"
 
InterruptIn echopin(p6); 				// Interrupting the echo pulse pin
DigitalOut triggerpin(p25); 			// Pin for providing trigger pulse
Serial terminal(USBTX, USBRX);
Timer timer;


// Takes duration of echo pulse width in us and returns distance from sensor in cms
float cal_distance(float duration)
{
    return (duration / 58.0);  			// d = (100*340*t/2)*(10^-6) ~ t/58
}

void timer_on() 						// ISR for rising edge
{
    timer.reset(); 						// On detecting rising edge , we start the timer
    timer.start();
}

void timer_off() 						// ISR for falling edge 
{
    timer.stop(); 						// On detecting falling edge , we stop timer
    float duration = (float)(timer.read_us()); 
    
    float distance = cal_distance(duration);
    terminal.printf("\n Object Distance cm : %f \n", distance);
}

int main()
{    
    echopin.rise(&timer_on); 				// Interrupt for rising edge 
    echopin.fall(&timer_off); 				// Interrupt for falling edge
    
    while(1) 								//Trigger Pulse of 10us after every 1sec
    {        
        triggerpin = 0;				
        wait_us(1);
        triggerpin = 1;
        wait_us(10);
        triggerpin = 0;
                   
        wait(1);
    }
}
