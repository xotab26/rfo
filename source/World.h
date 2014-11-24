#pragma once

#include "Network/Server.h"
#include "Common/Thread.h"

class WorldServer {
public:
	void start(CDatabase* _db, int tid){
		_t = Thread(tid, std::thread([this, tid, _db] {
			int port = atoi(Config::WorldPort);
			DWORD ipAddr = GetIPAddress(Config::WorldIP);
			g_WorldData[dwWorldNum].SetWorld(Config::WorldName, 0, true, tid);
			g_WorldData[dwWorldNum].OpenWorld(ipAddr, port);
			WorldData = &g_WorldData[dwWorldNum];
			WorldNum = tid;
			dwWorldNum++;

			Server srv(io_service, atoi(Config::WorldPort), db = _db);
			server = &srv;
			server->DEPLOY_TYPE = 1;
			server->SERVER_INDEX = 0;
			server->start(tid);
		}));
		thread_sleep(1);
	}

	unsigned long WorldNum;
	_WORLD_DATA* WorldData;

private:
	Thread _t;
	CDatabase* db;
	Server* server;
	asio::io_service io_service;
};