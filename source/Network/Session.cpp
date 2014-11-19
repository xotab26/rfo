#include "Server.h"
#include "Session.h"
#include "Handler/LoginHandler.h"
#include "Handler/WorldHandler.h"


void Session::Process(void* con, Packet p, int conn_type) {
	switch (conn_type) {
	case 0:
		LoginHandler::handle(this, p);
		break;
	case 1:
		WorldHandler::handle(this, p);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

void Session::disconnect(std::error_code ec){
	Server* srv = (Server*)server;

	auto s = std::move(srv->Connections[id]);
	srv->Connections.erase(id);

	size_t count = srv->Connections.size();
	std::string str(std::string(" - Connections: "));
	setTitle(str.append(std::to_string(count)));

	std::string er(". " + ec.message() + " | Connection Id " + std::to_string(id));
	if (Config::DEBUG) Print::Error(ec.value(), er.c_str());

	active = false;
}