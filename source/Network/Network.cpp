#include "Network.h"
#include "../Database/Database.h"

Network::Network(const char *name, int port){
	Name = name;
	Port = port;
	connCount = 0;
	IsRunning = false;
}

Network::~Network(){
	
}

void Network::Start(){
	try
	{
		endpoint = tcp::endpoint(tcp::v4(), 10001);
		tcp::acceptor acceptor = tcp::acceptor(io_service, endpoint);
		b_socket socket(io_service);

		printf("Server running on port %s\n", Port);

		while(IsRunning){
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			
			Connection conn(io_service);
			conn.id = connCount++;
			conn.socket = socket;

			tcp::endpoint remote_ep = socket.remote_endpoint();
			boost::asio::ip::address remote_ad = remote_ep.address();
			conn.address = remote_ad.to_string();

			Connections.insert(std::pair<uint, Connection>(conn.id, conn));

			printf("New connection from %s\n", conn.address);
		}
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void Network::Accept(){
	/*acceptor.async_accept(socket, [this](boost::system::error_code ec)
	{
		if (!ec){
			Connection conn;
			//conn.socket = socket;
		}

		Start();
	});*/
}

//TODO: May need improvement
bool Network::Send(Connection *conn, char *data){
	void* fullData = malloc(sizeof(uint16_t) + sizeof(data)); 
	//memcpy(fullData, (void*)opcode, sizeof(opcode));
	memcpy(&fullData + sizeof(uint16_t), data, sizeof(data));

	auto buf = boost::asio::buffer(fullData, sizeof(fullData));
	if(boost::asio::write(conn->socket, buf) > 0) return true;

	return false;
}