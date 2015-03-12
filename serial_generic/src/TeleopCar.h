

#include <iostream>
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <signal.h>

class TeleopCar
{
public:
	TeleopCar();
	void trasmitMessage(char c);
private:
	ros::NodeHandle nh_;
	std_msgs::Int8 velocity;
	ros::Publisher twist_pub_;

	const char KEYCODE_R 		= 0x43;
	const char KEYCODE_L 		= 0x44;
	const char KEYCODE_F 		= 0x41;
	const char KEYCODE_B 		= 0x42;
	const char KEYCODE_SPACE	= 0x20;
};

