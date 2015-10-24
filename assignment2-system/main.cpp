/*
This Code is for STEPPER MOTOR & SENSOR integration with mbed 1768 with Speed/Direction Control
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 2
Last Modified: 09-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "motor.h"
#include "ultra.h"

#define MAX_CLOCK_DISTANCE 14				// Reference Point 14cm
#define MIN_CLOCK_DISTANCE 4
#define MAX_ANTICLOCK_DISTANCE 24

InterruptIn echo(p6);
Serial term(USBTX, USBRX);
Timer pulse_width;
float dist = 0.0;
bool flag = true;

void calibrate(float d)					// Function for Speed modulation with distance
{    
    int distance = (int)d;
    
    if(distance <= MAX_CLOCK_DISTANCE)  //clock
    {
        if(distance <= MIN_CLOCK_DISTANCE) //min distance
        {
            motor_set_delay(MIN);  //fastest clockwise
        }
        else
        {
            float t = (distance - MIN_CLOCK_DISTANCE) * MIN;
            motor_set_delay(t);
        } 
        
        flag = true;       
    }
    else  //anti-clock
    {
        if(distance >= MAX_ANTICLOCK_DISTANCE) //max distance
        {
            motor_set_delay(MIN); //fastest anti-clockwise
        }
        else
        {
            float t = (MAX_ANTICLOCK_DISTANCE - distance) * MIN;
            motor_set_delay(t);                    
        }    
         
        flag = false;          
    }
}


int ultra_timer_duration()						//Return Timer count
{
    int duration;
    duration = pulse_width.read_us();
    //term.printf("\nTimer Reading cm:%d",duration );
    
    return duration;
}

void ultra_timer_on()							// Start Timer
{
    pulse_width.reset();
    pulse_width.start();
    //term.printf("\nECHO HIGH" );
}

void ultra_timer_off()						//Stop Timer, calculate distance, update speed of motor
{    
    pulse_width.stop();
    int duration = ultra_timer_duration();       
    dist = ultra_cal_distance(duration);
    //term.printf("\n Object Distance cm : %f", dist); 
    calibrate(dist);
    //term.printf("\nECHO LOW" );  
}


int main()									// Main Program
{
    motor_initialize();
    echo.rise(&ultra_timer_on);				// Interrupt on Echo posedge
    echo.fall(&ultra_timer_off);			//Interrupt on Echo Negedge
     
    while(1) 							//Trigger of 10us
    {
        ultra_call_trigger();  			
        
        if(flag)
        {
            motor_clockwise(); 
        }
        else
        {
            motor_anticlockwise();
        }                    
    }
}
