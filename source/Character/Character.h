#pragma once

#include "CharacterHeaders.h"
#include "../Database/Database.h"


class Character {
public:
	Character() { }

	~Character(){ }

	bool Set(CDatabase* _db, db_row row) { //TODO: Needs to be finished
		db = _db;

		memcpy(m_pAvatar.dbAvatar.m_wszAvatorName, row["name"].c_str(), max_name_len + 1);
		m_pAvatar.dbAvatar.m_dwRecordNum = atol(row["id"].c_str());
		m_pAvatar.dbAvatar.m_byRaceSexCode = (BYTE)atoi(row["race"].c_str());
		m_pAvatar.dbAvatar.m_bySlotIndex = (BYTE)atoi(row["slot"].c_str());
		memcpy(m_pAvatar.dbAvatar.m_szClassCode, row["class"].c_str(), class_code_len + 1);
		m_pAvatar.dbAvatar.m_byLevel = (BYTE)atoi(row["level"].c_str());
		m_pAvatar.dbAvatar.m_dwHP = atoi(row["currency1"].c_str());
		m_pAvatar.dbAvatar.m_dwFP = atoi(row["currency2"].c_str());
		m_pAvatar.dbAvatar.m_dwSP = atoi(row["currency2"].c_str());
		m_pAvatar.dbAvatar.m_dwDalant = atoi(row["currency1"].c_str());
		m_pAvatar.dbAvatar.m_dwGold = atoi(row["currency2"].c_str());
		m_pAvatar.dbAvatar.m_byMapCode = atoi(row["mapCode"].c_str());
		m_pAvatar.dbAvatar.m_fStartPos[0] = (float)atof(row["posX"].c_str());
		m_pAvatar.dbAvatar.m_fStartPos[1] = (float)atof(row["posY"].c_str());
		m_pAvatar.dbAvatar.m_fStartPos[2] = (float)atof(row["posZ"].c_str());
		m_pAvatar.dbAvatar.m_dwBaseShape = atoi(row["base_shape"].c_str());
		m_pAvatar.dbAvatar.m_dwLastConnTime = atoi(row["lastConnect"].c_str());

		m_pAvatar.dbAvatar.m_EquipKey[0].LoadDBKey(atoi(row["helmet"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[1].LoadDBKey(atoi(row["upper"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[2].LoadDBKey(atoi(row["lower"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[3].LoadDBKey(atoi(row["gloves"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[4].LoadDBKey(atoi(row["boots"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[5].LoadDBKey(atoi(row["jetpack"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[6].LoadDBKey(atoi(row["weapon"].c_str()));
		m_pAvatar.dbAvatar.m_EquipKey[7].LoadDBKey(atoi(row["shield"].c_str()));

		for (int i = 0; i < equip_fix_num; i++)
		{
			//avatar.m_dwFixEquipLv[i] = dbCharacterInfo.dwEUArray[i];
		}

		return (raw_data_row = row).size() == 0;
	}

	bool del(){
		std::string sQuery("DELETE FROM Characters WHERE id='");
		sQuery.append(std::to_string(m_pAvatar.dbAvatar.m_dwRecordNum) + "';");

		if (db->Query(sQuery.c_str())){
			return true;
		}

		return false;
	}

	CDatabase* db;
	_AVATOR_DATA m_pAvatar;
	db_row raw_data_row;
};