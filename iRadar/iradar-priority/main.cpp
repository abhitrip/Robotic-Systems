/*
This Code is for RADAR SYSTEM integration using PRIORITY on mbed 1768 which detects an object and displays on OLED.
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 5
Last Modified: 06-Nov-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"
#include "motor.h"
#include "ultra.h"
#include "magnetometer.h"
#include "radar.h"
#include "queue.h"


#define motor 0
#define ultra 1
#define magneto 2
#define lcd 3

void schedule_event();

Ticker random_event;
 event e;  
int main()
{
         //Create an event for pushing tasks in queue.
    e.pr = low;     //Default priority set to low

random_event.attach(schedule_event, 0.4);

//Peripheral Initialization    
   motor_init(0.02);
   ultra_init();
   mag_init(0.01);
   radar_init();
    
//Push first event Motor in queue
   e.type = motor;
   e.pr = high;
   queue_push(e);
    
//Object distance and Heading
    float dis = 0.0;
    //int angle = 13; //256;
    int angle=26;


//Push events in queue and service FIFO
    while(1)
    {        
        if(!queue_empty())
            e = queue_front();
        else
           
        {   event e;
            e.type = 0;
            e.pr = high; 
            queue_push(e);
        }
        
        switch(e.type)
        {
            case motor:
            {
                
                printf("\nMotor....");
                angle=motor_rotate();              
            }
            break;
            
            case ultra:
            {
                printf("\nUltra....");
                dis=ultra_start();
                wait_us(1);

            }
            break;
            
            case magneto:
            {
               printf("\nMagneto....");
                mag_start();          

            }
            break;
            
            case lcd:
            {                
            printf("\nLCD....");
            display_radar(dis, angle);       //Display the object position and heading        

            }
            break;
            
            default:
            {
               printf("\nDefault....");
               angle=motor_rotate();
            }
            break;  
        }
    }
}

void schedule_event()
{
int task=rand()%4;                      //Generate random interrupts
e.type = task;  

   if(e.type==0 || e.type==3) {         //Set prioity of motor and ultra highest
        e.pr=high;
        }
    else {                          //Set priority of led and magneto lowest
        e.pr=low;
    }

queue_push(e);
}
