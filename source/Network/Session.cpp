#pragma once

#include "Session.h"
#include "Handler/LoginHandler.h"
#include "Handler/WorldHandler.h"


Session::Session(tcp::socket& socket, int conn_type)
	: socket_(std::move(socket)) {
	connection_type = conn_type;
	do_read();
}

Session::~Session(){

}

void Session::Process(void* con, Packet p, int conn_type) {
	switch (conn_type) {
	case 0:
		LoginHandler::handle(this, p);
		break;
	case 1:
		WorldHandler::handle(this, p);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

size_t Session::send_data(BYTE* _type, void* data, WORD len) {
	char buffer[MAX_RECEIVE_SIZE];
	char* szMsg = (char*)data;

	_MSG_HEADER header;
	header.m_wSize = len + MSG_HEADER_SIZE;
	*(WORD*)header.m_byType = *(WORD*)_type;

	memcpy(&buffer[0], &header, MSG_HEADER_SIZE);
	memcpy(&buffer[MSG_HEADER_SIZE], szMsg, len);

	return asio::write(socket_, asio::buffer(buffer, header.m_wSize));
}

void Session::do_read() {
	char* data_;
	data_ = new char[MAX_RECEIVE_SIZE];
	socket_.async_read_some(asio::buffer(data_, MAX_RECEIVE_SIZE), [this, data_](std::error_code ec, std::size_t len) {
		if (!ec) {
			std::vector<char> data(data_, data_ + len);
			Packet p(&data[0], len);
			Process(this, p, connection_type);
		}
		do_read();
	});
}