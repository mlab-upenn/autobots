#define COMPILE_CONTROL_WITH_ENCODER_TOPIC
#ifdef COMPILE_CONTROL_WITH_ENCODER_TOPIC
#include "mbed.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>
#include <geometry_msgs/PointStamped.h>
#include <string.h>

// LED blinks on keyboard input
DigitalOut led1(LED1); //forward
DigitalOut led2(LED2); //back
DigitalOut led3(LED3); //left
DigitalOut led4(LED4); //right

// Registers on mbed
DigitalOut Right_Forward(p5);
DigitalOut Right_Backward(p6);
DigitalOut Right_Enable(p7);
DigitalOut Left_Forward(p8);
DigitalOut Left_Backward(p9);
DigitalOut Left_Enable(p10);
InterruptIn right_encoder(p21);
InterruptIn left_encoder(p23);

// test
//DigitalOut Simulate_left(p11);
//DigitalOut Simulate_right(p12);

// Interrupt routines
Ticker ticker_movement;
Ticker ticker_odmn;
Ticker ticker_spin;
//Ticker ticker_test_left;
//Ticker ticker_test_right;
//Timer timer;

int command = 0;
int old_command = 1;

//receive command from beagleboard
void velocityControl(const std_msgs::Int8& velocity_msg)
{
    if(velocity_msg.data == 1) {
        //forward
        command = 1;
    } else if (velocity_msg.data == 2) {
        //back
        command = 2;
    } else if(velocity_msg.data == 3) {
        //left
        command = 3;
    } else if (velocity_msg.data == 4) {
        //right
        command = 4;
    } else {
        command = 0;
    }

}


// variables for encoder update
unsigned long seq = 0; //record no. of encoder publishers
volatile long int r_count=0;
volatile long int l_count=0;
long int prev_r_count=0;
long int prev_l_count=0;
double distance=0.0;
double theta=0.0;
long double x_position=0.0;
long double y_position=0.0;
static int flag = 0;

// ros init
ros::NodeHandle nh;
ros::Subscriber<std_msgs::Int8> velocity("car_slam/cmd_vel", velocityControl);
char odom_frame[] = "/odom";
geometry_msgs::PointStamped encoder_odom;
ros::Publisher encoder_topic("/car_slam/encoder", &encoder_odom);

// functions that handle Encoder msg
void getEncoderTicks()
{
    encoder_odom.point.x = l_count - prev_l_count;
    encoder_odom.point.y = r_count - prev_r_count;
    prev_l_count = l_count;
    prev_r_count = r_count;//19.182 counts per inch
    encoder_odom.point.z = 0;
    encoder_odom.header.stamp = nh.now();
    encoder_odom.header.seq = seq;
    encoder_odom.header.frame_id = odom_frame;
    encoder_topic.publish ( &encoder_odom );
}


// handle encoder inputs, store in r_count, l_count
void right_slit(){
    r_count+= flag;
}
      
void left_slit(){
    l_count+=flag;
}

void reset_odo(){
    __disable_irq();
    l_count=0;
    r_count=0;
    __enable_irq();
    prev_r_count=0;
    prev_l_count=0;
    x_position=0.0;
    y_position=0.0;
    seq = 0;
}

void brake(){
    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    Right_Forward = 1;
    Right_Backward = 1;
    Right_Enable = 1;
    Left_Forward = 1;
    Left_Backward = 1;
    Left_Enable = 1;
    }

void stop(){
    ticker_movement.detach();
    brake();
    old_command = -1;
    }
void forward(){
    led1 = !led1; 
    // simulation purpose
//    r_count += 10; 
//    l_count += 10;
    Right_Forward = 1;
    Right_Backward = 0;
    Right_Enable = 1;
    Left_Forward = 1;
    Left_Backward = 0;
    Left_Enable = 1;
    wait(0.5);
    brake();
    }
void back(){
    led2 =!led2;
    // simulation purpose
//    r_count-=5;
//     l_count-=5;
    Right_Forward = 0;
    Right_Backward = 1;
    Right_Enable = 1;
    Left_Forward = 0;
    Left_Backward = 1;
    Left_Enable = 1;
    wait(0.5);
    brake();
     }
void left(){
    led3 =!led3;
    // simulation purpose
//    r_count+=10;
//    l_count+=1;
    Right_Forward = 1;
    Right_Backward = 0;
    Right_Enable = 1;
    Left_Forward = 1;
    Left_Backward = 1;
    Left_Enable = 1; 
    wait(0.5);
    brake();
    }
void right(){
    led4 =!led4;
//    r_count+=1;
//    l_count+=10;
    Right_Forward = 1;
    Right_Backward = 1;
    Right_Enable = 1;
    Left_Forward = 1;
    Left_Backward = 0;
    Left_Enable = 1;
    wait(0.5);
    brake();
    }

// send signal to ROS to process msgs in queue
void spin(){nh.spinOnce();}

//void test_left(){
//    // PTA5 for simulating left encoder
//    Simulate_left = 1;
//    wait(1);
//    Simulate_left = 0;
//}
//void test_right(){
//    // PTA4 for simulating right encoder
//    Simulate_right = 1;
//    wait(1);
//    Simulate_right = 0;
//}


int main()
{
    brake();
    reset_odo();
    right_encoder.fall(right_slit);
    left_encoder.fall(left_slit);
    
    nh.initNode();
    nh.advertise(encoder_topic);
    nh.subscribe(velocity);
    ticker_odmn.attach_us(&getEncoderTicks,549000);
    ticker_spin.attach_us(&spin,1000);
    
//     simulate encoder
//    ticker_test_left.attach_us(&test_left,1000000);
//    ticker_test_right.attach_us(&test_right,2000000);

    
    while (1) {
        if (command != old_command){
        switch (command) {
            // stop
            case 0:
                stop();
                old_command = 0;
                break;
            // move forward
            case 1:
                stop();
                ticker_movement.attach_us(&forward,1000000);
                old_command = 1;
                flag = 1;
                break;
            // move back
            case 2:
                stop();
                ticker_movement.attach_us(&back,1000000);
                old_command = 2;
                flag = -1;
                break;
            //turn left
            case 3:
                stop();
                ticker_movement.attach_us(&left,1000000);
                old_command = 3;
                break;
            //turn right
            case 4:
                stop();
                ticker_movement.attach_us(&right,1000000);
                old_command = 4;
                break;
            default:
                stop();
                break;
        }
        }
    }
}
#endif