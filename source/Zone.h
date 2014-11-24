#pragma once

#include "Network/Server.h"
#include "Common/Thread.h"

class ZoneServer {
public:
	void start(int port, CDatabase* _db, int tid){
		server = new Server(port, _db);
		server->setRef(this);
		server->DEPLOY_TYPE = 2;
		server->SERVER_INDEX = 0;
		server->start(tid);
	}

private:
	Server* server;
};