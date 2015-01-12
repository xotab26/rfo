#pragma once

#include "BaseHandler.h"
#include "../Protocol/zone_2232.h"


class WorldHandler : public BaseHandler {
public:
	static void handle(session nc, Packet p) {
		auto a = getAccount(nc);
		switch (p.kind) {
		case system_msg:
			_system_msg(nc, p, a);
			break;

		case chat_msg:
			_chat_msg(nc, p, a);
			break;

		case init_msg:
			_init_msg(nc, p, a);
			break;
		}
	}

private:
	static void _system_msg(session nc, Packet p, Account* a) {
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

	static void _init_msg(session nc, Packet p, Account* a) {
		int id = p.id;
		switch (id)
		{
		case base_download_request_clwr:
			_base_download_result_wrcl_(nc, a);
			break;

		case inven_download_request_clwr:
			_inven_download_result_wrcl_(nc, a);
			break;

		case cum_download_request_clwr:
			_cum_download_result_wrcl_(nc, a);
			break;

		case force_download_request_clwr:
			_force_download_result_wrcl_(nc, a);
			break;

		case quest_download_request_clwr:
			_quest_download_result_wrcl_(nc, a);
			break;
		}
	}

	static void _chat_msg(session nc, Packet p, Account* a) {
		int id = p.id;
		if (a->Accepted)
		{
			switch (id)
			{
			case chat_map_recv_yesorno_clwr:
				//_chat_map_recv_yesorno_clwr_(nc, p, a);
				break;
			}
		}
	}

#pragma region system_msg
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
			send.byCharNum = (char)a->CharNum;
			for (size_t i = 0; i < MAX_CHAR_PER_WORLDUSER; i++) {
				memcpy(&send.RegedList[i], &a->character[i].m_pAvatar.dbAvatar, sizeof(_REGED_AVATOR_DB));
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
		//auto pRecv = (_uilock_init_request_clwr*)p.buf;
		auto pRecv2 = (_uilock_fg_auth_req_clwr*)p.buf;
		
		if (strcmp(pRecv2->szPW, "test")){

		}

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

		a->CharIndex = pRecv->bySlotIndex;
		a->m_pAvatar = &a->character[a->CharIndex].m_pAvatar;

		_sel_char_result_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;
		send.bySlotIndex = pRecv->bySlotIndex;
		send.dwDalant = a->character[(int)pRecv->bySlotIndex].m_pAvatar.dbAvatar.m_dwDalant;
		send.dwGold = a->character[(int)pRecv->bySlotIndex].m_pAvatar.dbAvatar.m_dwGold;
		send.dwWorldSerial = 0;

		BYTE byType[msg_header_num] = { system_msg, sel_char_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}
#pragma endregion

#pragma region chat_msg
#pragma endregion

#pragma region init_msg
	static void _base_download_result_wrcl_(session nc, Account* a){
		auto m_pAvatar = &a->character[a->CharIndex].m_pAvatar;
		auto dbAvatar = a->character[a->CharIndex].raw_data_row;

		_base_download_result_wrcl Send;
		Send.byRetCode = RET_CODE_SUCCESS;
		Send.wZoneIndex = 0;//(WORD)g_Main.m_nWorldID;
		Send.dwExpRate = 0; //TODO: HARDCODED
		memcpy(Send.wClassHistory, m_pAvatar->dbAvatar.m_zClassHistory, sizeof(short) * 3);
		Send.wHP = (WORD)m_pAvatar->dbAvatar.m_dwHP;
		Send.wFP = (WORD)m_pAvatar->dbAvatar.m_dwFP;
		Send.wSP = (WORD)m_pAvatar->dbAvatar.m_dwSP;
		Send.dPvpPoint = m_pAvatar->dbPvpOrderView.dPvpPoint;
		Send.dPvpCashBag = m_pAvatar->dbPvpOrderView.dPvpCash;
		Send.dPvpTempCash = m_pAvatar->dbPvpOrderView.dPvpTempCash;
		Send.dwPvpRank = 1; //TODO: HARDCODED (need to make a pvp rank calculation)
		Send.byPvpClass = m_pAvatar->m_byPvpGrade;
		Send.byPlusKey = a->CryptPlus;
		Send.wXorKey = a->CryptKey;
		Send.wMaxHP = (WORD)atoi(dbAvatar["max_hp"].c_str());
		Send.wMaxFP = (WORD)atoi(dbAvatar["max_fp"].c_str());
		Send.wMaxSP = (WORD)atoi(dbAvatar["max_sp"].c_str());
		Send.wMapIndex = (WORD)m_pAvatar->dbAvatar.m_byMapCode;
		memcpy(Send.fPos, m_pAvatar->dbAvatar.m_fStartPos, sizeof(float) * 3);

		for (int i = 0; i < equip_fix_num; i++)
		{
			Send.EquipList[i].sTableCode = i;
			Send.EquipList[i].wItemIndex = m_pAvatar->dbAvatar.m_EquipKey[i].zItemIndex;
			Send.EquipList[i].dwUptInfo = m_pAvatar->dbAvatar.m_dwFixEquipLv[i];
			Send.EquipList[i].byCsMethod = m_pAvatar->dbAvatar.m_byCsMethod[i];
			Send.EquipList[i].dwT = m_pAvatar->dbAvatar.m_dwET[i];
		}

		for (int i = 0; i < embellish_fix_num; i++)
		{
			Send.EmbellishList[i].sTableCode = m_pAvatar->dbEquip.m_EmbellishList[i].Key.byTableCode;
			Send.EmbellishList[i].wItemIndex = m_pAvatar->dbEquip.m_EmbellishList[i].Key.wItemIndex;
			Send.EmbellishList[i].wNum = m_pAvatar->dbEquip.m_EmbellishList[i].wAmount;
			Send.EmbellishList[i].sClientIndex = m_pAvatar->dbEquip.m_EmbellishList[i].Key.bySlotIndex;
			Send.EmbellishList[i].byCsMethod = m_pAvatar->dbEquip.m_EmbellishList[i].byCsMethod;
			Send.EmbellishList[i].dwT = m_pAvatar->dbEquip.m_EmbellishList[i].dwT;
		}

		Send.byHolyMasterState = 0; //TODO: HARDCODED (need to make a race hierarchy)
		Send.dwGuildSerial = 0xffffffff; //TODO: HARDCODED (need to make guild system)
		Send.byGuildGrade = 0x0; //TODO: HARDCODED (need to make guild system)
		Send.byEffectValue[0] = 0x0;
		Send.byEffectValue[1] = 0x0;
		Send.byUseTrunkSlotNum = m_pAvatar->dbTrunk.bySlotNum;
		Send.wMaxDP = 150;//TODO: HARDCODED
		Send.wDP = 150;//TODO: HARDCODED
		Send.byHonorGuildRank = 0x0; //TODO: HARDCODED (need to make guild system)

		BYTE byType[msg_header_num] = { init_msg, base_download_result_wrcl };
		nc->send_data_v2(byType, &Send, Send.size());
	}

	static void _inven_download_result_wrcl_(session nc, Account* a){
		_inven_download_result_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;
		send.bySlotNum = 0;//TODO: HARDCODED
		send.byBagNum = a->m_pAvatar->dbAvatar.m_byBagNum;
		for (int i = 0; i < 100; i++)
		{
			send.ItemSlotInfo[i].byTableCode = a->m_pAvatar->dbInven.m_List[i].Key.byTableCode;
			send.ItemSlotInfo[i].sClientIndex = a->m_pAvatar->dbInven.m_List[i].Key.bySlotIndex;
			send.ItemSlotInfo[i].wItemIndex = a->m_pAvatar->dbInven.m_List[i].Key.wItemIndex;
			send.ItemSlotInfo[i].dwUptInfo = a->m_pAvatar->dbInven.m_List[i].dwUpt;
			send.ItemSlotInfo[i].dwDurPoint = a->m_pAvatar->dbInven.m_List[i].dwDur;
			send.ItemSlotInfo[i].byCsMethod = a->m_pAvatar->dbInven.m_List[i].byCsMethod;
			send.ItemSlotInfo[i].dwT = a->m_pAvatar->dbInven.m_List[i].dwT;
		}

		BYTE byType[msg_header_num] = { init_msg, inven_download_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());//TODO: returns incorrect size;
	}

	static void _cum_download_result_wrcl_(session nc, Account* a){
		_cum_download_result_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;
		send.Stat = a->m_pAvatar->dbStat;
		send.byLeftCuttingResNum = 0;
		for (int i = 0; i < 20; i++)
		{
			send.wleftResList[i] = 0;
		}

		BYTE byType[msg_header_num] = { init_msg, cum_download_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _force_download_result_wrcl_(session nc, Account* a){
		_force_download_result_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;
		send.bySlotNum = 0;//TODO: HARDCODED
		for (int i = 0; i < 88; i++)
		{
			send.ItemSlotInfo[i].dwCum = a->m_pAvatar->dbForce.m_List[i].Key.dwKey;
			send.ItemSlotInfo[i].wItemIndex = (WORD)i;
		}

		BYTE byType[msg_header_num] = { init_msg, force_download_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}

	static void _quest_download_result_wrcl_(session nc, Account* a){
		_quest_download_result_wrcl send;
		send.byRetCode = RET_CODE_SUCCESS;
		// TODO: HARDCODED
		send.bySlotNum = 0;
		for (int i = 0; i < 30; i++)
		{
			send.SlotInfo[i].byDBSlotIndex = i;
			send.SlotInfo[i].cont = a->m_pAvatar->dbQuest.m_List[i];
		}

		BYTE byType[msg_header_num] = { init_msg, quest_download_result_wrcl };
		nc->send_data_v2(byType, &send, send.size());
	}
#pragma endregion
};