#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

typedef tcp::socket b_socket;

const int max_id_len = 16;
const int max_pw_len = 16;
const int CHECK_KEY_NUM = 18;
const int MAX_WORLD_PER_GLOBAL = 1;