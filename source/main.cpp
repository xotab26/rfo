#include "Network/Server.h"
#include "Common/Thread.h"
#include <exception>

byte dwWorldNum;
std::map<int, _WORLD_DATA> g_WorldData;
asio::io_service* io_service;
std::map<int, Server*> servers;
ThreadManager TManager;

CDatabase db;

int server_index = 0;
const char* world_name;

void sleep(int ms){
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int run_server(int id, int port, int deploy_type) {
	Server srv(io_service[id], port, &db);
	servers[id] = std::move(&srv);
	servers[id]->DEPLOY_TYPE = deploy_type;
	servers[id]->SERVER_INDEX = 0;
	servers[id]->start(id);
	return id;
}

int server_thread(int id, int port, int deploy_type) {
	int _id = TManager.create(std::thread([id, port, deploy_type] { run_server(id, port, deploy_type); }));
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	return _id;
}

void create_world(const char* worldName){
	int port = atoi(Config::WorldPort.c_str());
	DWORD ipAddr = GetIPAddress(Config::WorldIP.c_str());
	int id = server_thread(server_index++, port, 1);

	g_WorldData[dwWorldNum].SetWorld(worldName, 0, true, id);
	g_WorldData[dwWorldNum].OpenWorld(ipAddr, port);
	WorldServer* ws = ((WorldServer*)servers[id]);
	ws->WorldData = &g_WorldData[dwWorldNum];
	ws->WorldNum = id;
	dwWorldNum++;
}

int getType(const char* v) {
	if (std::string(v) == "login") return 0;
	if (std::string(v) == "world") return 1;
	if (std::string(v) == "zone") return 2;
	return -1;
}

void new_server(int type_){
	switch (type_){
	case 0:
		server_thread(server_index++, atoi(Config::LoginPort.c_str()), 0);
		break;

	case 1:
		create_world(Config::ReadCfg()["World"]["WorldName"].c_str());
		break;

	case 2:
		server_thread(server_index++, atoi(Config::ZonePort.c_str()), 2);
		break;
	}
}

int main(int argc, char* argv[]) {
	Log("[[[[[[[[[[Developed By Tsume]]]]]]]]]]\n");
	setTitle(std::string(" - Connections: 0").c_str());
	auto cfg = Config::ReadCfg();

	TManager.start();
	dwWorldNum = 0;
	
	io_service = new asio::io_service[TManager.max_threads];

	world_name = cfg["World"]["WorldName"].c_str();

	try{
		if (db.Connect())
		{
			if (argc > 1) {
				new_server(getType(argv[1]));

				if (argc > 2){
					new_server(getType(argv[2]));
				}

				if (argc > 3){
					new_server(getType(argv[3]));
				}
			}
			else{
				if (Config::DEBUG) {
					new_server(0);
					new_server(1);
					new_server(2);
				}
			}		

			sleep(250);
			while (servers[0]->running)
			{
				if(Config::DEBUG) Log("Pinging SQL server to keep connection alive...");

				if (!db.ConnectionAlive()){
					Log("Connection to database lost!!");
					break;
				}
				
				sleep(120000);
			}
		}

		Log("Stopping...");
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}