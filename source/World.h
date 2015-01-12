#pragma once

#include "Network/Server.h"
#include "Common/Thread.h"

class WorldServer {
public:
	void start(Config* cfg, CDatabase* _db, int tid){
		DWORD ipAddr = GetIPAddress(cfg->WorldIP);
		WorldData.SetWorld(cfg->WorldName, 0, true, tid);
		WorldData.OpenWorld(ipAddr, atoi(cfg->WorldPort));
		WorldNum = tid;
		dwWorldNum++;

		server = new Server();
		server->setRef(this);
		server->DEPLOY_TYPE = 1;
		server->SERVER_INDEX = 0;
		server->Start(atoi(cfg->WorldPort), _db);
	}

	unsigned long WorldNum;
	_WORLD_DATA WorldData;

private:
	Server* server;
};