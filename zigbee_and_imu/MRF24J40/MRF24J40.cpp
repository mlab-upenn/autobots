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

#include "MRF24J40.h"

// MRF20J40 Short address control register mapping.
#define RXMCR     0x00
#define PANIDL    0x01
#define PANIDH    0x02
#define SADRL     0x03
#define SADRH     0x04
#define EADR0     0x05
#define EADR1     0x06
#define EADR2     0x07
#define EADR3     0x08
#define EADR4     0x09
#define EADR5     0x0a
#define EADR6     0x0b
#define EADR7     0x0c
#define RXFLUSH   0x0d

#define TXNMTRIG  0x1b
#define TXSR      0x24

#define ISRSTS    0x31
#define INTMSK    0x32
#define GPIO      0x33
#define TRISGPIO  0x34

#define RFCTL     0x36

#define BBREG2    0x3A

#define BBREG6    0x3E
#define RSSITHCCA 0x3F

// MRF20J40 Long address control register mapping.
#define RFCTRL0   0x200

#define RFCTRL2   0x202
#define RFCTRL3   0x203

#define RFCTRL6   0x206
#define RFCTRL7   0x207
#define RFCTRL8   0x208

#define CLKINTCR  0x211
#define CLCCTRL   0x220

MRF24J40::MRF24J40(PinName mosi, PinName miso, PinName sck, PinName cs, PinName reset) ://, PinName irq, PinName wake) :
    mSpi(mosi, miso, sck), // mosi, miso, sclk
    mCs(cs),
    mReset(reset)
//    mIrq(irq),
//    mWake(wake)
{
    mSpi.format(8, 0); // 8 bits, cpol=0; cpha=0
    mSpi.frequency(500000);
    Reset();
}

/*
void MRF24J40::DebugDump(Serial &ser)
{
   ser.printf("MRF24J40 registers:\r");
   ser.printf("RXMCR=0x%X\r", MrfReadShort(RXMCR));
   ser.printf("RXFLUSH=0x%X\r", MrfReadShort(RXFLUSH)); 
   ser.printf("TXNMTRIG=0x%X\r", MrfReadShort(TXNMTRIG));
   ser.printf("TXSR=0x%X\r", MrfReadShort(TXSR));
   ser.printf("ISRSTS=0x%X\r", MrfReadShort(ISRSTS)); 
   ser.printf("INTMSK=0x%X\r", MrfReadShort(INTMSK));
   ser.printf("GPIO=0x%X\r", MrfReadShort(GPIO));
   ser.printf("TRISGPIO=0x%X\r", MrfReadShort(TRISGPIO));
   ser.printf("RFCTL=0x%X\r", MrfReadShort(RFCTL));
   ser.printf("BBREG2=0x%X\r", MrfReadShort(BBREG2));
   ser.printf("BBREG6=0x%X\r", MrfReadShort(BBREG6));
   ser.printf("RSSITHCCA=0x%X\r", MrfReadShort(RSSITHCCA));
  
  
   ser.printf("RFCTRL0=0x%X\r", MrfReadLong(RFCTRL0));
   ser.printf("RFCTRL2=0x%X\r", MrfReadLong(RFCTRL2));
   ser.printf("RFCTRL3=0x%X\r", MrfReadLong(RFCTRL3));
   ser.printf("RFCTRL6=0x%X\r", MrfReadLong(RFCTRL6));
   ser.printf("RFCTRL7=0x%X\r", MrfReadLong(RFCTRL7));
   ser.printf("RFCTRL8=0x%X\r", MrfReadLong(RFCTRL8));
   ser.printf("CLKINTCR=0x%X\r", MrfReadLong(CLKINTCR));
   ser.printf("CLCCTRL=0x%X\r", MrfReadLong(CLCCTRL));
   ser.printf("\r");
}
*/

void MRF24J40::Reset(void)
{
    mCs = 1;
    // Pulse hardware reset.
    mReset = 0;
    wait_us(100);
    mReset = 1;
    wait_us(100);
    
    // Reset RF module.
    WriteShort(RFCTL, 0x04);
    WriteShort(RFCTL, 0x00);
  
    WriteShort(RFCTL, 0x00);
  
    WriteShort(PANIDL, 0xAA);
    WriteShort(PANIDH, 0xAA);
    WriteShort(SADRL, 0xAA);
    WriteShort(SADRH, 0xAA);
  
    // Flush RX fifo.
    WriteShort(RXFLUSH, 0x01);
  
    // Write MAC addresses here. We don't care.

    WriteLong(RFCTRL2, 0x80);  // Enable RF PLL.
  
    WriteLong(RFCTRL3, 0x00);  // Full power.
    WriteLong(RFCTRL6, 0x80);  // Enable TX filter (recommended)
    WriteLong(RFCTRL8, 0x10);  // Enhanced VCO (recommended)
      
    WriteShort(BBREG2,0x78);   // Clear Channel Assesment use carrier sense.
    WriteShort(BBREG6,0x40);   // Calculate RSSI for Rx packet.
    WriteShort(RSSITHCCA,0x00);// RSSI threshold for CCA. 
      
    WriteLong(RFCTRL0, 0x00);  // Channel 11.
  
    WriteShort(RXMCR, 0x01); // Don't check address upon reception.
//  MrfWriteShort(RXMCR, 0x00); // Check address upon reception.
  
    // Reset RF module with new settings.
    WriteShort(RFCTL, 0x04);
    WriteShort(RFCTL, 0x00);
}

void MRF24J40::Send(uint8_t *data, uint8_t length)
{
  uint8_t i;
  
  WriteLong(0x000, 0);   // No addresses in header.
  WriteLong(0x001, length); // 11 bytes
  for(i=0; i<length; i++)
    WriteLong(0x002+i, data[i]); 
    
  WriteShort(TXNMTRIG, 0x01);
}

uint8_t MRF24J40::Receive(uint8_t *data, uint8_t maxLength)
{
  uint8_t i, length;
  uint8_t lqi, rssi;
  
  if(ReadShort(ISRSTS)& 0x08)
  {
    length = ReadLong(0x300);
    lqi = ReadLong(0x301 + length);
    rssi = ReadLong(0x302 + length);
    for(i=0; i<length; i++)
      if(i<maxLength)
          *data++ = ReadLong(0x301 + (uint16_t)i);
      else
          ReadLong(0x301 + (uint16_t)i);
    if(length < maxLength)
       return length;          
  }
  return 0;
}

uint8_t MRF24J40::ReadShort (uint8_t address)
{
  uint8_t value;
  mCs = 0;
  wait_us(1);
  mSpi.write((address<<1) & 0x7E);
  wait_us(1);
  value = mSpi.write(0xFF);
  wait_us(1);
  mCs = 1;
  wait_us(1);
  return value;
}

void MRF24J40::WriteShort (uint8_t address, uint8_t data)
{
  mCs = 0;
  wait_us(1);
  mSpi.write(((address<<1) & 0x7E) | 0x01);
  wait_us(1);
  mSpi.write(data);
  wait_us(1);
  mCs = 1;
  wait_us(1);
}

uint8_t MRF24J40::ReadLong (uint16_t address)
{
  uint8_t value;
  mCs = 0;
  wait_us(1);
  mSpi.write((address>>3) | 0x80);
  wait_us(1);
  mSpi.write((address<<5) & 0xE0);
  wait_us(1);
  value = mSpi.write(0xFF);
  wait_us(1);
  mCs = 1;
  wait_us(1);
  return value;
}

void MRF24J40::WriteLong (uint16_t address, uint8_t data)
{
  mCs = 0;
  wait_us(1);
  mSpi.write((address>>3) | 0x80);
  wait_us(1);
  mSpi.write(((address<<5) & 0xE0) | 0x10);
  wait_us(1);
  mSpi.write(data);
  wait_us(1);
  mCs = 1;
  wait_us(1);
}
