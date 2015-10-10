#include "mbed.h"

#define ON 1
#define OFF 0

#define MIN 0.001
#define MAX 0.01

#define WTIME 0.001

DigitalOut motorpin1(p21);
DigitalOut motorpin2(p22);
DigitalOut motorpin3(p23);
DigitalOut motorpin4(p24);

int main() 
{
    while(1) 
    {
        motorpin1 = ON;
        wait(WTIME);
        motorpin4 = OFF;
        wait(WTIME);
        motorpin2 = ON;
        wait(WTIME);
        motorpin1 = OFF;
        wait(WTIME);        
        motorpin3 = ON;
        wait(WTIME);
        motorpin2 = OFF;
        wait(WTIME);
        motorpin4 = ON;
        wait(WTIME);
        motorpin3 = OFF;
        wait(WTIME);
    }
}