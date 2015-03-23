/*
 * Simple algorithm to use data from 5-ir receiver array
 * Hardware Setup: 5-ir receivers aligned symmetrically on top of 1 emitter.
 * Zhi Li 03/19/15
 */
#include "mbed.h"

AnalogIn ir_l1(p20);
AnalogIn ir_l2(p19);
AnalogIn ir_mid(p18);
AnalogIn ir_r1(p17);
AnalogIn ir_r2(p16);

DigitalOut led_forward(LED1);
DigitalOut led_stop(LED2);
DigitalOut led_left(LED3);
DigitalOut led_right(LED4);

Serial pc(USBTX, USBRX);    // tx, rx

#define FORWARD     1
#define BACKWARD    2
#define RIGHT       3
#define LEFT        4
#define STOP        0

int AMBIENT_LEFT  = 60; // tested on lab floor vs black tape
int AMBIENT_RIGHT = 60; // will also apply to cleaner floor like tiles
int AMBIENT_MID = 15;

float offset = 10.0;

int main() {
  pc.baud(115200);
  led_forward = 0;
  led_stop = 0;
  led_left = 0;
  led_right = 0;
  
  while (1) {
        float l1_val = ir_l1.read()*100.0f;
        float l2_val = ir_l2.read()*100.0f;
        float mid_val = ir_mid.read()*100.0f;
        float r1_val = ir_r1.read()*100.0f + offset; // potential light leak on pcb hole
        float r2_val = ir_r2.read()*100.0f;
        float left_val, right_val;
        
        pc.printf("l1 = %f l2 = %f mid = %f r1 = %f r2 = %f",l1_val, l2_val, mid_val, r1_val, r2_val);
        
        // may use weighted average
        left_val = l1_val + l2_val;
        right_val = r1_val + r2_val;
        
        // check if  value is not on line, if not set to max brightness
        if (left_val < AMBIENT_LEFT)  
            left_val = 0;
        if (right_val < AMBIENT_RIGHT) // check if  value is not on line, if not set to max brightness
            right_val = 0;
            
       if ((mid_val < AMBIENT_MID ) && (left_val == 0)&& (right_val == 0)){ // if both left and right are bright, it means there is no black line hence stop
            pc.printf("BIR %d EIR",STOP);
            led_stop = !led_stop;
        } else { 
            if ((left_val > 1.2*right_val) && (mid_val < AMBIENT_MID + 15)) {
                pc.printf("BIR %d EIR",RIGHT);
                led_right = !led_right;
            } else if ((right_val > 1.2*left_val) && (mid_val < AMBIENT_MID + 15)) {
                pc.printf("BIR %d EIR",LEFT);
                led_left = !led_left;
            } else {
              pc.printf("BIR %d EIR",FORWARD);
              led_forward = !led_forward;
            }
         }   
        wait(1);
    }
}
