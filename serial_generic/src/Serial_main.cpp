#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Serial_Connect.h"
#include <iostream>
#include <thread>

int main(int argc, char **argv)
{

	int BaudRate = 115200;
	if(argc < 2)
	{
		std::cout <<" please enter a valid SERIAL PORT address" << std::endl;
		return 0;
	}
	if(argc == 3)
	{
		BaudRate = atoi(argv[2]);
	}

	/*Ros Init*/
	ros::init(argc, argv, "serial_generic");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<std_msgs::String>("serial_generic", 1000);

	/*Program init*/
	std::thread first ;

	std::string SerialPort = argv[1];
	Serial_Connect serial(SerialPort,BaudRate,500);

	ros::Rate loop_rate(10);
	std::string  buffer;
	std_msgs::String msg;

	while (ros::ok())
	{
		buffer = serial.readLine_Until("\n");
		msg.data = buffer;
		std::cout << "buffer " << buffer << std::endl;
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
		//std::this_thread::sleep_for(std::chrono::milliseconds(700));
	}


	return 0;
}



