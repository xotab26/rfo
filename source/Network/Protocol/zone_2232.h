#pragma pack(push, 1)

#pragma region system_msg 01
#define enter_world_request_clzo 1	
struct _enter_world_request_clzo
{
	DWORD dwAccountSerial;
	DWORD dwMasterKey[CHECK_KEY_NUM];
	bool  bFullMode;
	DWORD dwProtocolVer;
	char  szClientVerCheckKey[33];

	int size()	{ return sizeof(*this); }
};

#define enter_world_result_zocl 2
struct _enter_world_result_zocl
{
	BYTE	byResult;
	BYTE	byUserGrade;
	BYTE	bySvrType;

	int size()	{ return sizeof(*this); }
};

#define reged_char_request_clwr 8
struct _reged_char_request_clwr
{
	char dummy[1];
	int size()	{ return sizeof(*this); }
};

#define reged_char_result_zone 9
struct _reged_char_result_wrcl
{
	char byRetCode;
	char byCharNum;
	int iLockType[3];
	_REGED_AVATOR_DB RegedList[3];

	enum LOCK_TYPE
	{
		LT_NONE = 0x0,
		LT_REQUEST_MOVE_CHARACTER = 0x1,
		LT_TOURNAMENT_CHARACTER = 0x2,
	};
	int size()	{ return (sizeof(*this) - sizeof(_REGED_AVATOR_DB)*(3 - byCharNum)); }
};

#define uilock_init_request_clwr 127
struct _uilock_init_request_clwr {
	char uszUILockPW[13];
	char uszUILockPW_Confirm[13];
	BYTE byUILock_HintIndex;
	char uszUILock_HintAnswer[17];
	int size() { return sizeof(*this); }
};

#define uilock_fg_auth_req_clwr 129
struct _uilock_fg_auth_req_clwr {
	char szPW[17];
	int size() { return sizeof(*this); }
};

#define uilock_fg_auth_req_wrcl 130
struct _uilock_fg_auth_req_wrcl {
	BYTE byRetCode;
	int size() { return sizeof(*this); }
};

#define add_char_request_clwr 10
struct _add_char_request_clwr
{
	BYTE bySlotIndex;
	char wszCharName[max_name_len + 1];
	BYTE byRaceSexCode;
	char szClassCode[class_code_len + 1];
	DWORD dwBaseShape;
	int size()	{ return sizeof(*this); }
};

#define add_char_result_zocl 11
struct _add_char_result_zocl
{
	BYTE byRetCode;
	BYTE byAddSlotIndex;
	int size()	{ return sizeof(*this); }
};

#define del_char_request_clwr 12
struct _del_char_request_clwr {

	BYTE bySlotIndex;

	int size()	{ return sizeof(*this); }
};

#define del_char_result_wrcl 13
struct _del_char_result_wrcl {

	BYTE	byRetCode;
	BYTE	bySlotIndex;
	DWORD	dwWorldSerial;

	int size()	{ return sizeof(*this); }
};

#define sel_char_request_clwr 14
struct _sel_char_request_clwr
{
	char bySlotIndex;
	int size()	{ return sizeof(*this); }
};

#define sel_char_result_wrcl 15
struct _sel_char_result_wrcl
{
	BYTE byRetCode;
	BYTE bySlotIndex;
	DWORD dwWorldSerial;
	DWORD dwDalant;
	DWORD dwGold;

	int size()	{ return sizeof(*this); }
};
#pragma endregion

#pragma region chat_msg 02
#define chat_map_recv_yesorno_clwr 10
struct _chat_map_recv_yesorno_clwr
{
	BYTE byRecv;
	int size()	{ return sizeof(*this); }
};
#pragma endregion

#pragma region init_msg 03
#define base_download_request_clwr 3
struct _base_download_request_clwr {
	char sDum[1];
	int size()	{ return sizeof(*this); }
};

#define base_download_result_wrcl 4
struct _base_download_result_wrcl {
	struct _list_equip
	{
		char sTableCode;
		WORD wItemIndex;
		DWORD dwUptInfo;
		BYTE byCsMethod;
		DWORD dwT;
	};

	struct _list_embellish
	{
		char sTableCode;
		WORD wItemIndex;
		WORD wNum;
		char sClientIndex;
		BYTE byCsMethod;
		DWORD dwT;
	};

	BYTE byRetCode;
	WORD wZoneIndex;
	DWORD dwExpRate;
	WORD wClassHistory[3];
	WORD wHP;
	WORD wSP;
	WORD wFP;
	long double dPvpPoint;
	long double dPvpCashBag;
	long double dPvpTempCash;
	DWORD dwPvpRank;
	BYTE byPvpClass;
	BYTE byPlusKey;
	WORD wXorKey;
	WORD wMaxHP;
	WORD wMaxSP;
	WORD wMaxFP;
	WORD wMapIndex;
	float fPos[3];
	_list_equip EquipList[8];
	_list_embellish EmbellishList[6];
	BYTE byHolyMasterState;
	DWORD dwGuildSerial;
	BYTE byGuildGrade;
	BYTE byEffectValue[2];
	BYTE byUseTrunkSlotNum;
	WORD wMaxDP;
	WORD wDP;
	BYTE byHonorGuildRank;

	int size()	{ return sizeof(*this); }
};

#define inven_download_request_clwr 5
struct _inven_download_request_clwr
{
	char dummy[1];
	int size()	{ return sizeof(*this); }
};

#define inven_download_result_wrcl 6
struct _inven_download_result_wrcl
{
	struct _list
	{
		BYTE byTableCode;
		WORD wItemIndex;
		QWORD dwDurPoint;
		char sClientIndex;
		DWORD dwUptInfo;
		BYTE byCsMethod;
		DWORD dwT;
	};
	BYTE byRetCode;
	BYTE byBagNum;
	BYTE bySlotNum;
	_list ItemSlotInfo[100];
	int size()	{ return (sizeof(*this) - sizeof(_list)*(100 - bySlotNum)); }
};

#define cum_download_request_clwr 7
#define cum_download_result_wrcl 8
struct _cum_download_result_wrcl
{
	BYTE byRetCode;
	_STAT_DB_BASE Stat;
	BYTE byLeftCuttingResNum;
	WORD wleftResList[20];
	int size() { return sizeof(*this); }
};

#define force_download_request_clwr 9
#define force_download_result_wrcl 10
struct _force_download_result_wrcl
{
	struct _list
	{
		WORD wItemIndex;
		DWORD dwCum;
		BYTE byCsMethod;
		DWORD dwT;
	};
	BYTE byRetCode;
	BYTE bySlotNum;
	_list ItemSlotInfo[88];
	int size()	{ return (sizeof(*this) - sizeof(_list)*(88 - bySlotNum)); }
};

#define quest_download_request_clwr 11
#define quest_download_result_wrcl 12
struct _quest_download_result_wrcl
{
	struct __list
	{
		BYTE byDBSlotIndex;
		_QUEST_DB_BASE::_LIST cont;
	};

	BYTE byRetCode;
	BYTE bySlotNum;
	__list SlotInfo[30];
	int size() { return sizeof(*this) - sizeof(__list) * (30 - bySlotNum); }
};
#pragma endregion

#pragma pack(pop)
