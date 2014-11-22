﻿#pragma pack(push, 1)

//system_msg	1
#define enter_world_request_zone 1 //Require user authentication	
struct _enter_world_request_zone {

	DWORD	dwAccountSerial;
	DWORD	dwMasterKey[CHECK_KEY_NUM];
	bool	bFullMode;	//full mode true, window mode.. false

	int size()	{ return sizeof(*this); }
};

#define enter_world_result_zone 2 //Results of user authentication
struct _enter_world_result_zone {
	//#define USER_DEGREE_STD			0 //General
	//#define USER_DEGREE_GID			1 //Guide
	//#define USER_DEGREE_MGR			2 //Operator
	//#define USER_DEGREE_DEV			3 //Developer

	BYTE	byResult;
	BYTE	byUserGrade;

	int size()	{ return sizeof(*this); }
};

#define reged_char_request_zone 8
struct _reged_char_request_zone {

	int size() { return 0; }
};

#define reged_char_result_zone 9
struct _reged_char_result_zone {

	BYTE	byRetCode;
	BYTE	byCharNum;

	int	dum1;
	int	dum2;
	int	dum3;

	_REGED_AVATOR_DB RegedList[MAX_CHAR_PER_WORLDUSER];

	_reged_char_result_zone(){
		byCharNum = 0;
	}

	int size(){
		return sizeof(*this) - sizeof(_REGED_AVATOR_DB)*(MAX_CHAR_PER_WORLDUSER - byCharNum);
	}
};

#define fireguard_request_zone 127
struct _fireguard_request_zone {

	int size() { return 0; }
};

#define fireguard_result_zone 130
struct _fireguard_result_zone {

	bool enabled;

	int size() { enabled = false; return 0; }
};

#pragma pack(pop)