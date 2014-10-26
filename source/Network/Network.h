#pragma once

#include "Protocol.h"
#include "PacketManager.h"
#include "../Account/Account.h"


class Network : PacketManager
{
public:
	Network(){
		debug = false;
		Port = "10001";
		Address = "0.0.0.0";
		SERVER_INDEX = 0;
		DEPLOY_TYPE = 0;
	}

	~Network(){
		Log("Killing server with type " + std::to_string(DEPLOY_TYPE));
	}

	void start(const char* serverName){
		_WORLD_DATA worldData;
		g_WorldData[SERVER_INDEX] = worldData;

		strcpy(WorldData()->m_szWorldName, serverName);
		WorldData()->m_dwGateIP = GetIPAddress(Address);
		WorldData()->m_wGatePort = (WORD) atoi(Port);
		WorldData()->m_nUserNum++;

		ns_mgr_init(&mgr, NULL);
		ns_bind(&mgr, getBind("tcp"), ev_handler);
		ns_bind(&mgr, getBind("udp"), ev_handler);

		WorldData()->m_bOpen = true;
		Log("Spawning server type " + std::to_string(DEPLOY_TYPE) + " (" + serverName + ") on port " + Port + "\n");

		for (;;) {
			ns_mgr_poll(&mgr, 1);
		}
		ns_mgr_free(&mgr);
	}

	static _WORLD_DATA* WorldData(){
		return &g_WorldData[SERVER_INDEX];
	}

	static void ev_handler(struct ns_connection *nc, int ev, void *p) {
		struct iobuf *io = &nc->recv_iobuf;
		(void) p;

		switch (ev) {
		case NS_ACCEPT:
			new_conn(nc);
			break;
		case NS_RECV:
			{
				Packet p(io->buf, io->len);
				iobuf_remove(io, io->len);				
				Process(nc, p);
			}
			break;
		case NS_CLOSE:
			close_conn(nc);
			break;
		}
	}

	static void new_conn(struct ns_connection *nc){
		WorldData()->m_nUserNum++;
		Connections[WorldData()->m_nUserNum] = CAccount::create(nc, WorldData()->m_nUserNum);
		nc->user_data = &Connections[WorldData()->m_nUserNum];
	}

	static void close_conn(struct ns_connection *nc){
		WorldData()->m_nUserNum--;
		auto account = PacketManager::getAccount(nc);
		Connections.erase(account->LocalId);
	}

	static std::map<int, CAccount> Connections;
	static struct ns_mgr mgr;

	int thread_id;
	static int SERVER_INDEX;
	const char* Address;
	const char* Port;
	bool debug;

private:
	char* getBind(const char* protcol){
		char* res;
		try{
			std::string s = std::string("").append(protcol).append("://0.0.0.0:").append(Port);
			res = Convert::ToChar(s);
		}catch(std::exception e){
			throw std::invalid_argument("Address & Port variables can NOT be null/empty!!");
		}
		return res;
	}
};