#pragma once

#include "Protocol.h"
#include "../Account/Account.h"

using namespace SkyNetLib::SNServer;

class Session
{
public:
	int send_data(BYTE* _type, void* data, WORD len);

	int send_data_v2(BYTE* _type, void* data, WORD len);

	void DisposeObject() { delete this; }

	ns_conn* conn;

	CDatabase* db;
	Account account;
	void* server;

	int id;
	int conn_type;
};