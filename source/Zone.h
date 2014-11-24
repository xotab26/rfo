#pragma once

#include "Network/Server.h"
#include "Common/Thread.h"

class ZoneServer {
public:
	void start(CDatabase* _db, int tid){
		_t = Thread(tid, std::thread([this, tid, _db] {
			Server srv(io_service, atoi(Config::ZonePort), db = _db);
			server = &srv;
			server->DEPLOY_TYPE = 2;
			server->SERVER_INDEX = 0;
			server->start(tid);
		}));
		thread_sleep(1);
	}

private:
	Thread _t;
	CDatabase* db;
	Server* server;
	asio::io_service io_service;
};