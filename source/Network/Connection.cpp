#include "connection.h"


bool connection::start(){

	return true;
}

std::string connection::address(){
	tcp::endpoint remote_ep = socket_.remote_endpoint();
	boost::asio::ip::address remote_ad = remote_ep.address();
	return remote_ad.to_string();
}