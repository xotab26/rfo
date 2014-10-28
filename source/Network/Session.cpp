#pragma once

#include "Session.h"
#include "Handler/LoginHandler.h"
#include "Handler/WorldHandler.h"


void Session::Process(void* con, Packet p, int conn_type) {
	switch (conn_type) {
	case 0:
		LoginHandler::handle(con, p);
		break;
	case 1:
		WorldHandler::handle(con, p);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void Session::do_read() {
	char* data_;
	data_ = new char[MAX_RECEIVE_SIZE];

	socket_.async_read_some(asio::buffer(data_, MAX_RECEIVE_SIZE), [this, data_](std::error_code ec, std::size_t len) {
		if (!ec) {
			char* data = new char[MAX_RECEIVE_SIZE];
			strcpy(data, &data_[0]);
			Process(this, Packet(data, len), connection_type);
		}

		do_read();
	});
}