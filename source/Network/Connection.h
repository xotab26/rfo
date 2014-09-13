#pragma once

#include "Protocol/protocol.h"
#include "../Account/Account.h"

class connection
	: public boost::enable_shared_from_this<connection>
{
public:
	typedef boost::shared_ptr<connection> pointer;

	static pointer create(boost::asio::io_service& io_service){ return pointer(new connection(io_service)); }

	bool start();
	bool stop();

	tcp::socket& socket(){ return socket_; }
	
	//The remote ipv4 address
	std::string address();

	//the connection id
	uint id;

	CAccount account;

private:
	tcp::socket socket_;

	connection(boost::asio::io_service& io_service) : socket_(io_service) {	}

	void handle_write(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/)	{

	}

};

