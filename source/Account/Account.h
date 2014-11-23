#pragma once

#include "../Network/Protocol.h"
#include "../Database/Database.h"
#include "../Character/Character.h"


class Account{
public:
	Account(){
		Accepted = false;
		nBillInform = 0;
		CharNum = 0;
		UserGrade = 0;
		LocalId = 0;
		AccountId = 0;
		Nick = "";
		Pass = "";
		Email = "";
		WorldIndex = 0;
		CryptPlus = 0;
		CryptKey = 228;
		UILockAuthorized = false;
	}

	~Account(){ }
	
	bool Verify(char* nick, char* pass){
		std::string query("SELECT * FROM Accounts WHERE nick='" + std::string(nick) + "' AND pass='" + pass + "'");
		return Accepted = Load(query);
	}
	
	bool Load(u_int aid) {
		std::string query("SELECT * FROM Accounts WHERE id='" + std::to_string(aid) + "'");
		return Load(query);
	}

	bool Load(std::string query){
		if (db->Connect()) {
			auto res = db->Select(query.c_str());
			if (!res.empty()) {
				AccountRow = res[0];
				if (AccountRow.size() <= 1){
					return false;
				}
			}

			AccountId = (u_int)atol(AccountRow["id"].c_str());
			UserGrade = (BYTE)atoi(AccountRow["type"].c_str());
			Nick = AccountRow["nick"];
			Pass = AccountRow["pass"];
			Email = AccountRow["email"];

			query = std::string("SELECT * FROM Characters WHERE account='" + std::to_string(AccountId) + "'");
			res = db->Select(query.c_str());

			CharNum = (short)res.size();

			for (short i = 0; i < CharNum; i++) {
				character[i].Set(db, res[i]);
			}

			return true;
		}

		return false;
	}

	const char* lock_reason(){
		return AccountRow["lock_reason"].c_str();
	}

	BYTE createChar(BYTE byRaceSexCode, BYTE bySlotIndex, DWORD dwBaseShape, char* classCode, char* charName){
		if (bySlotIndex > 3) return RET_CODE_SLOT_ERR;
		if (byRaceSexCode > 5) return RET_CODE_SLOT_ERR;
		if (!UILockAuthorized) return RET_CODE_NOT_AUTHORIZED;

		BYTE byMapCode = 0;
		float fPos[3];
		switch (byRaceSexCode)
		{
		case 0: //Bellato
		case 1:
			byMapCode = 0;
			fPos[0] = -5260.735352f;
			fPos[1] = 550.996521f;
			fPos[2] = 5244.625000f;
			break;
		case 2: //Cora
		case 3:
			byMapCode = 1;
			fPos[0] = 7381.450684f;
			fPos[1] = -155.090607f;
			fPos[2] = 1410.891113f;
			break;
		case 4: //Acretia
			byMapCode = 3;
			fPos[0] = -6416.386719f;
			fPos[1] = 1060.225098f;
			fPos[2] = -5491.602051f;
			break;
		}

		auto sQuery = std::string("INSERT INTO Characters (account,name,race,slot,class,base_shape,mapCode,posX,posY,posZ) values (");
		sQuery.append(std::to_string(AccountId) + ",'");
		sQuery.append(std::string(charName) + "',");
		sQuery.append(std::to_string(byRaceSexCode) + ",");
		sQuery.append(std::to_string(bySlotIndex) + ",'");
		sQuery.append(std::string(classCode) + "',");
		sQuery.append(std::to_string(dwBaseShape) + ",");
		sQuery.append(std::to_string(byMapCode) + ",");
		sQuery.append(std::to_string(fPos[0]) + ",");
		sQuery.append(std::to_string(fPos[1]) + ",");
		sQuery.append(std::to_string(fPos[2]) + ");");

		if (db->Query(sQuery.c_str())){
			return RET_CODE_SUCCESS;
		}

		return RET_CODE_SLOT_ERR;
	}

	static Account create(u_long localId){
		Account a;
		a.CharNum = 0;
		a.nBillInform = 0;
		a.Accepted = false;
		a.LocalId = localId;
		a.AccountId = 0xFFFFFFFF;
		return a;
	}

	bool Accepted;
	int nBillInform;
	short CharNum;
	BYTE UserGrade;
	u_long LocalId;
	u_long AccountId;
	std::string Nick;
	std::string Pass;
	std::string Email;
	WORD WorldIndex;
	BYTE CryptPlus;
	WORD CryptKey;
	bool UILockAuthorized;
	Character character[3];
	_AVATOR_DATA* m_pAvatar;
	short CharIndex;

	DWORD m_dwMasterKey[CHECK_KEY_NUM];

	CDatabase* db;
private:
	db_row AccountRow;
};