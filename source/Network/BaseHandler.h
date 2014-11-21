#pragma once

#include "Session.h"
#include "Protocol.h"
#include "../Account/Account.h"


class BaseHandler {
public:
	typedef Session* session;

	static Account* getAccount(session nc) { 
		return &nc->account;
	}

	static CDatabase* getDB(session nc){
		return nc->db;
	}
};