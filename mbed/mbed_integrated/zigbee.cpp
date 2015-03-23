#include "zigbee.h"

// Send / receive buffers.
// IMPORTANT: The MRF24J40 is intended as zigbee tranceiver; it tends
// to reject data that doesn't have the right header. So the first 
// 8 bytes in txBuffer look like a valid header. The remaining 120
// bytes can be used for anything you like.
uint8_t txBuffer[128]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};
uint8_t rxBuffer[128];

void receive_command(void const *)
{
    uint8_t rxLen;

    while(1)
    {
        uint8_t rxBuffer[128];
        // Check if any data was received. 
        rxLen = mrf.Receive(rxBuffer, 128);
        if(rxLen) 
        {
            led4 = !led4;
            char buffer[128] = {0};
            memcpy(buffer,rxBuffer+8,rxLen-10);
            buffer[rxLen-9] = '\0';            
            pc.printf("BMAIN %s EMAIN", buffer);
            // pc.printf("BMAIN %d %d %d %d %d EMAIN", (int)(buffer[0]),(int)(buffer[1]), (int)(buffer[2]), (int)(buffer[3]), (int)(buffer[4]));
            pc.printf("\r\n");
        }
        
        Thread::wait(100);
    }
}