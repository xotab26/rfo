#pragma once

#include "Protocol/protocol.h"
#include "TcpConnection.h"

class login {
public:

	static void command(void* cn, pktHeader header, std::vector<char> data)
	{
		//auto conn = (connection*) cn;

		switch (header.kind)
		{
		case 0:
			break;
		case 1:
			break;
		case 21://account
			break;
		}
	}
private:

};