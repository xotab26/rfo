#pragma once

#include "Protocol/login_client_2232.h"
#include "../Account/Account.h"

class login {
public:

	static void command(void* ptr, pktHeader header, std::vector<char> data)
	{
		switch (header.kind)
		{
		case account_msg:
			account(ptr, header.id, data);
			break;
		}
	}

	static void account(void* ptr, short id, std::vector<char> data);

private:

};