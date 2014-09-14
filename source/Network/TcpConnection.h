#pragma once

#include "Protocol/protocol.h"
#include "../Account/Account.h"
#include "Login.h"

class connection
	: public boost::enable_shared_from_this<connection>
{
public:
	typedef boost::shared_ptr<connection> pointer;
	
	/// <summary>
	/// Creates a pointer for a new instance.
	/// </summary>
	/// <param name="io_service">The io_service.</param>
	/// <returns></returns>
	static pointer create(boost::asio::io_service& io_service, CONNECTION_TYPE server_type){
		return pointer(new connection(io_service, server_type));
	}

	/// <summary>
	/// Starts this instance.
	/// </summary>
	/// <returns></returns>
	bool start(){
		do_read();
		return true;
	}

	/// <summary>
	/// Stops this instance.
	/// </summary>
	/// <returns></returns>
	bool stop();

	/// <summary>
	/// Gets the socket for this instance.
	/// </summary>
	/// <returns></returns>
	tcp::socket& socket(){ return socket_; }
	
	/// <summary>
	/// The remote ipv4 address for this instance.
	/// </summary>
	/// <returns></returns>
	/// Default constructor.
	std::string address(){
		return boost::lexical_cast<std::string>(socket_.remote_endpoint());
	}
		
	/// <summary>
	/// The identifier
	/// </summary>
	uint id;

	/// <summary>
	/// The Account
	/// </summary>
	CAccount account;

private:
	/// <summary>
	/// The socket_
	/// </summary>
	tcp::socket socket_;
	CONNECTION_TYPE connection_type;

	char data_[MAX_RECEIVE_SIZE];

	/// <summary>
	/// Initializes a new instance of the <see cref="connection"/> class.
	/// </summary>
	/// <param name="io_service">The io_service.</param>
	connection(boost::asio::io_service& io_service, CONNECTION_TYPE server_type) : socket_(io_service) { connection_type = server_type; }

	/// <summary>
	/// Accepts the specified data.
	/// </summary>
	/// <param name="data">The data.</param>
	/// <param name="length">The length.</param>
	void accept_data(pktHeader header, std::vector<char> data)
	{
		switch (connection_type)
		{
		case 0://login server
			login::command(this, header, data);
			break;
		case 1://world server
			break;
		case 2://zone server
			break;
		}
	}

	/// <summary>
	/// Do_reads this instance.
	/// </summary>
	void do_read(){
		auto self(shared_from_this());
		socket_.async_receive(boost::asio::buffer(data_), [this, self](boost::system::error_code ec, std::size_t length)	{
			if (!ec && length > 3)
			{
				pktHeader header;
				char _len[2] = {data_[0], data_[1]};
				char _len2[2] = {data_[2], data_[3]};
				short paktLen = Convert::ToShort(_len);
				short dataLen = Convert::ToShort(_len2);

				short el;
				if((paktLen - 6) == dataLen){
					header.len = dataLen;
					el = 2;
				}else{
					header.len = paktLen;
					el = 0;
				}

				char kind[2] = {data_[2+el], 0};
				header.kind = Convert::ToShort(kind);

				char id[2] = {data_[3+el], 0};
				header.id = Convert::ToShort(id);

				std::vector<char> data;
				for(int i = 0; i < length;i++){
					data.push_back(data_[i]);
				}
				
				accept_data(header, data);
			}
			do_read();
		});
	}

	/// <summary>
	/// Do_writes the specified data.
	/// </summary>
	/// <param name="data">The data.</param>
	void do_write(char *data){
		void* fullData = malloc(sizeof(uint16_t) + sizeof(data)); 
		//memcpy(fullData, (void*)opcode, sizeof(opcode));
		memcpy(&fullData + sizeof(uint16_t), data, sizeof(data));
		auto buf = boost::asio::buffer(fullData, sizeof(fullData));

		auto self(shared_from_this());
		boost::asio::async_write(socket_, buf, [this, self](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec) {
				
			}
		});
	}
};