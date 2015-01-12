#include "Login.h"
#include "World.h"
#include "Zone.h"
#include <exception>

byte dwWorldNum = 0;
std::thread _t[10];

int getType(const char* v) {
	if (std::string(v) == "login") return 0;
	if (std::string(v) == "world") return 1;
	if (std::string(v) == "zone") return 2;
	return -1;
}

void new_server(int type_, Config* _cfg, CDatabase* db, int id, void* server){
	switch (type_){
	case 0:_t[id] = std::thread([id, db, server, _cfg] {auto srv = (LoginServer*)server; srv->start(atoi(_cfg->LoginPort), db, id);	});
		break;

	case 1:_t[id] = std::thread([id, db, server, _cfg] {auto srv = (WorldServer*)server; srv->start(_cfg, db, id);	});
		break;

	case 2:_t[id] = std::thread([id, db, server, _cfg] {auto srv = (ZoneServer*)server; srv->start(atoi(_cfg->ZonePort), db, id);	});
		break;
	}
	thread_sleep(1);
}

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	Config::DEBUG = true;
#else
	Config::DEBUG = false;
#endif

	Log("[[[[[[[[[[Developed By Tsume]]]]]]]]]]\n");
	setTitle(" - Connections: 0");
	
	Config cfg;
	CDatabase db(&cfg);

	LoginServer login;
	WorldServer world;
	ZoneServer zone;

	int s_index = 0;
	
	try{
		if (db.Connect())
		{
			if (argc > 1) {
				new_server(getType(argv[1]), &cfg, &db, s_index++, &login);

				if (argc > 2){
					new_server(getType(argv[2]), &cfg, &db, s_index++, &world);
				}

				if (argc > 3){
					new_server(getType(argv[3]), &cfg, &db, s_index++, &zone);
				}
			}
			else{
				new_server(0, &cfg, &db, s_index++, &login);
				new_server(1, &cfg, &db, s_index++, &world);
				new_server(2, &cfg, &db, s_index++, &zone);
				Config::DEBUG = true;
			}

			bool running = true;

			while (running){
				if (Config::DEBUG) Log("Pinging SQL server to keep connection alive...");
				if (!db.ConnectionAlive()){ Log("Connection to database lost!!"); break; }
				std::this_thread::sleep_for(std::chrono::minutes(2));
			}
		}
		
		Log("Stopping...");
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}