/*
This Code is for RADAR API
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 4
Last Modified: 22-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "radar.h"

// an I2C sub-class that provides a constructed default
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);          //400Khz
        start();
    };
}; 

I2CPreInit i2c(p9,p10);
Adafruit_SSD1306_I2c gOled(i2c, p27);

void display_radar()
{
    int c =0;
    int count=13;   //13sweeps in 1 direction
    float cosTable[]={1,0.966,0.866,0.707,0.5,0.259,0,-0.259,-0.5,-0.707,-0.866,-0.966,-1}; //13steps
    float sinTable[]={0,-0.259,-0.5,-0.707,-0.866,-0.966,-1,-0.966,-0.866,-0.707,-0.5,-0.259,0};    //13steps
    while(1)
    {   
        int x1,y1;
        int r = 63;
        int x0 = 63;
        int y0 = 63;      
        //gOled.clearDisplay();
       
        //Circle construction
        gOled.display();
        gOled.drawCircle(x0,y0,r,1);
        gOled.drawCircle(x0,y0,2*r/4,1);
        gOled.drawCircle(x0,y0,3*r/4,1);
        gOled.drawCircle(x0,y0,r/4,1);
        gOled.drawLine(0,y0-1,127,y0-1,WHITE);// For the diameter solid line ; Comment if you don't require it  
        
        //Sweep Line
        while(count!=0){
        x1 = x0 - (int)(r*cosTable[c]); //clockwise; 
        y1 = y0 + (int)(r*sinTable[c]);
                     
        gOled.drawLine(x0,y0,x1,y1,WHITE);
        gOled.display();
        wait(0.1);  //Sweep Speed
        gOled.drawLine(x0,y0,x1,y1,BLACK);
        count--;
        c = (c+1)%13;
        }
        
        while (count!=13) {
        x1 = x0 + (int)(r*cosTable[c]); //AntiClockwise
        y1 = y0 + (int)(r*sinTable[c]);
                     
        gOled.drawLine(x0,y0,x1,y1,WHITE);
        gOled.display();
        wait(0.1);  //Sweep Speed
        gOled.drawLine(x0,y0,x1,y1,BLACK);
        count++;
        c = (c+1)%13;
        }
        
     }
}