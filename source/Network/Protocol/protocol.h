#pragma once

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

typedef char byte;
typedef unsigned int uint;
typedef unsigned short ushort;

using boost::asio::ip::tcp;

typedef tcp::socket b_socket;

static int PROTOCOL_TYPE;

enum C_TYPE{
	login = 0,
	world = 1,
	zone = 2
};

struct pktHeader {
	short len;
	short kind;
	short id;
};

enum {
	max_id_len = 16,
	max_pw_len = 16,
	CHECK_KEY_NUM = 18,
	MAX_WORLD_PER_GLOBAL = 1,
	MAX_RECEIVE_SIZE = 4096,
	msg_header_num = 2
};

#define	system_msg		1
#define chat_msg		2
#define init_msg		3
#define	position_msg	4
#define fight_msg		5
//nomsg 6
#define item_msg		7	
#define map_msg			8
//nomsg 9, 10
#define event_msg		11
#define trade_msg		12	
#define ui_msg			13
#define resource_msg	14
//nomsg 15
#define party_msg		16
#define effect_msg		17
#define dtrade_msg		18
#define dungeon_msg		19
#define sync_msg		20
#define account_msg		21
#define recall_msg		22	
#define unit_msg		23	
#define quest_msg		24
#define holy_msg		25
#define vote_msg		26
#define guild_msg		27
#define siege_msg		28
#define billing_msg		29
#define atrade_msg		30
#define buddy_msg		31
//nomsg 32
#define tship_msg		33
#define trunk_msg		34
#define darkhole_msg	35
//nomsg 36..39
#define test_msg		40
//nomsg 41..49
#define control_msg		50 
#define sms_msg			51
#define boss_sms_msg	52
#define	web_svr_msg		53
#define ctrl_svr_msg	54
#define elect_msg		55
#define gm_msg			56
#define fireguard_msg	57
#define unk_group_58	58