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

		case reged_char_result_zone:
			EnterWorldRequestZone(nc, p);
			break;
		}
	}

	static void EnterWorldRequestZone(session nc, Packet p) {
		_enter_world_request_zone* pRecv = (_enter_world_request_zone*)p.buf;
		Account* a = getAccount(nc);		
		a->Load(pRecv->dwAccountSerial);

		_enter_world_result_zone send;
		send.byResult = RET_CODE_SUCCESS;
		send.byUserGrade = 0;// a->UserGrade;

		BYTE byType[msg_header_num] = { system_msg, enter_world_result_zone };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void RegedCharResultZone(session nc, Packet p) {
		Account* a = getAccount(nc);

		_reged_char_result_zone send;
		send.byRetCode = RET_CODE_SUCCESS;
		send.byCharNum = a->CharNum;


		BYTE byType[msg_header_num] = { system_msg, enter_world_result_zone };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _account_msg(session nc, Packet p) {
		//auto a = getAccount(nc);
		int id = p.id;

		if (id == 0) {

		}
	}
};