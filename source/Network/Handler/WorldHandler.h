#pragma once

#include "../Session.h"
#include "../Protocol.h"
#include "../../Account/Account.h"


class WorldHandler {
	typedef Session* session;
	static Account* getAccount(session nc) { return &nc->account; }
public:
	static void handle(session nc, Packet p) {
		switch (p.kind) {
		case account_msg:
			_account_msg(nc, p);
			break;
		}
	}

private:
	static void _account_msg(session nc, Packet p) {
		auto a = getAccount(nc);
		int id = p.id;

		if (id == 0) {

		}
	}
};