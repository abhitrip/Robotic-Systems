/*
This Code is for integrating 3D Accelerometer with mbed 1768, printing logs on Serial Port
Course: CSE291E ( Robotics/Embedded Systems)
Assignment: 3
Last Modified: 16-Oct-2015
Team: CodeIT
Developers: Abhinav Garg; Abhijit Tripathy; Pulkit Bhatnagar
University of California, San Diego
*/

#include "mbed.h"

I2C i2c(p9, p10); //SDA, SCL
Serial terminal(USBTX, USBRX);

const int accelorometer_addr=0x32;

const int CTRL_REG1_A=0x20;
const int CTRL_REG4_A=0x23;

const int OUT_X_L_A=0x28;
const int OUT_X_H_A=0x29;
const int OUT_Y_L_A=0x2A;
const int OUT_Y_H_A=0x2B;
const int OUT_Z_L_A=0x2C;
const int OUT_Z_H_A=0x2D;

char read_byte_i2c (int addr, int reg)       // Reads one byte from an I2C bus START-->HOSTADR-->SUBADDR-->START-->READATA-->STOP
{
    char result;
    
    i2c.start();
    i2c.write(addr);                            // Slave/Device address
    i2c.write(reg);                             // Subaddress (register addess)
    
    i2c.start();                                // Change bus direction
    i2c.write(addr + 1);                        // Slave address with direction=read [bit0=1]
    
    result = i2c.read(0);
    i2c.stop();
    return (result);
}
    
void write_byte_i2c(int addr, int reg,char value)             // Write one byte to an I2C bus START-->ADDR-->SUBADDR-->DATA-->STOP 
{    
    i2c.start();
    i2c.write(addr);                                          // Slave/Device address
    i2c.write(reg);                                         // Subaddress (register addess)
    i2c.write(value);
    i2c.stop();
}

int main()
{
    //Set Accelorometer Control Registers    
    write_byte_i2c(accelorometer_addr, CTRL_REG1_A, 0x27);  //CTRL_REG1_A control   
    write_byte_i2c(accelorometer_addr, CTRL_REG4_A, 0x08);  //CTRL_REG4_A control 
    
    while(1) 
    {
        wait(0.1);  //10Hz
        
        char xL, xH, yL, yH, zL, zH;
        int X_acc, Y_acc, Z_acc;
        
        //Read output Accelerometer register values
        xL=read_byte_i2c(accelorometer_addr,OUT_X_L_A);
        xH=read_byte_i2c(accelorometer_addr,OUT_X_H_A);
        yL=read_byte_i2c(accelorometer_addr,OUT_Y_L_A);
        yH=read_byte_i2c(accelorometer_addr,OUT_Y_H_A);
        zL=read_byte_i2c(accelorometer_addr,OUT_Z_L_A);
        zH=read_byte_i2c(accelorometer_addr,OUT_Z_H_A);
        
        //Combine MSB and LSB, shift 4 for 12bit values
        X_acc = (signed short) ((xH << 8) | xL) >> 4;       
        Y_acc = (signed short) ((yH << 8) | yL) >> 4;
        Z_acc = (signed short) ((zH << 8) | zL) >> 4;
        
        terminal.printf("\nAccelerometer Reading : \n");
        terminal.printf("X:%d \t Y:%d \t Z:%d \n", X_acc, Y_acc, Z_acc);    
    }
}