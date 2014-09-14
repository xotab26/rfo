#pragma once

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

typedef unsigned int uint;
typedef unsigned short ushort;

using boost::asio::ip::tcp;

typedef tcp::socket b_socket;

static int PROTOCOL_TYPE;

enum {
	max_id_len = 16,
	max_pw_len = 16,
	CHECK_KEY_NUM = 18,
	MAX_WORLD_PER_GLOBAL = 1,
	MAX_RECEIVE_SIZE = 4096,
};

enum CONNECTION_TYPE{
	login = 0,
	world = 1,
	zone = 2
};

struct pktHeader {
	short len;
	short kind;
	short id;
};