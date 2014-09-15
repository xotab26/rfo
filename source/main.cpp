#include "Network/TcpServer.h"
#include "Utilities/utils.h"

int main(int argc, char* argv[])
{
	try{
		WriteLine("RF Online Emulator - Version 0.1.0");

		for(int i = 0; i < argc; i++){
			if(argv[i] == "223"){
				PROTOCOL_TYPE = 1;
			}else if(argv[i] == "2232"){
				PROTOCOL_TYPE = 2;
			}else{
				PROTOCOL_TYPE = 0;
			}
		}
		
		boost::asio::io_service io_service;
		TcpServer loginServer("Login Server", "10001", C_TYPE::login, io_service);
		loginServer.start();

		std::cin.get();
	}
	catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}