#pragma once

#include "CharacterHeaders.h"
#include "../Database/Database.h"

#pragma region CharacterData
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
	char		m_szAvatorName[max_name_len + 1];
	DWORD		m_dwRecordNum;
	BYTE		m_byRaceSexCode;
	BYTE		m_bySlotIndex;
	char		m_szClassCode[class_code_len + 1];
	BYTE		m_byLevel;
	DWORD		m_dwDalant;
	DWORD		m_dwGold;
	DWORD		m_dwBaseShape;
	_EQUIPKEY	m_EquipKey[equip_fix_num];
	BYTE		m_byEquipLv[equip_fix_num];
	DWORD		m_dwLastConnTime;

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
#pragma endregion


class Character : public _REGED {
public:
	Character() { }

	~Character(){ }

	bool Set(db_row row) { //TODO: Needs to be finished
		memcpy(m_szAvatorName, row["name"].c_str(), max_name_len + 1);
		m_dwRecordNum = atol(row["id"].c_str());
		m_byRaceSexCode = Convert::ToChar(row["race_sex"].c_str())[0];
		m_bySlotIndex = Convert::ToChar(row["slot"].c_str())[0];
		memcpy(m_szClassCode, row["class"].c_str(), class_code_len + 1);
		m_byLevel = (BYTE)(Convert::ToChar(row["level"].c_str())[0]);
		m_dwDalant = (DWORD)Convert::ToInt(row["currency1"].c_str());
		m_dwGold = (DWORD)Convert::ToInt(row["currency2"].c_str());
		m_dwBaseShape = (DWORD)Convert::ToInt(row["base_shape"].c_str());
		m_dwLastConnTime = (DWORD)Convert::ToInt(row["lastConnect"].c_str());;

		m_EquipKey[0].LoadDBKey(atoi(row["helmet"].c_str()));
		m_EquipKey[1].LoadDBKey(atoi(row["upper"].c_str()));
		m_EquipKey[2].LoadDBKey(atoi(row["lower"].c_str()));
		m_EquipKey[3].LoadDBKey(atoi(row["gloves"].c_str()));
		m_EquipKey[4].LoadDBKey(atoi(row["boots"].c_str()));
		m_EquipKey[5].LoadDBKey(atoi(row["jetpack"].c_str()));
		m_EquipKey[6].LoadDBKey(atoi(row["weapon"].c_str()));
		m_EquipKey[7].LoadDBKey(atoi(row["shield"].c_str()));

		for (int i = 0; i < equip_fix_num; i++)
		{
			//m_EquipKey[i].LoadDBKey(atoi(str));
			//m_dwFixEquipLv[i] = dbCharacterInfo.dwEUArray[i];
		}

		return (CharacterRow = row).size() == 0;
	}

private:
	db_row CharacterRow;
};