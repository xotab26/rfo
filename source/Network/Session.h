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

	size_t send_data_v2(BYTE* _type, void* data, WORD len) {
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
				int totalSize = 0;
				while (totalSize < len){
					std::vector<char> data;
					short curSize = Convert::ToShort(&data_[totalSize]);
					for (size_t i = 0; i < curSize; i++){
						data.push_back(data_[i + totalSize]);
					}
					totalSize += curSize;
					Process(this, Packet(data, curSize), connection_type);
				}

				start_read();
			}
			else call_error(ec);
		});
	}

	void call_error(std::error_code ec){
		switch (ec.value()){
		case 2://end of file
			Log("End of file. cid: " + std::to_string(id));
			break;
		default:
			disconnect(ec);
		}
	}

	void disconnect(std::error_code ec);

	tcp::socket socket_;
};