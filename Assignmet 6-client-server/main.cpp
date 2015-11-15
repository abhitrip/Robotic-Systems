/*
This Code is for BEAGLEBONE Integration with RADAR SYSTEM integration using FCFS on mbed 1768 which detects an object and displays on OLED.
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 5
Last Modified: 12-Nov-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathi; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"
#include "motor.h"
#include "ultra.h"
#include "magnetometer.h"
#include "radar.h"
#include "queue.h"

#define PI 3.142

#define start 1
#define stop 2
#define heading 3
#define display 4

Serial pc(USBTX, USBRX);
Serial uart(p13, p14);          //(tx,rx)

void schedule_event();

//Ticker random_event;            //Ticker to add events to queue
event e;        //Create an event for pushing tasks in queue.
    
int main()
{
//uart.baud(57600);

    e.pr = low;     //Default priority for FCFS

//random_event.attach(schedule_event, 0.4);

//Peripheral Initialization    
   motor_init(0.02);
   ultra_init();
//   mag_init(0.01);
//   radar_init();
    
  
    
//Object distance and Heading
    float dis = 0.0;
    //int angle = 13; //256;
    int angle=26;
    static int objects=0;
//max 5points
float o[6]={0};
int t[6]={0};    

    char cmd_get;
    int command;
    bool flag_motor = false;
    bool flag_first_head = true;
//Push events in queue and service FIFO
    while(1)
    {      
            dis=ultra_start();
            wait_us(1);
            if(dis < 10 && dis > 1) {          //save r and theta for 1cm < objects < 10cm, max 5 objects
                //printf("\nObject < 10cm detected");
                if(objects<6) {objects=objects+1;}
                else {objects=1;}
                o[objects]=dis;
                t[objects]=angle;               
                } else{}

        if(uart.readable()) {
            
            cmd_get = uart.getc();
            command=(cmd_get-48);       //ASCII convertion    
            e.type = command;
            if(command == 1 || command == 3) {
            flag_motor = true;}
            else {flag_motor =false;}
            queue_push(e);
        } 
        else {
            //printf("\nWaiting for input...");  
        }

        e = queue_front();
        
        switch(e.type)
        {    
            case start:                         //Motor Start
            {
                printf("\nMotor Start....");
                if (flag_motor) {
                    angle=motor_rotate();  
                    e.type = 1;
                    queue_push(e);            
                    }
                flag_first_head=true;

            }
            break;
            
            
            case stop: 
            {
                printf("\nMotor Stop....");
                flag_first_head=true;
                break;                   //Do nothing
            }
            
            case heading:
            {
                    
                    printf("\nMotor at Heading....");
                    //Moves to a specified heading
                    if(flag_first_head){
                    for (int i = 0 ; i< 20; i++) {
                        motor_clockwise();
                    }
                    }
                    //Rotate in 15deg only
                    if (flag_motor) {
                    flag_first_head=false;
                    angle=scan_at_head();   
                    e.type = 3;
                    queue_push(e);            
                    }                
            } 
            break;
            
            case display:
            {
    
                for(int i=objects; i>=1;i--) 
                {
                float theta = t[i]*3.5;
                float theta_rad = (theta)*PI/180;
                float x= o[i]*cos(theta_rad);
                float y= o[i]*sin(theta_rad);
                
                printf("\nObject[%d] Located at: X=%f,Y=%f", i, x, y);
                printf("\nObject[%d] Located at: r=%f,theta=%f",i, o[i], theta);
                
                uart.printf("\n\rObject[%d] Located at: (X=%f,Y=%f) and (r=%f,theta=%f)", i, x, y, o[i], theta);
                //uart.printf("%f,%f", x, y);
                }
                //uart.putc('q');
                flag_first_head=true;

            }
            break;
        }
    }
}

