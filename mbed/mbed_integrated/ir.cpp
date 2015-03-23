// ir receiver
#include "ir.h"

void read_ir(void const *)
{
    int AMBIENT_LEFT  = 60;
    int AMBIENT_RIGHT = 60;
    int AMBIENT_MID = 15;
    float offset = 10.0;
    
    while (1) {
          float l1_val = ir_l1.read()*100.0f;
          float l2_val = ir_l2.read()*100.0f;
          float mid_val = ir_mid.read()*100.0f;
          float r1_val = ir_r1.read()*100.0f + offset; // potential light leak on pcb hole
          float r2_val = ir_r2.read()*100.0f;
          float left_val, right_val;
        
          // might need to queue data and calculate average
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
              led2 = !led2; // here use led2 for stop
          } else { 
              if ((left_val > 1.2*right_val) && (mid_val < AMBIENT_MID + 15)) {
                  pc.printf("BIR %d EIR",RIGHT);
                  led4 = !led4;
              } else if ((right_val > 1.2*left_val) && (mid_val < AMBIENT_MID + 15)) {
                  pc.printf("BIR %d EIR",LEFT);
                  led3 = !led3;
              } else {
                pc.printf("BIR %d EIR",FORWARD);
                led1 = !led1;
              }
           }   
          // wait(1);
           Thread::wait(1000);
      }
}