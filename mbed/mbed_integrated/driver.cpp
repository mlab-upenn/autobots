#include "driver.h"

/*Interrupt handler*/
Ticker ticker_movement;
Ticker ticker_spin;
// might need mutex
int command = 0;
int old_command = -1;  
volatile int flag = 0; 

void brake(){
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    Right_Forward   = 1;
    Right_Backward  = 1;
    Right_Enable    = 1;
    Left_Forward    = 1;
    Left_Backward   = 1;
    Left_Enable     = 1;
    }


void forward(){
    led1 = !led1; 
    // simulation purpose
    Right_Forward   = 1;
    Right_Backward  = 0;
    Right_Enable    = 1;
    Left_Forward    = 1;
    Left_Backward   = 0;
    Left_Enable     = 1;
    wait(DELTA);
    brake();
    }
void back(){
    led2 =!led2;
    // simulation purpose
    Right_Forward   = 0;
    Right_Backward  = 1;
    Right_Enable    = 1;
    Left_Forward    = 0;
    Left_Backward   = 1;
    Left_Enable     = 1;
    wait(DELTA);
    brake();
     }
void left(){
    led3 =!led3;
    // simulation purpose
    Right_Forward   = 1;
    Right_Backward  = 0;
    Right_Enable    = 1;
    Left_Forward    = 1;
    Left_Backward   = 1;
    Left_Enable     = 1; 
    wait(DELTA);
    brake();
    }
void right(){
    led4 =!led4;
    Right_Forward   = 1;
    Right_Backward  = 1;
    Right_Enable    = 1;
    Left_Forward    = 1;
    Left_Backward   = 0;
    Left_Enable     = 1;
    wait(DELTA);
    brake();
    }

void stop(){
    ticker_movement.detach();
    brake();
    }

void updateMovement()
{
        if (flag != 0){
        switch (command) {
            case 0:     // stop
                stop();
                break;
            case 1:     // move forward
                stop();
                forward();
                //ticker_movement.attach_us(&forward,1000000);
                break;
            case 2:     // move back
                stop();
                back();
                //ticker_movement.attach_us(&back,1000000);
                break;
            case 3:     //turn left
                stop();
                left();
                //ticker_movement.attach_us(&left,1000000);
                break;
            case 4:     //turn right
                stop();
                right();
                //ticker_movement.attach_us(&right,1000000);
                break;
            default:
                stop();
                break;
        }
            flag = 0;
        }

}

 void movementControl(Int8& velocity_msg)
 {
     if((velocity_msg.data >= 0) && (velocity_msg.data <= 4))
     {
         command     = velocity_msg.data;
         flag = 1;
         // pc.printf("coming here");
     }
 }


void motor_controller(void const *)
{
    while(1) {
        brake();
        // motor_receive_command();
        if(pc.readable())
        {
            Int8 velocity_msg;
            velocity_msg.data = pc.getc() - '0';
            movementControl(velocity_msg);
            // pc.printf("I got %d\n",velocity_msg.data);
        }
        updateMovement();
        Thread::wait(100); // control frequency
    }
}