#pragma once

#include "Session.h"
#include <string>
#include <iostream>
#include <functional>
#include <asio.hpp>

using asio::ip::tcp;


class Server {
public:
	Server(asio::io_service& io_service_, short port, CDatabase* db)
		: acceptor(io_service_, tcp::endpoint(tcp::v4(), setPort(port))) {
		Log("Starting server on port " + std::to_string(port) + "");
		io_service = &io_service_;
		connection_count = 1;
		database = db;
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
			Log("new connection. cid = " + std::to_string(id));
			memcpy(session->account.m_dwMasterKey, m_dwMasterKey, sizeof(DWORD)*CHECK_KEY_NUM);
			Connections[id] = session;
			Connections[id]->connection_type = DEPLOY_TYPE;
			Connections[id]->account.db = database;
			Connections[id]->db = database;
			Connections[id]->server = this;
			Connections[id]->id = id;
			Connections[id]->start();
			SetTitle((int)Connections.size());
		}
		start_accept();
	}

	void start(int threadId) {
		GenerateMasterKey();
		thread_id = threadId;
		if ((running = database->Connect())){
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

	void GenerateMasterKey() {
		for (int i = 0; i < CHECK_KEY_NUM; i++) {
			DWORD dwR1 = ::rand();
			m_dwMasterKey[i] = (dwR1 << 16) + ::rand();
		}
	}

	std::map<int, Session::pointer> Connections;

	bool running;
	int thread_id;
	int DEPLOY_TYPE; //0 login - 1 world - 2 zone - 3 db
	int SERVER_INDEX;
	int connection_count;
	short Port;

	DWORD m_dwMasterKey[CHECK_KEY_NUM];
	
	CDatabase* database;
	asio::io_service* io_service;
	tcp::acceptor acceptor;
private:
	Config cfg;
};