/*
This Code is for ACCELEROMETER+MAGNETOMETR integration with I2C in mbed 1768 with 1Hz Console update
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
Ticker t_acc, t_mag;
Timer timer;
//Device Address
const int magnetometer_addr=0x3C;
const int accelorometer_addr=0x32;

//Register Sub-Address
//Accelerometer
const int CTRL_REG1_A=0x20;
const int CTRL_REG4_A=0x23;
const int OUT_X_L_A=0x28;
const int OUT_X_H_A=0x29;
const int OUT_Y_L_A=0x2A;
const int OUT_Y_H_A=0x2B;
const int OUT_Z_L_A=0x2C;
const int OUT_Z_H_A=0x2D;
//Megnetometer
const int CRA_REG_M=0x00;
const int MR_REG_M=0x02;
const int OUT_X_L_M=0x04;
const int OUT_X_H_M=0x03;
const int OUT_Y_L_M=0x08;
const int OUT_Y_H_M=0x07;
const int OUT_Z_L_M=0x06;
const int OUT_Z_H_M=0x05;
static int sample_acc=0;
static int sample_mag=0;


short X_mag, Y_mag, Z_mag;
int X_acc, Y_acc, Z_acc;
//Function Definition for I2C read and Write 1 byte
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

//Function to read magnetometer readings
void read_mag()
{
 //       wait(1);
        
        char xL, xH, yL, yH, zL, zH;
        
        //Read output Magnetometer register values
            xL=read_byte_i2c(magnetometer_addr,OUT_X_L_M);
            xH=read_byte_i2c(magnetometer_addr,OUT_X_H_M);
            yL=read_byte_i2c(magnetometer_addr,OUT_Y_L_M);
            yH=read_byte_i2c(magnetometer_addr,OUT_Y_H_M);
            zL=read_byte_i2c(magnetometer_addr,OUT_Z_L_M);
            zH=read_byte_i2c(magnetometer_addr,OUT_Z_H_M);
        
//        short X_mag, Y_mag, Z_mag;
        X_mag =  (xH << 8) | (xL) ; //Combine MSB and LSB
        Y_mag =  (yH << 8) | (yL) ;
        Z_mag =  (zH << 8) | (zL) ;
      
         //terminal.printf("\nMAGNETOMETER:\t X:%d \t Y:%d \t Z:%d \n", X_mag, Y_mag, Z_mag);    
        sample_mag++;

}

//Function to read accelerometer readings
void read_acc()
{


//       wait(1);
        
        char xL, xH, yL, yH, zL, zH;
        
        //Read output acceletrometer register values
            xL=read_byte_i2c(accelorometer_addr,OUT_X_L_A);
            xH=read_byte_i2c(accelorometer_addr,OUT_X_H_A);
            yL=read_byte_i2c(accelorometer_addr,OUT_Y_L_A);
            yH=read_byte_i2c(accelorometer_addr,OUT_Y_H_A);
            zL=read_byte_i2c(accelorometer_addr,OUT_Z_L_A);
            zH=read_byte_i2c(accelorometer_addr,OUT_Z_H_A);
        
//        int X_acc, Y_acc, Z_acc;
        X_acc = (signed short) ((xH << 8) | xL) >> 4;   //Combine MSB and LSB, shift 4 for 12bit values
        Y_acc = (signed short) ((yH << 8) | yL) >> 4;
        Z_acc = (signed short) ((zH << 8) | zL) >> 4;
      
         //terminal.printf("ACCELEROMETER:\t X:%d \t Y:%d \t Z:%d \n", X_acc, Y_acc, Z_acc);
        sample_acc++;

}


int main()
{
// NVIC_SetPriority(TIMER3_IRQn, 0);   
//    i2c.frequency(100000);                        //I2C Frequency Setting, default standard mode=100khz
    
    //Set Magnetometer Control Registers
   //CRA_REG_M control
   write_byte_i2c(magnetometer_addr, CRA_REG_M, 0x04);
     //MR_REG_M control
   write_byte_i2c(magnetometer_addr, MR_REG_M, 0x00);
 
    //Set Accelorometer Control Registers 
   //CTRL_REG1_A control
   write_byte_i2c(accelorometer_addr, CTRL_REG1_A, 0x27);
   //CTRL_REG4_A control 
   write_byte_i2c(accelorometer_addr, CTRL_REG4_A, 0x08);  
    
          
//              timer.start();    
 
 
      t_mag.attach(&read_mag,0.004);                //Max sampling frequency: 250Hz
      t_acc.attach(&read_acc,0.007);                //Max sampling frequency: 142Hz

       while(1){    
               terminal.printf("\nMAGNETOMETER:\t X:%d \t Y:%d \t Z:%d \n", X_mag, Y_mag, Z_mag);
               terminal.printf("ACCELEROMETER:\t X:%d \t Y:%d \t Z:%d \n", X_acc, Y_acc, Z_acc);
               terminal.printf("\nTotal Magnetometer samples: %d \t Total Accelerometer Samples: %d", sample_mag,sample_acc);
            
                wait(1);            //Print values at 1Hz
       }
}