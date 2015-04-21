/*
 * Euler Angles.h
 *
 *  Created on: Feb 14, 2015
 *      Author: srinivasan
 */

#ifndef EUANGLES_H_
#define EUANGLES_H_

class EuAngles {
public:
	float roll 	= 0;
	float pitch 	= 0;
	float yaw 	= 0;

	EuAngles();
	virtual ~EuAngles();
};

#endif /* EUANGLES_H_ */
