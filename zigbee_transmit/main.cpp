

#include "mbed.h"
#include "MRF24J40.h"
#include <string> 
using namespace std;

// RF tranceiver to link with handheld.
MRF24J40 mrf(p11, p12, p13, p14, p21);

// LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// Serial port for showing RX data.
Serial pc(USBTX, USBRX); 

// Send / receive buffers.
// IMPORTANT: The MRF24J40 is intended as zigbee tranceiver; it tends
// to reject data that doesn't have the right header. So the first 
// 8 bytes in txBuffer look like a valid header. The remaining 120
// bytes can be used for anything you like.
uint8_t txBuffer[128]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};
string read_serial()
{
    string buf;
    while(1)      
        if(pc.readable())
        {
            char c = pc.getc();
            pc.printf("%c",c);
/*            
        if((c == '\r')||(c == '\n'))
            {
                c = '\0';   
                buf+=(c);
                break;
            }
*/
            buf+=(c);
            break;
        } 
    pc.printf("\n");
    return buf;
}

int main (void)
{
    int count = 10;
    pc.baud(115200);
    pc.printf("Program Begins\r\n");
    while(1)
    {   
        uint8_t txBuffer[128]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};
        string s = read_serial();
        led2 = led2^1;
        memcpy(txBuffer+8,s.c_str(),s.length());
        mrf.Send(txBuffer, 8 + s.length());
    }
}

