/*
 * SerialConnect.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: srinivasan
 */
#include "Serial_Connect.h"

Serial_Connect::Serial_Connect( std::string port, unsigned int baud_rate, unsigned long time_out)
:io(), serial(io, port), timer(serial.get_io_service()),timeout(time_out)
{
	serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
}

bool Serial_Connect::write(std::string s)
{
	boost::asio::write(serial,boost::asio::buffer(s.c_str(),s.size()));
	return true;
}

// Normal termination*
bool Serial_Connect::handler(const boost::system::error_code& error,
				size_t bytes_transferred)
{
		read_error = (error || bytes_transferred == 0);
		
	 	timer.cancel(); 		// Cancel time

}

// if exception occured or timeout occured
void Serial_Connect::time_out(const boost::system::error_code& error) {
 
	if (error) {
	return;
	}
	 
	// if timed out
	serial.cancel();
}

std::string Serial_Connect::readLine_Until(const std::string& delim)
{

	std::string s;
	boost::asio::streambuf response;
		
	// Once cancelled the connection must be reset
	serial.get_io_service().reset();
 
	// Asynchronously read until delimiter
	boost::asio::async_read_until(serial, response, delim,
					boost::bind(&Serial_Connect::handler,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
 
	// Setup a deadline time to implement our timeout.
	timer.expires_from_now(boost::posix_time::milliseconds(timeout));
	timer.async_wait(boost::bind(&Serial_Connect::time_out,
	this, boost::asio::placeholders::error));
 
	// Block till read or cancelled
	serial.get_io_service().run();
 	
	std::istream str(&response);
	std::getline(str, s);
	return s;
}

Serial_Connect::~Serial_Connect() {
	serial.close();
}

