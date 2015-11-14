/*
This Code is for RADAR SYSTEM: ULTASONIC SENSOR API.
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 5
Last Modified: 05-Nov-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathi; Pulkit Bhatnagar
University of California, San Diego
*/

#include "ultra.h"
#include "mbed.h"

DigitalOut trigger(p25);
InterruptIn echo(p6);

Serial term(USBTX, USBRX);
Timer tim;

int duration = 0;
bool uflag = false;

void ultra_timer_on()
{
    tim.start();
    //term.printf("\nECHO HIGH" );
}

void ultra_timer_off()
{    
   
   duration = tim.read_us();
   //term.printf("\nECHO LOW  Time: %d", duration );
    tim.stop();
    tim.reset(); 
}


 float ultra_start()
 {
    wait(0.01);
    trigger = 0;
    wait_us(1);
    trigger = 1;
    wait_us(10);
    trigger = 0; 
    wait_us(2);
    
    float d = (duration * 0.017);               // d = (100*340*t/2)*(10^-6) ~ t/58 ~ t*0.017
    //term.printf("\n Object Distance cm : %d \t %f", duration, d);
    return d;
}

void ultra_init()
{
    echo.rise(&ultra_timer_on);
    echo.fall(&ultra_timer_off);
}
