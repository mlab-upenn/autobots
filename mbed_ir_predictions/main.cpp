#include "mbed.h"

AnalogIn   ir_left(p20);
AnalogIn   ir_right(p19);

DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);    // tx, rx

#define FORWARD     1
#define BACKWARD    2
#define RIGHT       3
#define LEFT        4
#define STOP        0
int AMBIENT_LEFT  = 35;
int AMBIENT_RIGHT = 35;


int main() {
  pc.baud(115200);

  while (1) {
        float left_val = ir_left.read()*100.0f;
        float right_val = ir_right.read()*100.0f;
        pc.printf("l = %f R = %f ",left_val,right_val);
        // check if  value is not on line, if not set to max brightness
        if(left_val < AMBIENT_LEFT)  
            left_val = 0;
        if (right_val < AMBIENT_RIGHT) // check if  value is not on line, if not set to max brightness
            right_val = 0;
            
       if ((left_val == 0)&& (right_val == 0)) // if both left and right are bright, it means there is no black line hence stop
            pc.printf("BIR %d EIR",STOP);
       else
       { 
            if (left_val > 1.2*right_val)
                pc.printf("BIR %d EIR",LEFT);
            else if (right_val > 1.2*left_val)
                pc.printf("BIR %d EIR",RIGHT);
            else
                pc.printf("BIR %d EIR",FORWARD);
        }
            
        wait(2);
    }
}
