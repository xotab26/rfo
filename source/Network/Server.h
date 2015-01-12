#pragma once
#include "Session.h"
#include <string>
#include <iostream>
#include <functional>

using namespace SkyNetLib::SNServer;
using namespace std;

class Server
{
public:
	void Start(short port, CDatabase* db);

	int setPort(short _port);

	void SetTitle(int count);

	void GenerateMasterKey();

	void setRef(void* serverRef);

	void Process(Packet p, int conn_type, Session* se);

	void OnConnected(void* p);	
	void OnDisconnected(void* p);	
	void OnMessageRecv(struct ns_connection *, struct iobuf *);	
	void OnMessageSent(struct ns_connection *, struct iobuf *);

	std::map<void*, Session*> Connections;
	
	bool running;
	int thread_id;
	int DEPLOY_TYPE; //0 login - 1 world - 2 zone - 3 db
	int SERVER_INDEX;
	int connection_count;
	short Port;

	DWORD m_dwMasterKey[CHECK_KEY_NUM];

	CDatabase* database;

	Config cfg;

	void* ServerRef;
};