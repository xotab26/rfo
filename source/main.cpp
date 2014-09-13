#include "Network/TcpServer.h"
#include "Utilities/utils.h"

int main(int argc, char* argv[])
{
	try{
		WriteLine("RF Online Emulator - Version 0.1.0");
		
		boost::asio::io_service io_service;
		TcpServer loginServer("Login Server", "10001", io_service);
		loginServer.start();

		std::cin.get();
	}
	catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}