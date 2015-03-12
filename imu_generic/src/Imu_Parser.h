/*
 * ImuParser.h
 *
 *  Created on: Feb 14, 2015
 *      Author: srinivasan
 */

#ifndef IMU_PARSER_H_
#define IMU_PARSER_H_
#include "Serial_Connect.h"
#include "Acclr_Data.h"
#include "Gyro_Data.h"
#include "Mgnto_Data.h"

class Imu_Parser {
public:
	Imu_Parser();

	/*reads the data from the serial and saves them into their respective buffers*/
	void Parse_Serial_Data(Serial_Connect& Imu_Serial);
	void Parse_Serial_Data(std::string buffer);

	/*Publishes Respective data*/
	Acclr_Data Publish_Accelerometer_Data();
	Mgnto_Data Publish_Magnetometer_Data();
	Gyro_Data Publish_Gyroscope_Data();

	/*Publish Gyroscope , accelerometer and Magnetometer data*/
	void Publish_All();

	/*Set serial port*/
	void set_Serial_Port(Serial_Connect SPort);

	bool isNewData();

	void Publish_All(Acclr_Data * A, Gyro_Data *G,  Mgnto_Data *M, bool *flag);

	virtual ~Imu_Parser();

private:

	volatile bool new_data;
	Acclr_Data Acclr;
	Gyro_Data  Gyro;
	Mgnto_Data Mgnt;

};

#endif /* IMU_PARSER_H_ */

