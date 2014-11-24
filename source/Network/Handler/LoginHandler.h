#pragma once

#include "BaseHandler.h"
#include "../Protocol/login_2232.h"
#include <time.h> 

class LoginHandler : public BaseHandler {
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

		if (id == crypty_key_request_cllo) {
			CryptKeyResult(nc);
		}
		else if (id == login_account_request_cllo) {
			LoginResult(nc, p);
		}
		else if (id == world_list_request_cllo) {
			if (a->Accepted) WorldListResult(nc, p);
		}
		else if (id == select_world_request_cllo) {
			SelectWorldResult(nc, p);
		}
	}

	static void CryptKeyResult(session nc) {
		auto a = getAccount(nc);

		_crypty_key_inform_locl send;
		//send.byPlus = a->CryptPlus = ::rand() % 5;
		//send.wKey = a->CryptKey = ::rand() % 254;
		send.byPlus = a->CryptPlus = 0;
		send.wKey = a->CryptKey = 228;

		BYTE byType[msg_header_num] = { account_msg, crypty_key_inform_locl };
		nc->send_data(byType, &send, send.size());

		a->CryptPlus += 1;
		a->CryptKey += 3;
	}

	static void LoginResult(session nc, Packet p) {
		auto a = getAccount(nc);

		auto pRecv = (_login_account_request_cllo*)p.buf;
		Crypt::crypt_login(pRecv->szAccountID, p.len, a->CryptPlus, a->CryptKey);

		if (!a->Verify(pRecv->szAccountID, pRecv->szPassword)) return;

		_login_account_result_locl send;
		send.bAdult = true;
		send.byBeChangedPass = 0;
		send.byRetCode = 0;
		send.dwAccountSerial = a->AccountId;
		send.dwBillingType = 1;//Premium or not

		time_t timer;
		send.dwTime = (DWORD)time(&timer);

		send.nNewAgree[0] = 0;
		send.nNewAgree[1] = 0;
		strcpy(send.uszBlockReason, a->lock_reason());

		BYTE byType[msg_header_num] = { account_msg, login_account_result_locl };
		nc->send_data(byType, &send, send.size());
	}

	static void WorldListResult(session nc, Packet p) {
		auto pRecv = (_world_list_request_cllo*)p.buf;

		DWORD ver = 0;
		if (pRecv->dwClientVersion < ver) return; //TODO: Only allow 2232(disconnect others)

		_world_list_result_locl Send;
		BYTE byRetCode = RET_CODE_SUCCESS;
		WORD wDataSize = 0;
		char szData[0x0FFF];
		int nPutPos = 0;

		if (g_WorldData.size() < 1) {
			byRetCode = RET_CODE_BEFORE_WORLD_LIST;
		}
		else {
			byRetCode = RET_CODE_SUCCESS;
			_world WorldData;
			WorldData.byNum = (BYTE)(dwWorldNum);

			for (DWORD i = 0; i < dwWorldNum; i++) {
				WorldData.bOpen = g_WorldData[i].m_bOpen;
				strcpy(WorldData.sName, g_WorldData[i].m_szWorldName);
				WorldData.byNameSize = (BYTE)(strlen(WorldData.sName) + 1);
				memcpy(&szData[nPutPos], &WorldData, WorldData.Size());
				wDataSize += WorldData.Size();
				nPutPos += WorldData.Size();
				WorldData.byNum = 0;
			}
			
			Send.byRetCode = byRetCode;
			Send.wDataSize = wDataSize + 1;

			memcpy(&Send.sListData, szData, wDataSize);
			BYTE byType[msg_header_num] = { account_msg, world_list_result_locl };
			nc->send_data(byType, &Send, Send.size());
		}
	}

	static void SelectWorldResult(session nc, Packet p) {
		auto recv = (_select_world_request_cllo*)p.buf;

		_select_world_result_locl send;
		auto a = getAccount(nc);

		auto worldData = &g_WorldData[a->WorldIndex = recv->wWorldIndex];

		if (worldData->m_bOpen) {
			send.bAllowAltTab = true;
			send.byRetCode = RET_CODE_SUCCESS;
			send.dwWorldGateIP = worldData->m_dwGateIP;
			send.wWorldGatePort = worldData->m_wGatePort;
			memcpy(send.dwWorldMasterKey, a->m_dwMasterKey, sizeof(DWORD)*CHECK_KEY_NUM);
		}
		else {
			send.byRetCode = RET_CODE_CLOSE_WORLD;
		}

		BYTE byType[msg_header_num] = { account_msg, select_world_result_locl };
		nc->send_data(byType, &send, send.size());
	}
};