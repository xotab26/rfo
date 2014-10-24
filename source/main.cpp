#include <exception>
#include <iostream>
#include <pthread.h>
#include "Network/UdpServer.h"


int main(int argc, char* argv[])
{
	auto cfg = Config::ReadCfg();

	UdpServer server;
	UdpServer server2;

	server.Address = Config::LoginIP.c_str();
	server.Port = Config::LoginPort.c_str();

	server2.Address = Config::WorldIP.c_str();
	server2.Port = Config::WorldPort.c_str();

	try{
		for(int i = 0; i < argc; i++){
			if(argv[i] == "debug"){
				server.debug = true;
			}
			if(argv[i] == "world"){
				server.Address = Config::WorldIP.c_str();
				server.Port = Config::WorldPort.c_str();
				SERVER_DEPLOY_TYPE = 1;
			}
			if(argv[i] == "zone"){
				server.Address = Config::ZoneIP.c_str();
				server.Port = Config::ZonePort.c_str();
				SERVER_DEPLOY_TYPE = 2;
			}
			if(argv[i] == "db"){
				server.Port = "45600";
				SERVER_DEPLOY_TYPE = 3;
			}
		}
				
		server.start(cfg["World"]["WorldName"].c_str());
		server2.start(cfg["World"]["WorldName"].c_str());

		printf("Stopping...");
		std::cin.get();
	}
	catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}