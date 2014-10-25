#include <exception>
#include <iostream>
#include "Network/UdpServer.h"
#include "ThreadManager.cpp"



UdpServer login_server;
UdpServer world_server;
UdpServer zone_server;

ThreadManager t_man;

const char* world_name;

bool running;

void login_srv(){
	DEPLOY_TYPE = 0;
	login_server.Address = Config::LoginIP.c_str();
	login_server.Port = Config::LoginPort.c_str();	
	login_server.start(world_name);
}

void world_srv(){
	DEPLOY_TYPE = 1;
	world_server.Address = Config::WorldIP.c_str();
	world_server.Port = Config::WorldPort.c_str();
	world_server.start(world_name);
}

void zone_srv(){
	DEPLOY_TYPE = 2;
	zone_server.Address = Config::ZoneIP.c_str();
	zone_server.Port = Config::ZonePort.c_str();
	zone_server.start(world_name);
}

int main(int argc, char* argv[])
{
	Log("[[[[[[[[[[Developed By Suspicioso]]]]]]]]]]\n");

	t_man.start();

	auto cfg = Config::ReadCfg();
	world_name = cfg["World"]["WorldName"].c_str();
	dwWorldNum = 1;

	try{
		if (argc > 1){
			int _type = atoi(argv[0]);
			int _port = atoi(argv[1]);
			
			switch (_type){
			case 0:
				//login_server.thread_id = t_man.create(&t);
				break;
				
			case 1:
				break;
				
			case 2:
				break;
			}
		}
		else{
			if (Config::DEBUG){
				login_server.thread_id = t_man.create(login_srv);
				world_server.thread_id = t_man.create(world_srv);
				zone_server.thread_id = t_man.create(zone_srv);
			}
		}
		
		running = true;

		while (running){
			char line[256];
			std::cin.get(line, 256);

			if (std::string(line) == ""){

			}
		}

		Log("Stopping...");
	}
	catch (std::exception& e){
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}