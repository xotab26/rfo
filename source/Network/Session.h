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

	Session(asio::io_service& io_service)
		: socket_(io_service) {
		active = false;
	}

	Session(tcp::socket& socket)
		: socket_(std::move(socket)) {
		active = false;
	}

	~Session() {
	}

	void start(){
		active = true;
		start_read();
	}

	tcp::socket& socket() {
		return socket_;
	}

	size_t send_data(BYTE* _type, void* data, WORD len);
	size_t send_data_v2(BYTE* _type, void* data, WORD len);
	void DisposeObject() { delete this; }

	CDatabase* db;
	Account account;
	void* server;

	int id;
	bool active;
	int connection_type;

private:
	void start_read();
	void Process(Packet p, int conn_type);
	void call_error(std::error_code ec);
	void disconnect(std::error_code ec);

	tcp::socket socket_;
};