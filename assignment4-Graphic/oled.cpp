#include "oled.h"

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

I2CPreInit gI2C(p9,p10);
Adafruit_SSD1306_I2c gOled2(gI2C,p27);

uint8_t arr[64 * 128 / 8] = {0,}; //screen
int c=0; //128
int r=0; //64 or 32
uint8_t d = 0x00;
bool enable = false;
bool vscroll = false;
bool linefull = false;

void oled_display(float t)
{
    gOled2.send(arr);        
    gOled2.display(d);
    wait(t);
}


void oled_clear()
{    
    enable = false;
    vscroll = false;
    linefull = false;
    d = 0x00;
    r=0;
    c=0;
    
    for(int i=0;i < (64 * 128 / 8); i++)
    {
        arr[i] = 0;
    }
    
    oled_display(0.05);
}



void oled_rowclear(int r)
{
    for(int i=0;i<128;i++)
    {
        arr[128*r+i] = 0x00;
    }
}


void oled_vscroll(bool input)
{
    vscroll = input;
}


void oled_checkoverflow()
{
    c=0;            
    r++;                      //next row
    
    if(r == (64/8)) //(64/8 or 32/8)
    {
        r=0;            
        enable = ((vscroll)?true:false);     
        
        if(vscroll == false)
        {
            oled_clear();
        }
    }    
    
    if(enable)
    {
        oled_rowclear(r);
        
        if((d >= 0x07) && (d < 0x3F))
        {
            d = d + 0x08;
        }
        else
        {
            d = 0x07;
        }
    }
    else
    {
        d = 0x00;
    }
}


bool oled_putc(char ch, bool displaycontrol)
{   
    if(linefull)
    {
        oled_checkoverflow();
        linefull = false;
    }
    
    if(ch == '\n')
    {
        linefull = true;
    }
    else
    {
        int i = (ch - 32); // ASCII - 32 to get font table index
        
        for(int j=(c%5); j<5; j++)
        {
            arr[128*r+c] = Font5x7[5*i+j];
            c++;
        }
        
        if((c%125) == 0) //(128 bytes / (5 bytes/char))
        {
            linefull = true;
            
            arr[128*r+c] = 0x00; //125th byte set 0
            c++;
            arr[128*r+c] = 0x00; //126th byte set 0
            c++;
            arr[128*r+c] = 0x00; //127th byte set 0
        }
    }
    
    if(displaycontrol)
    {
        oled_display(0.01);
    }
    
    return linefull;
}


void oled_printword(char *s)
{
    if(s)
    {
        int i=0;
        
        while(s[i])  //string not terminated
        {
            oled_putc(s[i], false);
            
            if((s[i] == ' ') || (s[i] == '\n')) //space meaning end of word
            {
                oled_display(0.05);
            }
            
            i++;
        }
        
        if(s[i-1] != '\n')
        {
            oled_display(0.05);
        }
                
        wait(2);
    }
}


void oled_printf(char *s, int delay)
{
    if(s)
    {
        Timer t;
        t.start();
        int i=0;
        bool linefull = false;
        
        while(s[i])  //string not terminated
        {
            linefull = oled_putc(s[i], false);     
            
            if(linefull)
            {
                while(t.read() < delay);
                oled_display(0);
                t.reset();
            } 
            
            i++;
        }
        
        oled_display(0);
    }
}