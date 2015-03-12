/*
 * ImuParser.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: srinivasan
 */

#include "Imu_Parser.h"
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include <vector>
#include <string.h>
#include <regex>
#include <boost/regex.hpp>
#include <mutex>

using std::vector;
using std::string;
using boost::is_any_of;
using boost::token_compress_on;
using boost::algorithm::split;
using std::cout;
using std::endl;

#define BOOST_REGEX 0

Imu_Parser::Imu_Parser()
{
	new_data = false;
}

void Imu_Parser::Parse_Serial_Data(Serial_Connect& SPort) {
	
	std::string buffer;
	std::string delimStart = "B";
	std::string delimEnd  =  "E";	
	while(1)
	{

		std::mutex mtx;
		buffer = SPort.readLine_Until("\n");
		
#if BOOST_REGEX
		//Boost regex
		const boost::regex e("(?<=B)(.*?)(?=E)");
		boost::smatch match;		
		if (boost::regex_search(buffer, match, e))
		{
			mtx.lock();
			new_data = true;
			std::stringstream ss(match[1]);
			ss >> Mgnt.x>> Mgnt.y >> Mgnt.z >> Acclr.x >> Acclr.y >> Acclr.z >> Gyro.x >> Gyro.y >> Gyro.z;
			mtx.unlock();
		}
#else
		std::size_t first 		= buffer.find(delimStart);
		std::size_t last 		= buffer.find(delimEnd);
		if((first  != std::string::npos) && (last  != std::string::npos))
		{
		mtx.lock();
			new_data = true;
			std::string strNew 	= buffer.substr(first + delimStart.length(),last-first - delimStart.length());
			std::stringstream ss(strNew);
			ss >> Mgnt.x>> Mgnt.y >> Mgnt.z >> Acclr.x >> Acclr.y >> Acclr.z >> Gyro.x >> Gyro.y >> Gyro.z;
		mtx.unlock();
		}
#endif
			
	}
}

Imu_Parser::~Imu_Parser() {

}

Acclr_Data Imu_Parser::Publish_Accelerometer_Data()
{
	return Acclr;
}

Gyro_Data Imu_Parser::Publish_Gyroscope_Data()
{
	return Gyro;
}

Mgnto_Data Imu_Parser::Publish_Magnetometer_Data()
{
	return Mgnt;
}

bool Imu_Parser::isNewData()
{
	return new_data;
}
void Imu_Parser::Publish_All(Acclr_Data * A, Gyro_Data *G,  Mgnto_Data *M , bool * flag)
{
	std::mutex mtx;
	mtx.lock();
	if(new_data)
	{
		*flag = true;
		*A = Acclr;
		*G = Gyro;
		*M = Mgnt;
		new_data = false;
	}
	mtx.unlock();
}

