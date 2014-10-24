#pragma once

#include "TcpConnection.h"

typedef std::pair<uint, connection::pointer> Connection_;
typedef std::map<uint, connection::pointer> Connections_;

class TcpServer
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="TcpServer"/> class.
	/// </summary>
	/// <param name="name">The name.</param>
	/// <param name="port">The port.</param>
	/// <param name="io_service">The io_service.</param>
	TcpServer(const char *name, const char *port, C_TYPE server_type, boost::asio::io_service& io_service) 
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), std::atoi(port))),
		socket_(io_service)
	{
		Port = boost::lexical_cast<std::string>(port).c_str();
		Name = name;
		connCount = 1;
		isRunning = false;
		serverType = server_type;
	}

	/// <summary>
	/// Finalizes an instance of the <see cref="TcpServer"/> class.
	/// </summary>
	~TcpServer(){ }

	/// <summary>
	/// Starts this instance.
	/// </summary>
	void start(){
		try
		{
			start_accept();
			isRunning = true;
			printf("%s running\n", Name);
			run();
		}
		catch(std::exception& e)
		{
			isRunning = false;
			std::cerr << "Exception: " << e.what() << std::endl;
		}
	}

	void run(){
		try
		{
			acceptor_.get_io_service().reset();
			acceptor_.get_io_service().run();
		}
		catch(std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << std::endl;
			run();
		}
	}

	/// <summary>
	/// Stops this instance.
	/// </summary>
	void stop(){
		acceptor_.get_io_service().stop();
		printf("%s stopped running\n", Name);
		isRunning = false;
	}

	Connections_ Connections;
	C_TYPE serverType;

	const char *Name;
	std::string Port;
	std::string Address;
	bool isRunning;	

private:
	uint connCount;

	/// <summary>
	/// Starts accepting new sockets.
	/// </summary>
	void start_accept(){
		connection::pointer new_conn = connection::create(acceptor_.get_io_service(), serverType);
		acceptor_.async_accept(new_conn->socket(), boost::bind(&TcpServer::handle_accept, this, new_conn, boost::asio::placeholders::error));
	}

	/// <summary>
	/// Handles accepted sockets.
	/// </summary>
	/// <param name="new_connection">The new_connection.</param>
	/// <param name="error">The error.</param>
	void handle_accept(connection::pointer new_conn, const boost::system::error_code& error){
		if (!error){
			new_conn->id = connCount++;
			if(new_conn->start()){
				Connections.insert(Connection_(new_conn->id, new_conn));
				printf("New connection from %s\n", new_conn->address().c_str());
			}

			start_accept();
		}
	}

	tcp::acceptor acceptor_;
	tcp::socket socket_;
};