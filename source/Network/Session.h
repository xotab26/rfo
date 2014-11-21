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

	size_t send_data(BYTE* _type, void* data, WORD len) {
		char buffer[MAX_RECEIVE_SIZE];
		char* szMsg = (char*)data;

		_MSG_HEADER header;
		header.m_wSize = len + MSG_HEADER_SIZE;
		*(WORD*)header.m_byType = *(WORD*)_type;

		memcpy(&buffer[0], &header, MSG_HEADER_SIZE);
		memcpy(&buffer[MSG_HEADER_SIZE], szMsg, len);

		return asio::write(socket_, asio::buffer(buffer, header.m_wSize));
	}

	void DisposeObject() {
		delete this;
	}

	CDatabase* db;
	Account account;
	void* server;

	int id;
	bool active;
	int connection_type;

private:
	void Process(void* con, Packet p, int conn_type);

	void start_read() {
		if (!active) return;

		char* data_;
		data_ = new char[MAX_RECEIVE_SIZE];
		socket_.async_receive(asio::buffer(data_, MAX_RECEIVE_SIZE), [this, data_](std::error_code ec, size_t len) {
			if (!ec) {
				std::vector<char> data(data_, data_ + len);
				Process(this, Packet(data, len), connection_type);
				start_read();
			}
			else call_error(ec);
		});
	}

	void call_error(std::error_code ec){
		switch (ec.value()){
		case 1:
		default:
			disconnect(ec);
		}
	}

	void disconnect(std::error_code ec);

	tcp::socket socket_;
};