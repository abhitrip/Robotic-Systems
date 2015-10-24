/*
This Code is for OLED integration with I2C in mbed 1768 for Text Display
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 4
Last Modified: 22-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "oled.h"

char story[] = "An embedded system is a computer system with a dedicated function within a larger mechanical or electrical system, often with real-time computing constraints. It is embedded as part of a complete device often including hardware and mechanical parts. Embedded systems control many devices in common use today. Examples of properties typical of embedded computers when compared with general-purpose ones are low power consumption, small size, rugged operating ranges, and low per-unit cost. This comes at the price of limited processing resources, which make them significantly more difficult to program and to interface with. However, by building intelligence mechanisms on the top of the hardware, taking advantage of possible existing sensors and the existence of a network of embedded units, one can both optimally manage available resources at the unit and network levels as well as provide augmented functionalities, well beyond those available.[4] For example, intelligent techniques can be designed to manage power consumption of embedded systems. Modern embedded systems are often based on microcontrollers (i.e. CPUs with integrated memory or peripheral interfaces)[6] but ordinary microprocessors (using external chips for memory and peripheral interface circuits) are also still common, especially in more complex systems. In either case, the processor(s) used may be types ranging from general purpose to those specialised in certain class of computations, or even custom designed for the application at hand. A common standard class of dedicated processors is the digital signal processor (DSP)." 
"Since the embedded system is dedicated to specific tasks, design engineers can optimize it to reduce the size and cost of the product and increase the reliability and performance. Some embedded systems are mass-produced, benefiting from economies of scale."
"Embedded systems range from portable devices such as digital watches and MP3 players, to large stationary installations like traffic lights, factory controllers, and largely complex systems like hybrid vehicles, MRI, and avionics. Complexity varies from low, with a single microcontroller chip, to very high with multiple units, peripherals and networks mounted inside a large chassis or enclosure."
"Embedded systems are commonly found in consumer, cooking, industrial, automotive, medical, commercial and military applications."
"Telecommunications systems employ numerous embedded systems from telephone switches for the network to cell phones at the end-user. Computer networking uses dedicated routers and network bridges to route data."
"Consumer electronics include personal digital assistants (PDAs), mp3 players, mobile phones, videogame consoles, digital cameras, DVD players, GPS receivers, and printers. Household appliances, such as microwave ovens, washing machinesand dishwashers, include embedded systems to provide flexibility, efficiency and features. Advanced HVAC systems use networked thermostats to more accurately and efficiently control temperature that can change by time of day and season. Home automation uses wired- and wireless-networking that can be used to control lights, climate, security, audio/visual, surveillance, etc., all of which use embedded devices for sensing and controlling."
"Transportation systems from flight to automobiles increasingly use embedded systems. New airplanes contain advanced avionics such as inertial guidance systems and GPS receivers that also have considerable safety requirements. Various electric motors - brushless DC motors, induction motors and DC motors - use electric/electronic motor controllers. Automobiles, electric vehicles, and hybrid vehicles increasingly use embedded systems to maximize efficiency and reduce pollution. Other automotive safety systems include anti-lock braking system (ABS), Electronic Stability Control (ESC/ESP), traction control (TCS) and automatic four-wheel drive."
"  [Source: Wikipedia] Thank You! :)";

int main()
{    
    while(1)
    {
        char ch = 'a';
        
        for(int i=0; i<500; i++)
        {
            oled_putc(ch);            //char print without scroll
        }
        
        oled_clear();        
        oled_vscroll(true);
        
        for(int i=0; i<500; i++)
        {
            oled_putc(ch);          //with scroll
            
            ch++;
            
            if(ch == ('Z'+1))
            {
                ch = 'a';
            }
            
            if(ch == ('z'+1))
            {
                ch = 'A';
            }
        }
        
        oled_clear();
        
        oled_printword("CodeIT: Abhijit, Abhinav, Pulkit");  //Print word by word    
        
        oled_clear();        
        oled_vscroll(true);
        oled_printf(story, 1);           //print line by line

        oled_clear();        
        oled_vscroll(true);
        oled_printword(story);          //Print word by word    
        
        oled_clear();
    }
}