#ifndef __SHARED_H__
#define __SHARED_H__

#include "mbed.h"

// LED 
static DigitalOut led1(LED1); // forward
static DigitalOut led2(LED2); // back
static DigitalOut led3(LED3); // left
static DigitalOut led4(LED4); // right
//static InterruptIn right_encoder   (p21);
//static InterruptIn left_encoder    (p23);

// serial
static Serial pc(USBTX, USBRX);    // tx, rx

#endif