#pragma once

#include "Session.h"
#include <string>
#include <iostream>
#include <functional>
#include <asio.hpp>

using asio::ip::tcp;


class Server {
public:
	Server(short port, CDatabase* db){
		Log("Starting server on port " + std::to_string(port) + "");
		io = std::shared_ptr<asio::io_service>(new asio::io_service());
		acceptor = std::shared_ptr<tcp::acceptor>(new tcp::acceptor(*io, tcp::endpoint(tcp::v4(), setPort(port))));
		connection_count = 1;
		database = db;
		running = false;
	}

	~Server() {
		Log("Killing server with type " + std::to_string(DEPLOY_TYPE));
	}

	void start(int threadId) {
		GenerateMasterKey();
		thread_id = threadId;
		if ((running = database->IsOpen())){
			start_accept();
			io->run();
		}
	}

	void start_accept() {
		Session::pointer nc = Session::create(acceptor->get_io_service());
		acceptor->async_accept(nc->socket(), std::bind(&Server::handle_accept, this, nc, std::placeholders::_1));
	}

	void handle_accept(Session::pointer session, const std::error_code& error) {
		if (!error) {
			int id = connection_count++;
			Log("new connection. cid = " + std::to_string(id));
			memcpy(session->account.m_dwMasterKey, m_dwMasterKey, sizeof(DWORD)*CHECK_KEY_NUM);
			Connections[id] = session;
			Connections[id]->connection_type = DEPLOY_TYPE;
			Connections[id]->account.db = database;
			Connections[id]->server = ServerRef;
			Connections[id]->db = database;
			Connections[id]->id = id;
			Connections[id]->start();
			SetTitle((int)Connections.size());
		}
		start_accept();
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

	void setRef(void* serverRef){
		ServerRef = serverRef;
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
	std::shared_ptr<asio::io_service> io;
	std::shared_ptr<tcp::acceptor> acceptor;
private:
	Config cfg;
	void* ServerRef;
};