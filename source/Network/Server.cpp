#include "Server.h"
#include "Handler/LoginHandler.h"
#include "Handler/WorldHandler.h"


typedef void(*sn_event)(void *);

void Server::Start(short port, CDatabase* db)
{
	Log("Starting server on port " + to_string(port) + "");
	SNServer::Start();
	connection_count = 1;
	database = db;

	SetOnConnectedEvent2(&Server::OnConnected);
	//SetOnConnectedEvent(OnConnected);
	//SetOnDisconnectedEvent(OnDisconnected);
	//SetOnMessageSentEvent(OnMessageSent);
	//SetOnMessageRecvEvent(OnMessageRecv);

	GenerateMasterKey();
	SNServer::Start();
}

void Server::OnConnected(void* p)
{
	int id = connection_count++;

	auto se = new Session();
	auto nc = (ns_connection*)p;
	nc->user_data = move(Connections[nc] = se);

	Log("new connection. cid = " + to_string(id));
	memcpy(se->account.m_dwMasterKey, m_dwMasterKey, sizeof(DWORD)*CHECK_KEY_NUM);

	Connections[nc]->conn_type = DEPLOY_TYPE;
	Connections[nc]->account.db = database;
	Connections[nc]->server = ServerRef;
	Connections[nc]->db = database;
	Connections[nc]->conn = nc;
	Connections[nc]->id = id;
}

void Server::OnDisconnected(void* p)
{
	auto nc = (ns_connection*)p;
	auto s = std::move(Connections[nc]);
	Connections.erase(s);
	
	size_t count = Connections.size();
	std::string str(std::string(" - Connections: "));
	setTitle(str.append(std::to_string(count)));

	std::string er("Disconnection by Id " + std::to_string(s->id));
}

void Server::OnMessageRecv(struct ns_connection *nc, struct iobuf *io)
{
	auto se = (Session*)nc->user_data;

	char* data_ = new char[MAX_RECEIVE_SIZE];
	size_t totalSize = 0;
	while (totalSize < io->len){
		std::vector<char> data;
		short curSize = Convert::ToShort(&data_[totalSize]);
		for (int i = 0; i < curSize; i++){
			data.push_back(data_[i + totalSize]);
		}
		totalSize += curSize;
		Process(Packet(data, curSize), DEPLOY_TYPE, se);
	}

	delete data_;
}

void Server::OnMessageSent(struct ns_connection *nc, struct iobuf *io)
{

}

void Server::Process(Packet p, int conn_type, Session* se)
{
	switch (conn_type) {
	case 0:
		LoginHandler::handle(se, p);
		break;
	case 1:
		WorldHandler::handle(se, p);
		break;
	case 2:
		break;
	case 3:
		break;
	}
}

int Server::setPort(short _port)
{
	return Port = _port;
}

void Server::SetTitle(int count)
{
	setTitle(std::string(" - Connections: " + std::to_string(count)).c_str());
}

void Server::GenerateMasterKey()
{
	for (int i = 0; i < CHECK_KEY_NUM; i++) {
		DWORD dwR1 = ::rand();
		m_dwMasterKey[i] = (dwR1 << 16) + ::rand();
	}
}

void Server::setRef(void* serverRef)
{
	ServerRef = serverRef;
}