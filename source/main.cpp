#include "Network/TcpServer.h"
#include "Utilities/utils.h"

int main(int argc, char* argv[])
{
	WriteLine("RF Online Emulator - Version 0.1.0");
	
	boost::asio::io_service io_service;
	TcpServer loginServer("Login", 10001, io_service);
	loginServer.start();

	return 0;
}