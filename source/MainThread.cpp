#include <exception>
#include <iostream>
#include "Network/Network.h"
#include "ThreadManager.cpp"


Network* Server;
ThreadManager TManager;

const char* world_name;

bool running;

void login_srv(int i){
	DEPLOY_TYPE = 0;
	Server[i].Address = Config::LoginIP.c_str();
	Server[i].Port = Config::LoginPort.c_str();
	Server[i].start(world_name);
}

void world_srv(int i){
	DEPLOY_TYPE = 1;
	Server[i].Address = Config::WorldIP.c_str();
	Server[i].Port = Config::WorldPort.c_str();
	Server[i].start(world_name);
}

void zone_srv(int i){
	DEPLOY_TYPE = 2;
	Server[i].Address = Config::ZoneIP.c_str();
	Server[i].Port = Config::ZonePort.c_str();
	Server[i].start(world_name);
}

int run_thread(void(*func)(int)){
	int id = TManager.create(func);
	return Server[id].thread_id = id;
}

int main(int argc, char* argv[])
{
	Log("[[[[[[[[[[Developed By Suspicioso]]]]]]]]]]\n");

	Server = new Network[TManager.max_threads];
	TManager.start();

	auto cfg = Config::ReadCfg();
	world_name = cfg["World"]["WorldName"].c_str();
	dwWorldNum = 1;

	try{
		if (argc > 1){
			int _type = atoi(argv[0]);
			int _port = atoi(argv[1]);
			
			switch (_type){
			case 0:
				Server[0].thread_id = TManager.create(login_srv);
				break;
				
			case 1:
				Server[1].thread_id = TManager.create(world_srv);
				break;
				
			case 2:
				Server[2].thread_id = TManager.create(zone_srv);
				break;
			}
		}
		else{
			if (Config::DEBUG){
				run_thread(login_srv);
				run_thread(world_srv);
				run_thread(zone_srv);
			}
		}

		switch (TManager.max_threads){
		case 1:
			for (int i = 0; i < TManager.thread_count; i++){
				auto _thread = TManager.Threads[i];
				_thread.join();
			}
			break;
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