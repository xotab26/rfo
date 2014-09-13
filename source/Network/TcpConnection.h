#pragma once

#include "Protocol/protocol.h"
#include "../Account/Account.h"

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
	static pointer create(boost::asio::io_service& io_service){
		return pointer(new connection(io_service));
	}

	/// <summary>
	/// Starts this instance.
	/// </summary>
	/// <returns></returns>
	bool start(){
		id = -1;
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

	char data_[MAX_RECEIVE_SIZE];

	/// <summary>
	/// Initializes a new instance of the <see cref="connection"/> class.
	/// </summary>
	/// <param name="io_service">The io_service.</param>
	connection(boost::asio::io_service& io_service) : socket_(io_service) {	}

	/// <summary>
	/// Accepts the specified data.
	/// </summary>
	/// <param name="data">The data.</param>
	/// <param name="length">The length.</param>
	void accept_data(const char *data, std::size_t &length)
	{
		
	}

	/// <summary>
	/// Do_reads this instance.
	/// </summary>
	void do_read(){
		auto self(shared_from_this());
		socket_.async_receive(boost::asio::buffer(data_), [this, self](boost::system::error_code ec, std::size_t length)	{
			if (!ec && length > 0)
			{
				char len[2] = {data_[0], data_[1]};
				int size = boost::lexical_cast<int>(len);
				
				accept_data(data_, length);
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

