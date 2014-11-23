#pragma region Defines
#define equip_fix_num				8		
#define embellish_fix_num			6		
#define bag_storage_num				100		
#define force_storage_num			88		
#define	animus_storage_num			4		
#define unit_storage_num			4		
#define quest_storage_num			15		
#define potion_belt_num				4		
#define sf_linker_num				8		
#define left_cutting_num			40		
#define class_history_num			3		

#define max_level					50
#define max_animus_level			50
#define max_skill_level				7
#define max_class_grade				4		
#define default_per_part			16		
#define base_fix_num				5		
#define one_bag_store_num			20		
#define max_bag_num					5		
#define max_unit_spare				8		
#define max_overlap_num				99		

#define no_part_wear				0xffff	
#define member_per_party			8		
#define MAX_EQUIP_EFFECT_KIND		4		
#define max_d_trade_item			15		
#define	CONT_SF_SIZE				5		
#define MAX_POTION_EFFECT_KIND		4		
#define STANDARD_MOVE_SPEED			15		
#define STANDARD_VIEW_SIZE			340		
#define MAX_TALIK_NUM				13		
#define attack_able_height			50		
#define attack_max_height			250		
#define EQUIP_MASTERY_CHECK_NUM		2		
#define max_quest_act_num			3		
#define max_quest_per_type			5		

#define max_skill_num				48		
#define force_mastery_num			24		
#define skill_mastery_num			8		
#define mastery_level_num			4		
#define itembox_dist_lootable		100		
#define upgrade_jewel_num			4		
#define MAX_ITEM_LV					7		
#define DEFAULT_ITEM_LV				3		
#define trade_item_max_num			100		
#define DEFAULT_Y_POS				-65535	

#define race_sex_kind_num			5	

#define sex_code_male				0	
#define sex_code_female				1	

#define race_code_bellato			0	
#define race_code_cora				1	
#define race_code_accretia			2	

#define class_code_warrior			0	
#define class_code_ranger			1	
#define class_code_spirit			2	
#define class_code_special			3	

#define mastery_code_weapon			0
#define mastery_code_defence		1
#define mastery_code_shield			2
#define mastery_code_skill			3
#define mastery_code_force			4
#define mastery_code_make			5
#define mastery_code_special		6
#define MASTERY_CODE_NUM			7

#define attack_range_short			0
#define attack_range_long			1

#define	wp_class_close				attack_range_short
#define	wp_class_long				attack_range_long
#define	WP_CLASS_NUM				2

#define mi_class_shield				0
#define mi_class_armor				1
#define mi_class_bullet				2
#define MI_CLASS_NUM				3

#define __NSI						0xFF
#define __NO_TALIK					0x0F
#define __DF_UPT					0x0FFFFFFF
#pragma endregion

static BYTE GetItemUpgedLv(DWORD dwLvBit)
{
	BYTE byLv = 0;
	for (int g = 0; g < MAX_ITEM_LV; g++)
	{
		BYTE byTemp = (BYTE)((dwLvBit >> (g * 4)) & 0x0000000F);
		if (byTemp == __NO_TALIK)
			break;
		byLv++;
	}
	return byLv;
}


#pragma pack(push, 1)
struct _POTIONKEY
{
	BYTE bySlotIndex;	
	BYTE byTableCode;	
	WORD wItemIndex;	

	bool IsFilled()		{ if (*(DWORD*)this == 0xFFFFFFFF) return false;	return true; }
	void SetRelease()	{ *(DWORD*)this = 0xFFFFFFFF; }
	int CovDBKey()	{ return *(int*)this; }
	void  LoadDBKey(int pl_nKey)	{ *(DWORD*)this = (DWORD)pl_nKey; }
};

struct _INVENKEY
{
	BYTE bySlotIndex;	
	BYTE byTableCode;	
	WORD wItemIndex;	

	bool IsFilled()		{ if (*(DWORD*)this == 0xFFFFFFFF) return false;	return true; }
	void SetRelease()	{ *(DWORD*)this = 0xFFFFFFFF; }
	int CovDBKey()	{ return *(int*)this; }
	void  LoadDBKey(int pl_nKey)	{ *(DWORD*)this = (DWORD)pl_nKey; }
};

struct _EQUIPKEY
{
	short zItemIndex;

	bool IsFilled()		{ if (zItemIndex == -1) return false;	return true; }
	void SetRelease()	{ zItemIndex = -1; }
	short CovDBKey()	{ return zItemIndex; }
	void  LoadDBKey(short pl_zKey)	{ zItemIndex = pl_zKey; }
};

struct _EMBELLKEY
{
	BYTE bySlotIndex;
	BYTE byTableCode;
	WORD wItemIndex;

	bool IsFilled()		{ if (*(DWORD*)this == 0xFFFFFFFF) return false;	return true; }
	void SetRelease()	{ *(DWORD*)this = 0xFFFFFFFF; }
	int CovDBKey()	{ return *(int*)this; }
	void  LoadDBKey(int pl_nKey)	{ *(DWORD*)this = (DWORD)pl_nKey; }
};

struct _FORCEKEY
{
	DWORD dwKey;

	void SetKey(BYTE pl_byItemIndex, DWORD pl_dwStat)
	{
		DWORD dwIndex = (DWORD)pl_byItemIndex;
		dwKey = ((DWORD)dwIndex << 24) | (pl_dwStat & 0x00FFFFFF);
	}
	void SetStat(DWORD pl_dwStat)
	{
		dwKey &= 0xFF000000;
		dwKey |= (pl_dwStat & 0x00FFFFFF);
	}

	BYTE GetIndex()	{ return (BYTE)(dwKey >> 24); }
	DWORD GetStat()	{ return (DWORD)(dwKey & 0x00FFFFFF); }

	bool IsFilled()		{ if (dwKey == 0xFFFFFFFF) return false;	return true; }
	void SetRelease()	{ dwKey = 0xFFFFFFFF; }
	int CovDBKey()	{ return (int)dwKey; }
	void  LoadDBKey(int pl_nKey)	{ dwKey = (DWORD)pl_nKey; }
};

struct _ANIMUSKEY
{
	BYTE byItemIndex;

	bool IsFilled()		{ if (*(BYTE*)this == 0xFF) return false;	return true; }
	void SetRelease()	{ *(BYTE*)this = 0xFF; }
	BYTE CovDBKey()	{ return *(BYTE*)this; }
	void  LoadDBKey(BYTE pl_byKey)	{ *(BYTE*)this = pl_byKey; }
};

struct _LINKKEY
{
	WORD wEffectCode;

	bool IsFilled()		{ if (*(WORD*)this == 0xFFFF) return false;	return true; }
	void SetRelease()	{ *(WORD*)this = 0xFFFF; }
	short CovDBKey()		{ return *(short*)this; }
	void  LoadDBKey(short pl_zKey)	{ *(WORD*)this = (WORD)pl_zKey; }
	void SetData(WORD wCode, WORD wIndex)	{ wEffectCode = ((wCode << 12) | wIndex); }
	WORD GetCode()	{ return wEffectCode >> 12; }
	WORD GetIndex()	{ return (wEffectCode & 0x0FFF); }
};

struct _REGED_AVATOR_DB
{
	char      m_wszAvatorName[17];
	DWORD     m_dwRecordNum;
	BYTE      m_byRaceSexCode;
	BYTE      m_bySlotIndex;
	char      m_szClassCode[class_code_len + 1];
	BYTE      m_byLevel;
	DWORD     m_dwDalant;
	DWORD     m_dwGold;
	DWORD     m_dwBaseShape;
	_EQUIPKEY m_EquipKey[equip_fix_num];
	BYTE      m_byEquipLv[equip_fix_num];
	DWORD     m_dwLastConnTime;

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
	DWORD m_dwFixEquipLv[equip_fix_num];
	DWORD m_dwItemETSerial[8];
	QWORD m_lnUID[8];
	BYTE m_byCsMethod[8];
	DWORD m_dwET[8];
	DWORD m_dwLendRegdTime[8];

	_REGED(){ init(); }

	void init()
	{
		_REGED_AVATOR_DB::Init();
		for (int i = 0; i < equip_fix_num; i++)
			m_dwFixEquipLv[i] = __DF_UPT;
	}

	void UpdateEquipLv(){
		for (int v = 0; v < equip_fix_num; v++)
			_REGED_AVATOR_DB::m_byEquipLv[v] = ::GetItemUpgedLv(m_dwFixEquipLv[v]);
	}
};

struct _AVATOR_DB_BASE : public _REGED
{
	DWORD	m_dwHP;					
	DWORD	m_dwFP;					
	DWORD	m_dwSP;					
	DWORD   m_dwDP;                 
	double	m_dExp;					
	double  m_dLossExp;
	double  m_dPvPPoint;
	double  m_dPvPCashBag;
	DWORD   m_dwPvpRank;            
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

struct _BELT_DB_BASE
{
	struct _POTION_LIST
	{
		_POTIONKEY	Key;

		_POTION_LIST()
		{
			Init();
		}

		void Init()
		{
			Key.SetRelease();
		};
	};

	struct _LINK_LIST
	{
		_LINKKEY	Key;

		_LINK_LIST()
		{
			Init();
		}

		void Init()
		{
			Key.SetRelease();
		};
	};

	_POTION_LIST	m_PotionList[potion_belt_num];
	_LINK_LIST		m_LinkList[sf_linker_num];

	_BELT_DB_BASE()
	{
		Init();
	}

	void Init()
	{
		int i;
		for (i = 0; i < potion_belt_num; i++)
			m_PotionList[i].Init();
		for (i = 0; i < sf_linker_num; i++)
			m_LinkList[i].Init();
	};
};

struct _EQUIP_DB_BASE
{
	struct _EMBELLISH_LIST
	{
		_EMBELLKEY Key;
		WORD wAmount;
		DWORD dwItemETSerial;
		QWORD lnUID;
		BYTE byCsMethod;
		DWORD dwT;
		DWORD dwLendRegdTime;
		_EMBELLISH_LIST(){ Init(); }

		void Init(){
			Key.SetRelease();
			wAmount = 0;
		};
	};

	_EMBELLISH_LIST		m_EmbellishList[7];

	_EQUIP_DB_BASE(){ Init(); }

	void Init(){
		for (int i = 0; i < 7; i++)
			m_EmbellishList[i].Init();
	};
};

struct _INVEN_DB_BASE
{
	struct _LIST
	{
		_INVENKEY Key;
		QWORD dwDur;
		DWORD dwUpt;
		DWORD dwItemETSerial;
		QWORD lnUID;
		BYTE byCsMethod;
		DWORD dwT;
		DWORD dwLendRegdTime;
		_LIST(){ Init(); }

		void Init(){
			Key.SetRelease();
			dwDur = 0;
			dwUpt = __DF_UPT;
		};
	};

	_LIST m_List[bag_storage_num];

	_INVEN_DB_BASE(){ Init(); }

	void Init(){
		for (int i = 0; i < bag_storage_num; i++)
			m_List[i].Init();
	};
};

struct _FORCE_DB_BASE
{
	struct _LIST
	{
		_FORCEKEY	Key;

		_LIST(){ Init(); }

		void Init(){
			Key.SetRelease();
		};
	};

	_LIST m_List[force_storage_num];

	_FORCE_DB_BASE(){ Init(); }

	void Init(){
		for (int i = 0; i < force_storage_num; i++)
			m_List[i].Init();
	};
};

struct _ANIMUS_DB_BASE
{
	struct _LIST
	{
		_ANIMUSKEY Key;
		QWORD dwExp;
		DWORD dwParam;
		DWORD dwItemETSerial;
		long lnUID;
		BYTE byCsMethod;
		DWORD dwT;
		DWORD dwLendRegdTime;
		_LIST(){ Init(); }

		void Init(){
			Key.SetRelease();
			dwExp = 0;
			dwParam = 0;
		};
	};

	_LIST m_List[animus_storage_num];

	_ANIMUS_DB_BASE(){ Init(); }

	void Init(){
		for (int i = 0; i < animus_storage_num; i++)
			m_List[i].Init();
	};
};

struct _UNIT_DB_BASE
{
	struct _LIST
	{
		BYTE	bySlotIndex;				
		BYTE	byFrame;					
		DWORD	dwGauge;					
		BYTE	byPart[6];					
		DWORD	dwBullet[2];				
		DWORD	dwSpare[8];					
		int		nPullingFee;				
		DWORD	dwCutTime;					
		WORD	wBooster;					
		_LIST(){ Init(); }

		void Init(BYTE byIndex = 0xFF){
			if (byIndex != 0xFF)
				bySlotIndex = byIndex;
			byFrame = 0xFF;
			memset(byPart, 0xFF, sizeof(byPart));
			memset(dwBullet, 0xFFFFFFFF, sizeof(dwBullet));
			memset(dwSpare, 0xFFFFFFFF, sizeof(dwSpare));
			dwGauge = 0;
			nPullingFee = 0;
			dwCutTime = 0;
		};

		void PushUnit(_LIST* pData){
			BYTE byBufferSlotIndex = bySlotIndex;
			memcpy(this, pData, sizeof(_LIST));
			bySlotIndex = byBufferSlotIndex;
		};

		void DelUnit(){
			byFrame = 0xFF;
		}
	};

	_LIST m_List[4];

	_UNIT_DB_BASE(){ Init(); }

	void Init(){
		for (int i = 0; i < 4; i++)
			m_List[i].Init(i);
	};
};

struct _CUTTING_DB_BASE
{
	struct _LIST
	{
		_INVENKEY Key;
		DWORD dwDur;

		_LIST(){ Init(); }

		void Init(){
			//byResIndex = 0xFF;
			dwDur = 0;
		};
	};

	bool m_bOldDataLoad;
	BYTE m_byLeftNum;
	_LIST	m_List[20];

	_CUTTING_DB_BASE(){ Init(); }

	void Init(){
		m_byLeftNum = 0;
		for (int i = 0; i < 20; i++)
			m_List[i].Init();
	};
};

struct _START_NPC_QUEST_HISTORY
{
	struct _SYSTEMTIME {
		WORD wYear;
		WORD wMonth;
		WORD wDayOfWeek;
		WORD wDay;
		WORD wHour;
		WORD wMinute;
		WORD wSecond;
		WORD wMilliseconds;
	};
	char szQuestCode[64];
	BYTE byLevel;
	_SYSTEMTIME tmStartTime;
	QWORD nEndTime;
};

struct _QUEST_DB_BASE
{
	struct _LIST
	{
		BYTE byQuestType;
		WORD wIndex;
		WORD wNum[3];
		DWORD dwPassSec;

		_LIST(){ Init(); }

		void Init(){
			byQuestType = 0xFF;
			wIndex = 0xFFFF;
			for (int i = 0; i < 3; i++)
				wNum[i] = 0xFFFF;
			dwPassSec = 0xFFFFFFFF;
		};
	};
	struct _NPC_QUEST_HISTORY
	{
		char szQuestCode[8];
		int nEventNo;
		BYTE byLevel;
		DWORD dwEventEndTime;
		_NPC_QUEST_HISTORY() { Init(); }

		void Init()
		{
			nEventNo = -1;
			byLevel = 0xFF;
			dwEventEndTime = 0xFFFFFFFF;
		}
	};
	_LIST m_List[30];
	_NPC_QUEST_HISTORY m_History[70];
	DWORD dwListCnt;
	_START_NPC_QUEST_HISTORY *m_StartHistory;


	_QUEST_DB_BASE(){ Init(); }

	void Init(){
		for (int i = 0; i < quest_storage_num; i++)
			m_List[i].Init();
	};
};

struct _STAT_DB_BASE
{
	enum {
		DATAPOS_WPCNT = 0,
		DATAPOS_DEF = DATAPOS_WPCNT + WP_CLASS_NUM,
		DATAPOS_SHLD = DATAPOS_DEF + 1,
		DATAPOS_SKILL = DATAPOS_SHLD + 1,
		DATAPOS_FORCE = DATAPOS_SKILL + max_skill_num,
		DATAPOS_MAKE = DATAPOS_FORCE + force_mastery_num,
		DATAPOS_SPECIAL = DATAPOS_MAKE + MI_CLASS_NUM
	};

	DWORD	m_dwDamWpCnt[WP_CLASS_NUM];
	DWORD	m_dwDefenceCnt;
	DWORD	m_dwShieldCnt;
	DWORD	m_dwSkillCum[max_skill_num];
	DWORD	m_dwForceCum[force_mastery_num];
	DWORD	m_dwMakeCum[MI_CLASS_NUM];
	DWORD	m_dwSpecialCum;


	_STAT_DB_BASE(){ Init(); }

	void Init(){
		memset(this, 0, sizeof(*this));
	};

	static int GetStatIndex(BYTE byMasteryClass, BYTE byIndex)
	{
		int nStatIndex = -1;
		switch (byMasteryClass)
		{
		case mastery_code_weapon:			nStatIndex = _STAT_DB_BASE::DATAPOS_WPCNT + byIndex;	break;
		case mastery_code_defence:			nStatIndex = _STAT_DB_BASE::DATAPOS_DEF;				break;
		case mastery_code_shield:			nStatIndex = _STAT_DB_BASE::DATAPOS_SHLD;				break;
		case mastery_code_skill:			nStatIndex = _STAT_DB_BASE::DATAPOS_SKILL + byIndex;	break;
		case mastery_code_force:			nStatIndex = _STAT_DB_BASE::DATAPOS_FORCE + byIndex;	break;
		case mastery_code_make:				nStatIndex = _STAT_DB_BASE::DATAPOS_MAKE + byIndex;		break;
		case mastery_code_special:			nStatIndex = _STAT_DB_BASE::DATAPOS_SPECIAL;			break;
		}
		return nStatIndex;
	}

	static bool IsRangePerMastery(BYTE byMasteryClass, BYTE byIndex)
	{
		switch (byMasteryClass)
		{
		case mastery_code_weapon:	if (byIndex < WP_CLASS_NUM)		return true;
		case mastery_code_defence:	if (byIndex == 0)				return true;
		case mastery_code_shield:	if (byIndex == 0)				return true;
		case mastery_code_skill:	if (byIndex < max_skill_num)		return true;
		case mastery_code_force:	if (byIndex < force_mastery_num) return true;
		case mastery_code_make:		if (byIndex < MI_CLASS_NUM)		return true;
		case mastery_code_special:	if (byIndex == 0)				return true;
		}
		return false;
	}
};

struct _LINK_DB_BASE
{
	struct _LIST
	{
		_LINKKEY Key;
	};
	_LIST m_LinkList[50];
	BYTE m_byLinkBoardLock;
	DWORD m_dwSkill[2];
	DWORD m_dwForce[2];
	DWORD m_dwCharacter[2];
	DWORD m_dwAnimus[2];
	DWORD m_dwInven;
	DWORD m_dwInvenBag[5];
};

struct _SFCONT_DB_BASE
{

	struct _LIST
	{
		DWORD dwKey;
		_LIST() { dwKey = 0xFFFFFFFF; }
	};
	_LIST m_List[2][8];
};

struct _TRADE_DB_BASE
{
	struct _LIST
	{
		byte byState;
		DWORD dwRegistSerial;
		BYTE byInvenIndex;
		DWORD dwPrice;
		QWORD tStartTime;
		BYTE bySellTurm;
		DWORD dwBuyerSerial;
		BYTE dwTax;
		QWORD tResultTime;
		char wszBuyerName[17];
		char szBuyerAccount[13];
	};
	_LIST m_List[20];
};

struct _BUDDY_DB_BASE
{
	struct _LIST
	{
		DWORD dwSerial;
		char wszName[17];
		_LIST() { dwSerial = 0xFFFFFFFF; }
	};
	_LIST m_List[50];
};

struct _TRUNK_DB_BASE
{
	struct _LIST
	{
		_INVENKEY Key;
		QWORD dwDur;
		DWORD dwUpt;
		BYTE byRace;
		DWORD dwItemETSerial;
		QWORD lnUID;
		BYTE byCsMethod;
		DWORD dwT;
		BYTE dwLendRegdTime;
		_LIST(){ Init(); }

		void Init(){
			Key.SetRelease();
			dwDur = 0;
			dwUpt = __DF_UPT;
		};
	};
	char wszPasswd[13];
	long double dDalant;
	long double dGold;
	byte byHintIndex;
	char wszHintAnswer[17];
	byte bySlotNum;
	_LIST m_List[100];
	byte byExtSlotNum;
	_LIST m_ExtList[40];
};

struct _COMBINEKEY
{
	BYTE byRewardIndex;
	BYTE byTableCode;
	WORD wItemIndex;
};

struct _ITEMCOMBINE_DB_BASE
{
	struct _LIST
	{
		_COMBINEKEY Key;
		DWORD dwDur;
		DWORD dwUpt;
	};
	bool m_bIsResult;
	BYTE m_byItemListNum;
	BYTE m_byDlgType;
	DWORD m_dwDalant;
	DWORD m_dwCheckKey;
	BYTE m_bySelectItemCount;
	_LIST m_List[24];
	DWORD m_dwResultEffectType;
	DWORD m_dwResultEffectMsgCode;
};

struct _AIOC_A_MACRODATA
{
	struct MACRO_ACTIONDATA
	{
		DWORD Action[10];
	};
	struct MACRO_CHATDATA
	{
		char Chat[5][256];
	};
	struct MACRO_POTIONDATA
	{
		DWORD Potion[3];
		DWORD PotionValue[3];
	};

	MACRO_POTIONDATA mcr_Potion[1];
	MACRO_ACTIONDATA mcr_Action[3];
	MACRO_CHATDATA mcr_Chat[2];

};

struct _POSTSTORAGE_DB_BASE
{
	struct __list
	{
		DWORD dwPSSerial;
		int nNumber;
		BYTE byState;
		int nKey;
		QWORD dwDur;
		DWORD dwUpt;
		DWORD dwGold;
		bool bUpdate;
		bool bRetProc;
		bool bNew;
		bool bUpdateIndex;
		char wszSendName[17];
		char wszRecvName[17];
		char wszTitle[21];
		char wszContent[201];
		QWORD lnUID;
	};
	__list m_PostList[50];
	bool m_bUpdate;
};

struct _RETURNPOST_DB_BASE
{
	bool m_bUpdate;
	int m_nMax;
	int m_nCum;
	DWORD m_RetSerials[30];
};

struct _DELPOST_DB_BASE
{
	struct __list
	{
		DWORD dwDelSerial;
		int nStorageIndex;
	};
	bool m_bUpdate;
	int m_nMax;
	int m_nCum;
	__list m_List[50];

};

struct _POSTDATA_DB_BASE
{
	_POSTSTORAGE_DB_BASE dbPost;
	_RETURNPOST_DB_BASE dbRetPost;
	_DELPOST_DB_BASE dbDelPost;
};

struct _CRYMSG_DB_BASE
{
	struct _LIST
	{
		char wszCryMsg[65];
	};

	_LIST m_List[10];
};

struct _PERSONALAMINE_INVEN_DB_BASE
{
	struct _LIST
	{
		_INVENKEY Key;
		DWORD dwDur;
	};

	bool bUsable;
	_LIST m_List[40];
};

struct _PVPPOINT_LIMIT_DB_BASE
{
	QWORD tUpdatedate;
	bool bUseUp;
	BYTE byLimitRate;
	long double dOriginalPoint;
	long double dLimitPoint;
	long double dUsePoint;
};

struct _PVP_ORDER_VIEW_DB_BASE
{
	QWORD tUpdatedate;
	int nDeath;
	int nKill;
	long double dTodayStacked;
	long double dPvpPoint;
	long double dPvpTempCash;
	long double dPvpCash;
	DWORD dwKillerSerial[10];
	char byContHaveCash;
	char byContLoseCash;
	bool bRaceWarRecvr;
};

struct _worlddb_sf_delay_info
{
	struct _eff_list
	{
		BYTE byEffectCode;
		WORD wEffectIndex;
		DWORD dwNextTime;
	};
	struct _mas_list
	{
		BYTE byEffectCode;
		BYTE byMastery;
		DWORD dwNextTime;
	};

	_eff_list EFF[10];
	_mas_list MAS[10];
};

struct _SUPPLEMENT_DB_BASE
{
	long double dPvpPointLeak;
	bool bLastAttBuff;
	DWORD dwBufPotionEndTime;
	DWORD dwRaceBuffClear;
	BYTE byVoted;
	BYTE VoteEnable;
	WORD wScanerCnt;
	DWORD dwScanerGetDate;
	DWORD dwAccumPlayTime;
	DWORD dwLastResetDate;
	DWORD dwActionPoint[3];
};

struct _PCBANG_PLAY_TIME
{
	DWORD dwAccSerial;
	DWORD dwLastConnTime;
	DWORD dwContPlayTime;
	bool bForcedClose;
	BYTE byReceiveCoupon;
	BYTE byEnsureTime;
};

struct _POTION_NEXT_USE_TIME_DB_BASE
{
	DWORD dwPotionNextUseTime[38];
};

struct _PCBANG_FAVOR_ITEM_DB_BASE
{
	QWORD lnUID[50];
};

struct _TIMELIMITINFO_DB_BASE
{
	DWORD dwAccSerial;
	DWORD dwFatigue;
	BYTE byTLStatus;
	DWORD dwLastLogoutTime;
};

struct _AVATOR_DATA
{
	_AVATOR_DB_BASE dbAvatar; 
	_LINK_DB_BASE dbLink; 
	_EQUIP_DB_BASE dbEquip;
	_FORCE_DB_BASE dbForce; 
	_ANIMUS_DB_BASE dbAnimus;
	_STAT_DB_BASE dbStat; 
	_INVEN_DB_BASE dbInven;
	_CUTTING_DB_BASE dbCutting;
	_QUEST_DB_BASE dbQuest;
	_UNIT_DB_BASE dbUnit;
	_SFCONT_DB_BASE dbSfcont;
	_TRADE_DB_BASE dbTrade;
	_BUDDY_DB_BASE dbBuddy;
	_TRUNK_DB_BASE dbTrunk;
	_ITEMCOMBINE_DB_BASE dbItemCombineEx;
	_AIOC_A_MACRODATA dbMacro;
	_POSTDATA_DB_BASE dbPostData;
	_CRYMSG_DB_BASE dbBossCry;
	BYTE m_byHSKTime;
	BYTE m_byPvpGrade;
	WORD m_wKillPoint;
	int m_iPvpPoint;
	WORD m_wDiePoint;
	BYTE m_byCristalBattleDBInfo;
	_PERSONALAMINE_INVEN_DB_BASE dbPersonalAmineInven;
	_PVPPOINT_LIMIT_DB_BASE dbPvpPointLimit;
	_PVP_ORDER_VIEW_DB_BASE dbPvpOrderView;
	_worlddb_sf_delay_info dbSFDelay;
	_SUPPLEMENT_DB_BASE dbSupplement;
	_PCBANG_PLAY_TIME dbPlayTimeInPcbang;
	bool m_bCristalBattleDateUpdate;
	_POTION_NEXT_USE_TIME_DB_BASE dbPotionNextUseTime;
	_PCBANG_FAVOR_ITEM_DB_BASE dbPcBangFavorItem;
	_TIMELIMITINFO_DB_BASE dbTimeLimitInfo;
	_AVATOR_DATA(){ InitData(); }

	void InitData()
	{
		dbAvatar.Init();
		dbEquip.Init();
		dbForce.Init();
		dbAnimus.Init();
		dbStat.Init();
		dbInven.Init();
		dbCutting.Init();
		//TODO: need to add init codes
	}
};

struct _STORAGE_POS
{
	enum { INVEN = 0, EQUIP, EMBELLISH, BELT, FORCE, ANIMUS, LINKER };
	enum { POS_NUM = LINKER + 1 };
	enum { STORAGE_NUM = ANIMUS + 1 };

	BYTE byStorageCode;
};

struct _STORAGE_POS_INDIV : public _STORAGE_POS
{
	WORD wItemSerial;
	BYTE byNum;
};

struct _GLBID
{
	DWORD	dwIndex;
	DWORD	dwSerial;
};

struct _CLID
{
	WORD	wIndex;
	DWORD	dwSerial;
};

struct _CHRID
{
	BYTE byID;
	WORD wIndex;
	DWORD dwSerial;
};

struct _COUNT_LV
{
	DWORD	dwCnt;
	int		nLv;
};

struct _ITEM_EFFECT
{
	int nEffectCode;
	float fEffectValue;
};

struct _WORLD_INFO
{
	BYTE byWorldCode;
	bool bOpen;
	bool bService;
	int	 nUserNum;
};

struct _animus_param		
{
	WORD wHP;				
	WORD wFP;				
};

struct _unit_bullet_param	
{
	WORD wBulletIndex;		
	WORD wLeftNum;			

	_unit_bullet_param(){
		*(DWORD*)this = 0xFFFFFFFF;
	}

	int IsFill(){
		if (*(DWORD*)this == 0xFFFFFFFF)
			return false;
		return true;
	}
};

struct _tuning_data		
{
	BYTE byPartCode;	
	BYTE byPartIndex;	
};

struct _ENTER_WORLD_TEMP_DATA
{
	DWORD				m_dwWorldIP;
	WORD				m_wWorldPort;
	char				m_szID[max_id_len + 1];
	DWORD				m_dwAccountSerial;
	DWORD				m_dwWorldMasterKey[CHECK_KEY_NUM];
};

struct _DBITEM
{
	BYTE byTableCode;
	WORD wItemSerial;
	DWORD dwItemUpgrade;
	BYTE byCSMethod;
	DWORD dwTime;
	_DBITEM()
	{
		byTableCode = 0xFF;
		dwItemUpgrade = 0x0FFFFFFF;
	}
};

struct _UILOCK_DATA
{
	bool bIsSet;
	char szUILockPW[13];
	BYTE byUILock_HintIndex;
	char szUILock_HintAnswer[17];
	_UILOCK_DATA() { Init(); }
	void Init() { bIsSet = false; }
};

struct _NOT_ARRANGED_AVATOR_DB
{
	DWORD dwSerial;
	BYTE byLv;
	BYTE byRaceSexCode;
	BYTE dwDalant;
	BYTE dwGold;
	char wszName[max_name_len + 1];
	char szServer[max_world_name_len + 1];
	char szClassCode[5];
};

#pragma pack(pop)