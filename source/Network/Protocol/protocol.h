#pragma once

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>


typedef unsigned int uint;
typedef unsigned short ushort;

using boost::asio::ip::tcp;

typedef tcp::socket b_socket;

const int max_id_len = 16;
const int max_pw_len = 16;
const int CHECK_KEY_NUM = 18;
const int MAX_WORLD_PER_GLOBAL = 1;