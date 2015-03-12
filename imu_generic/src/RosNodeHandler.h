#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Serial_Connect.h"
#include "Imu_Parser.h"
#include "SensorMsg_Imu.h"
#include <iostream>
#include <thread>

class RosNodeHandler
{
public:
	RosNodeHandler();
	virtual ~RosNodeHandler();
	void init();
private:
void serialCallback(const std_msgs::String::ConstPtr& msg);
	
	ros::NodeHandle n;
	ros::Publisher pub;
	ros::Subscriber sub;

};
