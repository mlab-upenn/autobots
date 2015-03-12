
#include "mbed.h"
#include "rtos.h"

#include "MRF24J40.h"
#include "HMC5843.h"
#include "ADXL345.h"
#include "ITG3200.h"

// RF tranceiver to link with handheld.
MRF24J40 mrf(p11, p12, p13, p14, p21);

// LEDs
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// Timer.
Timer timer;

// Serial port for showing RX data.
HMC5843 cmp(p28, p27);      // sda, scl
ADXL345 acc(p28, p27);      // sda, scl
ITG3200 gyr(p28, p27);      // sda, scl
Serial pc(USBTX, USBRX);    // tx, rx

// Send / receive buffers.
// IMPORTANT: The MRF24J40 is intended as zigbee tranceiver; it tends
// to reject data that doesn't have the right header. So the first 
// 8 bytes in txBuffer look like a valid header. The remaining 120
// bytes can be used for anything you like.
uint8_t txBuffer[128]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};

uint8_t rxBuffer[128];
uint8_t rxLen;



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
            led3 = led3^1;
            char buffer[128] = {0};
            memcpy(buffer,rxBuffer+8,rxLen-10);
            buffer[rxLen-9] = '\0';            
            pc.printf("BMAIN %s EMAIN", buffer);
            pc.printf("\r\n");
        }
    }
}


int main (void)
{

    Thread t(receive_command);
    pc.baud(115200);
    int readings[3];
    int final[9];
    char buffer[3];

    cmp.setDefault();
    wait(0.1);

    
       cmp.getAddress(buffer);
    if (acc.setPowerControl(0x00)){
         return 0;  }
    wait(.001);

       if(acc.setDataFormatControl(0x0B)){
        return 0;  }
    wait(.001);
    if(acc.setDataRate(ADXL345_3200HZ)){
        return 0;    }
     wait(.001);
    if(acc.setPowerControl(MeasurementMode)) {
        return 0;   } 
    pc.printf("Acc Id=%x \n\r", acc.getDeviceID());
    gyr.setLpBandwidth(LPFBW_256HZ);
    wait(1);
       
    while(1) 
        {

            cmp.readData(readings);
            final[0] = (int16_t)readings[0];
            final[1] = (int16_t)readings[1];
            final[2] = (int16_t)readings[2];
            wait(0.05);

            acc.getOutput(readings);
            final[3] = (int16_t)readings[0];
            final[4] = (int16_t)readings[1];
            final[5] = (int16_t)readings[2];
            wait(0.05);
            
            final[6] = (int16_t)gyr.getGyroX();
            final[7] = (int16_t)gyr.getGyroY();
            final[8] = (int16_t)gyr.getGyroZ();

            pc.printf("B %+4i %+4i %+4i %+5i %+5i %+5i %+5i %+5i %+5i E \r\n",final[0],final[1],final[2],final[3],final[4],final[5],final[6],final[7],final[8]);
            wait(0.05);

        }    

}

