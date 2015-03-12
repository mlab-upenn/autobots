/*
 * MbedHardware
 *
 *  Created on: Aug 17, 2011
 *      Author: nucho
 */

#ifndef MBEDHARDWARE_H_
#define MBEDHARDWARE_H_

#include"mbed.h"
#include"MODSERIAL.h"

#ifndef ROSSERIAL_BAUDRATE
#define ROSSERIAL_BAUDRATE    57600
#endif


class MbedHardware {
public:
    MbedHardware(MODSERIAL* io , int baud= ROSSERIAL_BAUDRATE)
            :iostream(*io){
        baud_ = baud;
        t.start();
    }
    MbedHardware()
            :iostream(USBTX, USBRX) {
        baud_ = ROSSERIAL_BAUDRATE;
        t.start();
    }
    MbedHardware(MbedHardware& h)
            :iostream(h.iostream) {
        this->baud_ = h.baud_;
        
        t.start();
    }

    void setBaud(int baud) {
        this->baud_= baud;
    }

    int getBaud() {
        return baud_;
    }

    void init() {
        iostream.baud(baud_);
    }

    int read() {
        if (iostream.readable()) {
            return iostream.getc();
        } else {
            return -1;
        }
    };
    void write(uint8_t* data, int length) {
        for (int i=0; i<length; i++) iostream.putc(data[i]);
    }

    unsigned long time() {
        return t.read_ms();
    }

protected:
    int baud_;
    MODSERIAL iostream;
    Timer t;
};


#endif /* MBEDHARDWARE_H_ */
