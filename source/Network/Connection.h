#pragma once

#include "Protocol/protocol.h"
#include "../Account/Account.h"

class Connection
{
public:
	Connection(boost::asio::io_service io_service);
	tcp::socket socket;
	std::string address;

	unsigned int id;
	CAccount account;

private:

};

