#pragma once

#include "Protocol.h"
#include "../Account/Account.h"

using asio::ip::tcp;


class Session : public std::enable_shared_from_this<Session>
{
public:
	typedef std::shared_ptr<Session> pointer;

	static pointer create(asio::io_service& io_service) {
		return pointer(new Session(io_service));
	}

	tcp::socket& socket() {
		return socket_;
	}

	Session(asio::io_service& io_service)
		: socket_(io_service) {
	}

	Session(tcp::socket& socket)
		: socket_(std::move(socket)) {
	}

	~Session(){	}

	void start(){
		do_read();
	}

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