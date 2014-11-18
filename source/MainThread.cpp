#include "Network/Server.h"
#include "ThreadManager.cpp"
#include <exception>
#include <iostream>


byte dwWorldNum;
std::map<int, _WORLD_DATA> g_WorldData;
asio::io_service* io_service;
std::map<int, Server*> servers;
ThreadManager TManager;

bool running;
int server_index = 0;
const char* world_name;


int run_server(int id, int port, int deploy_type) {
	Server srv(io_service[id], port);
	servers[id] = std::move(&srv);
	servers[id]->DEPLOY_TYPE = deploy_type;
	servers[id]->SERVER_INDEX = 0;
	servers[id]->start(id);
	return id;
}

int server_thread(int id, int port, int deploy_type) {
	TManager.create(std::thread([id, port, deploy_type] {
		run_server(id, port, deploy_type);
	})); 
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	return id;
}

void create_world(char* worldName){
	int id = server_thread(server_index++, atoi(Config::WorldPort.c_str()), 1);
	g_WorldData[dwWorldNum].OpenWorld(0, atoi(Config::WorldPort.c_str()));
	g_WorldData[dwWorldNum].SetWorld(worldName, 0, true, id);
	servers[id]->WorldData = &g_WorldData[dwWorldNum];
	servers[id]->WorldNum = id;
	dwWorldNum++;
}

int getType(const char* v) {
	if (std::string(v) == "login") return 0;
	if (std::string(v) == "world") return 1;
	if (std::string(v) == "zone") return 2;
	return -1;
}

int main(int argc, char* argv[]) {
	Log("[[[[[[[[[[Developed By Tsume]]]]]]]]]]\n");
	setTitle(std::string(" - Connections: 0").c_str());

	TManager.start();
	dwWorldNum = 0;

	io_service = new asio::io_service[TManager.max_threads];

	auto cfg = Config::ReadCfg();
	world_name = cfg["World"]["WorldName"].c_str();
	
	try{
		if (argc > 1) {
			int _type = getType(argv[1]);
			
			switch (_type){
			case 0:
				server_thread(server_index++, atoi(Config::LoginPort.c_str()), 0);
				break;
				
			case 1:
				create_world("RFTest01");
				break;
				
			case 2:
				server_thread(server_index++, atoi(Config::ZonePort.c_str()), 2);
				break;
			}
		}
		else{
			if (Config::DEBUG) {
				server_thread(server_index++, atoi(Config::LoginPort.c_str()), 0);
				//create_world("RFTest01");
				//server_thread(server_index++, atoi(Config::ZonePort.c_str()), 2);
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
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}