#include "ros/ros.h"
#include "std_msgs/String.h"
#include "Serial_Connect.h"
#include "Imu_Parser.h"
#include "SensorMsg_Imu.h"
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
	ros::init(argc, argv, "imu_9dof");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<sensor_msgs::Imu>("imu_9dof", 1);

	/*Program init*/
	Imu_Parser imu_parse;
	SensorMsg_Imu Imu;
	std::thread first ;  


	std::string SerialPort = argv[1];
	Serial_Connect serial(SerialPort,BaudRate,500);

	first  = std::thread(&Imu_Parser::Parse_Serial_Data,&imu_parse,std::ref(serial));  
	ros::Rate loop_rate(10);
	//	std::cout << "here " << loop_rate.cycleTime() << std::endl;
	while (ros::ok())
	{
		Imu.Sync_Data(std::ref(imu_parse));
		pub.publish(Imu.Get_Data());
		ros::spinOnce();
		//std::this_thread::sleep_for(std::chrono::milliseconds(700));
		//loop_rate.sleep();
		}

	// synchronize threads:
	first.join();                // pauses until first finishes

	return 0;
}



