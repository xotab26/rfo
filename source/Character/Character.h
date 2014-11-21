#pragma once

#include "../Database/Database.h"

class Character : public _REGED_AVATOR_DB {
public:
	Character() { }

	~Character(){ }

	bool Set(db_row row){
		memcpy(m_szAvatorName, row["nick"].c_str(), row["nick"].size());
		m_dwRecordNum = atol(row["id"].c_str());
		//m_byRaceSexCode = Convert::ToChar(row["id"].c_str())[0];
		m_bySlotIndex = Convert::ToChar(row["slot"].c_str())[0];
		memcpy(m_szClassCode, row["nick"].c_str(), row["nick"].size());
		m_byLevel = (BYTE)(Convert::ToChar(row["level"].c_str())[0]);
		m_dwDalant = (DWORD)Convert::ToInt(row["currency1"].c_str());
		m_dwGold = (DWORD)Convert::ToInt(row["currency2"].c_str());
		m_dwBaseShape = (DWORD)Convert::ToInt(row["base_shape"].c_str());
		memcpy(m_EquipKey, row["nick"].c_str(), row["nick"].size());
		memcpy(m_byEquipLv, row["nick"].c_str(), row["nick"].size());
		m_dwLastConnTime = Convert::ToChar(row["base_shape"].c_str())[0];
		
		return (CharacterRow = row).size() == 0;
	}
private:
	db_row CharacterRow;
};