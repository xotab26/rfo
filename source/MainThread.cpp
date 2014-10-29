#include "Network/Server.h"
#include "ThreadManager.cpp"
#include <exception>
#include <iostream>


byte dwWorldNum;
std::map<int, _WORLD_DATA> g_WorldData;

std::map<int, Server*> servers;
ThreadManager TManager;

const char* world_name;

bool running;

int server_index = 0;

asio::io_service* io_service;

void run_server(int i, int port, int deploy_type) {
	auto srv = Server(io_service[i], port);	
	servers[i] = std::move(&srv);
	servers[i]->Address = Config::LoginIP.c_str();
	servers[i]->DEPLOY_TYPE = deploy_type;
	servers[i]->start(i);
}

int server_thread(int id, int port, int deploy_type) {
	TManager.create(std::thread([id, port, deploy_type] {
		run_server(id, port, deploy_type);
	}));
	return id;
}

void create_world(char* worldName){
	int id = server_thread(server_index++, atoi(Config::WorldPort.c_str()), 1);
	Server* srv = servers[id];

	_WORLD_DATA worldData;
	g_WorldData[dwWorldNum] = worldData;
	g_WorldData[dwWorldNum].OpenWorld(0, atoi(Config::WorldPort.c_str()));
	g_WorldData[dwWorldNum].SetWorld(worldName, 0, true, id);
	srv->WorldData = &g_WorldData[dwWorldNum];
	srv->WorldNum = id;
	dwWorldNum++;
}

int getType(const char* v) {
	if (std::string(v) == "login") return 0;
	if (std::string(v) == "world") return 1;
	if (std::string(v) == "zone") return 2;
	return -1;
}

int main(int argc, char* argv[])
{
	Log("[[[[[[[[[[Developed By Suspicioso]]]]]]]]]]\n");
	setTitle(std::string(" - Connections: 0").c_str());

	TManager.start();
	dwWorldNum = 0;

	io_service = new asio::io_service[TManager.max_threads];

	auto cfg = Config::ReadCfg();
	world_name = cfg["World"]["WorldName"].c_str();
	
	try{
		if (argc > 1){
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
				server_thread(server_index++, atoi(Config::ZonePort.c_str()), 2);
				create_world("RFTest01");
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