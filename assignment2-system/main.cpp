#include "motor.h"
#include "ultra.h"

#define MAX_CLOCK_DISTANCE 14
#define MIN_CLOCK_DISTANCE 4
#define MAX_ANTICLOCK_DISTANCE 24

InterruptIn echo(p6);
Serial term(USBTX, USBRX);
Timer pulse_width;
float dist = 0.0;
bool flag = true;

void calibrate(float d)
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


int ultra_timer_duration()
{
    int duration;
    duration = pulse_width.read_us();
    //term.printf("\nTimer Reading cm:%d",duration );
    
    return duration;
}

void ultra_timer_on()
{
    pulse_width.reset();
    pulse_width.start();
    //term.printf("\nECHO HIGH" );
}

void ultra_timer_off()
{    
    pulse_width.stop();
    int duration = ultra_timer_duration();       
    dist = ultra_cal_distance(duration);
    //term.printf("\n Object Distance cm : %f", dist); 
    calibrate(dist);
    //term.printf("\nECHO LOW" );  
}


int main()
{
    motor_initialize();
    echo.rise(&ultra_timer_on);
    echo.fall(&ultra_timer_off);
     
    while(1) 
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
