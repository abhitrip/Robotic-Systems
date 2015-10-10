#include "mbed.h"
 
InterruptIn echopin(p6); 
DigitalOut triggerpin(p25); 
Serial terminal(USBTX, USBRX);
Timer timer;



float cal_distance(float duration)
{
    return (duration / 58.0);  
}

void timer_on() 
{
    timer.reset(); 
    timer.start();
}

void timer_off() 
{
    timer.stop(); 
    float duration = (float)(timer.read_us()); 
    
    float distance = cal_distance(duration);
    terminal.printf("\n Object Distance cm : %f \n", distance);
}

int main()
{    
    echopin.rise(&timer_on); 
    echopin.fall(&timer_off); 
    
    while(1) 
    {        
        triggerpin = 0;
        wait_us(1);
        triggerpin = 1;
        wait_us(10);
        triggerpin = 0;
                   
        wait(1);
    }
}
