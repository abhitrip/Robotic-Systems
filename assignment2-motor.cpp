#include "mbed.h"
#define WTIME 0.001
#define ON 1
#define OFF 0

Serial terminal(USBTX, USBRX);

DigitalOut motorpin1(p21);
DigitalOut motorpin2(p22);
DigitalOut motorpin3(p23);
DigitalOut motorpin4(p24);

void clockwise()
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

void anticlockwise()
{
    motorpin1 = ON;
    wait(WTIME);
    motorpin2 = OFF;
    wait(WTIME);
    motorpin4 = ON;
    wait(WTIME);
    motorpin1 = OFF;
    wait(WTIME);        
    motorpin3 = ON;
    wait(WTIME);
    motorpin4 = OFF;
    wait(WTIME);
    motorpin2 = ON;
    wait(WTIME);
    motorpin3 = OFF;
    wait(WTIME);
}

int main()
{
    int input = 0;
    
    while(1) 
    {        
        terminal.printf("\n Enter Choice [1 (clockwise), 0 (anti-clockwise)] : \n");
        terminal.scanf("%d", &input);
        terminal.printf("\n%d\n", input);
        fflush(stdin);
        
        motorpin1 = OFF;
        motorpin2 = OFF;
        motorpin3 = OFF;
        motorpin4 = OFF;   

        if(input)
        {
            while(!terminal.readable())
            {
                clockwise();
            }
        }
        else
        {
            while(!terminal.readable())
            {
                anticlockwise();
            }
        }        
    }
}
