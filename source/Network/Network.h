#pragma once

#include "Connection.h"

typedef unsigned int uint;

class Network
{
public:
	Network(const char* name, int port);
	~Network();
	void Start();
	void Stop();
	void Accept();

	static bool Send(Connection *conn, char *buf);
	int Receive(Connection conn, char *buf, size_t len);
	std::map<uint, Connection> Connections;

	int Port;
	const char *Name;
	const char *Address;
	bool IsRunning;	
private:
	uint connCount;
	boost::asio::io_service io_service;
	tcp::endpoint endpoint;
};