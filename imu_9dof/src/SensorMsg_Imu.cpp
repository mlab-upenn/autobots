/*
 * Rosinterface.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: srinivasan
 */

#include "SensorMsg_Imu.h"
#include <mutex>
#include <thread>

/*Constructor*/
SensorMsg_Imu::SensorMsg_Imu() {

	imu_msg.header.frame_id = "base_stabilized";
	imu_msg.orientation.x = 0.0;
	imu_msg.orientation.y = 0.0;
	imu_msg.orientation.z = 0.0;
	imu_msg.orientation.w = 0.0;

	imu_msg.angular_velocity.x = 0.0;
	imu_msg.angular_velocity.y = 0.0;
	imu_msg.angular_velocity.z = 0.0;

	imu_msg.linear_acceleration.x = 0.0;
	imu_msg.linear_acceleration.y = 0.0;
	imu_msg.linear_acceleration.z = 0.0;
	imu_msg.header.seq = 0;
	imu_msg.header.stamp = ros::Time::now();
}

/*Destructor*/
SensorMsg_Imu::~SensorMsg_Imu() {
}

/*Get the latest message*/
void SensorMsg_Imu::Sync_Data(Imu_Parser& parser){
	bool flag = false;
	while (!flag)
		parser.Publish_All(&Acclr, &Gyro, &Mgnt, &flag);
}

/*Return the imu message*/
sensor_msgs::Imu SensorMsg_Imu::Get_Data()
{	
	imu_msg.angular_velocity.x = Gyro.x;
	imu_msg.angular_velocity.y = Gyro.y;
	imu_msg.angular_velocity.z = Gyro.z;

	imu_msg.linear_acceleration.x = Acclr.x;
	imu_msg.linear_acceleration.y = Acclr.y;
	imu_msg.linear_acceleration.z = Acclr.z;
	
	imu_msg.header.seq   = Seq_count++;
	imu_msg.header.stamp = ros::Time::now();
	
	std::cout << imu_msg.linear_acceleration.x << " " << imu_msg.linear_acceleration.y << " " <<imu_msg.linear_acceleration.z << std::endl;
	return imu_msg;

}
