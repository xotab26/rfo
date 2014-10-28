#pragma once

#include "Protocol.h"

using asio::ip::tcp;


class Session {
public:
	Session(tcp::socket& socket, int conn_type)	
		: socket_(std::move(socket)) {	
		connection_type = conn_type;
		do_read();
	}

	size_t send_data(BYTE* _type, void* data, WORD len) {
		char buffer[MAX_RECEIVE_SIZE];
		char* szMsg = (char*) data;

		_MSG_HEADER header;
		header.m_wSize = len + MSG_HEADER_SIZE;
		*(WORD*) header.m_byType = *(WORD*) _type;

		memcpy(&buffer[0], &header, MSG_HEADER_SIZE);
		memcpy(&buffer[MSG_HEADER_SIZE], szMsg, len);

		return asio::write(socket_, asio::buffer(buffer, header.m_wSize));
	}

	void* user_data;
	void* server;

	int id;
	int connection_type;
private:
	void Process(void* con, Packet p, int conn_type);

	void do_read();

	tcp::socket socket_;
};