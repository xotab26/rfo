#pragma once

#include "Network/Server.h"
#include "Common/Thread.h"

class LoginServer {
public:
	void start(int port, CDatabase* _db, int tid){
		server = new Server();
		server->setRef(this);
		server->DEPLOY_TYPE = 0;
		server->SERVER_INDEX = 0;
		server->Start(port, _db);
	}

private:
	Server* server;
};