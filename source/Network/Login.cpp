#include "Login.h"
#include "TcpConnection.h"

void login::account(void* ptr, short id, std::vector<char> data){
	auto conn = (connection*) &ptr;

	switch(id)
	{
	case login_account_request_cllo:
		break;
	case world_list_request_cllo:
		break;
	case select_world_request_cllo:
		break;
	case crypty_key_request_cllo:
		_crypty_key_inform_locl Send;
		conn->XorPlus = Send.byPlus = ::rand() % 5;
		conn->XorKey = Send.wKey = ::rand() % 1024;

		byte byType[msg_header_num] = {account_msg, crypty_key_inform_locl};
		conn->SendMsg(byType, &Send);

		conn->XorPlus += 1;
		conn->XorKey +=3;
		break;
	}
}