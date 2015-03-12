#include "ros/ros.h"
#include "std_msgs/String.h"
#include "TeleopCar.h"
#include <boost/regex.hpp>
#include <iostream>

#define BOOST_REGEX 0

void controlCallback(const std_msgs::String::ConstPtr& msg)
{
	
	TeleopCar teleop_car;
#if BOOST_REGEX
	const boost::regex e("(?<=BMAIN)(.*?)(?=EMAIN)");
	boost::smatch match;
			
	if (boost::regex_search(std::string (msg->data.c_str()), match, e))
	{
		std::cout << "I heard: " << match[1].str() << std::endl;
		teleop_car.trasmitMessage(match[1].str()[0]);
	}
#else
	std::string delimStart = "BMAIN";
	std::string delimEnd  =  "EMAIN";	
	std::size_t first 		= msg->data.find(delimStart);
	std::size_t last 		= msg->data.find(delimEnd);
	if((first  != std::string::npos) && (last  != std::string::npos))
	{
		std::string strNew 	= msg->data.substr(first + delimStart.length(),last-first - delimStart.length());
		strNew.erase(std::remove(strNew.begin(),strNew.end(),' '),strNew.end());
		std::cout << "I heard: " << strNew[0] << std::endl;
		teleop_car.trasmitMessage(strNew[0]);
	}

#endif
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "get_control_info");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("serial_generic", 1000, controlCallback);

  ros::spin();

  return 0;
}
