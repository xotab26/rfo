#pragma once

#include "Protocol.h"
#include "../Account/Account.h"

using asio::ip::tcp;


class Session {
public:
	Session(tcp::socket& socket);
	~Session();

	size_t send_data(BYTE* _type, void* data, WORD len);

	Account account;
	void* server;

	int id;
	int connection_type;
private:
	void Process(void* con, Packet p, int conn_type);

	void disconnect(std::error_code ec);

	void do_read();

	tcp::socket socket_;
};