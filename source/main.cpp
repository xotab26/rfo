#include <exception>
#include <iostream>
//#include <pthread.h>
#include "Network/UdpServer.h"


extern int DEPLOY_TYPE;

UdpServer server;
UdpServer server2;

int main(int argc, char* argv[])
{
	auto cfg = Config::ReadCfg();

	dwWorldNum = 1;

	server.Address = Config::LoginIP.c_str();
	server.Port = Config::LoginPort.c_str();

	server2.Address = Config::WorldIP.c_str();
	server2.Port = Config::WorldPort.c_str();

	try{
		if(argc > 1){
			int _type = 0;
			int _port = 1;

			//server.Port = argv[_port];

			if(std::string(argv[_type]) == "debug"){
				server.debug = true;
			}
			if(std::string(argv[_type]) == "world"){
				server.Address = Config::WorldIP.c_str();
				server.Port = Config::WorldPort.c_str();
				DEPLOY_TYPE = 1;
			}
			if(std::string(argv[_type]) == "zone"){
				server.Address = Config::ZoneIP.c_str();
				server.Port = Config::ZonePort.c_str();
				DEPLOY_TYPE = 2;
			}
			if(std::string(argv[_type]) == "db"){
				server.Port = "45600";
				DEPLOY_TYPE = 3;
			}

			server.start(cfg["World"]["WorldName"].c_str());
			server2.start(cfg["World"]["WorldName"].c_str());
		}

		printf("Stopping...");
		std::cin.get();
	}
	catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}