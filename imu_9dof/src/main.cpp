//============================================================================
// Name        : main.cpp
// Author      : Srinivasan Ekambaram
// Version     :
// Copyright   : FOr use within UPenn and myself
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Serial_Connect.h"
#include "Imu_Parser.h"

using namespace std;

int main(int argc, char **argv) {
	if(argc < 2)
		std::cout <<" please enter a valid SERIAL PORT address" << std::endl;
	else{
		std::string SerialPort = argv[1];
		try
		{
			Serial_Connect serial(SerialPort,115200);
			Imu_Parser imu_parse;
			imu_parse.Parse_Serial_Data(serial);

		} catch(boost::system::system_error& e)
		{
			cout<<"Error: "<<e.what()<<endl;
			return 1;
		}
	}

	return 0;
}
