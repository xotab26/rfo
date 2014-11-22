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
			break;
		}
	}

private:
	static void _system_msg(session nc, Packet p) {
		auto a = getAccount(nc);
		int id = p.id;

		switch (id) {
		case enter_world_request_clzo:
			_enter_world_result_zocl_(nc, p, a);
			break;

		case reged_char_request_clwr:
			_reged_char_result_wrcl_(nc, p, a);
			break;

		case uilock_init_request_clwr:
			_uilock_fg_auth_req_wrcl_(nc, p, a);
			break;

		case uilock_fg_auth_req_clwr:
			_uilock_fg_auth_req_wrcl_(nc, p, a);
			break;

		case add_char_request_clwr:
			_add_char_result_zocl_(nc, p, a);
			break;

		case del_char_request_clwr:
			_del_char_request_clwr_(nc, p, a);
			break;

		case sel_char_request_clwr:
			_sel_char_result_wrcl_(nc, p, a);
			break;
		}
	}

#pragma region World Handlers
	static void _enter_world_result_zocl_(session nc, Packet p, Account* a) {
		auto pRecv = (_enter_world_request_clzo*)p.buf;
		a->Load(pRecv->dwAccountSerial);

		_enter_world_result_zocl send;
		send.byResult = RET_CODE_SUCCESS;
		send.byUserGrade = a->UserGrade;
		send.bySvrType = 0;

		BYTE byType[msg_header_num] = { system_msg, enter_world_result_zocl };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _reged_char_result_wrcl_(session nc, Packet p, Account* a) {
		_reged_char_result_wrcl send;
		if (a->CharNum > 0)
		{
			send.byRetCode = RET_CODE_SUCCESS;
			send.byCharNum = a->CharNum;
			for (size_t i = 0; i < MAX_CHAR_PER_WORLDUSER; i++) {
				memcpy(&send.RegedList[i], &a->character[i].avatar, sizeof(_REGED_AVATOR_DB));
			}
		}
		else
		{
			send.byRetCode = RET_CODE_SUCCESS;
			send.byCharNum = 0;
			send.iLockType[0] = 0x02;
			for (int i = 1; i < 3; i++) send.iLockType[i] = 0xffffffff;
		}

		BYTE byType[msg_header_num] = { system_msg, reged_char_result_zone };
		nc->send_data_v2(byType, &send, send.size());
		_uilock_fg_auth_req_wrcl_(nc, p, a);
	}

	static void _uilock_fg_auth_req_wrcl_(session nc, Packet p, Account* a) {
		auto pRecv = (_uilock_init_request_clwr*)p.buf;
		auto pRecv2 = (_uilock_fg_auth_req_clwr*)p.buf;

		a->UILockAuthorized = true;

		_uilock_fg_auth_req_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;

		BYTE byType[msg_header_num] = { ui_msg, uilock_fg_auth_req_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _add_char_result_zocl_(session nc, Packet p, Account* a){
		auto pRecv = (_add_char_request_clwr*)p.buf;

		_add_char_result_zocl send;
		send.byRetCode = a->createChar(pRecv->byRaceSexCode, pRecv->bySlotIndex, pRecv->dwBaseShape, pRecv->szClassCode, pRecv->wszCharName);
		send.byAddSlotIndex = pRecv->bySlotIndex;
		
		BYTE byType[msg_header_num] = { system_msg, add_char_result_zocl };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _del_char_request_clwr_(session nc, Packet p, Account* a){
		auto pRecv = (_del_char_request_clwr*)p.buf;

		_del_char_result_wrcl send;		
		if (a->character[pRecv->bySlotIndex].del()){
			send.byRetCode = RET_CODE_SUCCESS;
			send.bySlotIndex = pRecv->bySlotIndex;
			send.dwWorldSerial = a->WorldIndex;
		}
		else {
			send.byRetCode = RET_CODE_SLOT_ERR;
		}

		BYTE byType[msg_header_num] = { system_msg, del_char_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _sel_char_result_wrcl_(session nc, Packet p, Account* a){
		auto pRecv = (_sel_char_request_clwr*)p.buf;

		_sel_char_result_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;
		send.bySlotIndex = pRecv->bySlotIndex;
		send.dwDalant = a->character[pRecv->bySlotIndex].avatar.m_dwDalant;
		send.dwGold = a->character[pRecv->bySlotIndex].avatar.m_dwGold;
		send.dwWorldSerial = 0;

		BYTE byType[msg_header_num] = { system_msg, sel_char_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}
#pragma endregion
};