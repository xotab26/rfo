#include "TcpServer.h"
#include "../Database/Database.h"


void TcpServer::start(){
	try
	{
		start_accept();
		isRunning = true;
		printf("Server running on port %s\n", Port);
	}
	catch(std::exception& e)
	{
		isRunning = false;
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

/*
//TODO: May need improvement
bool Network::send(CConnection *conn, char *data){
	void* fullData = malloc(sizeof(uint16_t) + sizeof(data)); 
	//memcpy(fullData, (void*)opcode, sizeof(opcode));
	memcpy(&fullData + sizeof(uint16_t), data, sizeof(data));

	auto buf = boost::asio::buffer(fullData, sizeof(fullData));
	//if(boost::asio::write(conn->getSocket(), buf) > 0) return true;

	return false;
}*/