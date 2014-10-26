#ifndef _pt_zone_client_h_
#define _pt_zone_client_h_

#include "rf_protocol.h"
#include "CharacterDB.h"

#pragma pack(push, 1)

//
//system..	1
//
#define enter_world_request_zone 1	// ����� ������ ��û	
struct _enter_world_request_zone {

	DWORD	dwAccountSerial;
	DWORD	dwMasterKey[CHECK_KEY_NUM];			
	bool	bFullMode;	//full mode true, window mode.. false

	int size()	{ return sizeof(*this);	}
};

#define enter_world_result_zone 2// ����� ������ ���	
struct _enter_world_result_zone {

//�������..( CharacterDB.h )
//#define USER_DEGREE_STD			0		//�������-�Ϲ�
//#define USER_DEGREE_GID			1		//�������-���̵�
//#define USER_DEGREE_MGR			2		//�������-���
//#define USER_DEGREE_DEV			3		//�������-������

	BYTE	byResult;
	BYTE	byUserGrade; //�������..  2, 3��� ġƮŰ �� ��� �޽���, /�̵� ��밡��

	int size()	{ return sizeof(*this);	}
};

#define messenger_enter_key_inform_zocl	222
struct _messenger_enter_key_inform_zocl {	

	DWORD	dwAvatorSerial;			//add
	DWORD	dwKey[CHECK_KEY_NUM];
	DWORD	dwMessengerIP;

	int size()	{ return sizeof(*this);	}
};

#define movein_user_request_zone 3	// ����� ������ ��û
struct _movein_user_request_zone {

	DWORD	dwAccountSerial;	
	DWORD	dwZoneMasterKey;
	bool	bFullMode;	//full mode true, window mode.. false

	int size()	{ return sizeof(*this);	}
};

#define movein_user_result_zone 4// ����� ������ ���
struct _movein_user_result_zone {

	BYTE	byResult;

	int size()	{ return sizeof(*this);}//-(2560-wInitDataSize);	}
};

#define moveout_user_request_zone 5
struct _moveout_user_request_zone {

	//#define ZONE_TYPE_GATE	0	..ĳ���ͼ����� �ٽ��Ҷ��..
	//#define ZONE_TYPE_MAP		1	..���̵��� �޴ٸ�..
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

#define reged_char_request_zone 7 //��ω?ĳ���͸� �䱸
struct _reged_char_request_zone {

	int size() { return 0; }
};

#define reged_char_result_zone 8 //��ω?ĳ���͸� �䱸
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

#define add_char_request_zone 9	// ĳ���� ���
struct _add_char_request_zone {

	BYTE bySlotIndex;				
	char szCharName[max_name_len+1];
	BYTE byRaceSexCode;
	char szClassCode[class_code_len+1];	
	DWORD dwBaseShape;	
	
	int size()	{ return sizeof(*this);	}
};

#define add_char_result_zone 10	// ĳ���� ��� Ȯ��
struct _add_char_result_zone {

	BYTE byRetCode;	
	BYTE byAddSlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define del_char_request_zone 11	//������ �ɸ��� ����
struct _del_char_request_zone {
	
	BYTE bySlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define del_char_result_zone 12	//������ �ɸ��� ����Ȯ��
struct _del_char_result_zone {

	BYTE byRetCode;	
	BYTE bySlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define sel_char_request_zone 13	//�÷����� �ɸ��� ����
struct _sel_char_request_zone {
	
	BYTE bySlotIndex;

	int size()	{ return sizeof(*this);	}
};

#define sel_char_result_zone 14	//�÷����� �ɸ��� ����Ȯ��
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

//���� �����ؼ� �����͸� ���� �ٿ�ε������ byMapInMode = mapin_type_start
//��Ż�̵����� ��ġ������ �Ϸ��ϸ� byMapInMode = mapin_type_move
//��Ȱ�� ��ġ���� �Ϸ��ϸ� byMapInMode = mapin_type_revival
//���� client_load_complete_clzo �� _new_map_load_complete_clzo�� ������..

#define new_pos_start_request_clzo 1
struct _new_pos_start_request_clzo {

	//#define mapin_type_start		0	//���ӽ���..
	//#define mapin_type_move		1	//��Ż�̵�..
	//#define mapin_type_revival	2	//��Ȱ..
	//#define mapin_type_goto		3	//�����̵�..
	//#define mapin_type_recall     4	//�⵿..
	//#define mapin_type_dungeon    5	//����..

	BYTE byMapInMode;
};

#define new_pos_start_result_zocl 2
struct _new_pos_start_result_zocl {

	BYTE byMapInMode;	//�� byMapInMode�� ���ٿ�尪.. ���н� 0xFF..
};

#define base_download_request_clzo 5
struct _base_download_request_clzo {	
};

//���� ������ �ø��� �ο�����..
//1. Equip
//2. Embellish
//3. Belt
//4. Inven
//5. Force
//6. Animus
#define base_download_result_zocl 6
struct _base_download_result_zocl {

	BYTE byRetCode;	//0�̸� ����..

	WORD wZoneIndex;	//���� ���󿡼��� �ε���
	WORD wExpRate;	
	WORD wClassHistory[class_history_num];	//���� class ���
	WORD wHP;		
	WORD wSP;		
	WORD wFP;		
	WORD wMaxHP;			
	WORD wMaxSP;			
	WORD wMaxFP;			
	WORD wMapIndex;		//���ε���	
	short zPos[3];		//��ġ

	struct _list_equip{
		char sTableCode;	//table code	.. �� �����̸� -1
		WORD wItemIndex;	//item index
		DWORD dwUptInfo;//���׷��̵�����..�����ʺ��� 4��Ʈ�� ���׷��̵�����.. F�� ���ö��������۷����� ++�Ѵ�.
	}; 

	_list_equip EquipList[equip_fix_num];

	struct _list_embellish{
		char sTableCode;	//table code	.. �� �����̸� -1
		WORD wItemIndex;	//item index
		WORD wNum;		//ȭ���ϰ�� ��������
		char sClientIndex;	
	};
	
	_list_embellish EmbellishList[embellish_fix_num];	

	struct _list_belt{
		short zItemIndex;	//item index ��Ÿ� -1 
		BYTE byNum;		//����
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

//_movein_user_result_zone�Ŀ� �ƹ�Ÿ�����͸� �ٿ�޴´�.
//�κ��丮..
#define inven_download_request_clzo 7
struct _inven_download_request_clzo {
};

#define inven_download_result_zocl 8
struct _inven_download_result_zocl {	

	BYTE byRetCode;	//0�̸� ����..

	BYTE byBagNum;	
	BYTE bySlotNum;

	struct _list{
		BYTE byTableCode; 
		WORD wItemIndex;
		DWORD dwDurPoint;
		char sClientIndex;
		DWORD dwUptInfo;//���׷��̵�����
	}; 	
	
	_list ItemSlotInfo[bag_storage_num];

	int size(){
		if(byRetCode != 0)
			return sizeof(byRetCode);
		return sizeof(*this)-sizeof(_list)*(bag_storage_num-bySlotNum);
	}
};

//���� ����ġ..
#define cum_download_request_clzo 9
struct _cum_download_request_clzo { 
};

#define cum_download_result_zocl 10
struct _cum_download_result_zocl {

	BYTE byRetCode;	//0�̸� ����..

	_STAT_DB_BASE Stat;	

	BYTE byLeftCuttingResNum;				
	WORD wleftResList[left_cutting_num];	//..��������Ʈ: res�ε���, ��������Ʈ: res����

	int size(){
		if(byRetCode != 0)
			return sizeof(byRetCode);
		return sizeof(*this)-sizeof(WORD)*(left_cutting_num-byLeftCuttingResNum);
	}
};

//�����κ�����
#define force_download_request_clzo 11
struct _force_download_request_clzo {

};

#define force_download_result_zocl 12
struct _force_download_result_zocl {

	BYTE byRetCode;	//0�̸� ����..

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
		char sItemIndex;	//item index ��Ÿ� -1 
		DWORD dwExp;		//������ ���� �ɹ��������..
		DWORD dwParam;		//	_animus_param ���� ����ȯ�Ұ�..(CharacterDB.h)		//������ ���׷��̵� �ɹ��������..
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
	BYTE byAmount;	//��ø�������ϰ�� ����..
	WORD wBoxIndex;	
	DWORD dwOwerSerial;	//1���� �������մ� �Ǹ���..
	_CHRID idDumber;	//�������.. ����������������� 0xFF..
	BYTE byState;
	short zPos[3];
};

#define parkingunit_create_zocl 124
struct _parkingunit_create_zocl{

	WORD wObjIndex;
	DWORD dwObjSerial;
	BYTE byCreateType;	//#define unit_create_type_delivery	0	//���	//#define unit_create_type_leave		1	//����
	BYTE byFrame;
	BYTE byPart[UNIT_PART_NUM];
	DWORD dwOwerSerial;	
	short zPos[3];
	BYTE byTransDistCode;	//#define unit_trans_short_range		0	//���� �ٰŸ����� #define unit_trans_long_range		1	//���� ���Ÿ�����
};	

#define player_destroy_zocl 15
struct _player_destroy_zocl{	//����������//

	WORD wIndex;
	DWORD dwSerial;

	BYTE byState; //0: ��������, 1: ���̵�
};

#define player_die_zocl 16
struct _player_die_zocl{	//��ü�� ����//

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

//#define tower_des_type_back			0	//ȸ��
//#define tower_des_type_destroy		1	//�ı�
//#define tower_des_type_disconnect	2	//��ġ�� ��������

	BYTE byDestroyCode;	//�¾��׳�..ȸ����..
};

#define itembox_destroy_zocl 18
struct _itembox_destroy_zocl{

	WORD wIndex;
};

#define parkingunit_destroy_zocl 188
struct _parkingunit_destroy_zocl{

	WORD wObjIndex;
	DWORD dwObjSerial;
	BYTE byDestroyCode;//#define unit_destory_type_return	0	//�԰�#define unit_destory_type_take		1	//����
};

#define other_shape_request_clzo 19
struct _other_shape_request_clzo	{

	WORD wIndex;	//���ĳ������ �ε���
	
	enum { SHAPE_ALL = 0, SHAPE_PART };

	BYTE byReqType;	//�䱸����(0�̸� ÷���� ���(other_shape_all_zocl). 1�̸� �ٽø��� ������ �ٸ� ���)..
};

#define other_shape_all_zocl 20
struct _other_shape_all_zocl	{	//_other_shape_request_clzo�� ����� ÷���� ����ϰ��..	

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;
		
	BYTE byRecIndex;
	BYTE byFaceIndex;	
	BYTE byHairIndex;
	WORD wModelPerPart[equip_fix_num];//���� 4��Ʈ.. ���׷��̵巹��..  ������ 0xFFFF
	BYTE byUserGrade;	//������� 
	char szName[max_name_len+1];	

	BYTE byUnitFrameIndex;	//��Ÿ�������� 0xFF..
	BYTE byUnitPartIndex[UNIT_PART_NUM];	//byUnitFrameIndex�� 0xFF�� ����..

	_other_shape_all_zocl(){
		byUnitFrameIndex = 0xFF;
	}

	int size(){
		if(byUnitFrameIndex != 0xFF) return sizeof(*this);
		return sizeof(*this) - sizeof(byUnitPartIndex);
	}
};

#define other_shape_part_zocl 21
struct _other_shape_part_zocl	{		//_other_shape_request_clzo�� ����� ������ �ٲ� ����ϰ��..

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;
		
	WORD wModelPerPart[equip_fix_num];	//���� 4��Ʈ.. ���׷��̵巹��..  ������ 0xFFFF

	BYTE byUnitFrameIndex;	//��Ÿ�������� 0xFF..
	BYTE byUnitPartIndex[UNIT_PART_NUM];	//byUnitFrameIndex�� 0xFF�� ����..

	_other_shape_part_zocl(){
		byUnitFrameIndex = 0xFF;
	}

	int size(){
		if(byUnitFrameIndex != 0xFF) return sizeof(*this);
		return sizeof(*this) - sizeof(byUnitPartIndex);
	}
};

#define other_shape_failure_zocl 22
struct _other_shape_failure_zocl	{		//_other_shape_request_clzo�� ����� ��������

	WORD wOtherIndex;

	enum { NOT_LIVE = 0, NOT_SERIAL };

	BYTE byErrCode;
};

#define other_shape_change_zocl 23
struct _other_shape_change_zocl	{	//���� �÷��̾ ������ �ٲ۰��

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;

	BYTE byPartIndex;
	WORD wItemIndex;	//���� 4��Ʈ.. ���׷��̵巹��..  
};

#define other_unit_ride_change_zocl 233
struct _other_unit_ride_change_zocl	{	//���� �÷��̾ ���� �������� �ٲ۰��

	WORD	wIndex;
	DWORD	dwSerial;
	WORD	wEquipVer;

	bool	bTake;				//������ true, ������ false
	DWORD	dwUnitSerial;		//�𸣴� �ø����� ���.. �ٱ� ���Ϳ� �ִ� ����.. �÷��̾ ���͹����� ��������.. ���߿� ������ _other_shape_part_zocl�� ���ι޴´�..
	short	zNewPos[3];			//������ ������..
};

//�ڽ��� ���ο���� ���ϰ� ��Ÿ����.. ������ �÷��̾�� �Ѹ���.
#define other_new_view_zocl 24
struct _other_new_view_zocl{	

	WORD wIndex;
	DWORD dwSerial;
	WORD wEquipVer;
	short zPos[3];
	BYTE byRaceCode;

	//byViewType----
	//#define mapin_type_start		0	//���ӽ���		
	//#define mapin_type_move		1	//��Ż�̵�..
	//#define mapin_type_revival	2	//��Ȱ
	//#define mapin_type_goto		3	//�����̵�
	//#define mapin_type_recall     4	//�⵿..

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
	BYTE byZoneCode;	//0�̸� ���� ��.. 1�̸� �ٸ���.. => move_out�� ������.
};

#define other_map_out_zocl 30
struct _other_map_out_zocl{

	BYTE byMapOutType;
	DWORD dwSerial;
	BYTE byNextMap;	//������ ���� ����..�𸣴°��� 0xFF
};

//��Ȱ..
#define player_resurrect_zocl 31
struct _player_resurrect_zocl{

	BYTE byRet;
	BYTE byLevel;
	WORD wCurHP;
	WORD wCurFP;
	WORD wCurST;
};

#define exit_save_data_request_clzo 32
struct _exit_save_data_request_clzo {		//�ٲ�͸�����..����..

	WORD wDataSize;

//inven �����[1], { serial[2], client_index[1] }
///belt �����[1], { serial[2], client_index[1] }
///link �����[1], { effectcode[1], effectindex[1], client_index[1] }
///embell �����[1], { serial[2], client_index[1] }

	char sData[0x0FFF];

	int size(){
		return sizeof(*this)-sizeof(char)*(0x0FFF-wDataSize);
	}			
};

#define exit_save_data_result_zocl 33
struct _exit_save_data_result_zocl {
	
	BYTE byRetCode;	//0;//����, 1;//�ø���Ʋ�� 2;//�̹��ε�������

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
	short zCur[3];	//xyz..�������� ��ġ..
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
	WORD wLastEffectCode; //�ֱٿ� �ɸ� ȿ���ڵ�..(���� 4��Ʈ.. ȿ���ڵ�(effect_code_skill, effect_code_force, effect_code_class).. �������ʹ� �ε���..
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
	WORD wCompLeftSec;	//�� �������� �����ð�..(0�̸� �� ���� Ÿ��)
};

#define itembox_fixpositon_zocl 9	
struct _itembox_fixpositon_zocl{

	BYTE byItemTableCode;
	WORD wItemRecIndex;
	BYTE byAmount;	//��ø�������ϰ�� ����
	WORD wItemBoxIndex;
	DWORD dwOwerSerial;	//���� ������ 0xffff
	short zPos[3];
	BYTE byState;	//0: normal(�����ڸ��� �������մ»���) 
					//1: open(�������� ������ �ִ� ����) 
					//2: hurry(�Ҹ��ӹ�,������)
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
	WORD wLastEffectCode; //�ֱٿ� �ɸ� ȿ���ڵ�..(���� 1��Ʈ.. ȿ���ڵ�(effect_code_skill, effect_code_force..).. �������ʹ� �ε���.. 
	DWORD dwStateFlag; 
	BYTE byAddSpeed;	//ȿ�������� �����Ŵ� �̵��ӵ�
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

	WORD wItemSerial;	//town item �ø���(0xFFFF�� �����ʱ���ġ..���ڹ���) 
};

#define goto_baseportal_result_zocl 18
struct _goto_baseportal_result_zocl {

	BYTE byRet;//0;//����//1;//��ü������ 2;//��Ż�������� 3;//��ǥ ������ 4;//�ٸ�������
	BYTE byMapCode;	
	short zPos[3];
};

#define goto_avator_request_clzo 19
struct _goto_avator_request_clzo {		

	char szAvatorName[max_name_len+1];
};

#define goto_avator_result_zocl 20	
struct _goto_avator_result_zocl {	

	BYTE byRet;//0;//����//1;//�������� ���� 2;//����
	BYTE byMapCode;
	float fStartPos[3];
};

#define break_stop_result_zocl 21
struct _break_stop_result_zocl {	//..���̵��� �������� �߰��� ������ϴ°��..

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
	WORD wBulletSerial;	//	==> bullet�� ������ �����̸� 0xFF
};

#define attack_skill_request_clzo 5
struct _attack_skill_request_clzo {	

	BYTE byID;				
	WORD wIndex;
	BYTE byEffectCode;	//	effect_code_skill, effect_code_class ..		
	WORD wSkillIndex;
	WORD wBulletSerial;		//bullet ���� : 0xFFFF
};

#define attack_force_request_clzo 9
struct _attack_force_request_clzo {

	BYTE byID;
	WORD wIndex;		//�������� 0xFFFF	
	short zAreaPos[2];	//x, z
	WORD wForceSerial;
};

#define attack_unit_request_clzo 240
struct _attack_unit_request_clzo {		

	BYTE byID;
	WORD wIndex;		//�������� 0xFFFF	

	//#define unit_bullet_arms			0
	//#define unit_bullet_shoulder		1
	BYTE byWeaponPart;	
};

#define attack_test_request_clzo 105
struct _attack_test_request_clzo{

	BYTE	byEffectCode;
	BYTE	byEffectIndex;
	WORD	wBulletSerial;		//bullet ���� : 0xFFFF
	BYTE	byWeaponPart;		//�����ϰ��.. ����ž�»����ϰ��ݴ�� ����.. �������� �α׸�����.
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
	bool bCritical;		//1�̸� ũ��Ƽ�ð���

	BYTE byListNum;

	struct _dam_list{
		_CHRID idDster;	
		WORD wDamage;  //������		.. 0�̸� �̽�, 0xFFFF�� �ݰݱ�ɸ����¸� ħ..
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
	bool bCritical;		//1�̸� ũ��Ƽ�ð���

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
	short zAreaPos[2];	//�������ϰ�� Ÿ����
	BYTE byAttackPart;
	bool bCritical;		//1�̸� ũ��Ƽ�ð���

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
	bool bCritical;		//1�̸� ũ��Ƽ�ð���

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
	bool bCritical;		//1�̸� ũ��Ƽ�ð���

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
	BYTE	byBulletIndex;	// => 0xFF ����..	
	BYTE	byEffectCode;	// ȿ���ڵ�.. 0xFF�� �Ϲݰ���
	BYTE	byEffectIndex;	//�Ϲ��̸� ����..
	BYTE	byEffectLv;
	BYTE	byWeaponPart;	//unit�� ���..	
	short	zTar[2];
};			

#define attack_monster_inform_zocl 249
struct _attack_monster_inform_zocl{		
	
	_CHRID	idAtter;		
	BYTE	byAttackPart;	
	bool	bCritical;			//1�̸� ũ��Ƽ�ð���

	_CHRID	idDst;		
	WORD	wDamage;
	WORD	wLeftHP;
};	

#define attack_animus_inform_zocl 248
struct _attack_animus_inform_zocl{		
	
	_CHRID	idAtter;		
	BYTE	byAttackPart;	
	bool	bCritical;			//1�̸� ũ��Ƽ�ð���

	_CHRID	idDst;		
	WORD	wDamage;
	WORD	wLeftHP;
};	

#define attack_tower_inform_zocl 136
struct _attack_tower_inform_zocl{		
	
	_CHRID	idAtter;		
	BYTE	byAttackPart;	
	bool	bCritical;			//1�̸� ũ��Ƽ�ð���

	_CHRID	idDst;		
	WORD	wDamage;
	WORD	wLeftHP;	
};	

#define monster_chase_change_zocl 13	//all
struct _monster_chase_change_zocl{

	WORD	wMonIndex;
	short	zDstIndex; //-1�� NULL
};

#define mode_change_request_clzo 14
struct _mode_change_request_clzo{

	BYTE	byModeCode;	//	��ȭ���:0, �������:1 
};

#define mode_change_result_zocl 15
struct _mode_change_result_zocl{	

	BYTE	byModeCode;	//	��ȭ���:0, �������:1 
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
	DWORD dwOwerSerial;	//���� ������ oxffff 
	BYTE byState;	//0: normal(�����ڸ��� �������մ»���) 
					//1: open(�������� ������ �ִ� ����) 
					//2: hurry(�Ҹ��ӹ�,������)
};

#define itembox_take_request_clzo 2	
struct _itembox_take_request_clzo{

	WORD wItemBoxIndex;
	WORD wAddSerial;	//�������� �������ϰ�� ���� �ø���.. �������� ������ 0xFFFF
};

#define itembox_take_new_result_zocl 3		//_itembox_take_request_clzo�� wAddSerial�� 0xFFFF�ΰ��..
struct _itembox_take_new_result_zocl{		
	
	char sErrorCode;	//1;//��������� 2;//�������۾��� 3;//������ 4;//���¹ڽ� 5;//�������� 6;//�Ÿ�����
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

#define itembox_take_add_result_zocl 4		//_itembox_take_request_clzo�� wAddSerial�� �������..
struct _itembox_take_add_result_zocl{		
	
	char sErrorCode;	//1;//��������� 2;//�������۾��� 3;//������ 4;//���¹ڽ� 5;//�������� 6;//�Ÿ�����
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

	BYTE byErrCode;	//0;//����, 1;//������ġƲ�� 2;//���¾��� 3;//�����ʰ�
};

#define use_potion_request_clzo 7
struct _use_potion_request_clzo{	
	
	_STORAGE_POS_INDIV Item;	
};

#define use_potion_result_zocl 8
struct _use_potion_result_zocl{	//one	

	BYTE byErrCode;	//0;//����, //1;//������ġƲ�� 2;//���¾��� 3;//���Ǿƴ� 4;//�����ʰ� 5;//ȸ�������� 6;//�̹���������
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

	BYTE byErrCode;	//0;//����, //1;//������ġƲ�� 2;//���¾��� 3;//���������۾ƴ� 4;//����Ҽ��������� 5;//���е���� 6;//��չ�������
};

#define embellish_request_clzo 11	//����, �����, �Ѿ�..����
struct _embellish_request_clzo{	

	_STORAGE_POS_INDIV Item;
	WORD wChangeSerial;	//�ٲٴ°Ŷ�� ���� �������� �ø���.. �ƴϸ� 0xFFFF
};

#define embellish_result_zocl 12
struct _embellish_result_zocl{	

	BYTE byErrCode;	//0;//����,
};

#define off_part_request_clzo 13
struct _off_part_request_clzo{	

	_STORAGE_POS_INDIV Item;
};

#define off_part_result_zocl 14
struct _off_part_result_zocl{

	BYTE byErrCode;	//0;//����, 
};	

//���� ��ų������� ��Ÿ��� �������Ѵ�.
#define make_item_request_clzo 15
struct _make_item_request_clzo{		

	enum { material_num = 5	};

	_STORAGE_POS_INDIV ipMakeTool;	//�������� �ִ� ��ġ
	WORD wManualIndex;			//���۸޴����ε���

	BYTE byMaterialNum;			//����� ����
	_STORAGE_POS_INDIV ipMaterials[material_num];	//����� ��ᰡ �ִ� ��ġ

	_make_item_request_clzo(){
		byMaterialNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_STORAGE_POS_INDIV)*(material_num-byMaterialNum);
	}
};

//��Ź����� Ȯ���ϰ� ���۽�ų����..
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

	BYTE byErrCode;///1;//���¾����� 2;//���۸������� 3;//���۾ȵŴ� ������ 
					//5;//���̻��ش�Ż�����߰��Ҽ����� 6;//�̾����ۿ����ش�Ż�����߰��Ҽ�����
					//100;//��������, 101;//����Ż���ı� 102;//�������ı�
};

#define downgrade_item_request_clzo 19
struct _downgrade_item_request_clzo {	

	_STORAGE_POS_INDIV m_posUpgItem;	
	_STORAGE_POS_INDIV m_posTalik;
	_STORAGE_POS_INDIV m_posToolItem;
};

#define downgrade_item_result_zocl 20
struct _downgrade_item_result_zocl {

	BYTE byErrCode;////1;//����Ż�� 2;//�߸���Ż�� 3;//������ 4;//���¾����� 5;//���۾ȵŴ� ������ 6;//���ۉ¾��۾ƴ?
};

#define add_bag_request_clzo 21	
struct _add_bag_request_clzo {	

	WORD wBagItemSerial;
};

#define add_bag_result_zocl 22
struct _add_bag_result_zocl {	

	BYTE byErrCode; //0;//����, 1;//���°��� 2;//5���پ�������
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

	BYTE byRet;	////1;//�߸�����Ż���?2;//��Ż������ġ 3;//�߸��¸��ڵ?4;//�߸�����Ż�ڵ?5;//������ǥ�������� 
	BYTE byMapIndex;	//���� �ʰ� �ٸ���� ���ο� ���� �ε�.. �ε��� �ε�Ϸ� �޽����� ��������
	float fStartPos[3];
	BYTE byZoneCode;	//0�̸� ���� ��.. 1�̸� �ٸ���.. => move_out�� ������.
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

#define chat_far_failure_zocl 5//�÷��̾ ��ã�Ѵ�..
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

//#define CHAT_TYPE_OPERATOR		0 //���..
//#define CHAT_TYPE_CIRCLE		1 //�ֺ���ü��..
//#define CHAT_TYPE_WHISPER		2 //�ø����ȣ�� �ƴ»��� �ϴ���..
//#define CHAT_TYPE_FAR_WHISPER	3 //�ø����ȣ�� �𸣴»��� �ϴ���..
//#define CHAT_TYPE_PARTY			4 //��Ƽ���鿡��..
//#define CHAT_TYPE_RACE		5    //��������

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

//#define CHAT_TYPE_OPERATOR		0 //���..
//#define CHAT_TYPE_CIRCLE		1 //�ֺ���ü��..
//#define CHAT_TYPE_WHISPER		2 //�ø����ȣ�� �ƴ»��� �ϴ���..
//#define CHAT_TYPE_FAR_WHISPER	3 //�ø����ȣ�� �𸣴»��� �ϴ���..
//#define CHAT_TYPE_PARTY			4 //��Ƽ���鿡��..
//#define CHAT_TYPE_RACE		5    //��������
//#define CHAT_TYPE_MGRWSP		6 //��ڱӸ�

	BYTE byMessageType;	
	char szSenderName[max_name_len+1];	//NULL ����..

	BYTE bySize;
	char sChatData[max_message_size];	//���ϴ»�� �̸� ����

	int size()
	{
		return sizeof(*this)-(max_message_size-bySize);
	}
};

#define chat_lock_inform_zocl	19
struct _chat_lock_inform_zocl {	//add(4/19)

	bool	bLock;	//true�� �� ����..

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

	DWORD dwSerial;//�÷��̾��� �ø���..
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

	WORD wExpRate;	//������..
};	

#define change_class_command_zocl 5	
struct _change_class_command_zocl {		//���� ���

	WORD	wCurClassIndex;

};

#define select_class_request_clzo 6	
struct _select_class_request_clzo {		//class ����

	WORD	wSelClassIndex;
};

#define select_class_result_zocl 7	
struct _select_class_result_zocl {		//�ڽſ��� �������

	BYTE	byRetCode;
};

#define change_class_other_zocl 8	
struct _change_class_other_zocl {		//�ֺ����� ȿ�������ֱ�����.

	DWORD	dwPlayerSerial;
	WORD	wClassIndex;
};

#define reward_add_item_zocl 9	
struct _reward_add_item_zocl {	//������ ����(����, ����Ʈ ����)

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

	BYTE byStoreIndex;	//���� �ε���
	BYTE byBuyNum;	//ǰ���

	struct _list{
		BYTE byStorageCode;//�κ��丮: 0, ���: 1 ���: 2, ��Ʈ:3, ����:4
		DWORD dwGoodSerial;//�Ϲ��� �ε���
		BYTE byAmount;	
	};

	_list OfferList[trade_item_max_num];	//��������Ʈ:��ǰ��ȣ, ��������Ʈ:�찹��

	_buy_store_request_clzo(){
		byBuyNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-byBuyNum);
	}
};

#define buy_store_success_zocl 4
struct _buy_store_success_zocl{

	DWORD dwLeftDalant;	//���� �޶�Ʈ	
	DWORD dwLeftGold;	//���� ���		
	DWORD dwConsumDanlant;	//�Ҹ� �޶�Ʈ	
	DWORD dwConsumGold;	//�Ҹ� ���		
	BYTE  byDiscountRate;//������(�����)

	BYTE byBuyNum;	//ǰ���

	struct _list{
		WORD wSerial;
	};

	_list OfferList[trade_item_max_num];

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-byBuyNum);
	}
};

#define buy_store_failure_zocl 5
struct _buy_store_failure_zocl{	//�� ���н� ������ ǰ���� ������ ������

	DWORD dwDalant;	//�����ڱ�
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

	WORD wStoreIndex;	//���� �ε���
	BYTE bySellNum;	//ǰ���

	struct _list{
		BYTE byStorageCode;//�κ��丮: 0, ���: 1 ���: 2, ��Ʈ:3, ����:4
		WORD wSerial;
		BYTE byAmount;
	};

	_list Item[trade_item_max_num];	//��������:��ǰ�ø���, ��������Ʈ:�Ȱ���

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-bySellNum);
	}
};

#define sell_store_result_zocl 7
struct _sell_store_result_zocl{	

	BYTE bSucc;	//true �� ����
	DWORD dwLeftDalant;	//���� �޶�Ʈ	
	DWORD dwLeftGold;	//���� ���		
	DWORD dwProfitDanlant;	//�� �޶�Ʈ	
	DWORD dwProfitGold;	//�� ���
	BYTE  byDiscountRate;//������(�����) 
	
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

	BYTE byStoreIndex;	//���� �ε���
	BYTE byItemNum;	//ǰ���

	struct _list{
		BYTE byPositon;	//�κ��丮: 0, ���: 1 ���: 2, ��Ʈ:3, ����:4 ��ũ:5..
		WORD wSerial;
	};

	_list Item[trade_item_max_num];	//��������:��ǰ�ø���, ��������Ʈ:�Ȱ���

	_repair_request_clzo(){
		byItemNum = 0;
	}

	int size(){
		return sizeof(*this)-sizeof(_list)*(trade_item_max_num-byItemNum);
	}
};

#define repair_result_zocl 9
struct _repair_result_zocl{	

	BYTE bSucc;	//true �� ����
	DWORD dwLeftDalant;	//���� �޶�Ʈ	
	DWORD dwLeftGold;	//���� ���		
	DWORD dwConsumDanlant;	//�Ҹ� �޶�Ʈ	
	DWORD dwConsumGold;	//�Ҹ� ���	
	
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

	BYTE byErrCode;	//0;//����, 1;//�ݾ׺��� 
	DWORD dwLeftGold;		
	DWORD dwLeftDalant;
};

#define economy_history_inform_zocl 15	//	������ǥ�����丮(����ȯ��) ���ӽÿ� �ѹ� ������
struct _economy_history_inform_zocl {	//upt(4/19).. 

	WORD wEconomyGuide[RACE_NUM][MAX_ECONOMY_HISTORY];	//0~11.. 0: ����..11: �ֱ�	//
};

#define economy_rate_inform_zocl 16	//	������ǥ(����ȯ��) ���ӽÿ� ����ɶ����� 3����..
struct _economy_rate_inform_zocl {	

	bool	bStart;	//true�� ÷ ���� ���۽� �޴°����� wEconomyGuide�� �������� �ʴ´�.. false�ϰ�츸 �Ʒ��� �����ؼ� history�� �߰�..
	float	fPayExgRate;
	float	fTexRate;
	WORD	wMgrValue;	//������	//add(4/22)
	WORD	wEconomyGuide[RACE_NUM];	//upt(4/19)

	int size()	{	if(bStart) return sizeof(*this)-sizeof(wEconomyGuide); return sizeof(*this);	}
};

//
//ui_msg	13
//

#define sf_link_change_result_zocl 2
struct _sf_link_change_result_zocl{

	BYTE bySize;	//0�̸� ����
	char szErrorCode[max_error_code_size];

	int size(){
		return sizeof(*this)-(max_error_code_size-bySize);
	}
};

#define force_inven_change_request_clzo 3
struct _force_inven_change_request_clzo{	

	_STORAGE_POS_INDIV Item;	
	WORD wReplaceSerial;	//����̵��� 0xffff
};

#define force_inven_change_result_zocl 4
struct _force_inven_change_result_zocl{	

	BYTE byErrCode;
};

#define animus_inven_change_request_clzo 113
struct _animus_inven_change_request_clzo{		

	_STORAGE_POS_INDIV Item;	
	WORD wReplaceSerial;	//����̵��� 0xffff
};

#define animus_inven_change_result_zocl 114
struct _animus_inven_change_result_zocl{		

	BYTE byErrCode;
};

#define res_separation_request_clzo 11	//inventory����� ������.
struct _res_separation_request_clzo{		

	WORD wStartSerial;
	BYTE byMoveAmount;
};

#define res_separation_result_zocl 12	
struct _res_separation_result_zocl{

	BYTE byErrCode;	//0: ����, 1: �������ڸ� , 2: �����̵���, 3: �ڿ�,�����̾ƴ� 4: �����κ��丮����, 5: �׷��ø������ 6: ��������ʴ°���
	WORD wParentSerial;
	BYTE byParentAmount;
	WORD wChildSerial;
	BYTE byChildAmount;
};

#define res_division_request_clzo 13	//�ٸ� inventory�� ������ ���ս�Ų��.
struct _res_division_request_clzo{	

	WORD wStartSerial;	
	WORD wTarSerial;
	BYTE byMoveAmount;
};

#define res_division_result_zocl 14
struct _res_division_result_zocl{

	BYTE byErrCode;	//0: ����, 1: �������ڸ�, 3: �ڿ�,�����̾ƴ�, 4: �����������̵�, 5: �׷��ø������, 6: �����������ڿ�,�����ƴ�. 7: ��������ʴ°���, 8: �������̵��� 9: �̵��Ұ��̳�ħ
	WORD wParentSerial;		//0xFFFF�̸� ���Ի���
	BYTE byParentAmount;	
	WORD wChildSerial;		//new serial
	BYTE byChildAmount;
};

#define potionsocket_change_request_clzo 15
struct _potionsocket_change_request_clzo{

	_STORAGE_POS_INDIV Item;
	_STORAGE_POS_INDIV TarPos;//��ĭ���� �̵���  _STORAGE_POS_INDIV::wItemSerial = 0xFFFF..
	BYTE byStorageCode;	//upt(4/24).. ������ ��ĭ���� �̵�..(ydq)
};

#define potionsocket_change_result_zocl 16
struct _potionsocket_change_result_zocl{	

	BYTE byErrCode;	//0: ����, 1;//��밡�ɰ���ƴ� 2;//������������ 3;//���Ǿƴ� 4;//�ű��������
};

#define potionsocket_separation_request_clzo 17	//inventory����� ������.
struct _potionsocket_separation_request_clzo{		

	struct _pos{
		BYTE byPositon;	//�κ��丮: 0, ��Ʈ: 1, 
	};

	_pos StartPos;	
	_pos TargetPos;
	WORD wStartSerial;
	BYTE byMoveAmount;

};

#define potionsocket_separation_result_zocl 18
struct _potionsocket_separation_result_zocl{

	char sErrorCode;	//0: ����, -1: �������ڸ� , -2: �����̵���, -3: ������ �ƴϴ�. -4: ���� �κ��丮�� ����, -5: �׷� �ø����� ����
	WORD wParentSerial;
	BYTE byParentAmount;
	WORD wChildSerial;
	BYTE byChildAmount;
};

#define potionsocket_division_request_clzo 19	//�ٸ� inventory�� ������ ���ս�Ų��.
struct _potionsocket_division_request_clzo{	

	struct _pos{
		BYTE byPositon;	//�κ��丮: 0, ��Ʈ: 1, 
	};

	_pos StartPos;	
	_pos TargetPos;
	WORD wStartSerial;	
	WORD wTarSerial;
	BYTE byMoveAmount;
};

#define potionsocket_division_result_zocl 20	
struct _potionsocket_division_result_zocl{

	char sErrorCode;	//0: ����, -1: ���� ���ڸ�, -3: ������ �ƴϴ�, -4: �� ���� ���� �̵�, -5: �׷� �ø����� ����, -6: ���� ������ ������ �ƴ�.
	WORD wSerial;	//���и� byParentAmount ���� 0xffff�� ��
	BYTE byParentAmount;	//0�̸� ���� ����
	WORD wChildSerial;	
	BYTE byChildAmount;
};

//
//resource_msg	14
//

#define mine_start_request_clzo 1
struct _mine_start_request_clzo {

	BYTE byMineIndex;//���� ���� �ε��� 
};

#define mine_start_result_zocl 2
struct _mine_start_result_zocl {

	BYTE byErrCode;	//0: ����, 2: ��������, 3: ä����񿡷�, 4: ���� ä�������
	DWORD dwMineDelayTime;	//ä���ð�	
};

#define mine_cancle_request_clzo 3	
struct _mine_cancle_request_clzo {

	WORD wBatterySerial;	//�ٶ��� �ø���
};

#define mine_cancle_result_zocl 4
struct _mine_cancle_result_zocl {

	BYTE byErrCode;	//0: ����, 1: �ٶ�������, 3: �����ð� ���� 4:ä����񿡷�
	WORD wBatteryLeftDur;	//���� �ٶ��� �뷮
	WORD wEquipLeftDur;		//���� ä����� ������
};

#define mine_complete_request_clzo 5
struct _mine_complete_request_clzo {

	WORD wBatterySerial;	//�ٶ��� �ø���			
	BYTE byOreIndex;	//�������� �ε���
};

#define mine_complete_result_zocl 6
struct _mine_complete_result_zocl {

	BYTE byErrCode;//0: ����, 1: �����ð�����, 2: �������濡��, 3: ������������, 4:������������,5: ���͸� ����, 6;ä����� ����
	WORD wEquipLeftDur;		//���� ä����� ������
	WORD wBatteryLeftDur;	//���� �ٶ��� �뷮

	BYTE byOreIndex;
	WORD wOreSerial;
	BYTE byOreDur;	//1�̸� �� �ø����� ���ο� �ø��� 1�̻��̸� ���� �ø���
	
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

	BYTE byErrCode;	//0:���� 1:���� ����, �ø������ 2:�������� 3:�����ݺ��� 4:�����ӽð��� �Ⱥ�� 
	BYTE byLeftNum;
	DWORD dwLeftDalant;
	DWORD dwConsumDalant;
	
	BYTE byCuttingNum;

	struct _list {
		WORD wResIndex;		//�ڿ��δ콺
		BYTE byAddAmount;	//�߰��Ǵ� ��
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
	WORD wSerial; //����� �����Ŷ�� 0xFFFF
	BYTE byAddAmount;//�߰��Ǵ� ��
};

#define ore_into_bag_result_zocl 10
struct _ore_into_bag_result_zocl {

	BYTE byErrCode;	//0:���� 1:�������ƴ� 2:�ڿ����ų����� 3:��밡��ƴ� 4:����������� 5:���濡���½��� 6:���Դ�뷮�ʰ�, 7:����������̴ٸ�
	WORD wNewSerial; //���ο� �ø���.. ���������� �������� �����ǽø���
};

#define cutting_complete_request_clzo 11
struct _cutting_complete_request_clzo {

	BYTE byNpcRace;	//npc����.. 0:������, 1:�ڶ� 2:��ũ���þ� 
};

#define cutting_complete_result_zocl 12	
struct _cutting_complete_result_zocl {

	DWORD dwLeftGold;
};

//
//party_msg		16
//

//Ư������� ��Ƽ������ ������û
//���ǻ���.. �ڽ��� ���ҼӶǴ� ����..���� ���Ҽ��λ��¿����� ��û����
#define party_join_invitation_clzo 1
struct _party_join_invitation_clzo {

	WORD wDstIndex;
};

//Ư������ �ڽſ��� ��Ƽ�� ������û��
#define party_join_invitation_question_zocl 2
struct _party_join_invitation_question_zocl {
	
	_CLID idBoss;
};

//Ư������ �ڽſ��� ��Ƽ�� ������û�� �亯
#define party_join_invitation_answer_clzo 3
struct _party_join_invitation_answer_clzo {

	_CLID idBoss;
};

//Ư����Ƽ�忡�� �ڽ��� ��Ƽ������ ������û
//���ǻ���.. �ڽ��� ���Ҽ�.. ���� �����λ��¿����� ��û����
#define party_join_application_clzo 4
struct _party_join_application_clzo {

	WORD wBossIndex;
};

//Ư������ �ڽſ��� ��Ƽ������ ������
#define party_join_application_question_zocl 5
struct _party_join_application_question_zocl {

	_CLID idApplicant;
};

//Ư������ �ڽſ��� ��Ƽ������ ������û�� �亯
#define party_join_application_answer_clzo 6
struct _party_join_application_answer_clzo {
	
	_CLID idApplicant;
};

//������û�¶��� �ڽſ��� ����������Ʈ�� ����..
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

//������û�¶��� �����������鿡�� ��û�¶��� �˸�..
#define party_join_member_result_zocl 8
struct _party_join_member_result_zocl {

	DWORD dwJoinerSerial;
	char szJoinerName[max_name_len+1];
};


//������ �������� Ż������ ��û
#define party_leave_self_request_clzo 9
struct _party_leave_self_request_clzo {

};

//������ �������� Ż������ �ڽ��������������� �˸�..
//������ Ż���ǰ�� ���������ڰ� ������ �°�
#define party_leave_self_result_zocl 10
struct _party_leave_self_result_zocl {

	DWORD dwExiterSerial;		//0xFF�̸� ���и޽���..�ڽſ��Ը�
	bool bWorldExit;	

};

//�������� �����Ŵ�� ��û
#define party_leave_compulsion_request_clzo 11
struct _party_leave_compulsion_request_clzo {

	DWORD dwExiterSerial;
};

//�������� ������� �ٸ����������� �˸�..
#define party_leave_compulsion_result_zocl 12
struct _party_leave_compulsion_result_zocl {

	DWORD dwExiterSerial; //0xFF�̸�  ���и޽���..�ڽſ��Ը�
};

//������ ��ü��û..������ ����
#define party_disjoint_request_clzo 13
struct _party_disjoint_request_clzo {

};

//������ ��ü�����?���������� �˸�..
#define party_disjoint_result_zocl 14
struct _party_disjoint_result_zocl {
	
	BYTE bySuccess;	//(bool) false�� �ڽſ��Ը� ��.. true�� �� ��Ƽ������..
};

//�����°��û
#define party_succession_request_clzo 15
struct _party_succession_request_clzo {

	DWORD dwSuccessorSerial;
};

//�����°� �˸�
#define party_succession_result_zocl 16
struct _party_succession_result_zocl {

	DWORD dwSuccessorSerial;	//0xff�̸� ����.. �ڱ����׸�..
};

//��Ƽ��� ��ݿ�û
#define party_lock_request_clzo 115
struct _party_lock_request_clzo {

	bool bLock;	//true..���.. false.. ǰ..	
};

//��Ƽ��� ��ݿ�û �˸�
#define party_lock_result_zocl 116
struct _party_lock_result_zocl {	

	BYTE byLock;	//1..���.. 0.. ǰ..	0xFF : ����..
};

#define party_member_info_upd 17
struct _party_member_info_upd {

	DWORD dwMemSerial; //�ɹ��� �ø���.
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
		WORD wEffectCode;	//�ǿ��ʺ�Ʈ... effect_code.. �״������� SFIndex..	
		BYTE byEffectLv;	
		WORD wLeftSec;//�������ϼ��� �ֱٿ� �ɸ���..	//upt(4/24)
	};	

	_EFFECT Effect[CONT_SF_SIZE*2];
	
	int size(){ return sizeof(*this)-sizeof(_EFFECT)*(CONT_SF_SIZE*2-byContEffectNum); }
};

#define party_member_hp_upd 18
struct _party_member_hp_upd {	

	DWORD dwMemSerial; //�ɹ��� �ø���.
	WORD wHP;
};

#define party_member_fp_upd 19
struct _party_member_fp_upd {	

	DWORD dwMemSerial; //�ɹ��� �ø���.
	WORD wFP;
};

#define party_member_sp_upd 118
struct _party_member_sp_upd {	

	DWORD dwMemSerial; //�ɹ��� �ø���.
	WORD wSP;
};

#define party_member_lv_upd 119	
struct _party_member_lv_upd {	

	DWORD dwMemSerial; //�ɹ��� �ø���.
	BYTE byLv;
};

#define party_member_pos_upd 120	
struct _party_member_pos_upd {	

	DWORD dwMemSerial; //�ɹ��� �ø���.
	BYTE byMapCode;
	short zPos[2];
};

#define party_member_max_hfsp_upd 121
struct _party_member_max_hfsp_upd {

	DWORD dwMemSerial; //�ɹ��� �ø���.
	WORD wMaxHP;
	WORD wMaxFP;
	WORD wMaxSP;
};

#define party_member_effect_upd 20
struct _party_member_effect_upd {

	DWORD dwMemSerial; //�ɹ��� �ø���.
	BYTE byAlterCode;	//0: ����.. 1: ����..
	WORD wEffectCode;	//�ǿ��ʺ�Ʈ... effect_code.. �״������� SFIndex..
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

//������û..�Ͻú���, ����..
#define force_request_clzo 1
struct _force_request_clzo {

	WORD wForceSerial;
	_CHRID idDst;//�������..	
};

//������ �ڽſ��� �˸�
#define force_result_one_zocl 2
struct _force_result_one_zocl {

	BYTE byErrCode;//0:����, //1:��������������, //2:FP���� //3:���´�� 4;//�Ͻú���,���Ӿƴ� 5;//����Ҽ��������� 6;//�������غ�������������� 7;//�����̵溸������������� 8;//�������� 100;//�÷��̾� ��Ȳ�� �����ϴ� ����
	DWORD dwLeftFP;	//del(4/27)
	DWORD dwItemCum; //���������ۼ�������ġ..
};

//������ ����� �ֺ��� �˸�
#define force_result_other_zocl 3
struct _force_result_other_zocl {
	
	BYTE byRetCode;	//0�̸� ����..	
	BYTE byForceIndex;
	BYTE byForceLv;
	_CHRID idPerformer;	//������
	_CHRID idDster;		//�������..
};

//��ų��û..�Ͻú���, ����..
#define skill_request_clzo 4	
struct _skill_request_clzo {
	
	BYTE bySkillIndex;
	_CHRID idDst;//�������..	
};

//��ų�� �ڽſ��� �˸�
#define skill_result_one_zocl 5
struct _skill_result_one_zocl {

	BYTE byErrCode;//0:����, //1:�Ҽ����½�ų //2:FP���� //3:���´�� 4;//�Ͻú���,���Ӿƴ� 5;//����Ҽ����½�ų 6;//�����̵溸����ų������� 7;//��������, 100;//�÷��̾� ��Ȳ�� �����ϴ� ��ų
	DWORD dwLeftFP;	//del(4/27)
};

//��ų�� ����� �ֺ��� �˸�
#define skill_result_other_zocl 6
struct _skill_result_other_zocl {
	
	BYTE byRetCode;	//0�̸� ����..
	_CHRID idPerformer;	//������
	_CHRID idDster;		//�������..
	BYTE bySkillIndex;
	BYTE bySkillLv;
};

//Ŭ������ų��û..�Ͻú���, ����..
#define class_skill_request_clzo 44	
struct _class_skill_request_clzo {
	
	WORD wSkillIndex;
	_CHRID idDst;//�������..	
};

//��ų�� �ڽſ��� �˸�
#define class_skill_result_one_zocl 45
struct _class_skill_result_one_zocl {

	BYTE byErrCode;//0:����, //1:�Ҽ����½�ų //2:FP���� //3:���´�� 4;//�Ͻú���,���Ӿƴ� 5;//����Ҽ����½�ų 6;//�����̵溸����ų������� 7;//��������, 100;//�÷��̾� ��Ȳ�� �����ϴ� ��ų
	WORD wLeftFP;	//del(4/27)(ydq, why delete?)
};

//��ų�� ����� �ֺ��� �˸�
#define class_skill_result_other_zocl 46
struct _class_skill_result_other_zocl {
	
	BYTE byRetCode;	//0�̸� ����..
	_CHRID idPerformer;	//������
	_CHRID idDster;		//�������..
	WORD wSkillIndex;
};

#define effect_add_inform_zocl 7
struct _effect_add_inform_zocl {

	BYTE byLv;	
	WORD wEffectCode;	//�ǿ��ʺ�Ʈ... effect_code.. �״������� SFIndex..
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
						
	BYTE byStorageCode;	//�κ��丮:0, ���:1, ���: 2, ��Ʈ:3, ����:4, ��ũ:5
	BYTE byTableCode;	
	WORD wItemIndex;	
	DWORD dwDurPoint;	//��ø�������� ����.. ������������ ��������(�Ѱ賻����) ��������(���系����)
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
		BYTE byMaterSlotIndex;	//����Ÿ�������� �ʵ��� ������� �ʵ��� ���� 0 ~ 2
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

#define back_tower_request_clzo 17	//Ÿ����ü
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
	WORD	wLeftHP;	//0�̸� �ı�..
};

#define tower_complete_inform_zocl 20	//����Ÿ���ϼ�..
struct _tower_complete_inform_zocl {		//add(4/24)

	DWORD	dwTowerObjSerial;
};

#define alter_cont_effect_time_zocl 21	//�ɷ��ִ� ����ȿ���� ���� �ð��� �ٲ�
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
struct _d_trade_ask_request_clzo {	//wDstIndex���� �ŷ��� ��û

	WORD wDstIndex;	
};

#define d_trade_ask_result_clzo 2
struct _d_trade_ask_result_clzo {	//d_trade_ask_request_clzo�� ����� �ڽ����׿�

	BYTE byErrCode;//0;����//1;//�ڽ����̹�Ʈ���̵��� 2;//�Ÿ����� 3;//��ȿ�Ѵ��ƴ� 4;//��밡Ʈ���̵���
};

#define d_trade_ask_inform_zocl 3
struct _d_trade_ask_inform_zocl {	//idAsker�� �ڽ����� �ŷ��� ������

	_CLID idAsker;
};

//ANSWER
#define d_trade_answer_request_clzo 4
struct _d_trade_answer_request_clzo {	//���Ǹ� �޾Ƶ���

	_CLID idAsker;
};

#define d_trade_answer_result_zocl 5	//���нÿ���..
struct _d_trade_answer_result_zocl {	//���� �޾Ƶ����� ����	

	BYTE byErrCode;	//1;//��ȿ��ask���ƴ� 2;//asker���̹�Ʈ���̵��� 3;//answer���̹�Ʈ���̵��� 4;//asker���ڽ�����û�߾ƴ� 5;//�Ÿ��� �� 6;//��ȿ�� ����� �ƴ�
};

//START
#define d_trade_start_inform_zocl 6
struct _d_trade_start_inform_zocl {	//�ŷ������ ������ �κ��丮 ��ĭ��..��ĭ����ŭ �ŷ�����

	_CLID idAsker;
	BYTE byAskerEmptyNum;	
	_CLID idAnswer;
	BYTE byAnswerEmptyNum;	
};

//CANCLE
#define d_trade_cancle_request_clzo 7
struct _d_trade_cancle_request_clzo {	//�ŷ����

};

#define d_trade_cancle_result_zocl 8
struct _d_trade_cancle_result_zocl {	//����ڿ���
	
	BYTE byErrCode; //0�̸� ����..//1;//Ʈ���̵�ƴ� 2;//���ɸ����� 
};

#define d_trade_cancle_inform_zocl 9
struct _d_trade_cancle_inform_zocl {	//��Ҵ��� �������	

};

//LOCK
#define d_trade_lock_request_clzo 10
struct _d_trade_lock_request_clzo {		//���

};

#define d_trade_lock_result_zocl 11
struct _d_trade_lock_result_zocl {		//����ڿ���
	
	BYTE	byErrCode; //0�̸� ����..1;//Ʈ���̵���ƴ� 2;//���ɸ�����
};

#define d_trade_lock_inform_zocl 12
struct _d_trade_lock_inform_zocl {		//��󿡰�

};	

//ADD
#define d_trade_add_request_clzo 13
struct _d_trade_add_request_clzo {		//�ŷ�����߰�

	BYTE byStorageCode;
	DWORD dwSerial;
	BYTE bySlotIndex;
	BYTE byAmount;	
};

#define d_trade_add_result_zocl 14
struct _d_trade_add_result_zocl {
	
	BYTE byErrCode; //0�̸� ����//1;//Ʈ���̵���ƴ� 2;//�������� 3;//��ȿ�ѽ����� �ƴ� 4;//ä�������� 5;//���¾��� 6;//�߸��¾?
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
struct _d_trade_del_request_clzo {		//�ŷ���Ͽ��� ����

	BYTE bySlotIndex;
};

#define d_trade_del_result_zocl 17
struct _d_trade_del_result_zocl {
	
	BYTE byErrCode; //0�̸� ����.//0�̸� ����//1;//Ʈ���̵���ƴ� 2;//�������� 3;//��ȿ�ѽ����� �ƴ� 4;//�󽽷�
};

#define d_trade_del_inform_zocl 18
struct _d_trade_del_inform_zocl {

	BYTE bySlotIndex;
	BYTE byEmptyInvenNum;
};

#define d_trade_bet_request_clzo 19
struct _d_trade_bet_request_clzo {		//�ݾ� ����

	//#define money_unit_dalant	0
	//#define money_unit_gold	1

	BYTE byMoneyUnit;
	DWORD dwBetAmount;
};

#define d_trade_bet_result_zocl 20
struct _d_trade_bet_result_zocl {
	
	BYTE byErrCode; //0�̸� ����.//1;//�޶�Ʈ���� 2;//������ 3;//�������� 4;//��������
};

#define d_trade_bet_inform_zocl 21
struct _d_trade_bet_inform_zocl {

	BYTE byMoneyUnit;
	DWORD dwBetAmount;
};

#define d_trade_ok_request_clzo 22
struct _d_trade_ok_request_clzo {	//ok��ư

};

#define d_trade_ok_result_zocl 23
struct _d_trade_ok_result_zocl {
	
	BYTE byErrCode; //0�̸� ����..	100�̸� ��뿡 ���� ������ ����
};

#define d_trade_ok_inform_zocl 24
struct _d_trade_ok_inform_zocl {

};	

#define d_trade_accomplish_inform_zocl 25
struct _d_trade_accomplish_inform_zocl {	//�ŷ� ����
	
	DWORD	dwDalant;
	DWORD	dwGold;
	WORD	wStartSerial;
	bool	bSucc;	//��������.. false�� �ŷ��� �������� �ʱ�ȭ��
};

#define d_trade_close_inform_zocl 26	
struct _d_trade_close_inform_zocl {	//�ŷ� �������� ���	

	BYTE byCloseCode;	
};

#define d_trade_unit_info_inform_zocl 27	//������ �÷����� ��뿡�� ������ ������ �˸���.
struct _d_trade_unit_info_inform_zocl {		

	BYTE	byTradeSlotIndex;	//Ʈ���̵�â �ε���
	BYTE	byFrame;	
	DWORD	dwGauge;		
	BYTE	byPart[UNIT_PART_NUM];
	DWORD	dwBullet[UNIT_BULLET_NUM];
	DWORD	dwSpare[max_unit_spare];
	int		nDebtFee;	//ä�� ������, ���η�
};

#define d_trade_unit_add_inform_zocl 28	//�ŷ��� ������� ������ ���ԵǾ������� ���ֵ����͸� ������
struct _d_trade_unit_add_inform_zocl {		

	WORD	wUnitKeySerial;
	BYTE	bySlotIndex;
	BYTE	byFrame;	//0xFF�� �� ����
	DWORD	dwGauge;		//hp
	BYTE	byPart[UNIT_PART_NUM];
	DWORD	dwBullet[UNIT_BULLET_NUM];
	DWORD	dwSpare[max_unit_spare];
	int		nKeepingFee;	//ä�� ������
	int		nPullingFee;	//ä�� ���η� 
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
struct _goto_dungeon_result_zocl {	//	==> new_pos_start_request_clzo�� ����..

	BYTE	byRetCode;	
	BYTE	byMapCode;
	short	zPos[3];
	WORD	wLeftSec;	//������ 
	WORD	wTotalKillNum;	
	WORD	wMissionKillNum;
};

#define close_dungeon_inform_zocl 9
struct _close_dungeon_inform_zocl {

	BYTE byCompleteCode;//	CharacterDB.h.. dungeon_complete_code_timeout 0 (������ ������ ����..)
};

#define outof_dungeon_request_clzo 10
struct _outof_dungeon_request_clzo {

};

#define outof_dungeon_result_zocl 11
struct _outof_dungeon_result_zocl {		//==> new_pos_start_request_clzo�� ����..

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

	DWORD	dwConsumDalant;	//������
	DWORD	dwLeftDalant;	//���� �޶�Ʈ
};

#define unit_bullet_fill_request_clzo 7
struct _unit_bullet_fill_request_clzo {	

	BYTE	bySlotIndex;
	
//	#define unit_bullet_arms			0
//	#define unit_bullet_shoulder		1
//	#define UNIT_BULLET_NUM				2	

	BYTE	byBulletIndex[UNIT_BULLET_NUM];	//	.. ä�������� ��Ʈ�� 0xFF
};

#define unit_bullet_fill_result_zocl 8
struct _unit_bullet_fill_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	bool	byBulletIndex[UNIT_BULLET_NUM];	//ä�������� ��Ʈ�� 0xFF

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
	BYTE	byStoreIndex;	//0xFF�� ���Ÿ�����
	short	zUnitNewPos[3];	//������ġ���� 20�̴�..
};

#define unit_delivery_result_zocl 14
struct _unit_delivery_result_zocl {	

	BYTE    byRetCode;
	BYTE	bySlotIndex;
	BYTE	byTransDistCode;	//#define unit_trans_short_range		0	//���� �ٰŸ�����  #define unit_trans_long_range		1	//���� ���Ÿ�����
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

	short	zPlayerNewPos[3];	//������ġ���� 20�̴�..
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

#define unit_bullet_replace_request_clzo 32		//���ѿ� �ִ°��� źâ�� �ű��..
struct _unit_bullet_replace_request_clzo {	

	BYTE	bySlotIndex;
	BYTE	byPackIndex;
	BYTE	byBulletPart;	
};

#define unit_bullet_replace_result_zocl 33
struct _unit_bullet_replace_result_zocl {	

	BYTE    byRetCode;
};

#define unit_booster_charge_inform_zocl 34	//�ν��� ����
struct _unit_booster_charge_inform_zocl {	

	BYTE	bySlotIndex;
	WORD	wBoosterGauge;
};

#define unit_destroy_inform_zocl 35	//�����ı�
struct _unit_destroy_inform_zocl {		//add(4/24)
	
	BYTE	bySlotIndex;
};

#define unit_force_return_inform_zocl 36	//���ְ��� ����
struct _unit_force_return_inform_zocl {		//add(4/26)
	
	BYTE	bySlotIndex;
	DWORD	dwDebt;
};

//recall_msg.. 22

#define animus_recall_request_clzo 1	//��ȯ
struct _animus_recall_request_clzo {

	DWORD dwAnimusItemSerial;	//�ִϸӽ�â���ִ� �������� �ø���..
	WORD  wAnimusClientHP;		//Ŭ���̾�Ʈ���� ȸ���� HP
	WORD  wAnimusClientFP;		//Ŭ���̾�Ʈ���� ȸ���� FP
};

#define animus_recall_result_zocl 2
struct _animus_recall_result_zocl {	

	BYTE byResultCode;
	DWORD dwAnimusSerial;		//�ִϸӽ� �ɸ����� �ø���
	WORD  wAnimusHP;			//�ִϸӽ� HP
	WORD  wAnimusFP;			//�ִϸӽ� FP
	WORD  wAnimusExp;			//�ִϸӽ� Exp
	WORD  wLeftFP;				//�ڽ��� FP
};

#define animus_return_request_clzo 3	//��ȯ
struct _animus_return_request_clzo {
};

#define animus_return_result_zocl 4	//_animus_return_request_clzo�� ��� �Ǵ� �������� ������ȯ�� ���..
struct _animus_return_result_zocl {	

	BYTE  byResultCode;
	WORD  wAnimusItemSerial;
};

#define animus_command_request_clzo 5	//�ִϸӽ��� ���.. 
struct _animus_command_request_clzo {

	//#define animus_act_type_action	0	//�ל?
	//#define animus_act_type_follow	1	//Follow me!

	BYTE byCommandCode;
};

#define animus_command_inform_zocl 6	//�ִϸӽ��� ���º���.. ���������� ��尡 �ٲ�������..
struct _animus_command_inform_zocl {

	BYTE  byStateCode;
};

#define animus_target_request_clzo 7	//��ǥ��
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

#define animus_exp_inform_zocl 11		//�ִϸӽ��� ����ġ.. �ɸ��� ��ų�� ���� ��..
struct _animus_exp_inform_zocl {

	WORD wAnimusItemSerial;
	DWORD dwExp;
};

#define animus_lvup_inform_zocl 12		//�ִϸӽ��� ������.. (�ֺ�..)
struct _animus_lvup_inform_zocl {

	WORD wIndex;
	DWORD dwSerial;
	BYTE byLv;
};

#define animus_recall_wait_time_free_inform_zocl 13		//�ִϸӽ� ���� ���ð� ����..
struct _animus_recall_wait_time_free_inform_zocl {

	bool bFree;	//true �� ���ð�����.. falae�� �������..
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

	BYTE byErrCode; //0: ����..1: �迭�����ʰ�, 2: ����������Ʈ, 3: �ø����� Ʋ��

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
	WORD	wCount;	//0xFFFF�� �ش� �䱸�׼� �Ϸ�
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
