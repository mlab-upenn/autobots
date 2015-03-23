/* mbed MRF24J40 (IEEE 802.15.4 tranceiver) Library
 * Copyright (c) 2011 Jeroen Hilgers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
  
#ifndef MRF24J40_H
#define MRF25J40_H

#include "mbed.h"

/** MRF24J40 class. Provides a simple send/receive API for a microchip
 ** MFR24J40 IEEE 802.15.4 tranceiver. The tranceiver is available on a 
 ** module that can easilly be soldered to some header pins to use it with
 ** an mbed on a breadboard. The module is called 'MRF24J40MA' and can be 
 ** ordered for example by www.farnell.com.
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "MRF24J40.h"
 * 
 * // RF tranceiver to link with handheld.
 * MRF24J40 mrf(p11, p12, p13, p14, p21);
 * 
 * // LEDs
 * DigitalOut led1(LED1);
 * DigitalOut led2(LED2);
 * DigitalOut led3(LED3);
 * DigitalOut led4(LED4);
 * 
 * // Timer.
 * Timer timer;
 * 
 * // Serial port for showing RX data.
 * Serial pc(USBTX, USBRX); 
 * 
 * // Send / receive buffers.
 * // IMPORTANT: The MRF24J40 is intended as zigbee tranceiver; it tends
 * // to reject data that doesn't have the right header. So the first 
 * // 8 bytes in txBuffer look like a valid header. The remaining 120
 * // bytes can be used for anything you like.
 * uint8_t txBuffer[128]= {1, 8, 0, 0xA1, 0xB2, 0xC3, 0xD4, 0x00};
 * 
 * uint8_t rxBuffer[128];
 * uint8_t rxLen;
 * 
 * int main (void)
 * {
 *     uint8_t count = 0;
 *     pc.baud(115200);
 *     timer.start();
 *     while(1)
 *     {
 *         // Check if any data was received. 
 *         rxLen = mrf.Receive(rxBuffer, 128);
 *         if(rxLen) 
 *         {
 *             // Toggle LED 1 upon each reception of data.
 *             led1 = led1^1;
 *             // Send to serial.
 *             // IMPORTANT: The last two bytes of the received data
 *             // are the checksum used in the transmission. 
 *             for(uint8_t i=0; i<rxLen; i++)
 *             {
 *                 pc.printf("0x%02X ", rxBuffer[i]);
 *             }
 *             pc.printf("\r\n");
 *         }
 *         
 *         // Each second, send some data.
 *         if(timer.read_ms() >= 1000) 
 *         {
 *             timer.reset();
 *             // Toggle LED 2.
 *             led2 = led2^1;
 *             
 *             // UART.
 *             pc.printf("TXD\r\n");
 *             
 *             // Send counter value.
 *             count++;
 *             txBuffer[8] = count;
 *             mrf.Send(txBuffer, 9);
 *         }
 *     }
 * }
 * @endcode
 */


class MRF24J40
{
  public:
    /** Create a MRF24J40 object and initizalize it.
     *
     * @param pin mosi Spi MOSI pin connected to MRF's SDI.
     * @param pin miso Spi MISO pin connected to MRF's SDO.
     * @param pin sck  Spi SCK pin connected to MRF's SCK.
     * @param pin cs Pin connected to MRF's #CS.
     * @param pin reset Pin connected to MRF's #Reset.
     */
    MRF24J40(PinName mosi, PinName miso, PinName sck, PinName cs, PinName reset);//, PinName irq, PinName wake);
    
    /** Reset the MRF24J40 and initialize it.
     */
    void Reset(void);                             // Reset chip and configure it.
    
    /** Send data.
     *
     * Note that the MRF24J40 only handles data with a valid IEEE 802.15.4
     * header. See the example how to get around this.
     *
     * @param data Pointer to data to be send.
     * @param length Length of the data to be send in bytes.
     */
    void Send(uint8_t *data, uint8_t length);         // Send data.

    /** Check if any data was received.
     *
     * Note that the MRF24J40 appends two bytes of CRC for each packet.
     * So you will receive two bytes more than were send with the 'Send' function.
     *
     * @param data Pointer to buffer where received data can be placed.
     * @param maxLength Maximum amount of data to be placed in the buffer.
     * @param returns The number of bytes written into the buffer.
     */
    uint8_t Receive(uint8_t *data, uint8_t maxLength);  // Receive data if ready.
    
    // void DebugDump(Serial &ser);

  private:
    SPI mSpi;
    DigitalOut mCs;
    DigitalOut mReset;
    // DigitalIn mIrq;
    // DigitalIn mWake;

    uint8_t ReadShort (uint8_t address);
    void WriteShort (uint8_t address, uint8_t data);
    uint8_t ReadLong (uint16_t address);
    void WriteLong (uint16_t address, uint8_t data);
};

#endif