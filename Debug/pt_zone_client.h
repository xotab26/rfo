#ifndef _pt_zone_client_h_
#define _pt_zone_client_h_

#include "rf_protocol.h"
#include "CharacterDB.h"

#pragma pack(push, 1)

//
//system..	1
//
#define enter_world_request_zone 1	// »ç¿ëÀÚ ÀÎÁõÀ» ¿äÃ»	
struct _enter_world_request_zone {

	DWORD	dwAccountSerial;
	DWORD	dwMasterKey[CHECK_KEY_NUM];			
	bool	bFullMode;	//full mode true, window mode.. false

	int size()	{ return sizeof(*this);	}
};

#define enter_world_result_zone 2// »ç¿ëÀÚ ÀÎÁõÀÇ °á°ú	
struct _enter_world_result_zone {

//À¯Àúµî±Þ..( CharacterDB.h )
//#define USER_DEGREE_STD			0		//À¯Àúµî±Þ-ÀÏ¹Ý
//#define USER_DEGREE_GID			1		//À¯Àúµî±Þ-°¡ÀÌµå
//#define USER_DEGREE_MGR			2		//À¯Àúµî±Þ-¿î¿µÀÚ
//#define USER_DEGREE_DEV			3		//À¯Àúµî±Þ-°³¹ßÀÚ

	BYTE	byResult;
	BYTE	byUserGrade; //°èÁ¤µî±Þ..  2, 3µî±Þ Ä¡Æ®Å° ¹× ¿î¿µÀÚ ¸Þ½ÃÁö, /ÀÌµ¿ »ç¿ë°¡´É

	int size()	{ return sizeof(*this);	}
};

#define messenger_enter_key_inform_zocl	222
struct _messenger_enter_key_inform_zocl {	

	DWORD	dwAvatorSerial;			//add
	DWORD	dwKey[CHECK_KEY_NUM];
	DWORD	dwMessengerIP;

	int size()	{ return sizeof(*this);	}
};

#define movein_user_request_zone 3	// »ç¿ëÀÚ ÀÎÁõÀ» ¿äÃ»
struct _movein_user_request_zone {

	DWORD	dwAccountSerial;	
	DWORD	dwZoneMasterKey;
	bool	bFullMode;	//full mode true, window mode.. false

	int size()	{ return sizeof(*this);	}
};

#define movein_user_result_zone 4// »ç¿ëÀÚ ÀÎÁõÀÇ °á°ú
struct _movein_user_result_zone {

	BYTE	byResult;

	int size()	{ return sizeof(*this);}//-(2560-wInitDataSize);	}
};

#define moveout_user_request_zone 5
struct _moveout_user_request_zone {

	//#define ZONE_TYPE_GATE	0	..Ä³¸¯ÅÍ¼±ÅÃÀ» ´Ù½ÃÇÒ¶ó¹È..
	//#define ZONE_TYPE_MAP		1	..¸ÊÀÌµ¿À» ÇÞ´Ù¸é..
	BYTE	byNextZoneType;	

	int size() { return sizeof(*this); }
};

#define moveout_user_result_zone 6
struct _moveout_user_result_zone {

	BYTE	byRetCode;
	DWORD	dwIP;	
	WORD	wPort;
	DWORD	dwZoneMasterKey;

	int size()	{ return sizeof(*this);	}
};

#define reged_char_request_zone 7 //µî·Ï‰?Ä³¸¯ÅÍ¸¦ ¿ä±¸
struct _reged_char_request_zone {

	int size() { return 0; }
};

#define reged_char_result_zone 8 //µî·Ï‰?Ä³¸¯ÅÍ¸¦ ¿ä±¸
struct _reged_char_result_zone {

	BYTE	byRetCode;	
	BYTE	byCharNum;

	_REGED_AVATOR_DB RegedList[MAX_CHAR_PER_WORLDUSER];	

	_reged_char_result_zone(){
		byCharNum = 0;
	}

	int size(){ 
		return sizeof(*this)-sizeof(_REGED_AVATOR_DB)*(MAX_CHAR_PER_WORLDUSER-byCharNum);
	}
};

#define add_char_request_zone 9	// Ä³¸¯ÅÍ µî·Ï
struct _add_char_request_zone {

	BYTE bySlotIndex;				
	char szCharName[max_name_len+1];
	BYTE byRaceSexCode;
	char szClassCode[class_code_len+1];	
	DWORD dwBaseShape;	
	
	int size()	{ return sizeof(*this);	}
};

#define add_char_result_zone 10	// Ä³¸¯ÅÍ µî·Ï È®ÀÎ
struct _add_char_result_zone {

	BYTE byRetCode;	
	BYTE byAddSlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define del_char_request_zone 11	//»èÁ¦ÇÒ ÄÉ¸¯ÅÍ ¼±ÅÃ
struct _del_char_request_zone {
	
	BYTE bySlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define del_char_result_zone 12	//»èÁ¦ÇÒ ÄÉ¸¯ÅÍ ¼±ÅÃÈ®ÀÎ
struct _del_char_result_zone {

	BYTE byRetCode;	
	BYTE bySlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define sel_char_request_zone 13	//ÇÃ·¹ÀÌÇÒ ÄÉ¸¯ÅÍ ¼±ÅÃ
struct _sel_char_request_zone {
	
	BYTE bySlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define sel_char_result_zone 14	//ÇÃ·¹ÀÌÇÒ ÄÉ¸¯ÅÍ ¼±ÅÃÈ®ÀÎ
struct _sel_char_result_zone {

	BYTE byRetCode;	
	BYTE bySlotIndex;
	DWORD	dwWorldSerial; 

	int size()	{ return sizeof(*this);	}
};

//SERVER NOTIFY CODE
#define server_notify_inform_zone 17
struct _server_notify_inform_zone {

	WORD	wMsgCode;
	DWORD	dwPushIP;


	int size()	{	return sizeof(*this);	}
};

//
//init_msg..	3
//

//Á¸¿¡ Á¢¼ÓÇØ¼­ µ¥ÀÌÅÍ¸¦ ÀüºÎ ´Ù¿î·Îµå¹ÞÀ¸¸é byMapInMode = mapin_type_start
//Æ÷Å»ÀÌµ¿ÇÑÈÄ À§Ä¡º¸Á¤À» ¿Ï·áÇÏ¸é byMapInMode = mapin_type_move
//ºÎÈ°ÈÄ À§Ä¡º¸Á¤ ¿Ï·áÇÏ¸é byMapInMode = mapin_type_revival
//±âÁ¸ client_load_complete_clzo ¿Í _new_map_load_complete_clzo¸¦ ÇÕÃÆÀ½..

#define new_pos_start_request_clzo 1
struct _new_pos_start_request_clzo {

	//#define mapin_type_start		0	//°ÔÀÓ½ÃÀÛ..
	//#define mapin_type_move		1	//Æ÷Å»ÀÌµ¿..
	//#define mapin_type_revival	2	//ºÎÈ°..
	//#define mapin_type_goto		3	//¼ø°£ÀÌµ¿..
	//#define mapin_type_recall     4	//Ãâµ¿..
	//#define mapin_type_dungeon    5	//´øÁ¯..

	BYTE byMapInMode;
};

#define new_pos_start_result_zocl 2
struct _new_pos_start_result_zocl {

	BYTE byMapInMode;	//À§ byMapInModeÀÇ ¸®¹Ù¿îµå°ª.. ½ÇÆÐ½Ã 0xFF..
};

#define base_download_request_clzo 5
struct _base_download_request_clzo {	
};

//ÀúÀå ¾ÆÀÌÅÛ ½Ã¸®¾ó ºÎ¿©¼ø¼­..
//1. Equip
//2. Embellish
//3. Belt
//4. Inven
//5. Force
//6. Animus
#define base_download_result_zocl 6
struct _base_download_result_zocl {

	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..

	WORD wZoneIndex;	//ÇöÀç Á¸»ó¿¡¼­ÀÇ ÀÎµ¦½º
	WORD wExpRate;	
	WORD wClassHistory[class_history_num];	//°ú°Å class ±â·Ï
	WORD wHP;		
	WORD wSP;		
	WORD wFP;		
	WORD wMaxHP;			
	WORD wMaxSP;			
	WORD wMaxFP;			
	WORD wMapIndex;		//¸ÊÀÎµ¦½º	
	short zPos[3];		//À§Ä¡

	struct _list_equip{
		char sTableCode;	//table code	.. ºó ½½·ÔÀÌ¸é -1
		WORD wItemIndex;	//item index
		DWORD dwUptInfo;//¾÷±×·¹ÀÌµåÁ¤º¸..¿À¸¥ÂÊºÎÅÍ 4ºñÆ®¾¿ ¾÷±×·¹ÀÌµåÁ¤º¸.. F°¡ ³ª¿Ã¶§±îÁö¾÷±Û·¹º§À» ++ÇÑ´Ù.
	}; 

	_list_equip EquipList[equip_fix_num];

	struct _list_embellish{
		char sTableCode;	//table code	.. ºó ½½·ÔÀÌ¸é -1
		WORD wItemIndex;	//item index
		WORD wNum;		//È­»ìÀÏ°æ¿ì ³²Àº°¹¼ö
		char sClientIndex;	
	};
	
	_list_embellish EmbellishList[embellish_fix_num];	

	struct _list_belt{
		short zItemIndex;	//item index ºó°Å¸é -1 
		BYTE byNum;		//°¹¼ö
		char sClientIndex;	
	};
	
	_list_belt BeltList[potion_belt_num];

	struct _list_linker{
		BYTE byEffectCode;	
		WORD wItemIndex;	//item index
		char sClientIndex;	
	};

	_list_linker LinkerList[sf_linker_num];

	int size(){
		if(byRetCode != 0)
			return sizeof(byRetCode);
		return sizeof(*this);
	}
};

//_movein_user_result_zoneÈÄ¿¡ ¾Æ¹ÙÅ¸µ¥ÀÌÅÍ¸¦ ´Ù¿î¹Þ´Â´Ù.
//ÀÎº¥Åä¸®..
#define inven_download_request_clzo 7
struct _inven_download_request_clzo {
};

#define inven_download_result_zocl 8
struct _inven_download_result_zocl {	

	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..

	BYTE byBagNum;	
	BYTE bySlotNum;

	struct _list{
		BYTE byTableCode; 
		WORD wItemIndex;
		DWORD dwDurPoint;
		char sClientIndex;
		DWORD dwUptInfo;//¾÷±×·¹ÀÌµåÁ¤º¸
	}; 	
	
	_list ItemSlotInfo[bag_storage_num];

	int size(){
		if(byRetCode != 0)
			return sizeof(byRetCode);
		return sizeof(*this)-sizeof(_list)*(bag_storage_num-bySlotNum);
	}
};

//°¢Á¾ ´©ÀûÄ¡..
#define cum_download_request_clzo 9
struct _cum_download_request_clzo { 
};

#define cum_download_result_zocl 10
struct _cum_download_result_zocl {

	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..

	_STAT_DB_BASE Stat;	

	BYTE byLeftCuttingResNum;				
	WORD wleftResList[left_cutting_num];	//..ÇÏÀ§¹ÙÀÌÆ®: resÀÎµ¦½º, »óÀ§¹ÙÀÌÆ®: res°¹¼ö

	int size(){
		if(byRetCode != 0)
			return sizeof(byRetCode);
		return sizeof(*this)-sizeof(WORD)*(left_cutting_num-byLeftCuttingResNum);
	}
};

//Æ÷½ºÀÎº¥³»¿ë
#define force_download_request_clzo 11
struct _force_download_request_clzo {

};

#define force_download_result_zocl 12
struct _force_download_result_zocl {

	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..

	BYTE bySlotNum;

	struct _list{
		WORD wItemIndex;
		DWORD dwCum;
	}; 	

	_list ItemSlotInfo[force_storage_num];

	int size(){
		if(byRetCode != 0)
			return sizeof(byRetCode);
		return sizeof(*this)-sizeof(_list)*(force_storage_num-bySlotNum);
	}
};

#define special_download_request_clzo 122
struct _special_download_request_clzo {

};

#define unit_download_result_zocl 123
struct _unit_download_result_zocl {	

	struct _list{
		BYTE					bySlotIndex;
		_UNIT_DB_BASE::_LIST	UnitData;
	};

	BYTE	byUnitNum;
	_list	UnitList[unit_storage_num];		
	
	_unit_download_result_zocl()	{
		byUnitNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(unit_storage_num-byUnitNum);
	}
};

#define animus_download_result_zocl 144
struct _animus_download_result_zocl {

	struct _list{
		char sItemIndex;	//item index ºó°Å¸é -1 
		DWORD dwExp;		//¾ÆÀÌÅÛ ¼ö·® ¸É¹öº¯¼ö»ç¿ë..
		DWORD dwParam;		//	_animus_param À¸·Î Çüº¯È¯ÇÒ°Í..(CharacterDB.h)		//¾ÆÀÌÅÛ ¾÷±×·¹ÀÌµå ¸É¹öº¯¼ö»ç¿ë..
							//	struct _animus_param{
							//		WORD wHP;
							//		WORD wFP;		};
	};

	BYTE byAnimusNum;
	_list AnimusList[animus_storage_num];
	
	_animus_download_result_zocl()	{
		byAnimusNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(animus_storage_num-byAnimusNum);
	}
};

#define monster_create_zocl 13 (2232=10)
struct _monster_create_zocl{

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zPos[3];
	BYTE byInfo[4];

};

#define recallmon_create_zocl 113
struct _recallmon_create_zocl{	
	
	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zPos[3];
	BYTE byInfo[4];

};

#define npc_create_zocl 114
struct _npc_create_zocl {

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zPos[3];
};

#define animus_create_zocl 115
struct _animus_create_zocl {

	WORD wIndex;
	WORD wRecIndex;
	DWORD dwSerial;
	short zPos[3];
	BYTE byLv;	
};

#define tower_create_zocl 116
struct _tower_create_zocl {	

	WORD wIndex;
	WORD wRecIndex;
	DWORD dwSerial;
	short zPos[3];	
};

#define itembox_create_zocl 14
struct _itembox_create_zocl{	

	BYTE byItemTableCode;
	WORD wItemRecIndex;
	BYTE byAmount;	//ÁßÃ¸¾ÆÀÌÅÛÀÏ°æ¿ì °¹¼ö..
	WORD wBoxIndex;	
	DWORD dwOwerSerial;	//1Â÷·Î ÁÞÀ»¼öÀÕ´Â ±Ç¸®ÀÚ..
	_CHRID idDumber;	//¹ö¸°»ç¶÷.. ¹ö¸°»ç¶÷Á¤º¸¾øÀ¸¸é 0xFF..
	BYTE byState;
	short zPos[3];
};

#define parkingunit_create_zocl 124
struct _parkingunit_create_zocl{

	WORD wObjIndex;
	DWORD dwObjSerial;
	BYTE byCreateType;	//#define unit_create_type_delivery	0	//Ãâ°í	//#define unit_create_type_leave		1	//ÇÏÂ÷
	BYTE byFrame;
	BYTE byPart[UNIT_PART_NUM];
	DWORD dwOwerSerial;	
	short zPos[3];
	BYTE byTransDistCode;	//#define unit_trans_short_range		0	//À¯´Ö ±Ù°Å¸®¼ö¼Û #define unit_trans_long_range		1	//À¯´Ö ¿ø°Å¸®¼ö¼Û
};	

#define player_destroy_zocl 15
struct _player_destroy_zocl{	//Á¸¼­¹öÁ¾·á//

	WORD wIndex;
	DWORD dwSerial;

	BYTE byState; //0: °ÔÀÓÁ¾·á, 1: Á¸ÀÌµ¿
};

#define player_die_zocl 16
struct _player_die_zocl{	//½ÃÃ¼·Î Á×À½//

	WORD wIndex;
	DWORD dwSerial;
};

#define monster_destroy_zocl 17
struct _monster_destroy_zocl{

	WORD wIndex;
	DWORD dwSerial;	
	BYTE byDestroyCode;	//0.. die, 1.. respawn
};

#define npc_destroy_zocl 118
struct _npc_destroy_zocl{	

	WORD wIndex;
	DWORD dwSerial;	
};

#define animus_destroy_zocl 119
struct _animus_destroy_zocl {

	WORD wIndex;
	DWORD dwSerial;
	BYTE byDestroyCode;
};

#define tower_destroy_zocl 120
struct _tower_destroy_zocl {	

	WORD wIndex;
	DWORD dwSerial;

//#define tower_des_type_back			0	//È¸¼ö
//#define tower_des_type_destroy		1	//ÆÄ±«
//#define tower_des_type_disconnect	2	//¼³Ä¡ÀÚ °ÔÀÓÁ¾·á

	BYTE byDestroyCode;	//¸Â¾ÆÁ×³ª..È¸¼ö³Ä..
};

#define itembox_destroy_zocl 18
struct _itembox_destroy_zocl{

	WORD wIndex;
};

#define parkingunit_destroy_zocl 188
struct _parkingunit_destroy_zocl{

	WORD wObjIndex;
	DWORD dwObjSerial;
	BYTE byDestroyCode;//#define unit_destory_type_return	0	//ÀÔ°í#define unit_destory_type_take		1	//½ÂÂ÷
};

#define other_shape_request_clzo 19
struct _other_shape_request_clzo	{

	WORD wIndex;	//´ë»óÄ³¸¯ÅÍÀÇ ÀÎµ¦½º
	
	enum { SHAPE_ALL = 0, SHAPE_PART };

	BYTE byReqType;	//¿ä±¸À¯Çü(0ÀÌ¸é Ã·º¸´Â »ó´ë(other_shape_all_zocl). 1ÀÌ¸é ´Ù½Ã¸¸³­ ¹öÁ¯ÀÌ ´Ù¸¥ »ó´ë)..
};

#define other_shape_all_zocl 20
struct _other_shape_all_zocl	{	//_other_shape_request_clzoÀÇ °á°ú·Î Ã·º¸´Â »ó´ëÀÏ°æ¿ì..	

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;
		
	BYTE byRecIndex;
	BYTE byFaceIndex;	
	BYTE byHairIndex;
	WORD wModelPerPart[equip_fix_num];//»óÀ§ 4ºñÆ®.. ¾÷±×·¹ÀÌµå·¹º§..  ºñÂø¿ë 0xFFFF
	BYTE byUserGrade;	//À¯Àúµî±Þ 
	char szName[max_name_len+1];	

	BYTE byUnitFrameIndex;	//¾ÈÅ¸°íÀÖÀ¸¸é 0xFF..
	BYTE byUnitPartIndex[UNIT_PART_NUM];	//byUnitFrameIndexÀÌ 0xFF¸é ¹«½Ã..

	_other_shape_all_zocl(){
		byUnitFrameIndex = 0xFF;
	}

	int size(){
		if(byUnitFrameIndex != 0xFF) return sizeof(*this);
		return sizeof(*this) - sizeof(byUnitPartIndex);
	}
};

#define other_shape_part_zocl 21
struct _other_shape_part_zocl	{		//_other_shape_request_clzoÀÇ °á°ú·Î ¹öÁ¯ÀÌ ¹Ù²ï »ó´ëÀÏ°æ¿ì..

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;
		
	WORD wModelPerPart[equip_fix_num];	//»óÀ§ 4ºñÆ®.. ¾÷±×·¹ÀÌµå·¹º§..  ºñÂø¿ë 0xFFFF

	BYTE byUnitFrameIndex;	//¾ÈÅ¸°íÀÖÀ¸¸é 0xFF..
	BYTE byUnitPartIndex[UNIT_PART_NUM];	//byUnitFrameIndexÀÌ 0xFF¸é ¹«½Ã..

	_other_shape_part_zocl(){
		byUnitFrameIndex = 0xFF;
	}

	int size(){
		if(byUnitFrameIndex != 0xFF) return sizeof(*this);
		return sizeof(*this) - sizeof(byUnitPartIndex);
	}
};

#define other_shape_failure_zocl 22
struct _other_shape_failure_zocl	{		//_other_shape_request_clzoÀÇ °á°ú·Î ¿¡·¯¸®ÅÏ

	WORD wOtherIndex;

	enum { NOT_LIVE = 0, NOT_SERIAL };

	BYTE byErrCode;
};

#define other_shape_change_zocl 23
struct _other_shape_change_zocl	{	//ÁÖÀ§ ÇÃ·¹ÀÌ¾î°¡ ÀåÂøÀ» ¹Ù²Û°æ¿ì

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;

	BYTE byPartIndex;
	WORD wItemIndex;	//»óÀ§ 4ºñÆ®.. ¾÷±×·¹ÀÌµå·¹º§..  
};

#define other_unit_ride_change_zocl 233
struct _other_unit_ride_change_zocl	{	//ÁÖÀ§ ÇÃ·¹ÀÌ¾î°¡ À¯´Ö ½ÂÇÏÂ÷¸¦ ¹Ù²Û°æ¿ì

	WORD	wIndex;
	DWORD	dwSerial;
	WORD	wEquipVer;

	bool	bTake;				//½ÂÂ÷´Â true, ÇÏÂ÷´Â false
	DWORD	dwUnitSerial;		//¸ð¸£´Â ½Ã¸®¾óÀÇ °æ¿ì.. ¹Ù±ù ¼½ÅÍ¿¡ ÀÖ´Â À¯´Ö.. ÇÃ·¹ÀÌ¾îµµ ¼½ÅÍ¹ÛÀ¸·Î »©¹ö¸®°í.. ³ªÁß¿¡ ¸¸³ª¸é _other_shape_part_zocl·Î »õ·Î¹Þ´Â´Ù..
	short	zNewPos[3];			//½ÂÇÏÂ÷ »ÇÁö¼ð..
};

//ÀÚ½ÅÀÌ »õ·Î¿î°÷ÀÌ »ÐÇÏ°í ³ªÅ¸³¯¶§.. ÁÖÀ§ÀÇ ÇÃ·¹ÀÌ¾î¿¡°Ô »Ñ¸°´Ù.
#define other_new_view_zocl 24
struct _other_new_view_zocl{	

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;
	short zPos[3];
	BYTE byRaceCode;

	//byViewType----
	//#define mapin_type_start		0	//°ÔÀÓ½ÃÀÛ		
	//#define mapin_type_move		1	//Æ÷Å»ÀÌµ¿..
	//#define mapin_type_revival	2	//ºÎÈ°
	//#define mapin_type_goto		3	//¼ø°£ÀÌµ¿
	//#define mapin_type_recall     4	//Ãâµ¿..

	BYTE byViewType;
	DWORD dwStateFlag;
	WORD wLastEffectCode;
};

#define player_revival_request_clzo 28
struct _player_revival_request_clzo{

};

#define player_revival_zocl 29
struct _player_revival_zocl{

	BYTE byRet;
	WORD wStartMapIndex;
	short zPos[3];
	BYTE byLevel;
	WORD wCurHP;
	WORD wCurFP;
	WORD wCurST;	
	BYTE byZoneCode;	//0ÀÌ¸é °°Àº Á¸.. 1ÀÌ¸é ´Ù¸¥Á¸.. => move_outÀ» º¸³½´Ù.
};

#define other_map_out_zocl 30
struct _other_map_out_zocl{

	BYTE byMapOutType;
	DWORD dwSerial;
	BYTE byNextMap;	//³ª°¡¼­ »õ·Î µé¾î°¥¸Ê..¸ð¸£´Â°æ¿ì´Â 0xFF
};

//ºÎÈ°..
#define player_resurrect_zocl 31
struct _player_resurrect_zocl{

	BYTE byRet;
	BYTE byLevel;
	WORD wCurHP;
	WORD wCurFP;
	WORD wCurST;
};

#define exit_save_data_request_clzo 32
struct _exit_save_data_request_clzo {		//¹Ù²ï°Í¸¸À¸·Î..º¯°æ..

	WORD wDataSize;

//inven ÀúÀå¼ö[1], { serial[2], client_index[1] }
///belt ÀúÀå¼ö[1], { serial[2], client_index[1] }
///link ÀúÀå¼ö[1], { effectcode[1], effectindex[1], client_index[1] }
///embell ÀúÀå¼ö[1], { serial[2], client_index[1] }

	char sData[0x0FFF];

	int size(){
		return sizeof(*this)-sizeof(char)*(0x0FFF-wDataSize);
	}			
};

#define exit_save_data_result_zocl 33
struct _exit_save_data_result_zocl {
	
	BYTE byRetCode;	//0;//¼º°ø, 1;//½Ã¸®¾óÆ²¸² 2;//ÀÌ¹ÌÀÎµ¦½ÌÇßÀ½

};

#define stat_inform_zocl	34
struct _stat_inform_zocl {

	BYTE byStatIndex;
	DWORD dwNewStat;
};

#define fcitem_inform_zocl	35
struct _fcitem_inform_zocl {

	WORD wItemSerial;
	DWORD dwNewStat;
};

//
//position_msg..	4
//

#define move_request_clzo 1
struct _move_request_clzo{

	BYTE byMoveType;
	BYTE byModeType;
	short zCur[3];	//xyz
	short zTar[2];	//xz
};

#define real_movpos_request_clzo 2
struct _real_movpos_request_clzo {

	short zCur[3];	//xyz
};

#define move_error_result_zocl 22
struct _move_error_result_zocl {

	BYTE byErrCode;
	short zCur[3];	//xyz..¼­¹ö»óÀÇ À§Ä¡..
};

#define player_move_zocl 4
struct _player_move_zocl{	

	DWORD dwSerial;
	WORD wIndex;
	WORD wEquipVer;	
	BYTE byRaceCode;
	WORD wLastEffectCode;	
	DWORD dwStateFlag;
	short zCur[3];//xyz
	short zTar[2];	//xz
	BYTE byAddSpeed;
};

#define monster_move_zocl 5
struct _monster_move_zocl{ 

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	WORD wLastEffectCode;
	short zCur[3];
	short zTar[2];	//x,z
	WORD wHPRate;
	BYTE byInfo[4];
};

#define npc_move_zocl 106
struct _npc_move_zocl { 

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	WORD wLastEffectCode;		
	short zCur[3];
	short zTar[2];	//x,z
};

#define animus_move_zocl 107
struct _animus_move_zocl {	

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zCur[3];
	short zTar[2];
	WORD wHPRate;
	WORD wLastEffectCode;	
};

#define monster_chase_zocl 6
struct _monster_chase_zocl{

	WORD wRecIndex;
	WORD wIndex;
	WORD wDstIndex;
	BYTE byLastEffectCode;	
	short zCur[3];
	short zTar[2]; //x,z
	WORD wHPRate;
};

#define player_fixpositon_zocl 7
struct _player_fixpositon_zocl{

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;	

	BYTE byRaceCode;
	short zCur[3];
	WORD wLastEffectCode; //ÃÖ±Ù¿¡ °É¸° È¿°úÄÚµå..(¿ÞÂÊ 4ºñÆ®.. È¿°úÄÚµå(effect_code_skill, effect_code_force, effect_code_class).. ´ÙÀ½ºÎÅÍ´Â ÀÎµ¦½º..
	DWORD dwStateFlag;
};

#define object_real_fixpositon_zocl 77
struct _object_real_fixpositon_zocl{	

	BYTE byObjKind;
	BYTE byObjID;
	WORD wIndex;
	DWORD dwSerial;
};

#define monster_fixpositon_zocl 8
struct _monster_fixpositon_zocl{

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	WORD wLastEffectCode;		
	short zCur[3];
	WORD wHPRate;
	BYTE byInfo[4];	
};

#define npc_fixpositon_zocl 109
struct _npc_fixpositon_zocl {

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	WORD wLastEffectCode; 
	short zCur[3];
};

#define animus_fixpositon_zocl 110
struct _animus_fixpositon_zocl {	

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zCur[3];
	WORD wHPRate;
	BYTE byLv;	
	WORD wLastEffectCode;	
};

#define tower_fixpositon_zocl	111
struct _tower_fixpositon_zocl {	

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zCur[3];
	WORD wCompLeftSec;	//´Ù Áþ±âÀ§ÇØ ³²Àº½Ã°£..(0ÀÌ¸é ´Ù ÁöÀº Å¸¿ö)
};

#define itembox_fixpositon_zocl 9	
struct _itembox_fixpositon_zocl{

	BYTE byItemTableCode;
	WORD wItemRecIndex;
	BYTE byAmount;	//ÁßÃ¸¾ÆÀÌÅÛÀÏ°æ¿ì ¼ö·®
	WORD wItemBoxIndex;
	DWORD dwOwerSerial;	//´©°¡ ¹ö¸°°Ç 0xffff
	short zPos[3];
	BYTE byState;	//0: normal(ÁöÁ¤ÀÚ¸¸ÀÌ ¸ÔÀ»¼öÀÕ´Â»óÅÂ) 
					//1: open(´©±¸µçÁö ¸ÔÀ»¼ö ÀÖ´Â »óÅÂ) 
					//2: hurry(¼Ò¸êÀÓ¹Ú,±ôºýÀÓ)
};

#define parkingunit_fixpositon_zocl 99	
struct _parkingunit_fixpositon_zocl{

	WORD wObjIndex;
	DWORD dwObjSerial;
	BYTE byFrame;
	BYTE byPart[UNIT_PART_NUM];
	short zPos[3];
};

#define correct_position_zocl 10
struct _correct_position_zocl {

	BYTE byMapIndex;
	short sPos[3];
};

#define monster_stop_zocl 11
struct _monster_stop_zocl {

	WORD wIndex;
	short zCur[3];
};

#define player_stop_clzo 12
struct _player_stop_clzo {

	short zCur[3];
};

#define player_stop_zocl 13
struct _player_stop_zocl {

	DWORD dwSerial;
	short zCur[3];
};

#define player_real_move_zocl 14
struct _player_real_move_zocl {	

	WORD wIndex;
	DWORD dwSerial;
	WORD dwEquipVer;

	BYTE byRaceCode;
	short zCur[3];
	short zTar[2];	
	WORD wLastEffectCode; //ÃÖ±Ù¿¡ °É¸° È¿°úÄÚµå..(¿ÞÂÊ 1ºñÆ®.. È¿°úÄÚµå(effect_code_skill, effect_code_force..).. ´ÙÀ½ºÎÅÍ´Â ÀÎµ¦½º.. 
	DWORD dwStateFlag; 
	BYTE byAddSpeed;	//È¿°ú·ÎÀÎÇÑ Áõ°¡µÅ´Â ÀÌµ¿¼Óµµ
};

#define monster_real_move_zocl 15
struct _monster_real_move_zocl {		

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	WORD wLastEffectCode;		
	short zCur[3];
	short zTar[2];
	WORD wHPRate;
	BYTE byInfo[4];
};

#define npc_real_move_zocl 116
struct _npc_real_move_zocl {		

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	WORD wLastEffectCode;
	short zCur[3];
	short zTar[2];
};

#define animus_real_move_zocl 117
struct _animus_real_move_zocl {	

	WORD wRecIndex;
	WORD wIndex;
	DWORD dwSerial;
	short zCur[3];
	short zTar[2];
	WORD wHPRate;
	BYTE byLv;	
	WORD wLastEffectCode;
};

#define state_inform_zocl 16	
struct _state_inform_zocl {		

	DWORD dwSerial;
	DWORD dwState;
};

#define goto_baseportal_request_clzo 17
struct _goto_baseportal_request_clzo {

	WORD wItemSerial;	//town item ½Ã¸®¾ó(0xFFFF¸é Á¾Á·ÃÊ±âÀ§Ä¡..¹ßÀÚ¹öÁ¯) 
};

#define goto_baseportal_result_zocl 18
struct _goto_baseportal_result_zocl {

	BYTE byRet;//0;//¼º°ø//1;//½ÃÃ¼»óÅÂÀÓ 2;//Æ÷Å»À»¸øÀÐÀ½ 3;//ÁÂÇ¥ ¸ø¾òÀ½ 4;//´Ù¸¥Á¾Á·¸É
	BYTE byMapCode;	
	short zPos[3];
};

#define goto_avator_request_clzo 19
struct _goto_avator_request_clzo {		

	char szAvatorName[max_name_len+1];
};

#define goto_avator_result_zocl 20	
struct _goto_avator_result_zocl {	

	BYTE byRet;//0;//¼º°ø//1;//´ô¸¥Á¸¿¡ ÀÖÀ½ 2;//¾øÀ½
	BYTE byMapCode;
	float fStartPos[3];
};

#define break_stop_result_zocl 21
struct _break_stop_result_zocl {	//..³ôÀÌµîÀÇ ¹®Á¦¶«¿¡ Áß°£¿¡ ¸ØÃç¾ßÇÏ´Â°æ¿ì..

	BYTE byObjID;	
	DWORD dwObjSerial;
	short zCur[3];
};

#define move_type_change_request_clzo 222
struct _move_type_change_request_clzo {	

	BYTE byMoveType;	//	move_type_walk:0, move_type_run:1 
};

//
//fight_msg..	5
//
#define attack_gen_request_clzo 1
struct _attack_gen_request_clzo {

	BYTE byID;			
	WORD wIndex;
	BYTE byAttPart;		
	WORD wBulletSerial;	//	==> bullet°ú ¹«°üÇÑ °ø°ÝÀÌ¸é 0xFF
};

#define attack_skill_request_clzo 5
struct _attack_skill_request_clzo {	

	BYTE byID;				
	WORD wIndex;
	BYTE byEffectCode;	//	effect_code_skill, effect_code_class ..		
	WORD wSkillIndex;
	WORD wBulletSerial;		//bullet ¹«°ü : 0xFFFF
};

#define attack_force_request_clzo 9
struct _attack_force_request_clzo {

	BYTE byID;
	WORD wIndex;		//Áö¿ª±â¶ó¸é 0xFFFF	
	short zAreaPos[2];	//x, z
	WORD wForceSerial;
};

#define attack_unit_request_clzo 240
struct _attack_unit_request_clzo {		

	BYTE byID;
	WORD wIndex;		//Áö¿ª±â¶ó¸é 0xFFFF	

	//#define unit_bullet_arms			0
	//#define unit_bullet_shoulder		1
	BYTE byWeaponPart;	
};

#define attack_test_request_clzo 105
struct _attack_test_request_clzo{

	BYTE	byEffectCode;
	BYTE	byEffectIndex;
	WORD	wBulletSerial;		//bullet ¹«°ü : 0xFFFF
	BYTE	byWeaponPart;		//À¯´ÖÀÏ°æ¿ì.. À¯´ÖÅ¾½Â»óÅÂÀÏ°æ¿ì¹Ý´ë½Ã ¼¼ÆÃ.. À§¿¡²¨´Â ½Î±×¸®¹«½Ã.
	short	zTar[2];

	_attack_test_request_clzo()	{
		byEffectCode = 0xFF;
		byEffectIndex = 0xFF;
		wBulletSerial = 0xFFFF;
		byWeaponPart = 0xFF;
	}
};

#define attack_error_result_zocl 255
struct _attack_error_result_zocl {	

	char sFailureCode;
};

#define attack_gen_result_zocl 254
struct _attack_gen_result_zocl {	

	_CHRID idAtter;	
	BYTE byAttackPart;
	BYTE byBulletIndex;
	bool bCritical;		//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	BYTE byListNum;

	struct _dam_list{
		_CHRID idDster;	
		WORD wDamage;  //µ¥¹ÌÁö		.. 0ÀÌ¸é ¹Ì½º, 0xFFFF¸é ¹Ý°Ý±â°É¸°»óÅÂ¸¦ Ä§..
		WORD wLeftHP;
	};

	_dam_list DamList[32];
	
	int size(){
		return sizeof(*this)-sizeof(_dam_list)*(32-byListNum);
	}
};	

#define attack_skill_result_zocl 253
struct _attack_skill_result_zocl {	

	_CHRID idAtter;	
	BYTE byEffectCode;	//	effect_code_skill, effect_code_class ..		
	WORD wSkillIndex;	//	
	BYTE bySkillLv;	//add
	BYTE byAttackPart;
	BYTE byBulletIndex;
	bool bCritical;		//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	BYTE byListNum;

	typedef _attack_gen_result_zocl::_dam_list _dam_list;

	_dam_list DamList[32];
	
	int size(){
		return sizeof(*this)-sizeof(_dam_list)*(32-byListNum);
	}
};	

#define attack_force_result_zocl 252
struct _attack_force_result_zocl {	

	_CHRID idAtter;	
	BYTE byForceIndex;
	BYTE byForceLv;		
	short zAreaPos[2];	//Áö¿ª±âÀÏ°æ¿ì Å¸°ÙÁ¡
	BYTE byAttackPart;
	bool bCritical;		//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	BYTE byListNum;

	typedef _attack_gen_result_zocl::_dam_list _dam_list;

	_dam_list DamList[32];
	
	int size(){
		return sizeof(*this)-sizeof(_dam_list)*(32-byListNum);
	}
};	

#define attack_unit_result_zocl 251
struct _attack_unit_result_zocl {	

	_CHRID idAtter;	
	BYTE byWeaponPart;
	WORD wWeaponIndex;
	BYTE byBulletIndex;			
	BYTE byAttackPart;
	bool bCritical;		//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	BYTE byListNum;

	typedef _attack_gen_result_zocl::_dam_list _dam_list;

	_dam_list DamList[32];
	
	int size(){
		return sizeof(*this)-sizeof(_dam_list)*(32-byListNum);
	}
};	

#define attack_count_result_zocl 250
struct _attack_count_result_zocl {	

	_CHRID idAtter;	
	BYTE byAttackPart;
	bool bCritical;		//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	BYTE byListNum;

	typedef _attack_gen_result_zocl::_dam_list _dam_list;

	_dam_list DamList[32];
	
	int size(){
		return sizeof(*this)-sizeof(_dam_list)*(32-byListNum);
	}
};

#define attack_test_result_zocl 104
struct _attack_test_result_zocl{

	_CHRID	idAtter;	
	BYTE	byBulletIndex;	// => 0xFF ¹«°ü..	
	BYTE	byEffectCode;	// È¿°úÄÚµå.. 0xFF¸é ÀÏ¹Ý°ø°Ý
	BYTE	byEffectIndex;	//ÀÏ¹ÝÀÌ¸é ¹«½Ã..
	BYTE	byEffectLv;
	BYTE	byWeaponPart;	//unitÀÇ °æ¿ì..	
	short	zTar[2];
};			

#define attack_monster_inform_zocl 249
struct _attack_monster_inform_zocl{		
	
	_CHRID	idAtter;		
	BYTE	byAttackPart;	
	bool	bCritical;			//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	_CHRID	idDst;		
	WORD	wDamage;
	WORD	wLeftHP;
};	

#define attack_animus_inform_zocl 248
struct _attack_animus_inform_zocl{		
	
	_CHRID	idAtter;		
	BYTE	byAttackPart;	
	bool	bCritical;			//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	_CHRID	idDst;		
	WORD	wDamage;
	WORD	wLeftHP;
};	

#define attack_tower_inform_zocl 136
struct _attack_tower_inform_zocl{		
	
	_CHRID	idAtter;		
	BYTE	byAttackPart;	
	bool	bCritical;			//1ÀÌ¸é Å©¸®Æ¼ÄÃ°ø°Ý

	_CHRID	idDst;		
	WORD	wDamage;
	WORD	wLeftHP;	
};	

#define monster_chase_change_zocl 13	//all
struct _monster_chase_change_zocl{

	WORD	wMonIndex;
	short	zDstIndex; //-1Àº NULL
};

#define mode_change_request_clzo 14
struct _mode_change_request_clzo{

	BYTE	byModeCode;	//	ÆòÈ­¸ðµå:0, ÀüÅõ¸ðµå:1 
};

#define mode_change_result_zocl 15
struct _mode_change_result_zocl{	

	BYTE	byModeCode;	//	ÆòÈ­¸ðµå:0, ÀüÅõ¸ðµå:1 
};

#define breakdown_equip_item_zocl 16
struct _breakdown_equip_item_zocl{

	WORD	wPlayerIndex;	
	DWORD	dwPlayerSerial;
	WORD	dwEquipVer;

	BYTE	byPartIndex;
	WORD	wItemSerial;
};

#define shield_equip_dur_dec_zocl 17
struct _shield_equip_dur_dec_zocl{

	BYTE	byPartIndex;
	WORD	wSerial;
	WORD	wLeftDurPoint;
};

#define alter_weapon_bullet_inform_zocl 247	
struct _alter_weapon_bullet_inform_zocl {

	WORD	wItemSerial;
	WORD	wLeftNum;
};

#define alter_unit_bullet_inform_zocl 246	
struct _alter_unit_bullet_inform_zocl {

	BYTE	byPart;
	WORD	wLeftNum;
};

//
//item_msg	7
//

#define itembox_state_change_zocl 1
struct _itembox_state_change_zocl{

	WORD wItemBoxIndex;
	DWORD dwOwerSerial;	//´©°¡ ¹ö¸°°Ç oxffff 
	BYTE byState;	//0: normal(ÁöÁ¤ÀÚ¸¸ÀÌ ¸ÔÀ»¼öÀÕ´Â»óÅÂ) 
					//1: open(´©±¸µçÁö ¸ÔÀ»¼ö ÀÖ´Â »óÅÂ) 
					//2: hurry(¼Ò¸êÀÓ¹Ú,±ôºýÀÓ)
};

#define itembox_take_request_clzo 2	
struct _itembox_take_request_clzo{

	WORD wItemBoxIndex;
	WORD wAddSerial;	//Æ÷°³Áö´Â ¾ÆÀÌÅÛÀÏ°æ¿ì Æ÷°¶ ½Ã¸®¾ó.. Æ÷°¶°÷ÀÌ ¾øÀ¸¸é 0xFFFF
};

#define itembox_take_new_result_zocl 3		//_itembox_take_request_clzoÀÇ wAddSerialÀÌ 0xFFFFÀÎ°æ¿ì..
struct _itembox_take_new_result_zocl{		
	
	char sErrorCode;	//1;//ºó°ø°£¾øÀ½ 2;//±âÁ¸¾ÆÅÛ¾øÀ½ 3;//¸¸¶¥ÀÓ 4;//¾ø´Â¹Ú½º 5;//±ÇÇÑÁ¦ÇÑ 6;//°Å¸®Á¦ÇÑ
	BYTE byItemTableCode;
	WORD wItemIndex;
	DWORD dwCurDurPoint; 
	DWORD dwUptInfo;
	WORD wItemSerial;	

	int size(){
		if(sErrorCode != 0)
			return sizeof(sErrorCode);
		return sizeof(*this);
	}
};

#define itembox_take_add_result_zocl 4		//_itembox_take_request_clzoÀÇ wAddSerialÀ» ³ÖÀº°æ¿ì..
struct _itembox_take_add_result_zocl{		
	
	char sErrorCode;	//1;//ºó°ø°£¾øÀ½ 2;//±âÁ¸¾ÆÅÛ¾øÀ½ 3;//¸¸¶¥ÀÓ 4;//¾ø´Â¹Ú½º 5;//±ÇÇÑÁ¦ÇÑ 6;//°Å¸®Á¦ÇÑ
	WORD wItemSerial;	
	BYTE byAmount;

	int size(){
		if(sErrorCode != 0)
			return sizeof(sErrorCode);
		return sizeof(*this);
	}
};

#define throw_storage_request_clzo 5
struct _throw_storage_request_clzo{

	_STORAGE_POS_INDIV Item;
};

#define throw_storage_result_zocl 6
struct _throw_storage_result_zocl{	

	BYTE byErrCode;	//0;//¼º°ø, 1;//ÀúÀåÀ§Ä¡Æ²¸² 2;//¾ø´Â¾ÆÅÆ 3;//¼ö·®ÃÊ°ú
};

#define use_potion_request_clzo 7
struct _use_potion_request_clzo{	
	
	_STORAGE_POS_INDIV Item;	
};

#define use_potion_result_zocl 8
struct _use_potion_result_zocl{	//one	

	BYTE byErrCode;	//0;//¼º°ø, //1;//ÀúÀåÀ§Ä¡Æ²¸² 2;//¾ø´Â¾ÆÅÆ 3;//Æ÷¼Ç¾Æ´Ô 4;//¼ö·®ÃÊ°ú 5;//È¸º¹Àá±è»óÅÂ 6;//ÀÌ¹ÌÁ×Àº»óÅÂ
	WORD wPotionSerial;	
	WORD wHP;
	WORD wFP;
	WORD wSP;
	BYTE byLeftNum;		//add(4/19)
};

#define equip_part_request_clzo 9
struct _equip_part_request_clzo{

	_STORAGE_POS_INDIV Item;	
};

#define equip_part_result_zocl 10	
struct _equip_part_result_zocl{

	BYTE byErrCode;	//0;//¼º°ø, //1;//ÀúÀåÀ§Ä¡Æ²¸² 2;//¾ø´Â¾ÆÅÆ 3;//ÀåÂø¾ÆÀÌÅÛ¾Æ´Ô 4;//»ç¿ëÇÒ¼ö¾ø´ÂÁ¾Á· 5;//¹æÆÐµé¾úÀ½ 6;//¾ç¼Õ¹«±âµé¾úÀ½
};

#define embellish_request_clzo 11	//¹ÝÁö, ¸ñ°ÉÀÌ, ÃÑ¾Ë..Âø¿ë
struct _embellish_request_clzo{	

	_STORAGE_POS_INDIV Item;
	WORD wChangeSerial;	//¹Ù²Ù´Â°Å¶ó¸é ¹þ±æ ¾ÆÀÌÅÛÀÇ ½Ã¸®¾ó.. ¾Æ´Ï¸é 0xFFFF
};

#define embellish_result_zocl 12
struct _embellish_result_zocl{	

	BYTE byErrCode;	//0;//¼º°ø,
};

#define off_part_request_clzo 13
struct _off_part_request_clzo{	

	_STORAGE_POS_INDIV Item;
};

#define off_part_result_zocl 14
struct _off_part_result_zocl{

	BYTE byErrCode;	//0;//¼º°ø, 
};	

//Á¦ÀÛ ½ºÅ³»ç¿ëÀü¿¡ ¿ä°Å¸ÕÀú º¸³»¾ßÇÑ´ô.
#define make_item_request_clzo 15
struct _make_item_request_clzo{		

	enum { material_num = 5	};

	_STORAGE_POS_INDIV ipMakeTool;	//Á¦ÀÛÅøÀÌ ÀÖ´Â À§Ä¡
	WORD wManualIndex;			//Á¦ÀÛ¸Þ´º¾óÀÎµ¦½º

	BYTE byMaterialNum;			//»ç¿ëÇÒ Àç·á¼ö
	_STORAGE_POS_INDIV ipMaterials[material_num];	//»ç¿ëÇÒ Àç·á°¡ ÀÖ´Â À§Ä¡

	_make_item_request_clzo(){
		byMaterialNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_STORAGE_POS_INDIV)*(material_num-byMaterialNum);
	}
};

//¿ä°Å¹ÞÀº°Å È®ÀÎÇÏ°í Á¦ÀÛ½ºÅ³½ÃÀü..
#define make_item_result_zocl 16
struct _make_item_result_zocl{	

	BYTE byErrCode;
};

#define upgrade_item_request_clzo 17
struct _upgrade_item_request_clzo {

	_STORAGE_POS_INDIV m_posUpgItem;	
	_STORAGE_POS_INDIV m_posTalik;
	_STORAGE_POS_INDIV m_posToolItem;

	BYTE byJewelNum;
	_STORAGE_POS_INDIV m_posUpgJewel[upgrade_jewel_num];

	_upgrade_item_request_clzo(){
		byJewelNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_STORAGE_POS_INDIV)*(upgrade_jewel_num-byJewelNum);
	}
};

#define upgrade_item_result_zocl 18
struct _upgrade_item_result_zocl {

	BYTE byErrCode;///1;//¾ø´Â¾ÆÀÌÅÛ 2;//¾÷±Û¸¸¶¥ÇßÀ½ 3;//¾÷±Û¾ÈµÅ´Â ¾ÆÀÌÅÛ 
					//5;//´õÀÌ»óÇØ´çÅ»¸¯À»Ãß°¡ÇÒ¼ö¾øÀ½ 6;//ÀÌ¾ÆÀÌÅÛ¿¡´ÂÇØ´çÅ»¸¯À»Ãß°¡ÇÒ¼ö¾øÀ½
					//100;//·£´ý½ÇÆÐ, 101;//±âÁ¸Å»¸¯ÆÄ±« 102;//¾ÆÀÌÅÛÆÄ±«
};

#define downgrade_item_request_clzo 19
struct _downgrade_item_request_clzo {	

	_STORAGE_POS_INDIV m_posUpgItem;	
	_STORAGE_POS_INDIV m_posTalik;
	_STORAGE_POS_INDIV m_posToolItem;
};

#define downgrade_item_result_zocl 20
struct _downgrade_item_result_zocl {

	BYTE byErrCode;////1;//¾ø´ÂÅ»¸¯ 2;//Àß¸ø‰ÂÅ»¸¯ 3;//¾ø´ÂÅø 4;//¾ø´Â¾ÆÀÌÅÛ 5;//¾÷±Û¾ÈµÅ´Â ¾ÆÀÌÅÛ 6;//¾÷±Û‰Â¾ÆÅÛ¾Æ´?
};

#define add_bag_request_clzo 21	
struct _add_bag_request_clzo {	

	WORD wBagItemSerial;
};

#define add_bag_result_zocl 22
struct _add_bag_result_zocl {	

	BYTE byErrCode; //0;//¼º°ø, 1;//¾ø´Â°¡¹æ 2;//5°³´Ù¾²°íÀÖÀ½
};

#define delete_storage_inform_zocl 23
struct _delete_storage_inform_zocl {

	BYTE byStorageCode;
	WORD wSerial;
};

#define storage_refresh_inform_zocl 24
struct _storage_refresh_inform_zocl {

	BYTE byStorageCode;
	BYTE byItemNum;
	WORD wSerial[100];

	_storage_refresh_inform_zocl() {	byItemNum = 0;	}

	int size() {	return sizeof(*this)-sizeof(WORD)*(100-byItemNum);	}
};

#define alter_item_dur_zocl 25	
struct _alter_item_dur_zocl {

	BYTE	byStorageCode;
	WORD	wItemSerial;
	DWORD	dwDur;
};

//
//map_msg..	8
//
#define move_potal_request_clzo 1
struct _move_potal_request_clzo{

	BYTE byPotalIndex;	
};

#define move_potal_result_zocl 2
struct _move_potal_result_zocl{

	BYTE byRet;	////1;//Àß¸ø‰ÂÆ÷Å»¹øÈ?2;//Æ÷Å»°ú¸ÕÀ§Ä¡ 3;//Àß¸ø‰Â¸ÊÄÚµ?4;//Àß¸ø‰ÂÆ÷Å»ÄÚµ?5;//¿¬°áÁÂÇ¥¿µ¿ª¿¡·¯ 
	BYTE byMapIndex;	//ÇöÀç ¸Ê°ú ´Ù¸¥°æ¿ì »õ·Î¿î ¸ÊÀ» ·Îµå.. ·ÎµåÈÄ ·Îµå¿Ï·á ¸Þ½ÃÁö¸¦ º¸³»¾ßÇÔ
	float fStartPos[3];
	BYTE byZoneCode;	//0ÀÌ¸é °°Àº Á¸.. 1ÀÌ¸é ´Ù¸¥Á¸.. => move_outÀ» º¸³½´Ù.
};	

//
//confirm_msg..	9
//

//
//observer_msg.. 10
//
#define observer_move_request_clzo	1
struct _observer_move_request_clzo{

	float fMoveSpeed;
	short zCurPos[3];
	short zTarPos[3];
};

#define observer_move_result_zocl 2
struct _observer_move_result_zocl{

	float fMoveSpeed;
	short zCurPos[3];
	short zTarPos[3];
};


//
//chat_msg.. 2	
//

#define chat_operator_request_clzo 1//CHAT_TYPE_OPERATOR
struct _chat_operator_request_clzo {

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_circle_request_clzo 2//CHAT_TYPE_OPERATOR
struct _chat_circle_request_clzo {

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_whisper_request_clzo 3//CHAT_TYPE_WHISPER
struct _chat_whisper_request_clzo {

	WORD wDstIndex;

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_far_request_clzo 4//CHAT_TYPE_WHISPER
struct _chat_far_request_clzo {

	char szName[max_name_len+1];
	
	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_far_failure_zocl 5//ÇÃ·¹ÀÌ¾î¸¦ ¸øÃ£¾Ñ´Ù..
struct _chat_far_failure_zocl {
};

#define chat_party_request_clzo 6 //CHAT_TYPE_PARTY
struct _chat_party_request_clzo {

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_race_request_clzo 16
struct _chat_race_request_clzo {

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_cheat_request_clzo 7
struct _chat_cheat_request_clzo {

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_manage_request_clzo 77
struct _chat_manage_request_clzo {

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_mgr_whisper_request_clzo 66
struct _chat_mgr_whisper_request_clzo {	

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_message_receipt_udp	8
struct _chat_message_receipt_udp {	

//#define CHAT_TYPE_OPERATOR		0 //¿î¿µÀÚ..
//#define CHAT_TYPE_CIRCLE		1 //ÁÖº¯ÀüÃ¼¿¡..
//#define CHAT_TYPE_WHISPER		2 //½Ã¸®¾ó¹øÈ£¸¦ ¾Æ´Â»ó´ë¿Í ÀÏ´ëÀÏ..
//#define CHAT_TYPE_FAR_WHISPER	3 //½Ã¸®¾ó¹øÈ£¸¦ ¸ð¸£´Â»ó´ë¿Í ÀÏ´ëÀÏ..
//#define CHAT_TYPE_PARTY			4 //ÆÄÆ¼¿øµé¿¡°Ô..
//#define CHAT_TYPE_RACE		5    //µ¿Á·¿¡°Ô

	BYTE byMessageType;	
	DWORD dwSenderSerial;

	BYTE bySize;
	char sChatData[max_message_size];

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define announ_message_receipt_udp	18
struct _announ_message_receipt_udp {

//#define CHAT_TYPE_OPERATOR		0 //¿î¿µÀÚ..
//#define CHAT_TYPE_CIRCLE		1 //ÁÖº¯ÀüÃ¼¿¡..
//#define CHAT_TYPE_WHISPER		2 //½Ã¸®¾ó¹øÈ£¸¦ ¾Æ´Â»ó´ë¿Í ÀÏ´ëÀÏ..
//#define CHAT_TYPE_FAR_WHISPER	3 //½Ã¸®¾ó¹øÈ£¸¦ ¸ð¸£´Â»ó´ë¿Í ÀÏ´ëÀÏ..
//#define CHAT_TYPE_PARTY			4 //ÆÄÆ¼¿øµé¿¡°Ô..
//#define CHAT_TYPE_RACE		5    //µ¿Á·¿¡°Ô
//#define CHAT_TYPE_MGRWSP		6 //¿î¿µÀÚ±Ó¸»

	BYTE byMessageType;	
	char szSenderName[max_name_len+1];	//NULL Æ÷ÇÔ..

	BYTE bySize;
	char sChatData[max_message_size];	//¸»ÇÏ´Â»ç¶÷ ÀÌ¸§ Æ÷ÇÔ

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_lock_inform_zocl	19
struct _chat_lock_inform_zocl {	//add(4/19)

	bool	bLock;	//true¸é ¶ô ¼³Á¤..

	int size(){	return sizeof(*this);	}
};

//
//test_msg.. 0
//

#define socket_check_zocl 0
struct _socket_check_zocl {
};

//
//event_msg 11
//

#define level_up_zocl	1
struct _level_up_zocl{

	DWORD dwSerial;//ÇÃ·¹ÀÌ¾îÀÇ ½Ã¸®¾ó..
	BYTE byLevel;
};	

#define recover_zocl	2
struct _recover_zocl{

	WORD wHP;
	WORD wFP;
	WORD wST;
};

#define max_hfsp_zocl	3
struct _max_hfsp_zocl{	

	WORD wMaxHP;
	WORD wMaxFP;
	WORD wMaxST;
};

#define exp_alter_zocl	4	
struct _exp_alter_zocl	{

	WORD wExpRate;	//¸¸ºÐÀ²..
};	

#define change_class_command_zocl 5	
struct _change_class_command_zocl {		//ÀüÁ÷ ¸í·É

	WORD	wCurClassIndex;

};

#define select_class_request_clzo 6	
struct _select_class_request_clzo {		//class ¼±ÅÃ

	WORD	wSelClassIndex;
};

#define select_class_result_zocl 7	
struct _select_class_result_zocl {		//ÀÚ½Å¿¡°Ô ÀüÁ÷°á°ú

	BYTE	byRetCode;
};

#define change_class_other_zocl 8	
struct _change_class_other_zocl {		//ÁÖº¯¿¡°Ô È¿°úº¸¿©ÁÖ±âÀ§ÇÔ.

	DWORD	dwPlayerSerial;
	WORD	wClassIndex;
};

#define reward_add_item_zocl 9	
struct _reward_add_item_zocl {	//¾ÆÀÌÅÛ º¸»ó(ÀüÁ÷, Äù½ºÆ® º¸»ó)

	BYTE	byTableCode;
	WORD	wItemIndex;
	DWORD	dwDur;
	DWORD	dwLv;
	WORD	wItemSerial;
};

//
//trade_msg 12
//

#define buy_store_request_clzo 3	
struct _buy_store_request_clzo{	

	BYTE byStoreIndex;	//»óÁ¡ ÀÎµ¦½º
	BYTE byBuyNum;	//Ç°¸ñ¼ö

	struct _list{
		BYTE byStorageCode;//ÀÎº¥Åä¸®: 0, Àåºñ: 1 Àå½Ä: 2, º§Æ®:3, Æ÷½º:4
		DWORD dwGoodSerial;//ÀÏ¹ÝÀº ÀÎµ¦½º
		BYTE byAmount;	
	};

	_list OfferList[trade_item_max_num];	//»óÀ§¹ÙÀÌÆ®:»óÇ°¹øÈ£, ÇÏÀ§¹ÙÀÌÆ®:»ì°¹¼ö

	_buy_store_request_clzo(){
		byBuyNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-byBuyNum);
	}
};

#define buy_store_success_zocl 4
struct _buy_store_success_zocl{

	DWORD dwLeftDalant;	//³²Àº ´Þ¶õÆ®	
	DWORD dwLeftGold;	//³²Àº °ñµå		
	DWORD dwConsumDanlant;	//¼Ò¸ð ´Þ¶õÆ®	
	DWORD dwConsumGold;	//¼Ò¸ð °ñµå		
	BYTE  byDiscountRate;//ÇÒÀÎÀ²(¹éºÐÀ²)

	BYTE byBuyNum;	//Ç°¸ñ¼ö

	struct _list{
		WORD wSerial;
	};

	_list OfferList[trade_item_max_num];

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-byBuyNum);
	}
};

#define buy_store_failure_zocl 5
struct _buy_store_failure_zocl{	//À§ ½ÇÆÐ½Ã ¼±ÅÃÇÑ Ç°¸ñÀÇ °¹¼ö¸¦ º¸³½´Ù

	DWORD dwDalant;	//º¸À¯ÀÚ±Ý
	DWORD dwGold;
	
	BYTE byErrCodeLen;
	char szErrCode[max_error_code_size];

	_buy_store_failure_zocl(){
		byErrCodeLen = 0;	
	}

	int size(){
		return sizeof(*this)-(max_error_code_size-byErrCodeLen);
	}
};

#define sell_store_request_clzo 6
struct _sell_store_request_clzo{	

	WORD wStoreIndex;	//»óÁ¡ ÀÎµ¦½º
	BYTE bySellNum;	//Ç°¸ñ¼ö

	struct _list{
		BYTE byStorageCode;//ÀÎº¥Åä¸®: 0, Àåºñ: 1 Àå½Ä: 2, º§Æ®:3, Æ÷½º:4
		WORD wSerial;
		BYTE byAmount;
	};

	_list Item[trade_item_max_num];	//»óÀ§¿öµå:»óÇ°½Ã¸®¾ó, ÇÏÀ§¹ÙÀÌÆ®:ÆÈ°¹¼ö

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-bySellNum);
	}
};

#define sell_store_result_zocl 7
struct _sell_store_result_zocl{	

	BYTE bSucc;	//true ¸é ¼º°ø
	DWORD dwLeftDalant;	//³²Àº ´Þ¶õÆ®	
	DWORD dwLeftGold;	//³²Àº °ñµå		
	DWORD dwProfitDanlant;	//¹ø ´Þ¶õÆ®	
	DWORD dwProfitGold;	//¹ø °ñµå
	BYTE  byDiscountRate;//ÇÒÀÎÀ²(¹éºÐÀ²) 
	
	BYTE byErrCodeLen;
	char szErrCode[max_error_code_size];

	_sell_store_result_zocl(){
		byErrCodeLen = 0;
	}

	int size(){
		return sizeof(*this)-(max_error_code_size-byErrCodeLen);
	}
};

#define repair_request_clzo 8
struct _repair_request_clzo{

	BYTE byStoreIndex;	//»óÁ¡ ÀÎµ¦½º
	BYTE byItemNum;	//Ç°¸ñ¼ö

	struct _list{
		BYTE byPositon;	//ÀÎº¥Åä¸®: 0, Àåºñ: 1 Àå½Ä: 2, º§Æ®:3, Æ÷½º:4 ¸µÅ©:5..
		WORD wSerial;
	};

	_list Item[trade_item_max_num];	//»óÀ§¿öµå:»óÇ°½Ã¸®¾ó, ÇÏÀ§¹ÙÀÌÆ®:ÆÈ°¹¼ö

	_repair_request_clzo(){
		byItemNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-byItemNum);
	}
};

#define repair_result_zocl 9
struct _repair_result_zocl{	

	BYTE bSucc;	//true ¸é ¼º°ø
	DWORD dwLeftDalant;	//³²Àº ´Þ¶õÆ®	
	DWORD dwLeftGold;	//³²Àº °ñµå		
	DWORD dwConsumDanlant;	//¼Ò¸ð ´Þ¶õÆ®	
	DWORD dwConsumGold;	//¼Ò¸ð °ñµå	
	
	BYTE byErrCodeLen;
	char szErrCode[max_error_code_size];

	_repair_result_zocl(){
		byErrCodeLen = 0;
	}

	int size(){
		return sizeof(*this)-(max_error_code_size-byErrCodeLen);
	}
};

#define store_list_request_clzo 10
struct _store_lis_request_clzo{	
};

#define store_list_result_zocl 11
struct _store_list_result_zocl{	

	enum	{	max_store_per_map = 20 };

	BYTE byStoreNum;

	struct _store_pos{
		WORD wStoreIndex;
		float fPos[3];
	}; 

	_store_pos StorePos[max_store_per_map];

	int size(){
		return sizeof(*this)-sizeof(_store_pos)*(max_store_per_map-byStoreNum);
	}
};

#define exchange_dalant_for_gold_request_clzo 12
struct _exchange_dalant_for_gold_request_clzo {

	DWORD dwDalant;
};

#define exchange_gold_for_dalant_request_clzo 13
struct _exchange_gold_for_dalant_request_clzo {

	DWORD dwGold;
};

#define exchange_money_result_zocl 14		
struct _exchange_money_result_zocl {

	BYTE byErrCode;	//0;//¼º°ø, 1;//±Ý¾×ºÎÁ· 
	DWORD dwLeftGold;		
	DWORD dwLeftDalant;
};

#define economy_history_inform_zocl 15	//	°æÁ¦ÁöÇ¥È÷½ºÅä¸®(Áö±ÞÈ¯À²) Á¢¼Ó½Ã¿¡ ÇÑ¹ø º¸³»ÁÜ
struct _economy_history_inform_zocl {	//upt(4/19).. 

	WORD wEconomyGuide[RACE_NUM][MAX_ECONOMY_HISTORY];	//0~11.. 0: °ú°Å..11: ÃÖ±Ù	//
};

#define economy_rate_inform_zocl 16	//	°æÁ¦ÁöÇ¥(Áö±ÞÈ¯À²) Á¢¼Ó½Ã¿Í º¯°æµÉ¶§¸¶´Ù 3Á¾Á·..
struct _economy_rate_inform_zocl {	

	bool	bStart;	//true¸é Ã· °ÔÀÓ ½ÃÀÛ½Ã ¹Þ´Â°ÍÀ¸·Î wEconomyGuide´Â Àû¿ëÇÏÁö ¾Ê´Â´Ù.. falseÀÏ°æ¿ì¸¸ ¾Æ·¡²¨ Àû¿ëÇØ¼­ history¿¡ Ãß°¡..
	float	fPayExgRate;
	float	fTexRate;
	WORD	wMgrValue;	//°ü¸®°ª	//add(4/22)
	WORD	wEconomyGuide[RACE_NUM];	//upt(4/19)

	int size()	{	if(bStart) return sizeof(*this)-sizeof(wEconomyGuide); return sizeof(*this);	}
};

//
//ui_msg	13
//

#define sf_link_change_result_zocl 2
struct _sf_link_change_result_zocl{

	BYTE bySize;	//0ÀÌ¸é ¼º°ø
	char szErrorCode[max_error_code_size];

	int size(){
		return sizeof(*this)-(max_error_code_size-bySize);
	}
};

#define force_inven_change_request_clzo 3
struct _force_inven_change_request_clzo{	

	_STORAGE_POS_INDIV Item;	
	WORD wReplaceSerial;	//ºó°÷ÀÌµ¿Àº 0xffff
};

#define force_inven_change_result_zocl 4
struct _force_inven_change_result_zocl{	

	BYTE byErrCode;
};

#define animus_inven_change_request_clzo 113
struct _animus_inven_change_request_clzo{		

	_STORAGE_POS_INDIV Item;	
	WORD wReplaceSerial;	//ºó°÷ÀÌµ¿Àº 0xffff
};

#define animus_inven_change_result_zocl 114
struct _animus_inven_change_result_zocl{		

	BYTE byErrCode;
};

#define res_separation_request_clzo 11	//inventoryºó°÷¿¡ ³ª´«´Ù.
struct _res_separation_request_clzo{		

	WORD wStartSerial;
	BYTE byMoveAmount;
};

#define res_separation_result_zocl 12	
struct _res_separation_result_zocl{

	BYTE byErrCode;	//0: ¼º°ø, 1: °¹¼ö¸ðÀÚ¸§ , 2: ÀüºÎÀÌµ¿ÇÔ, 3: ÀÚ¿ø,¿ø¼®ÀÌ¾Æ´Ô 4: ³²ÀºÀÎº¥Åä¸®¾øÀ½, 5: ±×·±½Ã¸®¾ó¾øÀ½ 6: »ç¿ëÇÏÁö¾Ê´Â°¡¹æ
	WORD wParentSerial;
	BYTE byParentAmount;
	WORD wChildSerial;
	BYTE byChildAmount;
};

#define res_division_request_clzo 13	//´Ù¸¥ inventory¿Í ³ª´²¼­ º´ÇÕ½ÃÅ²´Ù.
struct _res_division_request_clzo{	

	WORD wStartSerial;	
	WORD wTarSerial;
	BYTE byMoveAmount;
};

#define res_division_result_zocl 14
struct _res_division_result_zocl{

	BYTE byErrCode;	//0: ¼º°ø, 1: °¹¼ö¸ðÀÚ¸§, 3: ÀÚ¿ø,¿ø¼®ÀÌ¾Æ´Ô, 4: ´õ¸¹Àº¾çÀ»ÀÌµ¿, 5: ±×·±½Ã¸®¾ó¾øÀ½, 6: °°ÀºÁ¾·ùÀÇÀÚ¿ø,¿ø¼®¾Æ´Ô. 7: »ç¿ëÇÏÁö¾Ê´Â°¡¹æ, 8: ´õ¸¹ÀÌÀÌµ¿ÇÔ 9: ÀÌµ¿ÇÒ°÷ÀÌ³ÑÄ§
	WORD wParentSerial;		//0xFFFFÀÌ¸é ½½·Ô»èÁ¦
	BYTE byParentAmount;	
	WORD wChildSerial;		//new serial
	BYTE byChildAmount;
};

#define potionsocket_change_request_clzo 15
struct _potionsocket_change_request_clzo{

	_STORAGE_POS_INDIV Item;
	_STORAGE_POS_INDIV TarPos;//ºóÄ­À¸·Î ÀÌµ¿Àº  _STORAGE_POS_INDIV::wItemSerial = 0xFFFF..
	BYTE byStorageCode;	//upt(4/24).. ¹«Á¶°Ç ºóÄ­À¸·Î ÀÌµ¿..(ydq)
};

#define potionsocket_change_result_zocl 16
struct _potionsocket_change_result_zocl{	

	BYTE byErrCode;	//0: ¼º°ø, 1;//»ç¿ë°¡´É°¡¹æ¾Æ´Ô 2;//Á¸ÀçÇÏÁö¾ÊÀ½ 3;//Æ÷¼Ç¾Æ´Ô 4;//¿Å±æ°ø°£¾øÀ½
};

#define potionsocket_separation_request_clzo 17	//inventoryºó°÷¿¡ ³ª´«´Ù.
struct _potionsocket_separation_request_clzo{		

	struct _pos{
		BYTE byPositon;	//ÀÎº¥Åä¸®: 0, º§Æ®: 1, 
	};

	_pos StartPos;	
	_pos TargetPos;
	WORD wStartSerial;
	BYTE byMoveAmount;

};

#define potionsocket_separation_result_zocl 18
struct _potionsocket_separation_result_zocl{

	char sErrorCode;	//0: ¼º°ø, -1: °¹¼ö¸ðÀÚ¸§ , -2: ÀüºÎÀÌµ¿ÇÔ, -3: Æ÷¼ÇÀÌ ¾Æ´Ï´Ù. -4: ³²Àº ÀÎº¥Åä¸®°¡ ¾ø´Ù, -5: ±×·± ½Ã¸®¾óÀº ¾ø´Ù
	WORD wParentSerial;
	BYTE byParentAmount;
	WORD wChildSerial;
	BYTE byChildAmount;
};

#define potionsocket_division_request_clzo 19	//´Ù¸¥ inventory¿Í ³ª´²¼­ º´ÇÕ½ÃÅ²´Ù.
struct _potionsocket_division_request_clzo{	

	struct _pos{
		BYTE byPositon;	//ÀÎº¥Åä¸®: 0, º§Æ®: 1, 
	};

	_pos StartPos;	
	_pos TargetPos;
	WORD wStartSerial;	
	WORD wTarSerial;
	BYTE byMoveAmount;
};

#define potionsocket_division_result_zocl 20	
struct _potionsocket_division_result_zocl{

	char sErrorCode;	//0: ¼º°ø, -1: °¹¼ö ¸ðÀÚ¸§, -3: Æ÷¼ÇÀÌ ¾Æ´Ï´Ù, -4: ´õ ¸¹Àº ¾çÀ» ÀÌµ¿, -5: ±×·± ½Ã¸®¾óÀº ¾ø´Ù, -6: °°Àº Á¾·ùÀÇ Æ÷¼ÇÀÌ ¾Æ´Ô.
	WORD wSerial;	//½ÇÆÐ¸é byParentAmount ºÎÅÍ 0xffff·Î ¿È
	BYTE byParentAmount;	//0ÀÌ¸é ½½·Ô »èÁ¦
	WORD wChildSerial;	
	BYTE byChildAmount;
};

//
//resource_msg	14
//

#define mine_start_request_clzo 1
struct _mine_start_request_clzo {

	BYTE byMineIndex;//±¤»ê ´õ¹Ì ÀÎµ¦½º 
};

#define mine_start_result_zocl 2
struct _mine_start_result_zocl {

	BYTE byErrCode;	//0: ¼º°ø, 2: ¹üÀ§¿¡·¯, 3: Ã¤±¼Àåºñ¿¡·¯, 4: ÇöÀç Ã¤±¼¸ðµåÀÓ
	DWORD dwMineDelayTime;	//Ã¤±¼½Ã°£	
};

#define mine_cancle_request_clzo 3	
struct _mine_cancle_request_clzo {

	WORD wBatterySerial;	//¹Ù¶¼¸® ½Ã¸®¾ó
};

#define mine_cancle_result_zocl 4
struct _mine_cancle_result_zocl {

	BYTE byErrCode;	//0: ¼º°ø, 1: ¹Ù¶¼¸®¿¡·¯, 3: Áö¿¬½Ã°£ ¿¡·¯ 4:Ã¤±¼Àåºñ¿¡·¯
	WORD wBatteryLeftDur;	//³²Àº ¹Ù¶¼¸® ¿ë·®
	WORD wEquipLeftDur;		//³²Àº Ã¤±¼Àåºñ ³»±¸¼º
};

#define mine_complete_request_clzo 5
struct _mine_complete_request_clzo {

	WORD wBatterySerial;	//¹Ù¶¼¸® ½Ã¸®¾ó			
	BYTE byOreIndex;	//¿ø¼®±¤¹° ÀÎµ¦½º
};

#define mine_complete_result_zocl 6
struct _mine_complete_result_zocl {

	BYTE byErrCode;//0: ¼º°ø, 1: Áö¿¬½Ã°£¿¡·¯, 2: ¿ø¼®°¡¹æ¿¡·¯, 3: ´ãÀ»°ø°£¾øÀ½, 4:¿ø¼®Á¾·ù¿¡·¯,5: º£ÅÍ¸® ¿¡·¯, 6;Ã¤±¼Àåºñ ¿¡·¯
	WORD wEquipLeftDur;		//³²Àº Ã¤±¼Àåºñ ³»±¸¼º
	WORD wBatteryLeftDur;	//³²Àº ¹Ù¶¼¸® ¿ë·®

	BYTE byOreIndex;
	WORD wOreSerial;
	BYTE byOreDur;	//1ÀÌ¸é À§ ½Ã¸®¾óÀº »õ·Î¿î ½Ã¸®¾ó 1ÀÌ»óÀÌ¸é ±âÁ¸ ½Ã¸®¾ó
	
};

#define mine_start_result_other_zocl 22
struct _mine_start_result_other_zocl {

	DWORD	dwSerial;
	WORD	wIndex;
};

#define mine_end_result_other_zocl 33
struct _mine_end_result_other_zocl {

	DWORD	dwSerial;
	WORD	wIndex;
};

#define ore_cutting_request_clzo 7	
struct _ore_cutting_request_clzo {

	BYTE byCuttingHouse;
	WORD wOreSerial;
	BYTE byProcessNum;
};

#define ore_cutting_result_zocl 8
struct _ore_cutting_result_zocl {

	BYTE byErrCode;	//0:¼º°ø 1:¿ø¼® °¡¹æ, ½Ã¸®¾ó½ÇÆÐ 2:¼ö·®½ÇÆÐ 3:¼ÒÁö±ÝºÎÁ· 4:°¡°øÀÓ½Ã°ø°£ ¾Èºñ¿ò 
	BYTE byLeftNum;
	DWORD dwLeftDalant;
	DWORD dwConsumDalant;
	
	BYTE byCuttingNum;

	struct _list {
		WORD wResIndex;		//ÀÚ¿øÀÎ´ì½º
		BYTE byAddAmount;	//Ãß°¡µÇ´Â ¾ç
	};

	_list ResList[100];

	_ore_cutting_result_zocl(){
		byCuttingNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(100-byCuttingNum);
	}
};

#define ore_into_bag_request_clzo 9	
struct _ore_into_bag_request_clzo {

	WORD wResIndex;
	WORD wSerial; //ºó°÷¿¡ ³ÖÀº°Å¶ó¸é 0xFFFF
	BYTE byAddAmount;//Ãß°¡µÇ´Â ¾ç
};

#define ore_into_bag_result_zocl 10
struct _ore_into_bag_result_zocl {

	BYTE byErrCode;	//0:¼º°ø 1:°¡°ø¸ðµå¾Æ´Ô 2:ÀÚ¿ø¾ø°Å³ªºÎÁ· 3:»ç¿ë°¡¹æ¾Æ´Ô 4:°¡¹æ°ø°£ºÎÁ· 5:°¡¹æ¿¡¾ø´Â½½·Ô 6:½½·Ô´ç¿ë·®ÃÊ°ú, 7:°¡¹æ°ú³»¿ëÀÌ´Ù¸§
	WORD wNewSerial; //»õ·Î¿î ½Ã¸®¾ó.. ±âÁ¸²¨¿¡´Ù ½×Àº°æ¿ì´Â ±âÁ¸ÀÇ½Ã¸®¾ó
};

#define cutting_complete_request_clzo 11
struct _cutting_complete_request_clzo {

	BYTE byNpcRace;	//npcÁ¾Á·.. 0:º§¸®Åä, 1:ÄÚ¶ó 2:¾ÆÅ©·¹½Ã¾Æ 
};

#define cutting_complete_result_zocl 12	
struct _cutting_complete_result_zocl {

	DWORD dwLeftGold;
};

//
//party_msg		16
//

//Æ¯Á¤´ë»óÀ» ÆÄÆ¼¿øÀ¸·Î ¸ðÁý¿äÃ»
//Á¶°Ç»çÇ×.. ÀÚ½ÅÀº ¹«¼Ò¼Ó¶Ç´Â º¸½º..»ó´ë´Â ¹«¼Ò¼ÓÀÎ»óÅÂ¿¡¼­¸¸ ¿äÃ»°¡´É
#define party_join_invitation_clzo 1
struct _party_join_invitation_clzo {

	WORD wDstIndex;
};

//Æ¯Á¤ÀÎÀÌ ÀÚ½Å¿¡°Ô ÆÄÆ¼¿¡ ¸ðÁý¿äÃ»ÇÔ
#define party_join_invitation_question_zocl 2
struct _party_join_invitation_question_zocl {
	
	_CLID idBoss;
};

//Æ¯Á¤ÀÎÀÌ ÀÚ½Å¿¡°Ô ÆÄÆ¼¿¡ ¸ðÁý¿äÃ»ÀÇ ´äº¯
#define party_join_invitation_answer_clzo 3
struct _party_join_invitation_answer_clzo {

	_CLID idBoss;
};

//Æ¯Á¤ÆÄÆ¼Àå¿¡°Ô ÀÚ½ÅÀ» ÆÄÆ¼¿øÀ¸·Î Áö¿ø¿äÃ»
//Á¶°Ç»çÇ×.. ÀÚ½ÅÀº ¹«¼Ò¼Ó.. »ó´ë´Â º¸½ºÀÎ»óÅÂ¿¡¼­¸¸ ¿äÃ»°¡´É
#define party_join_application_clzo 4
struct _party_join_application_clzo {

	WORD wBossIndex;
};

//Æ¯Á¤ÀÎÀÌ ÀÚ½Å¿¡°Ô ÆÄÆ¼¿øÀ¸·Î Áö¿øÇÔ
#define party_join_application_question_zocl 5
struct _party_join_application_question_zocl {

	_CLID idApplicant;
};

//Æ¯Á¤ÀÎÀÌ ÀÚ½Å¿¡°Ô ÆÄÆ¼¿øÀ¸·Î Áö¿ø¿äÃ»ÀÇ ´äº¯
#define party_join_application_answer_clzo 6
struct _party_join_application_answer_clzo {
	
	_CLID idApplicant;
};

//¸ðÁý¿äÃ»½Â¶ô½Ã ÀÚ½Å¿¡°Ô Á¶Á÷¿ø¸®½ºÆ®¸¦ º¸³¿..
#define party_join_joiner_result_zocl 7
struct _party_join_joiner_result_zocl {

	struct _list{
		DWORD dwSerial;
		char szAvatorName[max_name_len+1];
	};

	BYTE byListNum;
	_list List[member_per_party];

	_party_join_joiner_result_zocl(){ byListNum = 0; }

	int size(){ return sizeof(*this)-sizeof(_list)*(member_per_party-byListNum); }
};

//¸ðÁý¿äÃ»½Â¶ô½Ã ±âÁ¸Á¶Á÷¿øµé¿¡°Ô ¿äÃ»½Â¶ôÀ» ¾Ë¸²..
#define party_join_member_result_zocl 8
struct _party_join_member_result_zocl {

	DWORD dwJoinerSerial;
	char szJoinerName[max_name_len+1];
};


//½º½º·Î Á¶Á÷¿¡¼­ Å»ÅðÇÔÀ» ¿äÃ»
#define party_leave_self_request_clzo 9
struct _party_leave_self_request_clzo {

};

//½º½º·Î Á¶Á÷¿¡¼­ Å»ÅðÇÔÀ» ÀÚ½ÅÆ÷ÇÔÁ¶Á÷¿ø¿¡°Ô ¾Ë¸²..
//º¸½ºÀÇ Å»ÅðÀÇ°æ¿ì ´ÙÀ½²ý¹ßÀÚ°¡ º¸½º·Î ½Â°è
#define party_leave_self_result_zocl 10
struct _party_leave_self_result_zocl {

	DWORD dwExiterSerial;		//0xFFÀÌ¸é ½ÇÆÐ¸Þ½ÃÁö..ÀÚ½Å¿¡°Ô¸¸
	bool bWorldExit;	

};

//Á¶Á÷¿¡¼­ °­Åð½ÃÅ´À» ¿äÃ»
#define party_leave_compulsion_request_clzo 11
struct _party_leave_compulsion_request_clzo {

	DWORD dwExiterSerial;
};

//Á¶Á÷¿¡¼­ °­ÅðµÊÀ» ´Ù¸¥Á¶Á÷¿ø¿¡°Ô ¾Ë¸²..
#define party_leave_compulsion_result_zocl 12
struct _party_leave_compulsion_result_zocl {

	DWORD dwExiterSerial; //0xFFÀÌ¸é  ½ÇÆÐ¸Þ½ÃÁö..ÀÚ½Å¿¡°Ô¸¸
};

//Á¶Á÷À» ÇØÃ¼¿äÃ»..º¸½º¸¸ °¡´É
#define party_disjoint_request_clzo 13
struct _party_disjoint_request_clzo {

};

//Á¶Á÷ÀÌ ÇØÃ¼‰çÀ½À?Á¶Á÷¿ø¿¡°Ô ¾Ë¸²..
#define party_disjoint_result_zocl 14
struct _party_disjoint_result_zocl {
	
	BYTE bySuccess;	//(bool) false¸é ÀÚ½Å¿¡°Ô¸¸ ¿È.. true¸é Àü ÆÄÆ¼¿ø¿¡°Ô..
};

//º¸½º½Â°è¿äÃ»
#define party_succession_request_clzo 15
struct _party_succession_request_clzo {

	DWORD dwSuccessorSerial;
};

//º¸½º½Â°è ¾Ë¸²
#define party_succession_result_zocl 16
struct _party_succession_result_zocl {

	DWORD dwSuccessorSerial;	//0xffÀÌ¸é ½ÇÆÐ.. ÀÚ±âÇÑÅ×¸¸..
};

//ÆÄÆ¼¸â¹ö Àá±Ý¿äÃ»
#define party_lock_request_clzo 115
struct _party_lock_request_clzo {

	bool bLock;	//true..Àá±Ý.. false.. Ç°..	
};

//ÆÄÆ¼¸â¹ö Àá±Ý¿äÃ» ¾Ë¸²
#define party_lock_result_zocl 116
struct _party_lock_result_zocl {	

	BYTE byLock;	//1..Àá±Ý.. 0.. Ç°..	0xFF : ¿¡·¯..
};

#define party_member_info_upd 17
struct _party_member_info_upd {

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	WORD wHP;
	WORD wFP;
	WORD wSP;	
	WORD wMaxHP;	
	WORD wMaxFP;	
	WORD wMaxSP;
	BYTE byLv;	
	BYTE byMapCode;
	short zPos[2]; //x, z

	BYTE byContEffectNum;

	struct _EFFECT {
		WORD wEffectCode;	//¸Ç¿ÞÂÊºñÆ®... effect_code.. ±×´ÙÀ½ºÎÅÏ SFIndex..	
		BYTE byEffectLv;	
		WORD wLeftSec;//ÀÛÀº°ÍÀÏ¼ö·Ï ÃÖ±Ù¿¡ °É¸°°Å..	//upt(4/24)
	};	

	_EFFECT Effect[CONT_SF_SIZE*2];
	
	int size(){ return sizeof(*this)-sizeof(_EFFECT)*(CONT_SF_SIZE*2-byContEffectNum); }
};

#define party_member_hp_upd 18
struct _party_member_hp_upd {	

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	WORD wHP;
};

#define party_member_fp_upd 19
struct _party_member_fp_upd {	

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	WORD wFP;
};

#define party_member_sp_upd 118
struct _party_member_sp_upd {	

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	WORD wSP;
};

#define party_member_lv_upd 119	
struct _party_member_lv_upd {	

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	BYTE byLv;
};

#define party_member_pos_upd 120	
struct _party_member_pos_upd {	

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	BYTE byMapCode;
	short zPos[2];
};

#define party_member_max_hfsp_upd 121
struct _party_member_max_hfsp_upd {

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	WORD wMaxHP;
	WORD wMaxFP;
	WORD wMaxSP;
};

#define party_member_effect_upd 20
struct _party_member_effect_upd {

	DWORD dwMemSerial; //¸É¹öÀÇ ½Ã¸®¾ó.
	BYTE byAlterCode;	//0: »ðÀÔ.. 1: Á¦°Å..
	WORD wEffectCode;	//¸Ç¿ÞÂÊºñÆ®... effect_code.. ±×´ÙÀ½ºÎÅÏ SFIndex..
	BYTE byEffectLv;
};

#define party_exp_division_zocl 21
struct _party_exp_division_zocl {	//del..

	WORD wExpRate; 
};

//
//cheat_msg		15
//

#define cheat_force_all_use_zocl 1
struct _cheat_force_all_use_zocl {

	WORD wStartSerial;
};

//
//effect_msg		17
//

//Æ÷½º¿äÃ»..ÀÏ½Ãº¸Á¶, Áö¼Ó..
#define force_request_clzo 1
struct _force_request_clzo {

	WORD wForceSerial;
	_CHRID idDst;//½ÃÀü´ë»ó..	
};

//Æ÷½º¸¦ ÀÚ½Å¿¡°Ô ¾Ë¸²
#define force_result_one_zocl 2
struct _force_result_one_zocl {

	BYTE byErrCode;//0:¼º°ø, //1:¾ø´ÂÆ÷½º¾ÆÀÌÅÛ, //2:FPºÎÁ· //3:¾ø´Â´ë»ó 4;//ÀÏ½Ãº¸Á¶,Áö¼Ó¾Æ´Ô 5;//»ç¿ëÇÒ¼ö¾ø´ÂÆ÷½º 6;//Áö¼ÓÇÇÇØº¸Á¶Æ÷½º»ç¿ëÁ¦ÇÑ 7;//Áö¼ÓÀÌµæº¸Á¶Æ÷½º»ç¿ëÁ¦ÇÑ 8;//½ÃÀü½ÇÆÐ 100;//ÇÃ·¹ÀÌ¾î »óÈ²»ó »ç¿ë¸øÇÏ´Â Æ÷½º
	DWORD dwLeftFP;	//del(4/27)
	DWORD dwItemCum; //Æ÷½º¾ÆÀÌÅÛ¼º°ø´©ÀûÄ¡..
};

//Æ÷½ºÀÇ °á°ú¸¦ ÁÖº¯¿¡ ¾Ë¸²
#define force_result_other_zocl 3
struct _force_result_other_zocl {
	
	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..	
	BYTE byForceIndex;
	BYTE byForceLv;
	_CHRID idPerformer;	//½ÃÀüÀÚ
	_CHRID idDster;		//½ÃÀü´ë»ó..
};

//½ºÅ³¿äÃ»..ÀÏ½Ãº¸Á¶, Áö¼Ó..
#define skill_request_clzo 4	
struct _skill_request_clzo {
	
	BYTE bySkillIndex;
	_CHRID idDst;//½ÃÀü´ë»ó..	
};

//½ºÅ³¸¦ ÀÚ½Å¿¡°Ô ¾Ë¸²
#define skill_result_one_zocl 5
struct _skill_result_one_zocl {

	BYTE byErrCode;//0:¼º°ø, //1:ÇÒ¼ö¾ø´Â½ºÅ³ //2:FPºÎÁ· //3:¾ø´Â´ë»ó 4;//ÀÏ½Ãº¸Á¶,Áö¼Ó¾Æ´Ô 5;//»ç¿ëÇÒ¼ö¾ø´Â½ºÅ³ 6;//Áö¼ÓÀÌµæº¸Á¶½ºÅ³»ç¿ëÁ¦ÇÑ 7;//½ÃÀü½ÇÆÐ, 100;//ÇÃ·¹ÀÌ¾î »óÈ²»ó »ç¿ë¸øÇÏ´Â ½ºÅ³
	DWORD dwLeftFP;	//del(4/27)
};

//½ºÅ³ÀÇ °á°ú¸¦ ÁÖº¯¿¡ ¾Ë¸²
#define skill_result_other_zocl 6
struct _skill_result_other_zocl {
	
	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..
	_CHRID idPerformer;	//½ÃÀüÀÚ
	_CHRID idDster;		//½ÃÀü´ë»ó..
	BYTE bySkillIndex;
	BYTE bySkillLv;
};

//Å¬·¡½º½ºÅ³¿äÃ»..ÀÏ½Ãº¸Á¶, Áö¼Ó..
#define class_skill_request_clzo 44	
struct _class_skill_request_clzo {
	
	WORD wSkillIndex;
	_CHRID idDst;//½ÃÀü´ë»ó..	
};

//½ºÅ³¸¦ ÀÚ½Å¿¡°Ô ¾Ë¸²
#define class_skill_result_one_zocl 45
struct _class_skill_result_one_zocl {

	BYTE byErrCode;//0:¼º°ø, //1:ÇÒ¼ö¾ø´Â½ºÅ³ //2:FPºÎÁ· //3:¾ø´Â´ë»ó 4;//ÀÏ½Ãº¸Á¶,Áö¼Ó¾Æ´Ô 5;//»ç¿ëÇÒ¼ö¾ø´Â½ºÅ³ 6;//Áö¼ÓÀÌµæº¸Á¶½ºÅ³»ç¿ëÁ¦ÇÑ 7;//½ÃÀü½ÇÆÐ, 100;//ÇÃ·¹ÀÌ¾î »óÈ²»ó »ç¿ë¸øÇÏ´Â ½ºÅ³
	WORD wLeftFP;	//del(4/27)(ydq, why delete?)
};

//½ºÅ³ÀÇ °á°ú¸¦ ÁÖº¯¿¡ ¾Ë¸²
#define class_skill_result_other_zocl 46
struct _class_skill_result_other_zocl {
	
	BYTE byRetCode;	//0ÀÌ¸é ¼º°ø..
	_CHRID idPerformer;	//½ÃÀüÀÚ
	_CHRID idDster;		//½ÃÀü´ë»ó..
	WORD wSkillIndex;
};

#define effect_add_inform_zocl 7
struct _effect_add_inform_zocl {

	BYTE byLv;	
	WORD wEffectCode;	//¸Ç¿ÞÂÊºñÆ®... effect_code.. ±×´ÙÀ½ºÎÅÏ SFIndex..
};

#define effect_remove_inform_zocl 8
struct _effect_remove_inform_zocl {

	WORD wEffectCode;	
};

#define set_fp_inform_zocl 9	
struct _set_fp_inform_zocl {

	WORD wFP;
};

#define set_hp_inform_zocl 10
struct _set_hp_inform_zocl {

	WORD wHP;
};

#define set_sp_inform_zocl 11
struct _set_sp_inform_zocl {

	WORD wSP;
};

#define insert_item_inform_zocl 12
struct _insert_item_inform_zocl {
						
	BYTE byStorageCode;	//ÀÎº¥Åä¸®:0, Àåºñ:1, Àå½Ä: 2, º§Æ®:3, Æ÷½º:4, ¸µÅ©:5
	BYTE byTableCode;	
	WORD wItemIndex;	
	DWORD dwDurPoint;	//ÁßÃ¸¾ÆÀÌÅÛÀº ¼ö·®.. ³»±¸¾ÆÀÌÅÛÀº »óÀ§¿öµå(ÇÑ°è³»±¸¼º) ÇÏÀ§¿öµå(ÇöÀç³»±¸¼º)
	WORD wSerial;		
};

#define stun_inform_zocl 13
struct _stun_inform_zocl {

	_CHRID idStun;	
};

#define last_effect_change_inform_zocl 14
struct _last_effect_change_inform_zocl {

	BYTE  byObjID;	//obj_id_player.. obj_id_monter..	
	DWORD dwSerial;
	WORD wLastContEffect;	
};

#define make_tower_request_clzo 15
struct _make_tower_request_clzo {	

	enum	{	max_material = 30	};	

	WORD	wSkillIndex;	
	short	zPos[3];
	WORD	wTowerItemSerial;
	
	struct __material{
		WORD wItemSerial;
		BYTE byMaterSlotIndex;	//°¡µåÅ¸¿öµ¥ÀÌÅÍ ÇÊµåÁß Àç·áÁ¤ÀÇ ÇÊµåÀÇ ¼ø¼­ 0 ~ 2
		BYTE byAmount;
	};

	BYTE	byMaterialNum;
	__material Material[max_material];

	_make_tower_request_clzo()	{	byMaterialNum = 0;	}
	int size()	{ if(byMaterialNum > max_material) byMaterialNum = 0;	return sizeof(*this) - sizeof(__material) * (max_material - byMaterialNum);	}
};

#define make_tower_result_zocl 16
struct _make_tower_result_zocl {	

	BYTE	byErrCode;
	DWORD	dwTowerObjSerial;
	WORD	wLeftFP;	//add(4/25)
};

#define back_tower_request_clzo 17	//Å¸¿öÇØÃ¼
struct _back_tower_request_clzo {	

	DWORD	dwTowerObjSerial;
};

#define back_tower_result_zocl 18	
struct _back_tower_result_zocl {	

	BYTE	byErrCode;
	WORD	wItemSerial;
	WORD	wLeftHP;
};

#define alter_tower_hp_zocl 19
struct _alter_tower_hp_zocl {	

	WORD	wItemSerial;
	WORD	wLeftHP;	//0ÀÌ¸é ÆÄ±«..
};

#define tower_complete_inform_zocl 20	//°¡µåÅ¸¿ö¿Ï¼º..
struct _tower_complete_inform_zocl {		//add(4/24)

	DWORD	dwTowerObjSerial;
};

#define alter_cont_effect_time_zocl 21	//°É·ÁÀÖ´Â Áö¼ÓÈ¿°úÀÇ ³²Àº ½Ã°£ÀÌ ¹Ù²ñ
struct _alter_cont_effect_time_zocl {		//add(4/24)

	struct __list
	{
		WORD	wEffectCode;
		WORD	wLeftSec;
	};

	BYTE	byEffectNum;
	__list	List[CONT_SF_SIZE];

	_alter_cont_effect_time_zocl()	{	byEffectNum = 0;	}
	int size()	{	if(byEffectNum > CONT_SF_SIZE)	byEffectNum = 0; return sizeof(*this)-sizeof(__list)*(CONT_SF_SIZE-byEffectNum);	}
};

//
//dtrade_msg 18... 
//

//ASK
#define d_trade_ask_request_clzo 1
struct _d_trade_ask_request_clzo {	//wDstIndex¿¡°Ô °Å·¡¸¦ ¿äÃ»

	WORD wDstIndex;	
};

#define d_trade_ask_result_clzo 2
struct _d_trade_ask_result_clzo {	//d_trade_ask_request_clzoÀÇ °á°ú·Î ÀÚ½ÅÇÑÅ×¿È

	BYTE byErrCode;//0;¼º°ø//1;//ÀÚ½ÅÀÌÀÌ¹ÌÆ®·¹ÀÌµåÁß 2;//°Å¸®°¡¸Ø 3;//À¯È¿ÇÑ´ë»ó¾Æ´Ô 4;//»ó´ë°¡Æ®·¹ÀÌµåÁß
};

#define d_trade_ask_inform_zocl 3
struct _d_trade_ask_inform_zocl {	//idAsker°¡ ÀÚ½ÅÇÑÅ× °Å·¡¸¦ Á¦ÀÇÇÔ

	_CLID idAsker;
};

//ANSWER
#define d_trade_answer_request_clzo 4
struct _d_trade_answer_request_clzo {	//Á¦ÀÇ¸¦ ¹Þ¾ÆµéÀÓ

	_CLID idAsker;
};

#define d_trade_answer_result_zocl 5	//½ÇÆÐ½Ã¿¡¸¸..
struct _d_trade_answer_result_zocl {	//Á¦ÀÇ ¹Þ¾ÆµéÀÓÀÇ ½ÇÆÐ	

	BYTE byErrCode;	//1;//À¯È¿ÇÑask°¡¾Æ´Ô 2;//asker°¡ÀÌ¹ÌÆ®·¹ÀÌµå¸ðµå 3;//answer°¡ÀÌ¹ÌÆ®·¹ÀÌµå¸ðµå 4;//asker°¡ÀÚ½ÅÀ»¿äÃ»Áß¾Æ´Ô 5;//°Å¸®°¡ ¸Ø 6;//À¯È¿ÇÑ ´ë»óÀÌ ¾Æ´Ô
};

//START
#define d_trade_start_inform_zocl 6
struct _d_trade_start_inform_zocl {	//°Å·¡´ë»óÀÚ °¢°¢ÀÇ ÀÎº¥Åä¸® ºóÄ­¼ö..ºóÄ­¼ö¸¸Å­ °Å·¡°¡´É

	_CLID idAsker;
	BYTE byAskerEmptyNum;	
	_CLID idAnswer;
	BYTE byAnswerEmptyNum;	
};

//CANCLE
#define d_trade_cancle_request_clzo 7
struct _d_trade_cancle_request_clzo {	//°Å·¡Ãë¼Ò

};

#define d_trade_cancle_result_zocl 8
struct _d_trade_cancle_result_zocl {	//Ãë¼ÒÀÚ¿¡°Ô
	
	BYTE byErrCode; //0ÀÌ¸é ¼º°ø..//1;//Æ®·¹ÀÌµå¾Æ´Ô 2;//¶ô°É¸°»óÅÂ 
};

#define d_trade_cancle_inform_zocl 9
struct _d_trade_cancle_inform_zocl {	//Ãë¼Ò´çÇÑ »ç¶÷ÇÑÅ×	

};

//LOCK
#define d_trade_lock_request_clzo 10
struct _d_trade_lock_request_clzo {		//Àá±Ý

};

#define d_trade_lock_result_zocl 11
struct _d_trade_lock_result_zocl {		//Àá±ÙÀÚ¿¡°Ô
	
	BYTE	byErrCode; //0ÀÌ¸é ¼º°ø..1;//Æ®·¹ÀÌµå¸ðµå¾Æ´Ô 2;//¶ô°É¸°»óÅÂ
};

#define d_trade_lock_inform_zocl 12
struct _d_trade_lock_inform_zocl {		//´ë»ó¿¡°Ô

};	

//ADD
#define d_trade_add_request_clzo 13
struct _d_trade_add_request_clzo {		//°Å·¡¸ñ·ÏÃß°¡

	BYTE byStorageCode;
	DWORD dwSerial;
	BYTE bySlotIndex;
	BYTE byAmount;	
};

#define d_trade_add_result_zocl 14
struct _d_trade_add_result_zocl {
	
	BYTE byErrCode; //0ÀÌ¸é ¼º°ø//1;//Æ®·¹ÀÌµå¸ðµå¾Æ´Ô 2;//¶ô»óÅÂÀÓ 3;//À¯È¿ÇÑ½½·ÔÀÌ ¾Æ´Ô 4;//Ã¤¿öÁø½½·Ô 5;//¾ø´Â¾ÆÅÆ 6;//Àß¸ø‰Â¾?
};

#define d_trade_add_inform_zocl 15
struct _d_trade_add_inform_zocl {

	BYTE bySlotIndex;
	BYTE byTableCode;
	WORD wItemIndex;
	DWORD dwDurPoint;
	DWORD dwUdtInfo;
	BYTE byAmount;
	BYTE byEmptyInvenNum;
};

#define d_trade_del_request_clzo 16
struct _d_trade_del_request_clzo {		//°Å·¡¸ñ·Ï¿¡¼­ »èÁ¦

	BYTE bySlotIndex;
};

#define d_trade_del_result_zocl 17
struct _d_trade_del_result_zocl {
	
	BYTE byErrCode; //0ÀÌ¸é ¼º°ø.//0ÀÌ¸é ¼º°ø//1;//Æ®·¹ÀÌµå¸ðµå¾Æ´Ô 2;//¶ô»óÅÂÀÓ 3;//À¯È¿ÇÑ½½·ÔÀÌ ¾Æ´Ô 4;//ºó½½·Ô
};

#define d_trade_del_inform_zocl 18
struct _d_trade_del_inform_zocl {

	BYTE bySlotIndex;
	BYTE byEmptyInvenNum;
};

#define d_trade_bet_request_clzo 19
struct _d_trade_bet_request_clzo {		//±Ý¾× ¹èÆÃ

	//#define money_unit_dalant	0
	//#define money_unit_gold	1

	BYTE byMoneyUnit;
	DWORD dwBetAmount;
};

#define d_trade_bet_result_zocl 20
struct _d_trade_bet_result_zocl {
	
	BYTE byErrCode; //0ÀÌ¸é ¼º°ø.//1;//´Þ¶õÆ®ºÎÁ· 2;//°ñµåºÎÁ· 3;//´ÜÀ§¿¡·¯ 4;//¶ô»óÅÂÀÓ
};

#define d_trade_bet_inform_zocl 21
struct _d_trade_bet_inform_zocl {

	BYTE byMoneyUnit;
	DWORD dwBetAmount;
};

#define d_trade_ok_request_clzo 22
struct _d_trade_ok_request_clzo {	//ok¹öÆ°

};

#define d_trade_ok_result_zocl 23
struct _d_trade_ok_result_zocl {
	
	BYTE byErrCode; //0ÀÌ¸é ¼º°ø..	100ÀÌ¸é »ó´ë¿¡ ³ÖÀ» °ø°£ÀÌ ºÎÁ·
};

#define d_trade_ok_inform_zocl 24
struct _d_trade_ok_inform_zocl {

};	

#define d_trade_accomplish_inform_zocl 25
struct _d_trade_accomplish_inform_zocl {	//°Å·¡ ¼º»ç
	
	DWORD	dwDalant;
	DWORD	dwGold;
	WORD	wStartSerial;
	bool	bSucc;	//¼º°ø¿©ºÎ.. false¸é °Å·¡ÀÇ ¸ðµç°úÁ¤À» ÃÊ±âÈ­ÇÔ
};

#define d_trade_close_inform_zocl 26	
struct _d_trade_close_inform_zocl {	//°Å·¡ ¼­¹öÁ÷±Ç Ãë¼Ò	

	BYTE byCloseCode;	
};

#define d_trade_unit_info_inform_zocl 27	//À¯´ÖÀ» ¿Ã·ÈÀ»¶§ »ó´ë¿¡°Ô À¯´ÖÀÇ Á¤º¸¸¦ ¾Ë¸°´Ù.
struct _d_trade_unit_info_inform_zocl {		

	BYTE	byTradeSlotIndex;	//Æ®·¹ÀÌµåÃ¢ ÀÎµ¦½º
	BYTE	byFrame;	
	DWORD	dwGauge;		
	BYTE	byPart[UNIT_PART_NUM];
	DWORD	dwBullet[UNIT_BULLET_NUM];
	DWORD	dwSpare[max_unit_spare];
	int		nDebtFee;	//Ã¤¹« º¸°ü·á, °ßÀÎ·á
};

#define d_trade_unit_add_inform_zocl 28	//°Å·¡°¡ ¼º»çµÈÈÄ À¯´ÖÀÌ ÆûÇÔµÇ¾îÀÖÀ¸¸é À¯´Öµ¥ÀÌÅÍ¸¦ º¸³½´Ù
struct _d_trade_unit_add_inform_zocl {		

	WORD	wUnitKeySerial;
	BYTE	bySlotIndex;
	BYTE	byFrame;	//0xFF¸é ºó ½½·Ô
	DWORD	dwGauge;		//hp
	BYTE	byPart[UNIT_PART_NUM];
	DWORD	dwBullet[UNIT_BULLET_NUM];
	DWORD	dwSpare[max_unit_spare];
	int		nKeepingFee;	//Ã¤¹« º¸°ü·á
	int		nPullingFee;	//Ã¤¹« °ßÀÎ·á 
};

//dungeon_msg.. 19

#define battledungeon_open_request_clzo 1
struct _battledungeon_open_request_clzo	{

	DWORD dwItemSerial;
};

#define battledungeon_open_result_zocl 2
struct _battledungeon_open_result_zocl	{

	BYTE byRetCode;	
};

#define dungeongate_create_zocl 3
struct _dungeongate_create_zocl	{

	WORD wGateIndex;
	DWORD dwGateSerial;
	DWORD dwOpenerSerial;
	WORD wItemRecIndex;
	BYTE byState;
	short zPos[3];
};

#define dungeongate_destroy_zocl 4
struct _dungeongate_destroy_zocl {
		
	WORD wGateIndex;
	DWORD dwGateSerial;
};

#define dungeongate_fixpositon_zocl 5
struct _dungeongate_fixpositon_zocl {

	WORD wGateIndex;
	DWORD dwGateSerial;
	DWORD dwOpenerSerial;
	WORD wItemRecIndex;
	BYTE byState;
	short zPos[3];
};

#define dungeongate_state_change_zocl 6
struct _dungeongate_state_change_zocl {

	BYTE byState;
	WORD wGateIndex;
	DWORD dwGateSerial;
};

#define goto_dungeon_request_clzo 7
struct _goto_dungeon_request_clzo {	

	WORD	wGateIndex;
	DWORD	dwGateSerial;
};

#define goto_dungeon_result_zocl 8
struct _goto_dungeon_result_zocl {	//	==> new_pos_start_request_clzo·Î ¿¬°á..

	BYTE	byRetCode;	
	BYTE	byMapCode;
	short	zPos[3];
	WORD	wLeftSec;	//³²ÀºÃÊ 
	WORD	wTotalKillNum;	
	WORD	wMissionKillNum;
};

#define close_dungeon_inform_zocl 9
struct _close_dungeon_inform_zocl {

	BYTE byCompleteCode;//	CharacterDB.h.. dungeon_complete_code_timeout 0 (´øÁ¯ÀÌ ´ÝÈ÷´Â ÀÌÀ¯..)
};

#define outof_dungeon_request_clzo 10
struct _outof_dungeon_request_clzo {

};

#define outof_dungeon_result_zocl 11
struct _outof_dungeon_result_zocl {		//==> new_pos_start_request_clzo·Î ¿¬°á..

	BYTE	byRetCode;	
	BYTE	byMapCode;
	short	zPos[3];
};

#define killmon_dungeon_inform_zocl 12
struct _killmon_dungeon_inform_zocl {	

	WORD	wTotalKillNum;
	WORD	wMissionKillNum;
};

//unit_msg.. 23

#define unit_frame_buy_request_clzo 1
struct _unit_frame_buy_request_clzo {	

	BYTE byFrameCode;
};

#define unit_frame_buy_result_zocl 2
struct _unit_frame_buy_result_zocl {	

	BYTE    byRetCode;
	BYTE	byFrameCode;
	BYTE	byAddUnitSlot;
	BYTE	byKeyIndex;
	WORD	wKeySerial;

	DWORD	dwLeftMoney[MONEY_UNIT_NUM];
	DWORD	dwConsumMoney[MONEY_UNIT_NUM];
};

#define unit_sell_request_clzo 11
struct _unit_sell_request_clzo {	

	BYTE bySlotIndex;
};

#define unit_sell_result_zocl 22
struct _unit_sell_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	WORD	wKeySerial;

	DWORD	dwNonPayDalant;
	DWORD	dwAddMoney[MONEY_UNIT_NUM];
	DWORD	dwLeftMoney[MONEY_UNIT_NUM];
};

#define unit_part_tuning_request_clzo 3
struct _unit_part_tuning_request_clzo {	

	BYTE	bySlotIndex;

	BYTE    byTuningNum;
	_tuning_data	TuningList[UNIT_PART_NUM];

	_unit_part_tuning_request_clzo(){
		byTuningNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_tuning_data)*(UNIT_PART_NUM-byTuningNum);
	}
};

#define unit_part_tuning_result_zocl 4
struct _unit_part_tuning_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	BYTE	byPart[UNIT_PART_NUM];
	DWORD   dwBullet[UNIT_BULLET_NUM];	//add(4/24)

	int		nCost[MONEY_UNIT_NUM];	
	DWORD	dwLeftMoney[MONEY_UNIT_NUM];
};

#define unit_frame_repair_request_clzo 5
struct _unit_frame_repair_request_clzo {	

	BYTE	bySlotIndex;
};

#define unit_frame_repair_result_zocl 6
struct _unit_frame_repair_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	WORD	wNewGauge;

	DWORD	dwConsumDalant;	//¼ö¸®ºñ
	DWORD	dwLeftDalant;	//³²Àº ´Þ¶õÆ®
};

#define unit_bullet_fill_request_clzo 7
struct _unit_bullet_fill_request_clzo {	

	BYTE	bySlotIndex;
	
//	#define unit_bullet_arms			0
//	#define unit_bullet_shoulder		1
//	#define UNIT_BULLET_NUM				2	

	BYTE	byBulletIndex[UNIT_BULLET_NUM];	//	.. Ã¤¿ìÁö¾ÊÀº ÆÄÆ®´Â 0xFF
};

#define unit_bullet_fill_result_zocl 8
struct _unit_bullet_fill_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	bool	byBulletIndex[UNIT_BULLET_NUM];	//Ã¤¿ìÁö¾ÊÀº ÆÄÆ®´Â 0xFF

	DWORD	dwComsumMoney[MONEY_UNIT_NUM];
	DWORD	dwLeftMoney[MONEY_UNIT_NUM];
};

#define unit_pack_fill_request_clzo 111
struct _unit_pack_fill_request_clzo {	

	BYTE	bySlotIndex;

	BYTE	byFillNum;

	struct __list{					
		BYTE	bySpareIndex;
		BYTE	byBulletIndex;
	};

	__list	List[max_unit_spare];

	_unit_pack_fill_request_clzo()	{	byFillNum = 0;	}

	int size()	{	return sizeof(*this) - sizeof(__list)*(max_unit_spare - byFillNum);	}
};

#define unit_pack_fill_result_zocl 12
struct _unit_pack_fill_result_zocl {

	BYTE    byRetCode;
	BYTE	bySlotIndex;

	DWORD	dwComsumMoney[MONEY_UNIT_NUM];
	DWORD	dwLeftMoney[MONEY_UNIT_NUM];

	BYTE	byFillNum;

	typedef _unit_pack_fill_request_clzo::__list __list;

	__list	List[max_unit_spare];

	_unit_pack_fill_result_zocl()	{	byFillNum = 0;	}

	int size()	{	return sizeof(*this) - sizeof(__list)*(max_unit_spare - byFillNum);	}
};

#define unit_delivery_request_clzo 13
struct _unit_delivery_request_clzo {	

	BYTE	bySlotIndex;
	BYTE	byStoreIndex;	//0xFF¸é ¿ø°Å¸®¼ö¼Û
	short	zUnitNewPos[3];	//ÇöÀçÀ§Ä¡¿¡¼­ 20ÀÌ´Ï..
};

#define unit_delivery_result_zocl 14
struct _unit_delivery_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	BYTE	byTransDistCode;	//#define unit_trans_short_range		0	//À¯´Ö ±Ù°Å¸®¼ö¼Û  #define unit_trans_long_range		1	//À¯´Ö ¿ø°Å¸®¼ö¼Û
	DWORD	dwParkingUnitSerial;

	DWORD	dwPayDalant;
	DWORD	dwLeftDalant;
};

#define unit_return_request_clzo 15
struct _unit_return_request_clzo {	

};

#define unit_return_result_zocl 16
struct _unit_return_result_zocl {	

	BYTE    byRetCode;
	DWORD	dwPayDalant;
	DWORD   dwNewDalant;
};

#define unit_take_request_clzo 17
struct _unit_take_request_clzo {	

};

#define unit_take_result_zocl 18
struct _unit_take_result_zocl {	

	BYTE    byRetCode;
};

#define unit_leave_request_clzo 19
struct _unit_leave_request_clzo {	

	short	zPlayerNewPos[3];	//ÇöÀçÀ§Ä¡¿¡¼­ 20ÀÌ´Ï..
};

#define unit_leave_result_zocl 20
struct _unit_leave_result_zocl {	

	BYTE    byRetCode;
};

#define unit_alter_fee_inform_zocl 30
struct _unit_alter_fee_inform_zocl {		

	BYTE	bySlotIndex;
//	DWORD	dwKeepingFee;	del(4/22)
	DWORD	dwPullingFee;
};

#define parkingunit_change_owner_zocl 31
struct _parkingunit_change_owner_zocl {		

	WORD	wObjIndex;
	DWORD	dwObjSerial;
	DWORD	dwOldOwnerSerial;
	DWORD	dwNewOwnerSerial;
	BYTE	byNewOwnerUnitSlotIndex;
};

#define unit_bullet_replace_request_clzo 32		//¹éÆÑ¿¡ ÀÖ´Â°ÍÀ» ÅºÃ¢¿¡ ¿Å±ä´Ù..
struct _unit_bullet_replace_request_clzo {	

	BYTE	bySlotIndex;
	BYTE	byPackIndex;
	BYTE	byBulletPart;	
};

#define unit_bullet_replace_result_zocl 33
struct _unit_bullet_replace_result_zocl {	

	BYTE    byRetCode;
};

#define unit_booster_charge_inform_zocl 34	//ºÎ½ºÅÍ º¯°æ
struct _unit_booster_charge_inform_zocl {	

	BYTE	bySlotIndex;
	WORD	wBoosterGauge;
};

#define unit_destroy_inform_zocl 35	//À¯´ÖÆÄ±«
struct _unit_destroy_inform_zocl {		//add(4/24)
	
	BYTE	bySlotIndex;
};

#define unit_force_return_inform_zocl 36	//À¯´Ö°­Á¦ °ßÀÎ
struct _unit_force_return_inform_zocl {		//add(4/26)
	
	BYTE	bySlotIndex;
	DWORD	dwDebt;
};

//recall_msg.. 22

#define animus_recall_request_clzo 1	//¼ÒÈ¯
struct _animus_recall_request_clzo {

	DWORD dwAnimusItemSerial;	//¾Ö´Ï¸Ó½ºÃ¢¿¡ÀÖ´Â ¾ÆÀÌÅÛÀÇ ½Ã¸®¾ó..
	WORD  wAnimusClientHP;		//Å¬¶óÀÌ¾ðÆ®»óÀÇ È¸º¹µÈ HP
	WORD  wAnimusClientFP;		//Å¬¶óÀÌ¾ðÆ®»óÀÇ È¸º¹µÈ FP
};

#define animus_recall_result_zocl 2
struct _animus_recall_result_zocl {	

	BYTE byResultCode;
	DWORD dwAnimusSerial;		//¾Ö´Ï¸Ó½º ÄÉ¸¯ÅÍÀÇ ½Ã¸®¾ó
	WORD  wAnimusHP;			//¾Ö´Ï¸Ó½º HP
	WORD  wAnimusFP;			//¾Ö´Ï¸Ó½º FP
	WORD  wAnimusExp;			//¾Ö´Ï¸Ó½º Exp
	WORD  wLeftFP;				//ÀÚ½ÅÀÇ FP
};

#define animus_return_request_clzo 3	//±ÍÈ¯
struct _animus_return_request_clzo {
};

#define animus_return_result_zocl 4	//_animus_return_request_clzoÀÇ °á°ú ¶Ç´Â ¼­¹ö»óÀÇ °­Á¦±ÍÈ¯ÀÇ °æ¿ì..
struct _animus_return_result_zocl {	

	BYTE  byResultCode;
	WORD  wAnimusItemSerial;
};

#define animus_command_request_clzo 5	//¾Ö´Ï¸Ó½º¿¡ ¸í·É.. 
struct _animus_command_request_clzo {

	//#define animus_act_type_action	0	//¾×œ?
	//#define animus_act_type_follow	1	//Follow me!

	BYTE byCommandCode;
};

#define animus_command_inform_zocl 6	//¾Ö´Ï¸Ó½ºÀÇ »óÅÂº¯°æ.. ³»ºÎÀûÀ¸·Î ¸ðµå°¡ ¹Ù²ðÀû¸¶´Ù..
struct _animus_command_inform_zocl {

	BYTE  byStateCode;
};

#define animus_target_request_clzo 7	//¸ñÇ¥¹°
struct _animus_target_request_clzo {

	BYTE	byObjectID;
	WORD	wObjectIndex;
	DWORD	dwObjectSerial;
};

#define animus_target_result_zocl 8
struct _animus_target_result_zocl {	

	BYTE  byResultCode;
};

#define animus_hp_inform_zocl 9
struct _animus_hp_inform_zocl {	

	WORD wAnimusItemSerial;
	WORD wLeftHP;
};

#define animus_fp_inform_zocl 10
struct _animus_fp_inform_zocl {	

	WORD wAnimusItemSerial;
	WORD wLeftFP;
};

#define animus_exp_inform_zocl 11		//¾Ö´Ï¸Ó½ºÀÇ °æÇèÄ¡.. ÄÉ¸¯ÅÍ ½ºÅ³Àº µû·Î ¿È..
struct _animus_exp_inform_zocl {

	WORD wAnimusItemSerial;
	DWORD dwExp;
};

#define animus_lvup_inform_zocl 12		//¾Ö´Ï¸Ó½ºÀÇ ·¹º§¾÷.. (ÁÖº¯..)
struct _animus_lvup_inform_zocl {

	WORD wIndex;
	DWORD dwSerial;
	BYTE byLv;
};

#define animus_recall_wait_time_free_inform_zocl 13		//¾Ö´Ï¸Ó½º ¸®ÄÝ ´ë±â½Ã°£ ÇÁ¸®..
struct _animus_recall_wait_time_free_inform_zocl {

	bool bFree;	//true ¸é ´ë±â½Ã°£¾øÀ½.. falae¸é ¿ø·¡´ë·Î..
};

//sync_msg.. 19

#define object_server_pos_request_clzo 1
struct _object_server_pos_request_clzo {

	BYTE byObjKind;
	BYTE byObjID;
	WORD wObjIndex;
	DWORD dwObjSerial;
};

#define object_server_pos_result_zocl 2
struct _object_server_pos_result_zocl {		

	BYTE byErrCode; //0: ¼º°ø..1: ¹è¿­¹üÀ§ÃÊ°ú, 2: Á×Àº¿ÀºêÁ§Æ®, 3: ½Ã¸®¾óÀÌ Æ²¸²

	BYTE byObjKind;
	BYTE byObjID;
	WORD wObjIndex;
	DWORD dwObjSerial;

	float	fServerPos[3];
};

#define adjust_amount_inform_zocl 3
struct _adjust_amount_inform_zocl {

	BYTE byStorageCode;
	WORD wSerial;
	DWORD dwNewDur;
};

//
//quest_msg
//

#define insert_new_quest_inform_zocl 1
struct _insert_new_quest_inform_zocl {	//add(3/23)

	BYTE	bySlotIndex;
	DWORD	dwEventIndex;
	BYTE	byEventNodeIndex;
	DWORD	dwQuestIndex;
};

#define select_waited_quest_command_zocl 2
struct _select_waited_quest_command_zocl {	//add(3/23)

	DWORD	dwEventIndex;
	BYTE	byEventNodeIndex;
};

#define insert_quest_failure_zocl 3
struct _insert_quest_failure_zocl {	//add(3/23)

	DWORD	dwEventIndex;
	BYTE	byEventNodeIndex;
};

#define quest_complete_inform_zocl 4
struct _quest_complete_inform_zocl {	//add(3/23)

	BYTE	byQuestDBSlot;
};

#define quest_process_inform_zocl 5
struct _quest_process_inform_zocl {	//add(3/23)

	BYTE	byQuestDBSlot;
	BYTE	byActIndex;
	WORD	wCount;	//0xFFFF¸é ÇØ´ç ¿ä±¸¾×¼ð ¿Ï·á
};

#define quest_fail_inform_zocl 5
struct _quest_fail_inform_zocl {	//add(3/25)

//#define quest_fail_code_lv			0	
//#define quest_fail_code_timeout		1	

	BYTE	byFailCode;	
	BYTE	byQuestDBSlot;
};


#pragma pack(pop)

#endif
