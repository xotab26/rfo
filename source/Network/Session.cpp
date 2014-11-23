#include "Server.h"
#include "Session.h"
#include "Handler/LoginHandler.h"
#include "Handler/WorldHandler.h"


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

size_t Session::send_data_v2(BYTE* _type, void* data, WORD len) {
	char buffer[MAX_RECEIVE_SIZE];
	char* szMsg = (char*)data;

	_MSG_HEADERv2 header;
	header.m_wSize = len;
	header.m_wPsize = len + MSG_HEADER_v2_SIZE;
	header.m_wPsize += MSG_FOOTER_SIZE;
	*(WORD*)header.m_byType = *(WORD*)_type;

	memcpy(&buffer[0], &header, MSG_HEADER_v2_SIZE);
	memcpy(&buffer[MSG_HEADER_v2_SIZE], szMsg, len);

	_MSG_FOOTER ft; ft._c = 0; ft._t = 4;
	memcpy(&buffer[len + MSG_HEADER_v2_SIZE], &ft, MSG_FOOTER_SIZE);

	return asio::write(socket_, asio::buffer(buffer, header.m_wPsize));
}

void Session::start_read() {
	if (!active) return;

	char* data_;
	data_ = new char[MAX_RECEIVE_SIZE];
	socket_.async_receive(asio::buffer(data_, MAX_RECEIVE_SIZE), [this, data_](std::error_code ec, size_t len) {
		if (!ec) {
			size_t totalSize = 0;
			while (totalSize < len){
				std::vector<char> data;
				short curSize = Convert::ToShort(&data_[totalSize]);
				for (int i = 0; i < curSize; i++){
					data.push_back(data_[i + totalSize]);
				}
				totalSize += curSize;
				Process(Packet(data, curSize), connection_type);
			}

			start_read();
		}
		else call_error(ec);
	});
}

void Session::call_error(std::error_code ec){
	switch (ec.value()){
	case 2://end of file
		Log("End of file. cid: " + std::to_string(id));
		break;
	default:
		disconnect(ec);
	}
}

void Session::Process(Packet p, int conn_type) {
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

void Session::disconnect(std::error_code ec){
	Server* srv = (Server*)server;

	auto s = std::move(srv->Connections[id]);
	srv->Connections.erase(id);

	size_t count = srv->Connections.size();
	std::string str(std::string(" - Connections: "));
	setTitle(str.append(std::to_string(count)));

	std::string er(". " + ec.message() + " | Connection Id " + std::to_string(id));
	if (Config::DEBUG) Print::Error(ec.value(), er.c_str());

	active = false;
}