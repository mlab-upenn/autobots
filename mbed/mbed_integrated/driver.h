#ifndef __DRIVER_H__
#define __DRIVER_H__

#include "mbed.h"
#include "rtos.h"
#include "string"
#include "shared.h"
#define DELTA 0.5 // duration time the motor runs

// control
static DigitalOut Right_Forward    (p5);
static DigitalOut Right_Backward   (p6);
static DigitalOut Right_Enable     (p7);
static DigitalOut Left_Forward     (p8);
static DigitalOut Left_Backward    (p9);
static DigitalOut Left_Enable      (p10);

struct Int8{
 uint8_t data;
 };
 
void brake();
void forward();
void back();
void left();
void right();
void stop();
void updateMovement();
void movementControl(Int8& velocity_msg);
void motor_controller(void const *);

#endif