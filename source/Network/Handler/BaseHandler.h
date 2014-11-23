#pragma once

#include "../Server.h"
#include "../Session.h"
#include "../Protocol.h"
#include "../../Account/Account.h"


class BaseHandler {
public:
	typedef Session* session;

	static Account* getAccount(session nc) { 
		return &nc->account;
	}

	static CDatabase* getDB(session nc){
		return nc->db;
	}

	static _AVATOR_DATA* getAvatar(Account* a){
		return &a->character[a->CharIndex].m_pAvatar;
	}

	static Server* getServer(session nc){
		return (Server*)nc->server;
	}
};