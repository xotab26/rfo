#pragma once

#include "Network/Server.h"
#include "Common/Thread.h"

class LoginServer {
public:
	void start(CDatabase* _db, int tid){
		_t = Thread(tid, std::thread([this, tid, _db] {
			Server srv(io_service, atoi(Config::LoginPort), db = _db);
			server = &srv;
			server->DEPLOY_TYPE = 0;
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