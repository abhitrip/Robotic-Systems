/*
This Code is for printing a single char on SSD1306 OLED panel.  
Course: CSE291E ( Robotics/Embedded Systems)
Lab : 2
Last Modified: 22-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/




#include "mbed.h"
#include "Adafruit_SSD1306.h"
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);          //400Khz
        start();
    };
}; 

I2CPreInit LI2C(p9,p10);
Adafruit_SSD1306_I2c gOled(LI2C,p27);

#define OUR_PRINT // Enabled to print a character using own code , by populating Display buffer of Oled panel.


int main()
{   char c = 'a';
  
    
    while(1)
    {
        
#ifdef OUR_PRINT        
        gOled.SingleChar(c); // Custom function defined in Adafruit_SSD1306 driver class in Adafruit_SSD1306.h
                             //    to print a single character
#else
        gOled.printf(c); // If OUR_PRINT is disabled use the printf of Adafruit's Driver class
#endif
        gOled.display();
        wait(1.0);
    }
    
    
}
