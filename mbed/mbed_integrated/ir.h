#ifndef __IR_H__
#define __IR_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"

#define FORWARD     1
#define BACKWARD    2
#define RIGHT       3
#define LEFT        4
#define STOP        0

// ir read
static AnalogIn ir_l1(p20);
static AnalogIn ir_l2(p19);
static AnalogIn ir_mid(p18);
static AnalogIn ir_r1(p17);
static AnalogIn ir_r2(p16);

// function
void read_ir(void const *);

#endif