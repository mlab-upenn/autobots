#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <thread>
#include "RosNodeHandler.h"

int main(int argc, char **argv)
{

	/*Ros Init*/
	ros::init(argc, argv, "imu_generic");

	RosNodeHandler h;
	h.init();
	/*Program init*/
	ros::spin();
	return 0;
}



