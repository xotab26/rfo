#pragma pack(push, 1)

//system_msg	1
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
#pragma pack(pop)
