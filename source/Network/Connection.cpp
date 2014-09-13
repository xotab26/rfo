#include "Connection.h"


Connection::Connection(boost::asio::io_service io_service) 
	: socket(io_service) {
	
}