#include "RosNodeHandler.h"

RosNodeHandler::RosNodeHandler(){}

RosNodeHandler::~RosNodeHandler(){}

void RosNodeHandler::serialCallback(const std_msgs::String::ConstPtr& msg)
{
	Imu_Parser imu_parse;
	SensorMsg_Imu Imu;
	imu_parse.Parse_Serial_Data(std::string (msg->data.c_str()));
	if(imu_parse.isNewData())
	{
	 	Imu.Sync_Data(std::ref(imu_parse));
		pub.publish(Imu.Get_Data());
 	}
}
void RosNodeHandler::init()
{
	pub = n.advertise<sensor_msgs::Imu>("imu_topic", 1);
	sub = n.subscribe("serial_generic", 1000, &RosNodeHandler::serialCallback, this);
}
