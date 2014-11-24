#pragma once

#ifndef HAS_ASIO
#define HAS_ASIO
#include "asio.hpp"
#include "../Common/Utilities.h"
#endif

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong, QWORD;

struct Packet {
	Packet(std::vector<char> _buf, short _len){
		int size1 = Convert::ToShort(&_buf[0]);
		int size2 = Convert::ToShort(&_buf[2]);

		int h_size = 4;
		if ((size1 - 6) == size2){
			h_size = 6;
		}

		buf = new char[len = _len];
		for (size_t i = 0; i < len; i++)
			buf[i] = _buf[i];

		kind = buf[h_size - 2];
		id = buf[h_size - 1];

		buf = &buf[h_size];//remove header
	}

	char* buf;
	size_t len;
	char kind;
	char id;
};

enum {
	CHECK_KEY_NUM = 4,
	MAX_WORLD_PER_GLOBAL = 1,
	MAX_RECEIVE_SIZE = 4096,
	MAX_CHAR_PER_WORLDUSER = 3,
	msg_header_num = 2
};

enum SERVER_DPLOY_TYPE {
	Login, World, Zone
};

#pragma pack(push, 1)

struct _MSG_HEADER{
	WORD m_wSize;
	BYTE m_byType[msg_header_num];	
};

struct _MSG_HEADERv2{
	WORD m_wPsize;
	WORD m_wSize;
	BYTE m_byType[msg_header_num];
};

struct _MSG_FOOTER{
	char _c;
	int _t;
};

#pragma pack(pop)

#define MSG_HEADER_SIZE sizeof(_MSG_HEADER)
#define MSG_HEADER_v2_SIZE sizeof(_MSG_HEADERv2)
#define MSG_FOOTER_SIZE sizeof(_MSG_FOOTER)

struct _WORLD_DATA {
	bool m_bOpen;
	char m_szWorldName[33];
	DWORD m_dwGateIP;
	WORD m_wGatePort;
	int m_nUserNum;
	BYTE m_byType;
	bool m_bFreeServer;
	int m_nWorldKey;
	int m_nNetIndex;

	_WORLD_DATA() {
		m_bOpen = false;
		m_bFreeServer = false;
		m_nNetIndex = -1;
	}

	void SetWorld(const char *szWorldName, BYTE byType, bool bFree,int nNetIndex) {
		strcpy(m_szWorldName, szWorldName);
		m_byType = byType;
		m_bFreeServer = bFree;
		m_nNetIndex = nNetIndex;
	}

	void OpenWorld(DWORD dwGateIP, WORD wGatePort) {
		m_bOpen = true;
		m_dwGateIP = dwGateIP;
		m_wGatePort = wGatePort;
		m_nUserNum = 0;
		Log("World %s is now open!", m_szWorldName);
	}

	void CloseWorld() {
		m_bOpen = false;
		Log("World %s is now closed!", m_szWorldName);
	}

	void SetUserNum(int nUserNum) {
		m_nUserNum = nUserNum;
	}
};

struct _world
{
	BYTE byNum;
	bool bOpen;
	BYTE byNameSize;
	char sName[33];

	int Size()
	{
		return sizeof(*this)-(33-byNameSize); 
	}
};

typedef std::map<int, _WORLD_DATA> WORLD_DATA;

#ifndef GLOBAL_H // header guards
#define GLOBAL_H

extern byte dwWorldNum;
extern std::map<int, _WORLD_DATA> g_WorldData;

#define max_id_len					12	
#define max_pw_len					12	
#define max_name_len				16	
#define max_world_name_len			32	
#define max_map_name_len			20	
#define class_code_len				4	
#define max_message_size			255	
#define max_error_code_size			64	

#define	system_msg		1
#define chat_msg		2
#define init_msg		3
#define	position_msg	4
#define fight_msg		5
#define item_msg		7	
#define map_msg			8
#define observer_msg	10						
#define event_msg		11
#define trade_msg		12	
#define ui_msg			13
#define resource_msg	14
#define cheat_msg		15
#define party_msg		16
#define effect_msg		17
#define dtrade_msg		18
#define dungeon_msg		19
#define unit_msg		23
#define recall_msg		22
#define quest_msg		24
#define sync_msg		20
#define account_msg		21
#define waps_msg		30
#define test_msg		40
#define control_msg		50 

#define check_msg		101
#define secure_msg		102
#define real_msg		222


#define RET_CODE_SUCCESS			0	
#define RET_CODE_ASYNC_ERR			1	
#define RET_CODE_CLOSE_WORLD		2	
#define RET_CODE_BEFORE_LOGIN		3	
#define RET_CODE_FAULT_SERIAL		4	
#define RET_CODE_ALREADY_LOGIN		5	
#define RET_CODE_WRONG_USERID		6	
#define RET_CODE_WRONG_PASSWD		7	
#define RET_CODE_USER_FULL			8	
#define RET_CODE_NONEXIST_WAIT		9	
#define RET_CODE_NONEXIST_MAP		10	
#define RET_CODE_ALREADY_REGED		11	
#define RET_CODE_BEFORE_REGED		12	
#define RET_CODE_SLOT_ERR			50	
#define RET_CODE_CLASS_ERR			13	
#define RET_CODE_EMPTY_SLOT			14	
#define RET_CODE_NOT_REGED			15	
#define RET_CODE_ALREADY_SEL		16	
#define RET_CODE_ALREADY_EXIT		17	
#define RET_CODE_NONEXIST_ZONE		18	
#define RET_CODE_NONNEXT_ZONE		19	
#define RET_CODE_ALREADY_MOVE_OUT	20	
#define RET_CODE_WRONG_MASTERKEY	21	
#define RET_CODE_DB_OPEN_ERR		22  
#define RET_CODE_REGED_ACCOUNT		23  
#define RET_CODE_DB_QUERY_ERR		24  
#define RET_CODE_REGED_AVATOR		25	
#define RET_CODE_FULL_LOGIN			26	
#define RET_CODE_BEFORE_NOT_EXIST	27	
#define RET_CODE_ACCOUNT_NOT_SUIT	28	
#define RET_CODE_NOT_OPEN_WORLD		29	
#define RET_CODE_NOT_EQUAL_VERSION	30	
#define RET_CODE_BEFORE_WORLD_LIST  31	
#define RET_CODE_NOT_WORLD_LIST		32	
#define RET_CODE_NOT_WAIT_MODE		33	
#define RET_CODE_NONE_AUTHOR_WORLD	34	
#define RET_CODE_FAULT_ZONE_MOVE	35	
#define RET_CODE_ALREADY_SELECT_AVATOR	36 
#define RET_CODE_NONEXIST_DB_RECORD		37	
#define RET_CODE_NOTUSEABLE_AVATORNAME	38	
#define RET_CODE_NOT_ADMIN			39	
#define RET_CODE_BLOCK_AVATOR		40	
#define RET_CODE_LOBBY_CLOSE		41	
#define RET_CODE_HBKFILE_ERROR		42	
#define RET_CODE_NOT_AUTHORIZED		43	
#define RET_CODE_DB_WAIT			44	
#define RET_CODE_LOGIN_DEV_MODE		45	
#define RET_CODE_BLOCK_CHAT			46	
#define RET_CODE_ERR_CHAR_NAME		47	
#define	RET_CODE_NO_SERVICE			48	
#define	RET_CODE_NO_SAVED_AVATOR	49	
#define RET_CODE_INTERNAL_ERROR		100	
#define RET_CODE_NET_PROCESS_ERROR	200	
#define RET_CODE_PROGRAM_EXIT		0xFF

#endif