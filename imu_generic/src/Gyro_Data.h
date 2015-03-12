/*
 * Gyro_Data.h
 *
 *  Created on: Feb 14, 2015
 *      Author: srinivasan
 */

#ifndef GYRO_DATA_H_
#define GYRO_DATA_H_

class Gyro_Data {
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Gyro_Data();
	virtual ~Gyro_Data();
};

#endif /* GYRO_DATA_H_ */
