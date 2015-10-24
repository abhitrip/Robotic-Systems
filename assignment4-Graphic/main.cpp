/*
This Code is for OLED integration with I2C in mbed 1768 for Radar Sweep Display
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 4
Last Modified: 22-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "radar.h"

int main()
{
	while(1)
	{
        display_radar();		//Custom API for Radar sweep display
	}
}