// ROS control with keyboard over mbed
/*
  use arrow keys to control movement: 
    up---straight
    down---back
    right---turn right
    left---turn left
    other keys: stop
*/

#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_R 0x43
#define KEYCODE_L 0x44
#define KEYCODE_F 0x41
#define KEYCODE_B 0x42
#define KEYCODE_SPACE 0x20
class TeleopCar
{
public:
  TeleopCar();
  void keyLoop();

private:
  ros::NodeHandle nh_;
  std_msgs::Int8 velocity;
  ros::Publisher twist_pub_;
  
};

TeleopCar::TeleopCar()
{
  velocity.data = 0;
  twist_pub_ = nh_.advertise<std_msgs::Int8>("car_slam/cmd_vel", 1);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_car");
  TeleopCar teleop_car;

  signal(SIGINT,quit);

  teleop_car.keyLoop();
  
  return(0);
}


void TeleopCar::keyLoop()
{
  char c;
  bool dirty=false;


  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the car.");


  for(;;)
    {
      // get the next event from the keyboard
      if(read(kfd, &c, 1) < 0)
	{
	  perror("read():");
	  exit(-1);
	}

      velocity.data=0;
      ROS_DEBUG("value: 0x%02X\n", c);
  
      switch(c)
	{
	case KEYCODE_L:
	  ROS_DEBUG("LEFT");
	  velocity.data = 3;
	  dirty = true;
	  break;
	case KEYCODE_R:
	  ROS_DEBUG("RIGHT");
	  velocity.data = 4;
	  dirty = true;
	  break;
	case KEYCODE_F:
	  ROS_DEBUG("FORWARD");
	  velocity.data = 1;
	  dirty = true;
	  break;
	case KEYCODE_B:
	  ROS_DEBUG("BACK");
	  velocity.data = 2;
	  dirty = true;
	  break;

	case KEYCODE_SPACE:
	  ROS_DEBUG("STOP");
	  velocity.data = 0;
	  dirty = true;
	  break;
	}
   
    
      if(dirty ==true)
	{
	  twist_pub_.publish(velocity);
	  dirty=false;
	}
    }


  return;
}
