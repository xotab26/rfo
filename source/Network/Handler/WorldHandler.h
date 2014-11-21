#pragma once

#include "../BaseHandler.h"
#include "../Protocol/zone_2232.h"


class WorldHandler : public BaseHandler {
public:
	static void handle(session nc, Packet p) {
		switch (p.kind) {
		case system_msg:
			_system_msg(nc, p);
			break;

		case account_msg:
			_account_msg(nc, p);
			break;
		}
	}

private:
	static void _system_msg(session nc, Packet p) {
		int id = p.id;

		switch (id) {
		case enter_world_request_zone:
			EnterWorldRequestZone(nc, p);
			break;
		}
	}

	static void EnterWorldRequestZone(session nc, Packet p) {//TODO: doesn't return the correct AccountSerial
		_enter_world_request_zone* pRecv = (_enter_world_request_zone*)p.buf;
		auto db = getDB(nc);

		auto query = std::string("SELECT * FROM Accounts WHERE id=");
		query.append(std::to_string(pRecv->dwAccountSerial));
		auto row = db->Select(query.c_str());

		_enter_world_result_zone send;
		auto a = getAccount(nc);

		BYTE byType[msg_header_num] = { system_msg, enter_world_request_zone };
		nc->send_data(byType, &send, send.size());
	}

	static void _account_msg(session nc, Packet p) {
		//auto a = getAccount(nc);
		int id = p.id;

		if (id == 0) {

		}
	}
};