#pragma once

#include "connection.h"

typedef std::pair<uint, connection::pointer> Connection_;
typedef std::map<uint, connection::pointer> Connections_;

class TcpServer
{
public:
	TcpServer(const char *name, ushort port, boost::asio::io_service& io_service) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)){
		Name = name;
		Port = port;
		connCount = 0;
		isRunning = false;
	}

	~TcpServer(){ }

	void start();
	void stop();
	void accept();

	Connections_ Connections;

	int Port;
	const char *Name;
	const char *Address;
	bool isRunning;	
private:
	uint connCount;
	tcp::endpoint endpoint;

	void TcpServer::start_accept(){
		connection::pointer new_connection = connection::create(acceptor_.get_io_service());
		acceptor_.async_accept(new_connection->socket(), boost::bind(&TcpServer::handle_accept, this, new_connection, boost::asio::placeholders::error));
	}

	void handle_accept(connection::pointer new_connection, const boost::system::error_code& error){
		if (!error){
			new_connection->id = connCount++;
			new_connection->start();

			printf("New connection from %s\n", new_connection->address());
			Connections.insert(Connection_(new_connection->id, new_connection));

			start_accept();
		}
	}

	tcp::acceptor acceptor_;
};