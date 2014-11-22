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