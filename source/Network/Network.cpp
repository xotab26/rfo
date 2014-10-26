#include "Network.h"


std::map<int, CAccount> Network::Connections;
struct ns_mgr Network::mgr;
int Network::SERVER_INDEX;