#include "Login.h"
#include "World.h"
#include "Zone.h"
#include <exception>


Config cfg;

byte dwWorldNum = 0;
WORLD_DATA g_WorldData;
int server_index = 0;

LoginServer login;
WorldServer world;
ZoneServer zone;

int getType(const char* v) {
	if (std::string(v) == "login") return 0;
	if (std::string(v) == "world") return 1;
	if (std::string(v) == "zone") return 2;
	return -1;
}

void new_server(int type_, CDatabase* db){
	switch (type_){
	case 0:
		login.start(db, server_index++);
		break;

	case 1:
		world.start(db, server_index++);
		break;

	case 2:
		zone.start(db, server_index++);
		break;
	}
}

int main(int argc, char* argv[]) {
#ifdef _DEBUG
	Config::DEBUG = true;
#else
	Config::DEBUG = false;
#endif

	Log("[[[[[[[[[[Developed By Tsume]]]]]]]]]]\n");
	setTitle(std::string(" - Connections: 0").c_str());

	CDatabase db;
	
	try{
		if (db.Connect())
		{
			if (argc > 1) {
				new_server(getType(argv[1]), &db);

				if (argc > 2){
					new_server(getType(argv[2]), &db);
				}

				if (argc > 3){
					new_server(getType(argv[3]), &db);
				}
			}
			else{
				new_server(0, &db);
				new_server(1, &db);
				new_server(2, &db);
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