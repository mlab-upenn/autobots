//============================================================================
// Name        : serialWrite.cpp
// Author      : Srinivasan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Serial_Connect.h"
#include "getch.h"
using namespace std;

int main(int argc, char** argv) {
	int BaudRate = 115200;


	/*Setup the serial port*/
	if(argc < 2)
	{
		std::cout <<" please enter a valid SERIAL PORT address" << std::endl;
		return 0;
	}
	if(argc == 3)
	{
		BaudRate = atoi(argv[2]);
	}
	std::string SerialPort = argv[1];
	Serial_Connect serial(SerialPort,BaudRate,500);

	char c;
	/*Loop endlessly*/
	while(1)
	{
		c = getch();

		// transmitting only space or arrow keys (escape sequences)
		if ((int) c == 27)
		{
			getch();
			c = getch();
			serial.write(string(1,c));
		}
		else if ((int) c == 32)
			serial.write(string(1,c));
	}
	return 0;
}
