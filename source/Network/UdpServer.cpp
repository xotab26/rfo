#include "UdpServer.h"


std::map<int, CAccount> UdpServer::Connections;
struct ns_mgr UdpServer::mgr;
int UdpServer::SERVER_INDEX;