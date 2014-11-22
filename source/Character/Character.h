#pragma once

#include "CharacterHeaders.h"
#include "../Database/Database.h"

#pragma region CharacterData
#pragma pack(push, 1)
struct _EQUIPKEY
{
	short zItemIndex;

	bool IsFilled()		{ if (zItemIndex == -1) return false;	return true; }
	void SetRelease()	{ zItemIndex = -1; }
	short CovDBKey()	{ return zItemIndex; }
	void  LoadDBKey(short pl_zKey)	{ zItemIndex = pl_zKey; }
};

struct _REGED_AVATOR_DB
{
	char m_szAvatorName[max_name_len + 1];
	u_int m_dwRecordNum;
	char m_byRaceSexCode;
	char m_bySlotIndex;
	char m_szClassCode[class_code_len + 1];
	char m_byLevel;
	u_int m_dwDalant;
	u_int m_dwGold;
	u_int m_dwBaseShape;
	_EQUIPKEY m_EquipKey[equip_fix_num];
	char m_byEquipLv[equip_fix_num];
	u_int m_dwLastConnTime;

	_REGED_AVATOR_DB(){ Init(); }

	void Init(){
		memset(this, 0, sizeof(*this));
		m_bySlotIndex = 0xFF;
		m_dwRecordNum = 0xFFFFFFFF;
		for (int i = 0; i < equip_fix_num; i++)
			m_EquipKey[i].SetRelease();
	}
};

struct _REGED : public _REGED_AVATOR_DB
{
	DWORD   m_dwFixEquipLv[equip_fix_num];

	_REGED(){ init(); }

	void init()
	{
		_REGED_AVATOR_DB::Init();
		for (int i = 0; i < equip_fix_num; i++)
		{
			m_dwFixEquipLv[i] = __DF_UPT;
		}
	}

	void UpdateEquipLv(){
		for (int v = 0; v < equip_fix_num; v++)
		{
			_REGED_AVATOR_DB::m_byEquipLv[v] = ::GetItemUpgedLv(m_dwFixEquipLv[v]);
		}
	}
};

struct _AVATOR_DB_BASE : public _REGED
{
	DWORD	m_dwHP;
	DWORD	m_dwFP;
	DWORD	m_dwSP;
	double	m_dExp;
	BYTE	m_byBagNum;
	BYTE	m_byMapCode;
	short	m_zClassHistory[class_history_num];
	float	m_fStartPos[3];
	DWORD	m_dwTotalPlayMin;
	DWORD	m_dwStartPlayTime;

	_AVATOR_DB_BASE(){ Init(); }

	void Init(){
		_REGED::Init();
		for (int i = 0; i < class_history_num; i++)
			m_zClassHistory[i] = -1;
	};
};
#pragma pack(pop)
#pragma endregion


class Character {
public:
	Character() { }

	~Character(){ }

	bool Set(CDatabase* _db, db_row row) { //TODO: Needs to be finished
		db = _db;

		memcpy(avatar.m_szAvatorName, row["name"].c_str(), max_name_len + 1);
		avatar.m_dwRecordNum = atol(row["id"].c_str());
		avatar.m_byRaceSexCode = (BYTE)atoi(row["race_sex"].c_str());
		avatar.m_bySlotIndex = (BYTE)atoi(row["slot"].c_str());
		memcpy(avatar.m_szClassCode, row["class"].c_str(), class_code_len + 1);
		avatar.m_byLevel = (BYTE)atoi(row["level"].c_str());
		avatar.m_dwDalant = atoi(row["currency1"].c_str());
		avatar.m_dwGold = atoi(row["currency2"].c_str());
		avatar.m_dwBaseShape = atoi(row["base_shape"].c_str());
		avatar.m_dwLastConnTime = atoi(row["lastConnect"].c_str());

		avatar.m_EquipKey[0].LoadDBKey(atoi(row["helmet"].c_str()));
		avatar.m_EquipKey[1].LoadDBKey(atoi(row["upper"].c_str()));
		avatar.m_EquipKey[2].LoadDBKey(atoi(row["lower"].c_str()));
		avatar.m_EquipKey[3].LoadDBKey(atoi(row["gloves"].c_str()));
		avatar.m_EquipKey[4].LoadDBKey(atoi(row["boots"].c_str()));
		avatar.m_EquipKey[5].LoadDBKey(atoi(row["jetpack"].c_str()));
		avatar.m_EquipKey[6].LoadDBKey(atoi(row["weapon"].c_str()));
		avatar.m_EquipKey[7].LoadDBKey(atoi(row["shield"].c_str()));

		for (int i = 0; i < equip_fix_num; i++)
		{
			//avatar.m_EquipKey[i].LoadDBKey(atoi(str));
			//avatar.m_dwFixEquipLv[i] = dbCharacterInfo.dwEUArray[i];
		}

		return (raw_data_row = row).size() == 0;
	}

	bool del(){
		auto q = std::string("DELETE FROM Characters WHERE id='");
		q.append(std::to_string(avatar.m_dwRecordNum) + "'");
		
		if (db->Query(q.c_str())){
			return true;
		}

		return false;
	}

	CDatabase* db;
	_REGED_AVATOR_DB avatar;
	db_row raw_data_row;
};