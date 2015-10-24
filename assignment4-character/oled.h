/*
This Code is for OLED API: putc, printf and clear
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 4
Last Modified: 22-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#ifndef OLED_H
#define OLED_H

#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "font_5x7.h"

bool oled_putc(char ch, bool diplaycontrol = true);
void oled_clear();
void oled_vscroll(bool input);
void oled_printf(char* s, int delay=0);
void oled_printword(char*);

#endif