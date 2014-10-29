#pragma once

#include "Session.h"

using asio::ip::tcp;


class Server {
public:
	Server(asio::io_service& io_service, short port)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), socket_(io_service) {
		connection_count = 0;
		//Port = new char[2];
		strcpy(Port = new char[2], std::to_string(port).c_str());
		Address = "0.0.0.0";
		SERVER_INDEX = 0;
		DEPLOY_TYPE = 0;
		do_accept();
	}

	~Server() {
		Log("Killing server with type " + std::to_string(DEPLOY_TYPE));
	}

	void do_accept() {
		acceptor_.async_accept(socket_, [this](std::error_code ec) {
			if (!ec) {
				int id = connection_count++;
				Connections[id] = std::make_shared<Session>(std::move(socket_));
				Connections[id]->connection_type = DEPLOY_TYPE;
				Connections[id]->server = this;
				Connections[id]->id = id;
				SetTitle((int)Connections.size());
			}

			do_accept();
		});
	}

	void setWorldName(const char* serverName) {
		strcpy(World_Data.m_szWorldName, serverName);
	}

	void start(int i) {
		thread_id = i;
		World_Data.m_dwGateIP = GetIPAddress(Address);
		World_Data.m_wGatePort = (WORD) atoi(Port);
		World_Data.m_bOpen = true;
		World_Data.m_nUserNum++;
		dwWorldNum = 0;
		
		Log("Spawning server type " + std::to_string(DEPLOY_TYPE) + " (" + World_Data.m_szWorldName + ") on port " + Port + "\n");
		socket_.get_io_service().run();
	}

	void SetTitle(int count){
		setTitle(std::string(" - Connections: " + std::to_string(count)).c_str());
	}

	std::map<int, std::shared_ptr<Session>> Connections;

	int thread_id;
	int DEPLOY_TYPE; //0 login - 1 world - 2 zone - 3 db
	int SERVER_INDEX;
	int connection_count;
	const char* Address;
	char* Port;

	unsigned long dwWorldNum;
	_WORLD_DATA World_Data;
private:
	tcp::acceptor acceptor_;
	tcp::socket socket_;
};