#pragma once

#include "Session.h"
#include <string>
#include <iostream>
#include <functional>
#include <asio.hpp>

using asio::ip::tcp;

class Server {
public:
	Server(asio::io_service& io_service_, short port)
		: acceptor(io_service_, tcp::endpoint(tcp::v4(), setPort(port))) {
		io_service = &io_service_;
		running = false;		
	}

	~Server() {
		Log("Killing server with type " + std::to_string(DEPLOY_TYPE));
	}

	void start_accept() {
		Session::pointer nc = Session::create(acceptor.get_io_service());
		acceptor.async_accept(nc->socket(), std::bind(&Server::handle_accept, this, nc, std::placeholders::_1));
	}

	void handle_accept(Session::pointer session, const std::error_code& error) {
		if (!error) {
			int id = connection_count++;
			Connections[id] = session;
			Connections[id]->connection_type = DEPLOY_TYPE;
			Connections[id]->account.db = &database;
			Connections[id]->server = this;
			Connections[id]->id = id;
			Connections[id]->start();
			SetTitle((int)Connections.size());
		}
		start_accept();
	}

	void start(int threadId) {
		thread_id = threadId;
		if (running = database.Connect()){
			char* p = new char[2];
			strcpy(p = new char[2], std::to_string(Port).c_str());
			Log("Spawning server type " + std::to_string(DEPLOY_TYPE) + " on port " + p + "\n");

			start_accept();
			io_service->run();
		}
	}

	int setPort(short _port){
		return Port = _port;
	}

	void SetTitle(int count){
		setTitle(std::string(" - Connections: " + std::to_string(count)).c_str());
	}

	std::map<int, Session::pointer> Connections;

	bool running;
	int thread_id;
	int DEPLOY_TYPE; //0 login - 1 world - 2 zone - 3 db
	int SERVER_INDEX;
	int connection_count;
	short Port;

	unsigned long WorldNum;
	_WORLD_DATA* WorldData;
	
	CDatabase database;

	asio::io_service* io_service;
	tcp::acceptor acceptor;
private:
};