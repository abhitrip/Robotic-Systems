/*
This Code is for testing magnetometer sensor connectivity integration with mbed 1768 with communciation via I2c
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
const int magnetometer_addr=0x3C;
const int CRA_REG_M=0x00;
const int MR_REG_M=0x02;
const int OUT_X_L_M=0x04;
const int OUT_X_H_M=0x03;
const int OUT_Y_L_M=0x08;
const int OUT_Y_H_M=0x07;
const int OUT_Z_L_M=0x06;
const int OUT_Z_H_M=0x05;

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
 
//Set Magnetometer Control Registers
   //CRA_REG_M control
   write_byte_i2c(magnetometer_addr, CRA_REG_M, 0x04);
     //MR_REG_M control
   write_byte_i2c(magnetometer_addr, MR_REG_M, 0x00);
  
    
    
     while(1) 
    {
        wait(1);                //1Hz
        
        char xL, xH, yL, yH, zL, zH;
        
        //Read output Magnetometer register values
            xL=read_byte_i2c(magnetometer_addr,OUT_X_L_M);
            xH=read_byte_i2c(magnetometer_addr,OUT_X_H_M);
            yL=read_byte_i2c(magnetometer_addr,OUT_Y_L_M);
            yH=read_byte_i2c(magnetometer_addr,OUT_Y_H_M);
            zL=read_byte_i2c(magnetometer_addr,OUT_Z_L_M);
            zH=read_byte_i2c(magnetometer_addr,OUT_Z_H_M);
        
        short X_mag, Y_mag, Z_mag;
        X_mag =  (xH << 8) | (xL) ;                 //Combine MSB and LSB
        Y_mag =  (yH << 8) | (yL) ;
        Z_mag =  (zH << 8) | (zL) ;
      
         terminal.printf("X:%d \t Y:%d \t Z:%d \n", X_mag, Y_mag, Z_mag);
        
          
    }
}