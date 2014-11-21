#pragma pack(push, 1)

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
#define USER_DEGREE_STD			0 //General
#define USER_DEGREE_GID			1 //Guide
#define USER_DEGREE_MGR			2 //Operator
#define USER_DEGREE_DEV			3 //Developer

	BYTE	byResult;
	BYTE	byUserGrade;

	int size()	{ return sizeof(*this); }
};

#pragma pack(pop)
