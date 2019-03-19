
#include "mmk_type.h"
#include "mmi_text.h"
#include "mmi_common.h"
#include "magic_tower_img.h"
#include "magic_tower_text.h"
#include "magic_tower_ring.h"
//****************************************************************************//
//地图基本信息
//****************************************************************************//
#define MT_MAP_FLOOR_NUM			22
#define MT_MAP_ROW_NUM				11
#define MT_MAP_COLUMN_NUM			11

#define MT_MAP_UNIT_WIDTH			20
#define MT_MAP_UNIT_HEIGHT			20

#define MT_MAP_UNIT_WIDTH_F			32
#define MT_MAP_UNIT_HEIGHT_F		32
//****************************************************************************//
//模块信息 (游戏将UI划分为3个模块：背景模块；当前信息显示模块；地图模块)
//****************************************************************************//
//当前信息显示模块
#define MT_INFO_WIDTH					60
#define MT_INFO_HEIGHT					220
	//起点
#define MT_INFO_START_POINT				{10,10}
	//图片宽高
#define MT_INFO_HERO_IMG_WIDTH			60
#define MT_INFO_HERO_IMG_HEIGHT			30
#define MT_INFO_LEVEL_FONT				12
#define MT_INFO_HERO_MARIN				2
	//层数
#define MT_INFO_FLOOR_FONT				13
#define MT_INFO_FLOOR_MARIN				2
	//item宽高
#define MT_INFO_ITEM_LABEL_FONT			12
#define MT_INFO_ITEM_VALUE_FONT			15
#define MT_INFO_ITEM_WIDTH				60
#define MT_INFO_ITEM_LABEL_HEIGHT		13
#define MT_INFO_ITEM_VALUE_HEIGHT		12
	//key宽高
#define MT_INFO_ITEM_HEY_MARIN			2
#define MT_INFO_KEY_FONT				15
#define MT_INFO_KEY_HEIGHT				20
#define MT_INFO_KEY_WIDTH				60

//地图模块
#define MT_MAP_START_POINT			{90,10}
#define MT_MAP_WIDTH				220
#define MT_MAP_HEIGHT				220

//Fight模块
#define	MT_FIGHT_WIDTH				290
#define MT_FIGHT_HEIGHT				140
#define MT_FIGHT_START_POINT		{15,25}
#define MT_FIGHT_ENEMY_POINT		{35,27}
#define MT_FIGHT_HERO_POINT			{232,27}
#define MT_FIGHT_FONT				16
#define MT_FIGHT_VALUE_WIDTH		39
#define MT_FIGHT_VALUE_HEIGHT		22
#define MT_FIGHT_VALUE_POINT_HP1	{83,37}
#define MT_FIGHT_VALUE_POINT_OF1	{83,70}
#define MT_FIGHT_VALUE_POINT_DF1	{83,104}
#define MT_FIGHT_VALUE_POINT_HP2	{176,37}
#define MT_FIGHT_VALUE_POINT_OF2	{176,70}
#define MT_FIGHT_VALUE_POINT_DF2	{176,104}

//STORE模块
#define MT_STORE_WIDTH				130
#define MT_STORE_HEIGHT				130
#define MT_STORE_TIP_RECT			{25,6,124,35}
#define MT_STORE_FONT				10
#define MT_STORE_HILIGHT_COLOR		MMI_BLUE_COLOR
#define MT_STORE_OPTION_START_POINT {0,45}
#define MT_STORE_OPTION_MARIN		20

//DIALOG模块
#define MT_DIALOG_WIDTH				150
#define MT_DIALOG_HEIGHT			60
#define MT_DIALOG_HEAD_POINT		{6,6}
#define MT_DIALOG_TITLE_RECT		{30,6,140,19}
#define MT_DIALOG_CONTENT_RECT		{30,20,140,53}
#define MT_DIALOG_TITLE_FONT		15
#define MT_DIALOG_CONTENT_FONT		13

//tool tip模块
#define MT_TOOLTIP_WIDTH			240
#define MT_TOOLTIP_HEIGHT			71
#define MT_TOOLTIP_START_POINT		{80,70}

//enemy info 模块
#define MT_ENEMY_INFO_FRAME_WIDTH	22
#define MT_ENEMY_INFO_FRAME_HEIGHT	22
#define MT_ENEMY_INFO_FONT			11

//TIP模块(运用字符串显示,区别于tool tip模块)
#define MT_TIP_WIDTH				206
#define MT_TIP_HEIGHT				46
#define MT_TIP_START_POINT			{97,75}
#define MT_TIP_FONT					16

//其他模块
#define MT_START_VOICE_RECT_YEW		{50,120,88,152}
#define MT_START_VOICE_RECT_NO		{229,120,267,152}
#define MT_START_MENU_RECT_START	{110,65,210,91}
#define MT_START_MENU_RECT_READ		{110,94,210,120}
#define MT_START_MENU_RECT_HELP		{110,123,210,149}
#define MT_START_MENU_RECT_ABOUT	{110,152,210,178}
#define MT_START_MENU_RECT_EXIT		{110,181,210,207}
#define MT_SAVE_DIALOG_POINT		{114,71}
#define MT_SAVE_RECT_YES			{132,104,163,119}
#define MT_SAVE_RECT_NO				{188,104,219,119}
#define MT_SAVE_RECT_CANCEL			{241,104,272,119}
//****************************************************************************//
//UI效果量
//****************************************************************************//
#define MT_UNIT_ANIM_FRAME_NUM	2
#define INSTRUCTION_TIMER		100

//****************************************************************************//
//自定义数据类型
//****************************************************************************//
typedef uint16 MAP[MT_MAP_FLOOR_NUM][MT_MAP_ROW_NUM][MT_MAP_COLUMN_NUM];

//所有元素的总和
typedef enum
{
	MAP_UNIT_NULL,

	//地图中的固定元素
	MAP_UNIT_STAR,
	MAP_UNIT_FLOOD,
	MAP_UNIT_FLOOR,
	MAP_UNIT_WALL,
	MAP_UNIT_UPSTAIR,
	MAP_UNIT_DOWNSTAIR,
	MAP_UNIT_UNKEY_DOOR,	
	MAP_UNIT_S_DOOR,				//SPECIAL DOOR
	MAP_UNIT_Y_DOOR,
	MAP_UNIT_B_DOOR,
	MAP_UNIT_R_DOOR,
	//商店,包括NPC商人
	MAP_UNIT_STORE3_0,
	MAP_UNIT_STORE3_1,
	MAP_UNIT_STORE3_2,
	MAP_UNIT_NPC_5_1,
	MAP_UNIT_NPC_5_2,
	MAP_UNIT_STORE11_0,
	MAP_UNIT_STORE11_1,
	MAP_UNIT_STORE11_2,
	MAP_UNIT_NPC_12_1,
	MAP_UNIT_NPC_13_1,

	//NPC,不包括商人
	MAP_UNIT_NPC_0_1,
	MAP_UNIT_NPC_0_2,				
	MAP_UNIT_NPC_2_1,
	MAP_UNIT_NPC_2_2,
	MAP_UNIT_NPC_4_1,
	MAP_UNIT_NPC_4_2,
	MAP_UNIT_NPC_15_1_0,
	MAP_UNIT_NPC_15_1_1,
	MAP_UNIT_NPC_15_2_0,
	MAP_UNIT_NPC_15_2_1,
	MAP_UNIT_NPC_16_1,				//红衣魔王
	MAP_UNIT_NPC_18_1,				//公主
	MAP_UNIT_NPC_19_1,				//MASTER
	MAP_UNIT_NPC_19_2,				//MASTER
	MAP_UNIT_NPC_21_1,				//MASTER
	//消耗品
	MAP_UNIT_Y_KEY,					//钥匙
	MAP_UNIT_B_KEY,
	MAP_UNIT_R_KEY,
	MAP_UNIT_BIG_KEY,
	
	MAP_UNIT_OF_CRYSTAL,			//属性			OFFENSIVE CRYSTAL									
	MAP_UNIT_DF_CRYSTAL,			//				DEFENSIVE CRYSTAL
	MAP_UNIT_LEVEL_UP,
	MAP_UNIT_BIG_LEVEL_UP,

	MAP_UNIT_MONEY,					//金币
	
	MAP_UNIT_SWORD_A,				//武器
	MAP_UNIT_SHIELD_A,
	MAP_UNIT_SWORD_B,
	MAP_UNIT_SHIELD_B,
	MAP_UNIT_SWORD_C,
	MAP_UNIT_SHIELD_C,

	MAP_UNIT_SMALL_SUPPLY,			//生命值
	MAP_UNIT_BIG_SUPPLY,
	
	MAP_UNIT_TOOL_LOOK,				//辅助品
	MAP_UNIT_TOOL_CROSS,
	MAP_UNIT_TOOL_JUMP,
	MAP_UNIT_HAMMER,
	MAP_UNIT_HAMMER_18FLOOR,
	MAP_UNIT_TOOL_WARTER,

	//英雄、怪物
	MAP_UNIT_GIRL,
	MAP_UNIT_PRINCESS,
	MAP_UNIT_HERO,

	MAP_UNIT_GREEN_SLIME,
	MAP_UNIT_RED_SLIME,
	MAP_UNIT_CYAN_SLIME,
	MAP_UNIT_SLIME_LORD,
	MAP_UNIT_SKELETON_A,
	MAP_UNIT_SKELETON_B,
	MAP_UNIT_SKELETON_C,
	MAP_UNIT_BAT,
	MAP_UNIT_BIG_BAT,
	MAP_UNIT_VAMPIRE_BAT,
	MAP_UNIT_PRIEST,
	MAP_UNIT_SUPER_PRIEST,
	MAP_UNIT_SORCERER,
	MAP_UNIT_SUPER_SORCERER,
	MAP_UNIT_GUARD_A,
	MAP_UNIT_GUARD_B,
	MAP_UNIT_GUARD_C,
	MAP_UNIT_ZOMBIE,
	MAP_UNIT_SUPER_ZOMBIE,
	MAP_UNIT_ROCK,
	MAP_UNIT_SWORDSMAN,
	MAP_UNIT_UNDERWORLD_SOLDIER,
	MAP_UNIT_UNDERWORLD_HEADER,
	MAP_UNIT_UNDERWORLD_HEADER2,
	MAP_UNIT_GOLD_GUARD,
	MAP_UNIT_GUARD_HEADER,
	MAP_UNIT_UPWORLD_SOLDIER,
	MAP_UNIT_UPWORLD_SOLDIER2,
	MAP_UNIT_UPWORLD_PRIEST,
	MAP_UNIT_UPWORLD_PRIEST2,
	MAP_UNIT_SHADOW_SOLDIER,
	MAP_UNIT_WHITE_SERGEANT,
	MAP_UNIT_RED_SERGEANT,
	MAP_UNIT_RED_SERGEANT2,
	MAP_UNIT_SPIDER,
	MAP_UNIT_DRAGON,
	MAP_UNIT_MASTER,
	MAP_UNIT_MASTER2,
	
	MAP_UNIT_CHEAT_TIP,
	MAP_UNIT_SAVE_TIP,
	MAP_UNIT_SOUND_ON,
	MAP_UNIT_SOUND_OFF,
	MAP_UNIT_TEST,
	MAP_UNIT_MAX

}MT_UNIT_E;


//定义英雄和怪物的攻防等属性
typedef struct
{
	int32	health;
	int16	offensive;
	int16	defensive;
	uint32	coin;
	uint16	experience;
}MT_LIFE_T;

//每个元素属性的结构体
typedef struct
{
	MT_UNIT_E		unit_id;
	wchar*			name_str;							//不是所有的元素都需要一个名字，例如城墙等
	MMI_IMAGE_ID_T	icon[MT_UNIT_ANIM_FRAME_NUM];		//不是所有元素都有多个图片桢，  例如城墙等
	MMI_IMAGE_ID_T	icon_fight;							//Fight画面中的图片
	MT_LIFE_T		life;								//不是所有元素都附有攻防属性，  例如城墙、NPC等
	void*			add_value;							//特殊元素的附加值
}MT_UNIT_PRO_T;

//地图坐标.每个点标志一个20*20的矩形区域.
//注意:	x对应地图中的列,y对应地图中的行.
typedef struct
{
	int8	x;
	int8	y;
}POS_T;

typedef struct
{
	MT_UNIT_E	dialog_host;
	uint8*		dialog_str;

}SINGLE_DIALOG_T;

typedef struct
{
	GUI_POINT_T			dialog_pos[2];
	SINGLE_DIALOG_T*	dialog_ptr;
	uint16				dislog_num;
}DIALOG_T;

typedef uint8*   STORE_OPTION[5];

typedef struct
{
	STORE_OPTION	store_option;
	GUI_POINT_T		start_point;
	MMI_IMAGE_ID_T	head_img;

}STORE_T;
//当前游戏状态的标志量
typedef struct
{
	uint8	floor;
	uint8	achieve_floor;
	uint8	level;
	POS_T	hero_pos;
	uint8	yellow_key_num;
	uint8	blue_key_num;
	uint8	red_key_num;

// 	uint8	weapon;
// 	uint8	shield;
	BOOLEAN	is_get_cross;
	BOOLEAN	is_get_look;
	BOOLEAN is_get_hammer18;
	BOOLEAN is_get_jump;

}MT_STATE_T;

//保存游戏时需要保存的数据
typedef struct  
{
	uint32		save_mark;
	MAP			map_info;
	MT_LIFE_T	hero_info;
	MT_STATE_T	state_info;
}MT_GAME_SAVE_T;

// {	MAP_UNIT_NULL,				TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},

//所有元素的属性 需与MT_UNIT_E枚举类型一一对应
//校检时利用用VA显示的枚举变量值进行逐行检查.
#define TXT_NULL	NULL
LOCAL const MT_UNIT_PRO_T s_mt_unit_pro[MAP_UNIT_MAX] = 
{
	{	MAP_UNIT_NULL,				NULL,			{IMAGE_NULL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},

	//地图中的固定元素
	{	MAP_UNIT_STAR,				NULL,			{IMAGE_MT_STAR0,IMAGE_MT_STAR1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_FLOOD,				NULL,			{IMAGE_MT_FLOOD0,IMAGE_MT_FLOOD1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_FLOOR,				NULL,			{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_WALL,				NULL,			{IMAGE_MT_WALL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_UPSTAIR,			NULL,			{IMAGE_MT_UPSTAIR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_DOWNSTAIR,			NULL,			{IMAGE_MT_DOWNSTAIR,IMAGE_NULL},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_UNKEY_DOOR,		NULL,			{IMAGE_MT_UL_DOOR0,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_S_DOOR,			NULL,			{IMAGE_MT_S_DOOR0,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_Y_DOOR,			NULL,			{IMAGE_MT_Y_DOOR0,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_B_DOOR,			NULL,			{IMAGE_MT_B_DOOR0,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_R_DOOR,			NULL,			{IMAGE_MT_R_DOOR0,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_STORE3_0,			NULL,			{IMAGE_MT_STORE0,IMAGE_MT_STORE1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_STORE3_1,			NULL,			{IMAGE_NULL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_STORE3_2,			NULL,			{IMAGE_NULL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_5_1,			TXT_NULL,		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_5_2,			TXT_NULL,		{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_STORE11_0,			NULL,			{IMAGE_MT_STORE0,IMAGE_MT_STORE1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_STORE11_1,			NULL,			{IMAGE_NULL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_STORE11_2,			NULL,			{IMAGE_NULL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_12_1,			TXT_NULL,		{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_13_1,			TXT_NULL,		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},

	{	MAP_UNIT_NPC_0_1,			"仙子",			{IMAGE_MT_NPC_D0,IMAGE_MT_NPC_D1},			IMAGE_MT_NPC_D_F,{0},			{0}},
	{	MAP_UNIT_NPC_0_2,			"仙子",			{IMAGE_MT_NPC_D0,IMAGE_MT_NPC_D1},			IMAGE_MT_NPC_D_F,{0},			{0}	},
	{	MAP_UNIT_NPC_2_1,			"神秘老人",		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_2_2,			"商人",			{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_4_1,			"小偷",			{IMAGE_MT_NPC_C0,IMAGE_MT_NPC_C1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_4_2,			"小偷",			{IMAGE_MT_NPC_C0,IMAGE_MT_NPC_C1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_1_0,		"神秘老人",		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_1_1,		"神秘老人",		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_2_0,		"商人",			{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_2_1,		"商人",			{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_16_1,			"红衣魔王",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_18_1,			"公主",			{IMAGE_MT_PRINCESS0,IMAGE_MT_PRINCESS1},	IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_19_1,			"冥灵魔王",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_19_2,			"冥灵魔王",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_21_1,			"冥灵魔王",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	//消耗品
	{	MAP_UNIT_Y_KEY,				TXT_NULL,		{IMAGE_MT_Y_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"得到一把 黄钥匙"},
	{	MAP_UNIT_B_KEY,				TXT_NULL,		{IMAGE_MT_B_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"得到一把 蓝钥匙"},
	{	MAP_UNIT_R_KEY,				TXT_NULL,		{IMAGE_MT_R_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"得到一把 红钥匙"},
	{	MAP_UNIT_BIG_KEY,			TXT_NULL,		{IMAGE_MT_BIG_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"得到一把大钥匙,每把钥匙加1"},
	{	MAP_UNIT_OF_CRYSTAL,		TXT_NULL,		{IMAGE_MT_OF_CRYSTAL,IMAGE_NULL},			IMAGE_NULL,{0},					"得到攻击水晶,攻击力加3"},
	{	MAP_UNIT_DF_CRYSTAL,		TXT_NULL,		{IMAGE_MT_DF_CRYSTAL,IMAGE_NULL},			IMAGE_NULL,{0},					"得到防御水晶,防御力加3"},
	{	MAP_UNIT_LEVEL_UP,			TXT_NULL,		{IMAGE_MT_LEVEL_A,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 小飞羽,等级加1"},
	{	MAP_UNIT_BIG_LEVEL_UP,		TXT_NULL,		{IMAGE_MT_LEVEL_A,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 大飞羽,等级加3"},
	{	MAP_UNIT_MONEY,				TXT_NULL,		{IMAGE_MT_MONEY,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 金圆,金币加300"},
	{	MAP_UNIT_SWORD_A,			TXT_NULL,		{IMAGE_MT_SWORD_A,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 铁剑,攻击力加10"},
	{	MAP_UNIT_SHIELD_A,			TXT_NULL,		{IMAGE_MT_SHIELD_A,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 铁盾,防御力加10"},
	{	MAP_UNIT_SWORD_B,			TXT_NULL,		{IMAGE_MT_SWORD_B,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 青锋剑,攻击力加70"},
	{	MAP_UNIT_SHIELD_B,			TXT_NULL,		{IMAGE_MT_SHIELD_B,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 黄金盾,攻击力加85"},
	{	MAP_UNIT_SWORD_C,			TXT_NULL,		{IMAGE_MT_SWORD_C,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 星光神剑,攻击加150"},
	{	MAP_UNIT_SHIELD_C,			TXT_NULL,		{IMAGE_MT_SHIELD_C,IMAGE_NULL},				IMAGE_NULL,{0},					"得到 光芒神盾,防御加190"},
	{	MAP_UNIT_SMALL_SUPPLY,		TXT_NULL,		{IMAGE_MT_SMALL_SUPPLY,IMAGE_NULL},			IMAGE_NULL,{0},					"得到 小血瓶,生命值加200"},
	{	MAP_UNIT_BIG_SUPPLY,		TXT_NULL,		{IMAGE_MT_BIG_SUPPLY,IMAGE_NULL},			IMAGE_NULL,{0},					"得到 大血瓶,生命值加500"},
	{	MAP_UNIT_TOOL_LOOK,			TXT_NULL,		{IMAGE_MT_TOOL_LOOK,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_LOOK,{0},					{0}},
	{	MAP_UNIT_TOOL_CROSS,		TXT_NULL,		{IMAGE_MT_TOOL_CROSS,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_CROSS,{0},				{0}},
	{	MAP_UNIT_TOOL_JUMP,			TXT_NULL,		{IMAGE_MT_TOOL_JUMP,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_JUMP,{0},					{0}},
	{	MAP_UNIT_HAMMER,			TXT_NULL,		{IMAGE_MT_TOOL_HAMMER_A,IMAGE_NULL},		IMAGE_NULL,{0},								{0}},
	{	MAP_UNIT_HAMMER_18FLOOR,	TXT_NULL,		{IMAGE_MT_TOOL_HAMMER_B,IMAGE_NULL},		IMAGE_MT_TOOL_TIP_18,{0},					{0}},
	{	MAP_UNIT_TOOL_WARTER,		TXT_NULL,		{IMAGE_MT_TOOL_WARTER,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_WARTER,{0},				{0}},

	//英雄、怪物
	{	MAP_UNIT_GIRL,				"仙子",			{IMAGE_MT_NPC_D0,IMAGE_MT_NPC_D1},								IMAGE_MT_NPC_D_F,				{0},									{0}	},
	{	MAP_UNIT_PRINCESS,			"公主",			{IMAGE_MT_PRINCESS0,IMAGE_MT_PRINCESS1},						IMAGE_MT_PRINCESS_F,			{0},									{0}	},
	{	MAP_UNIT_HERO,				"勇士",			{IMAGE_MT_HERO_D1,IMAGE_MT_HERO_D1},							IMAGE_MT_HERO_F,				{0},									{0}	},
		//第一阶 1~10层
	{	MAP_UNIT_GREEN_SLIME,		"绿史莱姆",		{IMAGE_MT_GREEN_SLIME0,IMAGE_MT_GREEN_SLIME1},					IMAGE_MT_GREEN_SLIME_F,			{50,20,1,1,1},							{0}	},
	{	MAP_UNIT_RED_SLIME,			"红史莱姆",		{IMAGE_MT_RED_SLIME0,IMAGE_MT_RED_SLIME1},						IMAGE_MT_RED_SLIME_F,			{70,15,2,2,2},							{0}	},
	{	MAP_UNIT_CYAN_SLIME,		"青史莱姆",		{IMAGE_MT_CYAN_SLIME0,IMAGE_MT_CYAN_SLIME1},					IMAGE_MT_CYAN_SLIME_F,			{200,35,10,5,5},						{0}	},
	{	MAP_UNIT_SLIME_LORD,		"史莱姆王",		{IMAGE_MT_SLIME_LORD0,IMAGE_MT_SLIME_LORD1},					IMAGE_MT_SLIME_LORD_F,			{700,250,125,32,30},					{0}	},
	{	MAP_UNIT_SKELETON_A,		"骷髅队长",		{IMAGE_MT_SKELETON_A0,IMAGE_MT_SKELETON_A1},					IMAGE_MT_SKELETON_A_F,			{400,90,50,15,12},						{0}	},
	{	MAP_UNIT_SKELETON_B,		"骷髅士兵",		{IMAGE_MT_SKELETON_B0,IMAGE_MT_SKELETON_B1},					IMAGE_MT_SKELETON_B_F,			{150,40,20,8,6},						{0}	},
	{	MAP_UNIT_SKELETON_C,		"骷髅人",		{IMAGE_MT_SKELETON_C0,IMAGE_MT_SKELETON_C1},					IMAGE_MT_SKELETON_C_F,			{110,25,5,5,4},							{0}	},
	{	MAP_UNIT_BAT,				"小蝙蝠",		{IMAGE_MT_BAT0,IMAGE_MT_BAT1},									IMAGE_MT_BAT_F,					{100,20,5,3,3},							{0}	},
	{	MAP_UNIT_BIG_BAT,			"大蝙蝠",		{IMAGE_MT_BIG_BAT0,IMAGE_MT_BIG_BAT1},							IMAGE_MT_BIG_BAT_F,				{150,65,30,10,8},						{0}	},
	{	MAP_UNIT_VAMPIRE_BAT,		"吸血蝙蝠",		{IMAGE_MT_VAMPIRE_BAT0,IMAGE_MT_VAMPIRE_BAT1},					IMAGE_MT_VAMPIRE_BAT_F,			{550,160,90,25,20},						{0}	},
	{	MAP_UNIT_PRIEST,			"法师",			{IMAGE_MT_PRIEST0,IMAGE_MT_PRIEST1},							IMAGE_MT_PRIEST_F,				{125,50,25,10,7},						{0}	},
	{	MAP_UNIT_SUPER_PRIEST,		"高级法师",		{IMAGE_MT_SUPER_PRIEST0,IMAGE_MT_SUPER_PRIEST1},				IMAGE_MT_SUPER_PRIEST_F,		{100,200,110,30,25},					{0}	},
	{	MAP_UNIT_SORCERER,			"术士",			{IMAGE_MT_SORCERER0,IMAGE_MT_SORCERER1},						IMAGE_MT_SORCERER_F,			{250,120,70,20,17},						{0}	},
	{	MAP_UNIT_SUPER_SORCERER,	"高级术士",		{IMAGE_MT_SUPER_SORCERER0,IMAGE_MT_SUPER_SORCERER1},			IMAGE_MT_SUPER_SORCERER_F,		{500,400,260,47,45},					{0}	},
	{	MAP_UNIT_GUARD_A,			"高级卫兵",		{IMAGE_MT_GUARD_A0,IMAGE_MT_GUARD_A1},							IMAGE_MT_GUARD_A_F,				{1500,560,460,60,60},					{0}	},
	{	MAP_UNIT_GUARD_B,			"中级卫兵",		{IMAGE_MT_GUARD_B0,IMAGE_MT_GUARD_B1},							IMAGE_MT_GUARD_B_F,				{1250,500,400,55,55},					{0}	},
	{	MAP_UNIT_GUARD_C,			"初级卫兵",		{IMAGE_MT_GUARD_C0,IMAGE_MT_GUARD_C1},							IMAGE_MT_GUARD_C_F,				{450,150,90,22,19},						{0}	},
	{	MAP_UNIT_ZOMBIE,			"僵尸",			{IMAGE_MT_ZOMBIE0,IMAGE_MT_ZOMBIE1},							IMAGE_MT_ZOMBIE_F,				{300,75,45,13,10},						{0}	},
	{	MAP_UNIT_SUPER_ZOMBIE,		"高级僵尸",		{IMAGE_MT_SUPER_ZOMBIE0,IMAGE_MT_SUPER_ZOMBIE1},				IMAGE_MT_SUPER_ZOMBIE_F,		{900,450,330,50,50},					{0}	},
	{	MAP_UNIT_ROCK,				"石头怪",		{IMAGE_MT_ROCK0,IMAGE_MT_ROCK1},								IMAGE_MT_ROCK_F,				{500,115,65,15,15},						{0}	},
	{	MAP_UNIT_SWORDSMAN,			"双手剑士",		{IMAGE_MT_SWORDSMAN0,IMAGE_MT_SWORDSMAN1},						IMAGE_MT_SWORDSMAN_F,			{1200,620,520,65,75},					{0}	},
	{	MAP_UNIT_UNDERWORLD_SOLDIER,"冥卫士",		{IMAGE_MT_UNDERWORLD_SOLDIER0,IMAGE_MT_UNDERWORLD_SOLDIER1},	IMAGE_MT_UNDERWORLD_SOLDIER_F,	{2000,680,590,70,65},					{0}	},
	{	MAP_UNIT_UNDERWORLD_HEADER,	"冥队长",		{IMAGE_MT_UNDERWORLD_HEADER0,IMAGE_MT_UNDERWORLD_HEADER1},		IMAGE_MT_UNDERWORLD_HEADER_F,	{2500,900,850,84,75},					{0}	},
	{	MAP_UNIT_UNDERWORLD_HEADER2,"冥队长",		{IMAGE_MT_UNDERWORLD_HEADER0,IMAGE_MT_UNDERWORLD_HEADER1},		IMAGE_MT_UNDERWORLD_HEADER_F,	{3333,1200,1133,112,100},				{0}	},
	{	MAP_UNIT_GOLD_GUARD,		"金骑士",		{IMAGE_MT_GOLD_GUARD0,IMAGE_MT_GOLD_GUARD1},					IMAGE_MT_GOLD_GUARD_F,			{850,350,200,45,40},					{0}	},
	{	MAP_UNIT_GUARD_HEADER,		"骑士队长",		{IMAGE_MT_GUARD_HEADER0,IMAGE_MT_GUARD_HEADER1},				IMAGE_MT_GUARD_HEADER_F,		{900,750,650,77,70},					{0}	},
	{	MAP_UNIT_UPWORLD_SOLDIER,	"灵卫士",		{IMAGE_MT_UPWORLD_SOLDIER0,IMAGE_MT_UPWORLD_SOLDIER1},			IMAGE_MT_UPWORLD_SOLDIER_F,		{1200,980,900,88,75},					{0}	},
	{	MAP_UNIT_UPWORLD_SOLDIER2,	"灵卫士",		{IMAGE_MT_UPWORLD_SOLDIER0,IMAGE_MT_UPWORLD_SOLDIER1},			IMAGE_MT_UPWORLD_SOLDIER_F,		{1600,1300,1200,117,100},				{0}	},
	{	MAP_UNIT_UPWORLD_PRIEST,	"灵法师",		{IMAGE_MT_UPWORLD_PRIEST0,IMAGE_MT_UPWORLD_PRIEST1},			IMAGE_MT_UPWORLD_PRIEST_F,		{1500,830,730,80,70},					{0}	},
	{	MAP_UNIT_UPWORLD_PRIEST2,	"灵法师",		{IMAGE_MT_UPWORLD_PRIEST0,IMAGE_MT_UPWORLD_PRIEST1},			IMAGE_MT_UPWORLD_PRIEST_F,		{2000,1106,973,106,93},					{0}	},
	{	MAP_UNIT_SHADOW_SOLDIER,	"影子战士",		{IMAGE_MT_SHADOW_SOLDIER0,IMAGE_MT_SHADOW_SOLDIER1},			IMAGE_MT_SHADOW_SOLDIER_F,		{3100,1150,1050,92,80},					{0}	},
	{	MAP_UNIT_WHITE_SERGEANT,	"白衣武士",		{IMAGE_MT_WHITE_SERGEANT0,IMAGE_MT_WHITE_SERGEANT1},			IMAGE_MT_WHITE_SERGEANT_F,		{1300,300,150,40,35},					{0}	},
	{	MAP_UNIT_RED_SERGEANT,		"红衣武士",		{IMAGE_MT_RED_SERGEANT0,IMAGE_MT_RED_SERGEANT1},				IMAGE_MT_RED_SERGEANT_F,		{15000,1000,1000,100,100},				{0}	},
	{	MAP_UNIT_RED_SERGEANT2,		"红衣魔王",		{IMAGE_MT_RED_SERGEANT0,IMAGE_MT_RED_SERGEANT1},				IMAGE_MT_RED_SERGEANT_F,		{20000,1333,1333,133,133},				{0}	},
	{	MAP_UNIT_SPIDER,			"血影",			{IMAGE_MT_SPIDER0,IMAGE_MT_SPIDER1},							IMAGE_MT_SPIDER_F,				{99999,5000,4000,0,0},					{0}	},
	{	MAP_UNIT_DRAGON,			"魔龙",			{IMAGE_MT_DRAGON0,IMAGE_MT_DRAGON1},							IMAGE_MT_DRAGON_F,				{99999,9999,5000,0,0},					{0}	},
	{	MAP_UNIT_MASTER,			"魔王",			{IMAGE_MT_MASTER0,IMAGE_MT_MASTER1},							IMAGE_MT_MASTER_F,				{30000,1700,1500,250,220},				{0}	},
	{	MAP_UNIT_MASTER2,			"魔王",			{IMAGE_MT_MASTER0,IMAGE_MT_MASTER1},							IMAGE_MT_MASTER_F,				{4500,2550,2250,312,275},				{0}	},
	{	MAP_UNIT_CHEAT_TIP,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"作弊模式已开启"},
	{	MAP_UNIT_SAVE_TIP,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"游戏已保存"},
	{	MAP_UNIT_SOUND_ON,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"音乐：开"},
	{	MAP_UNIT_SOUND_OFF,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"音乐：关"},
	{	NULL,						TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},									{0}	},

};
#undef TXT_NULL
//初始英雄信息
LOCAL const MT_LIFE_T	s_mt_hero_info_hard = 
{
	1000,
	10,
	10,
	0
};

LOCAL const MT_LIFE_T	s_mt_hero_info_medium = 
{
	3000,
	20,
	20,
	0
};

LOCAL const MT_LIFE_T	s_mt_hero_info_easy = 
{
	5000,
	30,
	30,
	0
};

// 对话数据
	//每段文字最好不要超过33个字节.
LOCAL const SINGLE_DIALOG_T s_dialog_0_1[42] = 
{
	{MAP_UNIT_HERO,"  ......"},
	{MAP_UNIT_NPC_0_1,"  你醒了!"},
	{MAP_UNIT_HERO,"  ......\n你是谁?我在哪里?"},
	{MAP_UNIT_NPC_0_1,"  我是这里的仙子,刚才你被这里的"},
	{MAP_UNIT_NPC_0_1,"小怪打晕了."},
	{MAP_UNIT_HERO,"  ...\n剑,剑,我的剑呢?"},
	{MAP_UNIT_NPC_0_1,"  你的剑被他们抢走了,我只来得及"},
	{MAP_UNIT_NPC_0_1,"将你救出来."},
	{MAP_UNIT_HERO,"  那,公主呢?我是来救公主的."},
	{MAP_UNIT_NPC_0_1,"  公主还在里面,你这样进去是打不过"},
	{MAP_UNIT_NPC_0_1,"里面的妖怪的."},
	{MAP_UNIT_HERO,"  那我怎么办?我答应了国王一定要"},
	{MAP_UNIT_HERO,"把公主就出来的."},
	{MAP_UNIT_NPC_0_1,"  放心吧,我把我的力量借给你,你就"},
	{MAP_UNIT_NPC_0_1,"可以打赢那些妖怪了.不过,"},
	{MAP_UNIT_NPC_0_1,"你得先帮我去找一样东西,找到了再"},
	{MAP_UNIT_NPC_0_1,"来这里找我."},
	{MAP_UNIT_HERO,"  找东西?找什么东西?"},
	{MAP_UNIT_NPC_0_1,"  是一个十字架,中间有一颗红色的"},
	{MAP_UNIT_NPC_0_1,"宝石."},
	{MAP_UNIT_NPC_0_1,"  我本是这座塔的守护者,"},
	{MAP_UNIT_NPC_0_1,"可不久前,从北方来了一批恶魔,"},
	{MAP_UNIT_NPC_0_1,"他们占领了这座塔,并将我的魔力"},
	{MAP_UNIT_NPC_0_1,"封在了这个十字架里面,如果你能"},
	{MAP_UNIT_NPC_0_1,"将它带出来,那我的魔力便会慢慢"},
	{MAP_UNIT_NPC_0_1,"恢复,到时候我便可以把力量借给你"},
	{MAP_UNIT_NPC_0_1,"去救公主了."},
	{MAP_UNIT_NPC_0_1,"  要记住:只有用我的魔力才可以"},
	{MAP_UNIT_NPC_0_1,"打开21层的门."},
	{MAP_UNIT_HERO,"  ......\n好吧,我试试看."},
	{MAP_UNIT_NPC_0_1,"  刚才我去看过了,你的剑被放在3楼,"},
	{MAP_UNIT_NPC_0_1,"你的盾在5楼,而那个十字架被放在"},
	{MAP_UNIT_NPC_0_1,"7楼,你得先去取回你的剑和盾."},
	{MAP_UNIT_NPC_0_1,"  另外,在塔里的其他楼层上,还"},
	{MAP_UNIT_NPC_0_1,"存放了好几百年的宝物,如果得到"},
	{MAP_UNIT_NPC_0_1,"他们,对于你对付这里面的怪物,"},
	{MAP_UNIT_NPC_0_1,"将有非常大的帮助."},
	{MAP_UNIT_HERO,"  可是,我怎么进去呢?"},
	{MAP_UNIT_NPC_0_1,"  我这里有3把钥匙,你先拿去,"},
	{MAP_UNIT_NPC_0_1,"在塔里面还有很多这样的钥匙,"},
	{MAP_UNIT_NPC_0_1,"你一定要珍惜使用."},
	{MAP_UNIT_NPC_0_1,"  勇敢的去吧,勇士!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_0_2[8] = 
{
	{MAP_UNIT_HERO,"  仙子,我已经将那个十字架找到了."},
	{MAP_UNIT_GIRL,"  你做的很好.\n那么,现在我"},
	{MAP_UNIT_GIRL,"就开始授与你更强的力量!"},
	{MAP_UNIT_GIRL,"  咪啦哆咪哗......"},
	{MAP_UNIT_GIRL,"  好了,我已经将你的能力提升了!"},
	{MAP_UNIT_GIRL,"  记住:如果你没有足够的实力的话,"},
	{MAP_UNIT_GIRL,"不要去第21层!在那里,你所有宝物"},
	{MAP_UNIT_GIRL,"的法力都会失去作用!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_2_1[] = 
{
	{MAP_UNIT_HERO,		"  您已经得救了!"},
	{MAP_UNIT_NPC_2_1,	"  哦,我的孩子,真是太感谢你了!"},
	{MAP_UNIT_NPC_2_1,	"  这个地方又脏又破,我真的快呆不"},
	{MAP_UNIT_NPC_2_1,	"下去了."},
	{MAP_UNIT_HERO,		"  快走吧,我还得去救被关在这里的公"},
	{MAP_UNIT_HERO,		"主."},
	{MAP_UNIT_NPC_2_1,	"  哦,你是来救公主的,为了表示对你的"},
	{MAP_UNIT_NPC_2_1,	"感谢,这个东西就送给你吧,这还是我"},
	{MAP_UNIT_NPC_2_1,	"年轻的时候用过的,拿着它去解救"},
	{MAP_UNIT_NPC_2_1,	"公主吧!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_2_2[] = 
{
	{MAP_UNIT_HERO,		"  您已经得救了!"},
	{MAP_UNIT_NPC_2_2,	"  哦,是嘛,真是太感谢你了!"},
	{MAP_UNIT_NPC_2_2,	"  我是个商人,不知为什么被抓到这里"},
	{MAP_UNIT_NPC_2_2,	"来了."},
	{MAP_UNIT_HERO,		"  您现在已经自由了!"},
	{MAP_UNIT_NPC_2_2,	"  哦,对对对,我已经自由了."},
	{MAP_UNIT_NPC_2_2,	"  那这个东西就送给你吧,本来我准备"},
	{MAP_UNIT_NPC_2_2,	"卖钱的.相信它对你一定很有帮助!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_4_1[26] = 
{
	{MAP_UNIT_HERO,		"  你已经得救了"},
	{MAP_UNIT_NPC_4_1,	"  啊,那真是太好了,我又可以在这"},
	{MAP_UNIT_NPC_4_1,	"里面寻宝了!"},
	{MAP_UNIT_NPC_4_1,	"  哦,还没有自我介绍,我叫Jack,"},
	{MAP_UNIT_NPC_4_1,	"是这附近有名的小偷,什么金银财宝"},
	{MAP_UNIT_NPC_4_1,	"我样样偷过."},
	{MAP_UNIT_NPC_4_1,	"  不过这次运气可不是太好,刚进来"},
	{MAP_UNIT_NPC_4_1,	"就被抓了."},
	{MAP_UNIT_NPC_4_1,	"  现在你帮我打开了门,那我帮你"},
	{MAP_UNIT_NPC_4_1,	"做一件事吧."},
	{MAP_UNIT_HERO,		"  快走吧,外面还有很多怪物,我可能"},
	{MAP_UNIT_HERO,		"顾不上你."},
	{MAP_UNIT_NPC_4_1,	"  不,不,不会有事的.快说吧,"},
	{MAP_UNIT_NPC_4_1,	"叫我做什么?"},
	{MAP_UNIT_HERO,		"  ......\n你会开门吗?"},
	{MAP_UNIT_NPC_4_1,	"  那当然."},
	{MAP_UNIT_HERO,		"  那就请你帮我打开第二层的门吧!"},
	{MAP_UNIT_NPC_4_1,	"  那个简单,不过,如果你能帮我?"},
	{MAP_UNIT_NPC_4_1,	"找到一把嵌了红色宝石的铁榔头的话,"},
	{MAP_UNIT_NPC_4_1,	"我还帮你打通第18层的路"},
	{MAP_UNIT_HERO,		"  嵌了红色宝石的铁榔头?,好吧,"},
	{MAP_UNIT_HERO,		"我帮你找找."},
	{MAP_UNIT_NPC_4_1,	"  非常感谢你.一会我就把第二层"},
	{MAP_UNIT_NPC_4_1,	"的门打开."},
	{MAP_UNIT_NPC_4_1,	"  如果你找到那个铁榔头的话,还是"},
	{MAP_UNIT_NPC_4_1,	"来这里找我!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_4_2[4] = 
{	
	{MAP_UNIT_HERO,		"  哈,快看,我找到了什么!"},
	{MAP_UNIT_NPC_4_2,	"  太好了,这个东西果然是在这里."},
	{MAP_UNIT_NPC_4_2,	"  好吧,我这就去帮你修好第18层的"},
	{MAP_UNIT_NPC_4_2,	" 路面."},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_1_0[] = 
{	
	{MAP_UNIT_NPC_15_1_0,		"  你好,勇敢的孩子,你终于来到这里了."},
	{MAP_UNIT_NPC_15_1_0,		"  我将给你一个非常好的宝物,它可以"},
	{MAP_UNIT_NPC_15_1_0,		"使你的攻击力提升120 点.但这必须用"},
	{MAP_UNIT_NPC_15_1_0,		"你的 500 点经验来进行交换,"},
	{MAP_UNIT_NPC_15_1_0,		"你考虑一下子吧."},
	{MAP_UNIT_HERO,				"  这,可我现在还没有那么多的经验."},
	{MAP_UNIT_NPC_15_1_0,		"  那等你的经验够了再来吧!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_1_1[] = 
{	
	{MAP_UNIT_NPC_15_1_1,		"  你好,勇敢的孩子,你终于来到这里了."},
	{MAP_UNIT_NPC_15_1_1,		"  我将给你一个非常好的宝物,它可以使"},
	{MAP_UNIT_NPC_15_1_1,		"你的攻击力提升 120 点.但这必须用"},
	{MAP_UNIT_NPC_15_1_1,		"你的 500 点经验来进行交换,"},
	{MAP_UNIT_NPC_15_1_1,		"你考虑一下子吧."},
	{MAP_UNIT_HERO,				"  好吧,那就将剑给我吧!"},
	{MAP_UNIT_NPC_15_1_1,		" 那好吧,这把剑就给你了!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_2_0[] = 
{	
	{MAP_UNIT_NPC_15_2_1,		"  啊哈,欢迎你的到来!我这里有一件对"},
	{MAP_UNIT_NPC_15_2_1,		"你来说非常好的宝物,只要你出得起钱,"},
	{MAP_UNIT_NPC_15_2_1,		"我就卖给你."},
	{MAP_UNIT_HERO,				"  什么宝物?多少钱?"},
	{MAP_UNIT_NPC_15_2_1,		"  是这个游戏里最好的盾牌,防御值"},
	{MAP_UNIT_NPC_15_2_1,		"可以增加120点,而你只要出500个"},
	{MAP_UNIT_NPC_15_2_1,		"金币就可以买下."},
	{MAP_UNIT_NPC_15_2_1,		"  怎么样?你有500个金币吗?"},
	{MAP_UNIT_HERO,				"  啊?我还没有."},
	{MAP_UNIT_NPC_15_2_1,		"  那等你有了500个金币再来找我吧!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_2_1[] = 
{	
	{MAP_UNIT_NPC_15_2_1,		"  啊哈,欢迎你的到来!我这里有一件对"},
	{MAP_UNIT_NPC_15_2_1,		"你来说非常好的宝物,只要你出得起钱,"},
	{MAP_UNIT_NPC_15_2_1,		"我就卖给你."},
	{MAP_UNIT_HERO,				"  什么宝物?多少钱?"},
	{MAP_UNIT_NPC_15_2_1,		"  是这个游戏里最好的盾牌,防御值"},
	{MAP_UNIT_NPC_15_2_1,		"可以增加120点,而你只要出500个"},
	{MAP_UNIT_NPC_15_2_1,		"金币就可以买下."},
	{MAP_UNIT_NPC_15_2_1,		"  怎么样?你有500个金币吗?"},
	{MAP_UNIT_HERO,				"  我有500个金币."},
	{MAP_UNIT_NPC_15_2_1,		"  好,成交!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_16_1[] = 
{	
	{MAP_UNIT_HERO,			"  ......"},
	{MAP_UNIT_NPC_16_1,		"  停止吧,愚蠢的人类!"},
	{MAP_UNIT_HERO,			"  该停止的是你!魔王."},
	{MAP_UNIT_HERO,			"  快说,公主被关在哪里?"},
	{MAP_UNIT_NPC_16_1,		"  等你打赢我再说吧!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_18_1[] = 
{	
	{MAP_UNIT_HERO,			"  公主!你得救了!"},
	{MAP_UNIT_NPC_18_1,		"  啊,你是来救我的吗?"},
	{MAP_UNIT_HERO,			"  是的,我是奉了国王的命令来救你的."},
	{MAP_UNIT_HERO,			"  请你快随我出去吧!"},
	{MAP_UNIT_NPC_18_1,		"  不,我还不想走."},
	{MAP_UNIT_HERO,			"  为什么?这里到处是大恶魔."},
	{MAP_UNIT_NPC_18_1,		"  正是因为这里面到处都有恶魔,"},
	{MAP_UNIT_NPC_18_1,		"所以才不可以就这样出去,我要看到"},
	{MAP_UNIT_NPC_18_1,		"那个大恶魔被杀死!"},
	{MAP_UNIT_NPC_18_1,		"  英勇的勇士,如果你能够将那个"},
	{MAP_UNIT_NPC_18_1,		"大恶魔杀死,我就和你一起出去!"},
	{MAP_UNIT_HERO,			"  大恶魔?我已经杀死了一个魔王!"},
	{MAP_UNIT_NPC_18_1,		"  大恶魔在这座塔的最顶层,你杀死"},
	{MAP_UNIT_NPC_18_1,		"的那个可能只是一个小恶魔."},
	{MAP_UNIT_HERO,			"  好,那你等着,等我杀了那个大恶魔"},
	{MAP_UNIT_HERO,			"再来这里找你!"},
	{MAP_UNIT_NPC_18_1,		"  大恶魔比你刚才杀死的那个厉害多"},
	{MAP_UNIT_NPC_18_1,		"了.而且他还会变身,变身后的魔王"},
	{MAP_UNIT_NPC_18_1,		"他的攻击力和防御力都会提升"},
	{MAP_UNIT_NPC_18_1,		"至少一半以上,你得小心!"},
	{MAP_UNIT_NPC_18_1,		"  请你一定要杀死大魔王!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_19_1[] = 
{	
	{MAP_UNIT_HERO,			"  大魔头,你的死期到了!"},
	{MAP_UNIT_NPC_19_1,		"  哈哈哈......\n你真由意思."},
	{MAP_UNIT_NPC_19_1,		"  别以为蝶仙那家伙给了你力量,你就"},
	{MAP_UNIT_NPC_19_1,		"可以打败我,想打败我你还早着呢!"},
	{MAP_UNIT_HERO,			"  废话少说,去死吧!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_19_2[] = 
{	
	{MAP_UNIT_NPC_19_2,		"  看不出来你还有两下子"},
	{MAP_UNIT_NPC_19_2,		"  有本事的话就来21楼."},
	{MAP_UNIT_NPC_19_2,		"  在那里,你可以见识我真正的实力!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_21_1[] = 
{	
	{MAP_UNIT_NPC_21_1,		"  啊......\n  怎么可能"},
	{MAP_UNIT_NPC_21_1,		"  我怎么可能会被你打败呢?"},
	{MAP_UNIT_NPC_21_1,		"  不,不要这样........."},
};
//需与MAP_UNIT_E枚举变量顺序相同
LOCAL const DIALOG_T s_dialog[] = 
{
	{	{{160,120},{100,90}},	&s_dialog_0_1,	sizeof(s_dialog_0_1)/sizeof(SINGLE_DIALOG_T)},					//与第0层的仙女的第一次对话.
	{	{{160,120},{100,90}},	&s_dialog_0_2,	sizeof(s_dialog_0_2)/sizeof(SINGLE_DIALOG_T)},					//与第0层的仙女的第一次对话.
	{	{{160,120},{100,90}},	&s_dialog_2_1,	sizeof(s_dialog_2_1)/sizeof(SINGLE_DIALOG_T)},					//与第4层的盗贼的第一次对话.
	{	{{160,120},{100,90}},	&s_dialog_2_2,	sizeof(s_dialog_2_2)/sizeof(SINGLE_DIALOG_T)},					//与第4层的盗贼的第一次对话.
	{	{{160,120},{100,90}},	&s_dialog_4_1,	sizeof(s_dialog_4_1)/sizeof(SINGLE_DIALOG_T)},					//与第4层的盗贼的第一次对话.
	{	{{160,120},{100,90}},	&s_dialog_4_2,	sizeof(s_dialog_4_2)/sizeof(SINGLE_DIALOG_T)},					//与第4层的盗贼的第一次对话.
	{	{{77,99},{150,150}},	&s_dialog_15_1_0,sizeof(s_dialog_15_1_0)/sizeof(SINGLE_DIALOG_T)},				//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_15_1_1,sizeof(s_dialog_15_1_1)/sizeof(SINGLE_DIALOG_T)},				//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_15_2_0,sizeof(s_dialog_15_2_0)/sizeof(SINGLE_DIALOG_T)},				//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_15_2_1,sizeof(s_dialog_15_2_1)/sizeof(SINGLE_DIALOG_T)},				//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_16_1,	sizeof(s_dialog_16_1)/sizeof(SINGLE_DIALOG_T)},					//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_18_1,	sizeof(s_dialog_18_1)/sizeof(SINGLE_DIALOG_T)},					//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_19_1,	sizeof(s_dialog_19_1)/sizeof(SINGLE_DIALOG_T)},					//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_19_2,	sizeof(s_dialog_19_2)/sizeof(SINGLE_DIALOG_T)},					//与第15层的神秘老人的对话.
	{	{{77,99},{150,150}},	&s_dialog_21_1,	sizeof(s_dialog_21_1)/sizeof(SINGLE_DIALOG_T)},					//与第15层的神秘老人的对话.
};

//需与MAP_UNIT_E枚举变量顺序相同
LOCAL const	STORE_T s_store[] = 
{
	//第3层的商店
	{
		{
			"  想要增加你的能力吗?如果你有25个金币,你可以选择一项:",
			"增加 800 点生命",
			"增加 4 点攻击力",
			"增加 4 点防御力",
			"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  想要增加你的能力吗?如果你有25个金币,你可以选择一项:",
			"增加 800 点生命",
			"增加 4 点攻击力",
			"增加 4 点防御力",
			"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  想要增加你的能力吗?如果你有25个金币,你可以选择一项:",
			"增加 800 点生命",
			"增加 4 点攻击力",
			"增加 4 点防御力",
			"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},

	//第5层的使用经验值的商店
	{
		{
			"  你好,英勇的人类,只要你有足够的经验,我就可以让你变得强大:",
			"提升一级 (需要100点)",
			"增加5点攻击 (需要30点)",
			"增加5点防御 (需要30点)",
			"离开商店"
		},
		{125,60},		
		IMAGE_MT_NPC_A0,
	},
	//第5层买钥匙的商店
	{
		{
			"  相信你一定有特殊的需求,只要你有金币,我就可以帮你:",
			"购买 1 把黄钥匙 ($ 10)",
			"购买 1 把蓝钥匙 ($ 50)",
			"购买 1 把红钥匙 ($ 100)",
			"离开商店"
		},
		{155,55},		
		IMAGE_MT_NPC_B0,
	},
	//第11层的商店
	{
		{
			"  想要增加你的能力吗?如果你有100个金币,你可以选择一项:",
			"增加 4000 点生命",
			"增加 20 点攻击力",
			"增加 20 点防御力",
			"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  想要增加你的能力吗?如果你有100个金币,你可以选择一项:",
			"增加 4000 点生命",
			"增加 20 点攻击力",
			"增加 20 点防御力",
			"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  想要增加你的能力吗?如果你有100个金币,你可以选择一项:",
				"增加 4000 点生命",
				"增加 20 点攻击力",
				"增加 20 点防御力",
				"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},

	//买钥匙的商人
	{
		{
			"  哦,欢迎你的到来,如果你手里缺少金币,我可以帮你:",
				"卖出 1 把黄钥匙 ($ 7)",
				"卖出 1 把蓝钥匙 ($ 35)",
				"卖出 1 把红钥匙 ($ 70)",
				"离开商店"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	//第13层使用经验的商人
	{
		{
			"  你好,英勇的人类,只要你有足够的经验,我就可以让你变得强大:",
			"提升三级 (需要270点)",
			"增加17点攻击 (需要95点)",
			"增加17点防御 (需要95点)",
			"离开商店"
		},
		{125,60},		
		IMAGE_MT_NPC_A0,
	},

	{
		{
			"  你好,英勇的人类,只要你有足够的经验,我就可以让你变得强大:",
				"提升三级 (需要270点)",
				"增加17点攻击 (需要95点)",
				"增加17点防御 (需要95点)",
				"离开商店"
		},
		{125,60},		
		IMAGE_MT_NPC_A0,
	},

};

LOCAL const wchar*	s_other_tip[] = 
{
	"得到 铜剑 攻击加30",
	"得到 铜盾 防御加30",
	"得到 圣光剑 攻击加120!",
	"得到 星光盾 防御加120"

};
//动画数据
LOCAL MMI_IMAGE_ID_T s_anim_ul_door[4] = {IMAGE_MT_UL_DOOR0,IMAGE_MT_UL_DOOR1,IMAGE_MT_UL_DOOR2,IMAGE_MT_UL_DOOR3};
LOCAL MMI_IMAGE_ID_T s_anim_y_door[4] = {IMAGE_MT_Y_DOOR0,IMAGE_MT_Y_DOOR1,IMAGE_MT_Y_DOOR2,IMAGE_MT_Y_DOOR3};
LOCAL MMI_IMAGE_ID_T s_anim_b_door[4] = {IMAGE_MT_B_DOOR0,IMAGE_MT_B_DOOR1,IMAGE_MT_B_DOOR2,IMAGE_MT_B_DOOR3};
LOCAL MMI_IMAGE_ID_T s_anim_r_door[4] = {IMAGE_MT_R_DOOR0,IMAGE_MT_R_DOOR1,IMAGE_MT_R_DOOR2,IMAGE_MT_R_DOOR3};
LOCAL MMI_IMAGE_ID_T s_anim_s_door[4] = {IMAGE_MT_S_DOOR0,IMAGE_MT_S_DOOR1,IMAGE_MT_S_DOOR2,IMAGE_MT_S_DOOR3};

LOCAL MMI_IMAGE_ID_T s_anim_hero[4][2] = {
											{IMAGE_MT_HERO_U0,IMAGE_MT_HERO_U1},
											{IMAGE_MT_HERO_R0,IMAGE_MT_HERO_R1},
											{IMAGE_MT_HERO_D0,IMAGE_MT_HERO_D1},
											{IMAGE_MT_HERO_L0,IMAGE_MT_HERO_L1},
										};

//地图数据

LOCAL const POS_T		s_hero_pos[MT_MAP_FLOOR_NUM][2] = 
{
	//0~4
	{{5, 10},{5, 1 }},
	{{5, 9 },{1, 0 }},
	{{0, 1 },{0, 9 }},
	{{1, 10},{10, 9 }},
	{{10,9},{0,9}},

	//5~9
	{{0,9},{9,9}},
	{{9,9},{5,10}},
	{{5,10},{1,0}},
	{{0,1},{7,4}},
	{{6,3},{6,7}},
		
	//10~14
	{{4,6},{0,9}},
	{{1,10},{9,10}},
	{{9,10},{1,10}},
	{{1,10},{4,10}},
	{{5,9},{5,0}},

	//15~19
	{{3,0},{7,0}},
	{{5,0},{5,6}},
	{{5,8},{1,10}},
	{{1,10},{9,10}},
	{{9,10},{5,4}},
		
	//20~21
	{{5,4},{5,6}},
	{{5,5},{0}},

};


#define M0(x)	MAP_UNIT_##x
#define M1(x)	MAP_UNIT_##x
#define M2(x)	MAP_UNIT_##x
#define M3(x)	MAP_UNIT_##x
#define M4(x)	MAP_UNIT_##x
#define M5(x)	MAP_UNIT_##x
#define M6(x)	MAP_UNIT_##x
#define M7(x)	MAP_UNIT_##x
#define M8(x)	MAP_UNIT_##x
#define M9(x)	MAP_UNIT_##x
#define M10(x)	MAP_UNIT_##x
#define W		MAP_UNIT_WALL
#define F		MAP_UNIT_FLOOR

// 	//for copy
// 	{
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 
// 	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
// 	},

LOCAL const MAP			s_mt_fit_map = 
{

 	//第0层
 	{
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(UPSTAIR),	M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 		
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		F,				M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 	
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		F,				M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 	
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		F,				M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 	
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		F,				M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 	
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		F,				M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 	
	 	{ W,				M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		F,				M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		W},
	 	
	 	{ W,				W,				W,				W,				W,				M5(Y_DOOR),		W,				W,				W,				W,				W},
	 	
	 	{ M0(FLOOD),		W,				M2(FLOOD),		W,				F,				M4(NPC_0_1),		F,				W,				M8(FLOOD),		W,				M10(FLOOD)},
	 	
	 	{ M0(FLOOD),		M1(FLOOD),		M2(FLOOD),		M3(FLOOD),		M4(FLOOD),		F,				M6(FLOOD),		M7(FLOOD),		M8(FLOOD),		M9(FLOOD),		M10(FLOOD)},
	 	
	 	{ M0(FLOOD),		M1(FLOOD),		M2(FLOOD),		M3(FLOOD),		M4(FLOOD),		F,				M6(FLOOD),		M7(FLOOD),		M8(FLOOD),		M9(FLOOD),		M10(FLOOD)},
 	},

 	//第1层
	{
	 	{ M0(UPSTAIR),		M1(FLOOR),		M2(Y_KEY),		M3(GREEN_SLIME),M4(RED_SLIME),	M5(GREEN_SLIME),M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(FLOOR)},
			
	 	{ M0(SMALL_SUPPLY),	M1(FLOOR),		M2(SKELETON_C),	M3(Y_DOOR),		M4(FLOOR),		M5(WALL),		M6(SMALL_SUPPLY),M7(Y_KEY),		M8(SMALL_SUPPLY),M9(WALL),		M10(FLOOR)},

	 	{ M0(Y_KEY),		M1(SKELETON_C),	M2(OF_CRYSTAL),	M3(WALL),		M4(FLOOR),		M5(WALL),		M6(SMALL_SUPPLY),M7(Y_KEY),		M8(SMALL_SUPPLY),M9(WALL),		M10(FLOOR)},

	 	{ M0(WALL),			M1(Y_DOOR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(WALL),		M7(WALL),		M8(CYAN_SLIME),	M9(WALL),		M10(FLOOR)},

	 	{ M0(Y_KEY),		M1(SKELETON_B),	M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(Y_DOOR),		M6(PRIEST),		M7(GREEN_SLIME),M8(BAT),		M9(WALL),		M10(FLOOR)},

	 	{ M0(DF_CRYSTAL),	M1(FLOOR),		M2(B_KEY),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(WALL),			M1(Y_DOOR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(SKELETON_B),	M2(FLOOR),		M3(WALL),		M4(WALL),		M5(R_DOOR),		M6(WALL),		M7(WALL),		M8(WALL),		M9(Y_DOOR),		M10(WALL)},

	 	{ M0(SMALL_SUPPLY),	M1(BIG_SUPPLY),	M2(Y_KEY),		M3(WALL),		M4(R_KEY),		M5(FLOOR),		M6(FLOOR),		M7(WALL),		M8(Y_KEY),		M9(ZOMBIE),		M10(B_KEY)},

	 	{ M0(SMALL_SUPPLY),	M1(TOOL_LOOK),	M2(Y_KEY),		M3(WALL),		M4(FLOOR),		M5(DOWNSTAIR),	M6(FLOOR),		M7(WALL),		M8(Y_KEY),		M9(Y_KEY),		M10(Y_KEY)},
	},

	//第2层
	{
	 	{ M0(DOWNSTAIR),	M1(WALL),		M2(FLOOR),		M3(GUARD_HEADER),M4(FLOOR),		M5(WALL),		M6(OF_CRYSTAL),	M7(DF_CRYSTAL),	M8(Y_KEY),		M9(R_KEY),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(DF_CRYSTAL),	M3(WALL),		M4(BIG_SUPPLY),	M5(WALL),		M6(OF_CRYSTAL),	M7(DF_CRYSTAL),	M8(Y_KEY),		M9(B_KEY),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(Y_KEY),		M5(WALL),		M6(OF_CRYSTAL),	M7(DF_CRYSTAL),	M8(Y_KEY),		M9(GOLD_GUARD),	M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(Y_KEY),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(Y_DOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(Y_DOOR),		M8(FLOOR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_DOOR),		M3(WALL),		M4(WALL),		M5(Y_DOOR),		M6(WALL),		M7(WALL),		M8(Y_DOOR),		M9(WALL),		M10(WALL)},

	 	{ M0(FLOOR),		M1(S_DOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(WALL),		M7(FLOOR),		M8(GOLD_GUARD),	M9(FLOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_DOOR),		M3(WALL),		M4(WALL),		M5(B_DOOR),		M6(WALL),		M7(UNKEY_DOOR),	M8(WALL),		M9(UNKEY_DOOR),	M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(BIG_SUPPLY),	M5(SMALL_SUPPLY),M6(WALL),		M7(FLOOR),		M8(WALL),		M9(FLOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(BIG_SUPPLY),	M5(SMALL_SUPPLY),M6(WALL),		M7(FLOOR),		M8(WALL),		M9(FLOOR),		M10(WALL)},

	 	{ M0(UPSTAIR),		M1(WALL),		M2(OF_CRYSTAL),	M3(WALL),		M4(BIG_SUPPLY),	M5(SMALL_SUPPLY),M6(WALL),		M7(NPC_2_1),	M8(WALL),		M9(NPC_2_2),	M10(WALL)},
	},
		
	//第3层
	{
	 	{ M0(SWORD_A),		M1(RED_SLIME),	M2(Y_KEY),		M3(WALL),		M4(STORE3_0),	M5(STORE3_1),	M6(STORE3_2),	M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},

	 	{ M0(RED_SLIME),	M1(Y_KEY),		M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(BAT),		M10(FLOOR)},

	 	{ M0(Y_KEY),		M1(SKELETON_C),	M2(FLOOR),		M3(WALL),		M4(WALL),		M5(Y_DOOR),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(WALL),			M1(Y_DOOR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(SKELETON_C),	M6(FLOOR),		M7(WALL),		M8(Y_KEY),		M9(WALL),		M10(RED_SLIME)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(FLOOR),		M7(WALL),		M8(Y_KEY),		M9(WALL),		M10(BAT)},

	 	{ M0(GREEN_SLIME),	M1(WALL),		M2(FLOOR),		M3(BAT),		M4(RED_SLIME),	M5(BAT),		M6(FLOOR),		M7(WALL),		M8(Y_KEY),		M9(WALL),		M10(RED_SLIME)},

	 	{ M0(GREEN_SLIME),	M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(WALL),		M6(WALL),		M7(Y_DOOR),		M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(BAT),		M5(WALL),		M6(RED_SLIME),	M7(FLOOR),		M8(RED_SLIME),	M9(WALL),		M10(FLOOR)},

	 	{ M0(WALL),			M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(WALL),		M6(DF_CRYSTAL),	M7(BAT),		M8(Y_KEY),		M9(WALL),		M10(FLOOR)},

	 	{ M0(DOWNSTAIR),	M1(FLOOR),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(OF_CRYSTAL),	M7(BIG_SUPPLY),	M8(Y_KEY),		M9(WALL),		M10(UPSTAIR)},
	},
	
	//第4层
	{
	 	{ M0(FLOOR),		M1(CYAN_SLIME),	M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(NPC_4_1),	M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(CYAN_SLIME),	M10(FLOOR)},

	 	{ M0(Y_DOOR),		M1(WALL),		M2(Y_DOOR),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(WALL),		M8(Y_DOOR),		M9(WALL),		M10(Y_DOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(UNKEY_DOOR),	M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(SKELETON_C),	M3(WALL),		M4(BIG_BAT),	M5(VAMPIRE_BAT),M6(BIG_BAT),	M7(WALL),		M8(SKELETON_C),	M9(WALL),		M10(FLOOR)},

	 	{ M0(BAT),			M1(WALL),		M2(SMALL_SUPPLY),M3(WALL),		M4(DF_CRYSTAL),	M5(BIG_BAT),	M6(DF_CRYSTAL),	M7(WALL),		M8(SMALL_SUPPLY),M9(WALL),		M10(BAT)},

	 	{ M0(BAT),			M1(WALL),		M2(SMALL_SUPPLY),M3(WALL),		M4(WALL),		M5(R_DOOR),		M6(WALL),		M7(WALL),		M8(SMALL_SUPPLY),M9(WALL),		M10(BAT)},

	 	{ M0(RED_SLIME),	M1(WALL),		M2(FLOOR),		M3(WALL),		M4(ZOMBIE),		M5(GUARD_C),	M6(ZOMBIE),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(RED_SLIME)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(OF_CRYSTAL),	M5(ZOMBIE),		M6(OF_CRYSTAL),	M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(B_DOOR),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(Y_KEY),		M5(FLOOR),		M6(Y_KEY),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(UPSTAIR),		M1(WALL),		M2(FLOOR),		M3(CYAN_SLIME),	M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(CYAN_SLIME),	M8(FLOOR),		M9(WALL),		M10(DOWNSTAIR)},
	},

	//第5层
	{
	 	{ M0(BIG_KEY),		M1(WALL),		M2(SMALL_SUPPLY),M3(WALL),		M4(BIG_SUPPLY),	M5(PRIEST),		M6(FLOOR),		M7(FLOOR),		M8(PRIEST),		M9(Y_KEY),		M10(B_KEY)},

	 	{ M0(FLOOR),		M1(WALL),		M2(OF_CRYSTAL),	M3(WALL),		M4(PRIEST),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(PRIEST),		M10(Y_KEY)},

	 	{ M0(BIG_BAT),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(SKELETON_B),	M5(FLOOR),		M6(WALL),		M7(WALL),		M8(Y_DOOR),		M9(WALL),		M10(WALL)},

	 	{ M0(FLOOR),		M1(Y_DOOR),		M2(PRIEST),		M3(WALL),		M4(SHIELD_A),	M5(SKELETON_B),	M6(WALL),		M7(FLOOR),		M8(ZOMBIE),		M9(SKELETON_B),	M10(NPC_5_2)},

	 	{ M0(BIG_BAT),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(SKELETON_B)},

	 	{ M0(OF_CRYSTAL),	M1(WALL),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(BAT),		M6(SKELETON_C),	M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(DF_CRYSTAL),	M1(WALL),		M2(WALL),		M3(CYAN_SLIME),	M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(NPC_5_1),	M2(WALL),		M3(CYAN_SLIME),	M4(WALL),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(ZOMBIE),		M9(GUARD_C),	M10(FLOOR)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(BAT),		M4(WALL),		M5(Y_DOOR),		M6(WALL),		M7(B_DOOR),		M8(WALL),		M9(Y_DOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(WALL),		M3(FLOOR),		M4(WALL),		M5(BAT),		M6(WALL),		M7(DF_CRYSTAL),	M8(Y_DOOR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(DOWNSTAIR),	M1(FLOOR),		M2(BAT),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(WALL),		M7(Y_KEY),		M8(WALL),		M9(UPSTAIR),	M10(WALL)},
	},
	
	//第6层
	{
	 	{ M0(LEVEL_UP),		M1(SKELETON_A),	M2(WALL),		M3(DF_CRYSTAL),	M4(WALL),		M5(Y_KEY),		M6(SLIME_LORD),	M7(MONEY),		M8(WALL),		M9(BIG_SUPPLY),		M10(BIG_SUPPLY)},

	 	{ M0(SKELETON_A),	M1(Y_KEY),		M2(WALL),		M3(OF_CRYSTAL),	M4(WALL),		M5(FLOOR),		M6(Y_KEY),		M7(SLIME_LORD),	M8(WALL),		M9(ROCK),		M10(BIG_SUPPLY)},

	 	{ M0(Y_KEY),		M1(VAMPIRE_BAT),M2(B_DOOR),		M3(FLOOR),		M4(B_DOOR),		M5(VAMPIRE_BAT),M6(FLOOR),		M7(Y_KEY),		M8(WALL),		M9(FLOOR),		M10(ROCK)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(WALL),		M3(GUARD_C),	M4(WALL),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(WALL),		M9(SUPER_SORCERER),	M10(FLOOR)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(R_DOOR),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(Y_DOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(SUPER_PRIEST),M3(FLOOR),		M4(Y_KEY),		M5(Y_KEY),		M6(Y_KEY),		M7(FLOOR),		M8(SUPER_PRIEST),M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(BIG_BAT),	M3(Y_DOOR),		M4(BIG_BAT),	M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_DOOR),		M3(WALL),		M4(Y_DOOR),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(B_DOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(BIG_BAT),	M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(WALL),		M4(UPSTAIR),	M5(FLOOR),		M6(Y_DOOR),		M7(Y_DOOR),		M8(FLOOR),		M9(DOWNSTAIR),	M10(WALL)},
	},
	//第7层
	{
	 	{ M0(UPSTAIR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(WALL),		M9(WALL),		M10(WALL)},

	 	{ M0(WALL),			M1(WALL),		M2(FLOOR),		M3(VAMPIRE_BAT),M4(WALL),		M5(B_DOOR),		M6(WALL),		M7(SKELETON_A),	M8(FLOOR),		M9(WALL),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(VAMPIRE_BAT),M3(DF_CRYSTAL),	M4(WALL),		M5(WHITE_SERGEANT),	M6(WALL),	M7(OF_CRYSTAL),	M8(SKELETON_A),	M9(FLOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(WALL),		M3(WALL),		M4(WALL),		M5(UNKEY_DOOR),	M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(B_DOOR),		M3(WHITE_SERGEANT),	M4(UNKEY_DOOR),	M5(TOOL_CROSS),	M6(UNKEY_DOOR),	M7(WHITE_SERGEANT),	M8(B_DOOR),	M9(FLOOR),	M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(UNKEY_DOOR),	M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(SMALL_SUPPLY),M3(OF_CRYSTAL),	M4(WALL),		M5(WHITE_SERGEANT),	M6(WALL),	M7(DF_CRYSTAL),	M8(SMALL_SUPPLY),M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(Y_KEY),		M3(SMALL_SUPPLY),M4(WALL),		M5(B_DOOR),		M6(WALL),		M7(SMALL_SUPPLY),M8(Y_KEY),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(B_KEY),		M4(B_KEY),		M5(BIG_SUPPLY),	M6(B_KEY),		M7(B_KEY),		M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(WALL),		M3(WALL),		M4(WALL),		M5(R_DOOR),		M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(WALL),			M1(FLOOR),		M2(FLOOR),		M3(Y_DOOR),		M4(DOWNSTAIR),	M5(FLOOR),		M6(FLOOR),		M7(Y_DOOR),		M8(FLOOR),		M9(FLOOR),		M10(WALL)},
	},
	
	//第8层
	{
	 	{ M0(DOWNSTAIR),	M1(WALL),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M5(WALL),		M6(FLOOR),		M7(Y_KEY),		M8(SKELETON_A),	M9(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(Y_DOOR),		M5(WALL),		M6(Y_DOOR),		M7(WALL),		M8(WALL),		M9(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M5(B_DOOR),		M6(FLOOR),		M7(FLOOR),		M8(WALL),		M9(OF_CRYSTAL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(SORCERER),	M5(WALL),		M5(WALL),		M6(WALL),		M7(BIG_BAT),	M8(WALL),		M9(CYAN_SLIME)},

	 	{ M0(BIG_BAT),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(SMALL_SUPPLY),M5(WALL),		M5(UPSTAIR),	M6(FLOOR),		M7(FLOOR),		M8(WALL),		M9(CYAN_SLIME)},

	 	{ M0(VAMPIRE_BAT),	M1(WALL),		M2(DF_CRYSTAL),	M3(WALL),		M4(SMALL_SUPPLY),M5(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR)},

	 	{ M0(BIG_BAT),		M1(WALL),		M2(CYAN_SLIME),	M3(WALL),		M4(FLOOR),		M5(FLOOR),		M5(FLOOR),		M6(WALL),		M7(FLOOR),		M8(VAMPIRE_BAT),M9(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(CYAN_SLIME),	M3(WALL),		M4(WALL),		M5(WALL),		M5(GUARD_C),	M6(WALL),		M7(Y_DOOR),		M8(WALL),		M9(WALL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(SKELETON_A),	M4(FLOOR),		M5(WALL),		M5(SKELETON_A),	M6(WALL),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(WALL),		M4(Y_DOOR),		M5(WALL),		M5(FLOOR),		M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(SORCERER),	M3(FLOOR),		M4(FLOOR),		M5(WALL),		M5(FLOOR),		M6(SLIME_LORD),	M7(WHITE_SERGEANT),	M8(SLIME_LORD),	M9(FLOOR)},
	},
	
	//第9层
	{
	 	{ M0(TOOL_JUMP),	M1(Y_KEY),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(Y_KEY),		M1(FLOOR),		M2(SUPER_ZOMBIE),M3(Y_DOOR),	M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(Y_DOOR),		M10(SKELETON_A)},

	 	{ M0(WALL),			M1(Y_DOOR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(R_DOOR),		M4(FLOOR),		M5(WALL),		M6(DOWNSTAIR),	M7(WALL),		M8(FLOOR),		M9(WALL),		M10(SMALL_SUPPLY)},

	 	{ M0(WALL),			M1(B_DOOR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(WALL)},

	 	{ M0(DF_CRYSTAL),	M1(SUPER_SORCERER),	M2(OF_CRYSTAL),	M3(WALL),	M4(SORCERER),	M5(WALL),		M6(UPSTAIR),	M7(WALL),		M8(FLOOR),		M9(WALL),		M10(SMALL_SUPPLY)},

	 	{ M0(WALL),			M1(Y_DOOR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(Y_DOOR),		M8(FLOOR),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(SKELETON_A),	M1(SMALL_SUPPLY),M2(SKELETON_A),M3(WALL),		M4(WALL),		M5(B_DOOR),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(B_KEY),		M1(SKELETON_A),	M2(SMALL_SUPPLY),M3(WALL),		M4(ROCK),		M5(SORCERER),	M6(ROCK),		M7(WALL),		M8(FLOOR),		M9(Y_DOOR),		M10(SKELETON_A)},

	 	{ M0(SWORD_B),		M1(B_KEY),		M2(SKELETON_A),	M3(Y_DOOR),		M4(BIG_SUPPLY),	M5(ROCK),		M6(BIG_SUPPLY),	M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},
	},

	//第10层
	{
	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(DF_CRYSTAL),M4(SUPER_ZOMBIE),M5(WALL),		M6(SUPER_ZOMBIE),M7(OF_CRYSTAL),M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(WALL),		M3(WALL),		M4(Y_DOOR),		M5(WALL),		M6(Y_DOOR),		M7(WALL),		M8(WALL),		M9(FLOOR),		M10(SUPER_SORCERER)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(WALL),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(SUPER_SORCERER),	M10(BIG_SUPPLY)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(WALL)},

	 	{ M0(BIG_BAT),		M1(WALL),		M2(FLOOR),		M3(FLOOR),		M4(Y_KEY),		M5(Y_KEY),		M6(Y_KEY),		M7(FLOOR),		M8(FLOOR),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(VAMPIRE_BAT),	M1(WALL),		M2(FLOOR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(Y_DOOR),		M8(WALL),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(BIG_BAT),		M1(WALL),		M2(FLOOR),		M3(UNKEY_DOOR),	M4(FLOOR),		M5(DOWNSTAIR),	M6(WALL),		M7(FLOOR),		M8(Y_DOOR),		M9(VAMPIRE_BAT),M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(Y_DOOR),		M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(SMALL_SUPPLY),M3(DF_CRYSTAL),M4(OF_CRYSTAL),M5(WALL),		M6(FLOOR),		M7(VAMPIRE_BAT),M8(FLOOR),		M9(WALL),		M10(Y_KEY)},

	 	{ M0(FLOOR),		M1(WALL),		M2(SMALL_SUPPLY),M3(DF_CRYSTAL),M4(OF_CRYSTAL),M5(R_DOOR),		M6(SORCERER),	M7(WALL),		M8(SORCERER),	M9(WALL),		M10(Y_KEY)},

	 	{ M0(UPSTAIR),		M1(WALL),		M2(SMALL_SUPPLY),M3(DF_CRYSTAL),M4(OF_CRYSTAL),M5(WALL),		M6(B_KEY),		M7(WALL),		M8(B_KEY),		M9(WALL),		M10(SMALL_SUPPLY)},
	},
	
	//第11层
	{
	 	{ M0(SMALL_SUPPLY),	M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(B_KEY),		M5(WALL),		M6(R_KEY),		M7(WALL),		M8(BIG_SUPPLY),	M9(SHIELD_B),	M10(BIG_SUPPLY)},

	 	{ M0(SMALL_SUPPLY),	M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(B_KEY),		M5(WALL),		M6(R_KEY),		M7(WALL),		M8(GUARD_B),	M9(GUARD_A),	M10(GUARD_B)},

	 	{ M0(SMALL_SUPPLY),	M1(WALL),		M2(Y_KEY),		M3(WALL),		M4(B_KEY),		M5(WALL),		M6(R_KEY),		M7(WALL),		M8(FLOOR),		M9(GUARD_B),	M10(FLOOR)},

	 	{ M0(Y_DOOR),		M1(WALL),		M2(Y_DOOR),		M3(WALL),		M4(Y_DOOR),		M5(WALL),		M6(Y_DOOR),		M7(WALL),		M8(WALL),		M9(B_DOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(WALL),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(Y_DOOR),		M1(WALL),		M2(WALL),		M3(B_DOOR),		M4(WALL),		M5(WALL),		M6(WALL),		M7(B_DOOR),		M8(WALL),		M9(WALL),		M10(Y_DOOR)},

	 	{ M0(DF_CRYSTAL),	M1(WALL),		M2(FLOOR),		M3(GUARD_B),	M4(BIG_SUPPLY),	M5(SWORDSMAN),	M6(BIG_SUPPLY),	M7(GUARD_B),	M8(FLOOR),		M9(WALL),		M10(OF_CRYSTAL)},

	 	{ M0(DF_CRYSTAL),	M1(WALL),		M2(SUPER_ZOMBIE),M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(SUPER_ZOMBIE),M9(WALL),		M10(OF_CRYSTAL)},

	 	{ M0(DF_CRYSTAL),	M1(WALL),		M2(SUPER_ZOMBIE),M3(WALL),		M4(STORE11_0),	M5(STORE11_1),	M6(STORE11_2),	M7(WALL),		M8(SUPER_ZOMBIE),M9(WALL),		M10(OF_CRYSTAL)},

	 	{ M0(WALL),			M1(WALL),		M2(R_DOOR),		M3(WALL),		M4(SMALL_SUPPLY),M5(FLOOR),		M6(SMALL_SUPPLY),M7(WALL),		M8(R_DOOR),		M9(WALL),		M10(WALL)},

	 	{ M0(DOWNSTAIR),	M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(UPSTAIR)},
	},
	
	//第12层
	{
	 	{ M0(NPC_12_1),		M1(DF_CRYSTAL),	M2(WALL),		M3(FLOOR),		M4(GOLD_GUARD),	M5(GUARD_HEADER),M6(GOLD_GUARD),M7(FLOOR),		M8(WALL),		M9(BIG_SUPPLY),	M10(HAMMER_18FLOOR)},

	 	{ M0(OF_CRYSTAL),	M1(FLOOR),		M2(WALL),		M3(FLOOR),		M4(WALL),		M5(Y_DOOR),		M6(WALL),		M7(FLOOR),		M8(WALL),		M9(FLOOR),		M10(BIG_SUPPLY)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(WALL),		M3(FLOOR),		M4(WALL),		M5(GUARD_HEADER),M6(WALL),		M7(FLOOR),		M8(WALL),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(SWORDSMAN),	M2(WALL),		M3(FLOOR),		M4(WALL),		M5(Y_KEY),		M6(WALL),		M7(FLOOR),		M8(WALL),		M9(UPWORLD_SOLDIER),M10(FLOOR)},

	 	{ M0(SWORDSMAN),	M1(UNDERWORLD_SOLDIER),	M2(WALL),M3(FLOOR),		M4(WALL),		M5(Y_KEY),		M6(WALL),		M7(FLOOR),		M8(WALL),		M9(UPWORLD_PRIEST),	M10(UPWORLD_SOLDIER)},

	 	{ M0(WALL),			M1(B_DOOR),		M2(WALL),		M3(FLOOR),		M4(WALL),		M5(SMALL_SUPPLY),M6(WALL),		M7(FLOOR),		M8(WALL),		M9(B_DOOR),		M10(WALL)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(WALL),		M5(SMALL_SUPPLY),M6(WALL),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(FLOOR),		M4(WALL),		M5(WALL),		M6(WALL),		M7(FLOOR),		M8(WALL),		M9(WALL),		M10(WALL)},

	 	{ M0(DF_CRYSTAL),	M1(SWORDSMAN),	M2(Y_DOOR),		M3(GUARD_B),	M4(GUARD_B),	M5(GUARD_A),	M6(GUARD_B),	M7(GUARD_B),	M8(Y_DOOR),		M9(SWORDSMAN),	M10(OF_CRYSTAL)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(Y_DOOR),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},

	 	{ M0(UPSTAIR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(DOWNSTAIR)},
	},
	
	//第13层
	{
	 	{ M0(FLOOR),		M1(SWORDSMAN),	M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(UNDERWORLD_SOLDIER),M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(Y_DOOR),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(WALL),		M2(FLOOR),		M3(FLOOR),		M4(GUARD_B),	M5(FLOOR),		M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(BIG_SUPPLY),	M1(WALL),		M2(R_DOOR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(FLOOR)},

	 	{ M0(GOLD_GUARD),	M1(WALL),		M2(FLOOR),		M3(FLOOR),		M4(UNDERWORLD_SOLDIER),	M5(WALL),M6(GUARD_B),	M7(WALL),		M8(OF_CRYSTAL),	M9(WALL),		M10(FLOOR)},

	 	{ M0(GUARD_HEADER),	M1(WALL),		M2(FLOOR),		M3(UNDERWORLD_HEADER),M4(UNKEY_DOOR),	M5(WALL),M6(GUARD_A),	M7(WALL),		M8(OF_CRYSTAL),	M9(WALL),		M10(FLOOR)},

	 	{ M0(GOLD_GUARD),	M1(WALL),		M2(UNDERWORLD_SOLDIER),M3(UNKEY_DOOR),M4(NPC_13_1),	M5(WALL),	M6(GUARD_B),	M7(WALL),		M8(OF_CRYSTAL),	M9(WALL),		M10(DF_CRYSTAL)},

	 	{ M0(FLOOR),		M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(FLOOR),		M7(WALL),		M8(FLOOR),		M9(WALL),		M10(DF_CRYSTAL)},

	 	{ M0(FLOOR),		M1(GOLD_GUARD),	M2(FLOOR),		M3(WALL),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(UNDERWORLD_SOLDIER),	M8(FLOOR),M9(WALL),		M10(DF_CRYSTAL)},

	 	{ M0(WALL),			M1(WALL),		M2(FLOOR),		M3(WALL),		M4(BIG_SUPPLY),	M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(FLOOR)},

	 	{ M0(DOWNSTAIR),	M1(FLOOR),		M2(FLOOR),		M3(B_DOOR),		M4(FLOOR),		M5(UPSTAIR),	M6(WALL),		M7(BIG_LEVEL_UP),M8(UNDERWORLD_HEADER),	M9(Y_DOOR),	M10(FLOOR)},
	},
	
	//第14层
	{
	 	{ M0(WALL),			M1(FLOOR),		M2(UPWORLD_SOLDIER),M3(BIG_KEY),M4(UPSTAIR),	M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(BIG_SUPPLY),	M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(BIG_SUPPLY),	M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(WALL),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(WALL),		M3(WALL),		M4(WALL),		M5(TOOL_WARTER),M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(WALL),		M3(WALL),		M4(WALL),		M5(UNKEY_DOOR),	M6(WALL),		M7(WALL),		M8(WALL),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(SMALL_SUPPLY),M3(WALL),		M4(WALL),		M5(UNDERWORLD_SOLDIER),	M6(WALL),M7(WALL),		M8(SMALL_SUPPLY),M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(STAR),		M3(STAR),		M4(WALL),		M5(UNDERWORLD_HEADER),	M6(WALL),M7(STAR),		M8(STAR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(STAR),		M3(STAR),		M4(WALL),		M5(UNDERWORLD_SOLDIER),	M6(WALL),M7(STAR),		M8(STAR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(FLOOR),		M2(STAR),		M3(STAR),		M4(WALL),		M5(B_DOOR),		M6(WALL),		M7(STAR),		M8(STAR),		M9(FLOOR),		M10(WALL)},

	 	{ M0(WALL),			M1(GUARD_B),	M2(GUARD_A),	M3(GUARD_B),	M4(B_DOOR),		M5(FLOOR),		M6(B_DOOR),		M7(GUARD_B),	M8(GUARD_A),	M9(GUARD_B),	M10(WALL)},

	 	{ M0(WALL),			M1(WALL),		M2(WALL),		M3(WALL),		M4(WALL),		M5(DOWNSTAIR),	M6(WALL),		M7(WALL),		M8(WALL),		M9(WALL),		M10(WALL)},
	},
	
	//第15层
	{
	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(DOWNSTAIR),	M5(STAR),		M6(UPSTAIR),	M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(WALL),		M7(WALL),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(WALL),		M3(WALL),		M4(NPC_15_1_0),	M5(WALL),		M6(NPC_15_2_0),	M7(WALL),		M8(WALL),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(WALL),		M3(WALL),		M4(DF_CRYSTAL),	M5(WALL),		M6(DF_CRYSTAL),	M7(WALL),		M8(WALL),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(WALL),		M3(WALL),		M4(OF_CRYSTAL),	M5(WALL),		M6(OF_CRYSTAL),	M7(WALL),		M8(WALL),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(FLOOR),		M7(WALL),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(WALL),		M4(Y_DOOR),		M5(WALL),		M6(Y_DOOR),		M7(WALL),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(STAR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(R_DOOR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},
	},
	
	//第16层
	{
	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(FLOOR),		M5(DOWNSTAIR),	M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(FLOOR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(FLOOR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(WALL),		M4(R_DOOR),		M5(WALL),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(WALL),		M3(WALL),		M4(NPC_16_1),	M5(WALL),		M6(WALL),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(WALL),		M3(WALL),		M4(RED_SERGEANT),M5(WALL),		M6(WALL),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(WALL),		M3(WALL),		M4(FLOOR),		M5(WALL),		M6(WALL),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(WALL),		M3(WALL),		M4(UPSTAIR),	M5(WALL),		M6(WALL),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(WALL),		M4(WALL),		M5(WALL),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},

	 	{ M0(STAR),M1(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR)},
	},
	
	//第17层
	{
	 	{ M0(STAR),			M1(UPWORLD_SOLDIER2),M2(UNDERWORLD_HEADER2),M3(FLOOR),M4(FLOOR),	M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(UPWORLD_SOLDIER2)},

	 	{ M0(STAR),			M1(UNDERWORLD_HEADER2),M2(STAR),	M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(STAR),			M1(FLOOR),		M2(STAR),		M3(UPWORLD_SOLDIER2),M4(FLOOR),	M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(UPWORLD_SOLDIER2)},

	 	{ M0(STAR),			M1(FLOOR),		M2(STAR),		M3(FLOOR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(FLOOR),		M2(STAR),		M3(FLOOR),		M4(STAR),		M5(UPWORLD_SOLDIER2),M6(FLOOR),	M7(FLOOR),		M8(FLOOR),		M9(UPWORLD_SOLDIER2),M10(STAR)},

	 	{ M0(STAR),			M1(FLOOR),		M2(STAR),		M3(UPWORLD_SOLDIER2),M4(FLOOR),	M5(FLOOR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(FLOOR),		M10(STAR)},

	 	{ M0(STAR),			M1(FLOOR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(UPWORLD_SOLDIER2),M8(FLOOR),	M9(UPWORLD_SOLDIER2),M10(STAR)},

	 	{ M0(STAR),			M1(UNDERWORLD_HEADER2),M2(STAR),	M3(STAR),		M4(STAR),		M5(DOWNSTAIR),	M6(STAR),		M7(FLOOR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(UPWORLD_SOLDIER2),M2(UNDERWORLD_HEADER2),M3(FLOOR),M4(SHADOW_SOLDIER),	M5(FLOOR),	M6(STAR),	M7(UPWORLD_SOLDIER2),M8(FLOOR),	M9(FLOOR),		M10(UPWORLD_SOLDIER2)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(UPSTAIR),		M1(FLOOR),		M2(SHADOW_SOLDIER),	M3(FLOOR),	M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(UPWORLD_SOLDIER2)},
	},
	
	//第18层
	{
	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(WALL),		M5(WALL),		M6(WALL),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(WALL),		M4(WALL),		M5(NPC_18_1),	M6(WALL),		M7(WALL),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(WALL),		M4(WALL),		M5(UNKEY_DOOR),	M6(WALL),		M7(WALL),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(WALL),		M4(WALL),		M5(R_DOOR),		M6(WALL),		M7(WALL),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(WALL),		M5(R_DOOR),		M6(WALL),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(DOWNSTAIR),	M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},
	},
	
	//第19层
	{
	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(FLOOR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(FLOOR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(FLOOR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(FLOOR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(FLOOR),		M3(STAR),		M4(STAR),		M5(UPSTAIR),	M6(STAR),		M7(STAR),		M8(FLOOR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(FLOOR),		M3(STAR),		M4(STAR),		M5(FLOOR),		M6(STAR),		M7(STAR),		M8(FLOOR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(RED_SERGEANT2),M3(STAR),		M4(STAR),		M5(FLOOR),		M6(STAR),		M7(STAR),		M8(RED_SERGEANT2),M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(UNKEY_DOOR),	M3(STAR),		M4(STAR),		M5(MASTER),		M6(STAR),		M7(STAR),		M8(UNKEY_DOOR),	M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(SWORD_C),	M3(STAR),		M4(STAR),		M5(NPC_19_1),	M6(STAR),		M7(STAR),		M8(SHIELD_C),	M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(FLOOR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(FLOOR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(FLOOR)},

	 	{ M0(FLOOR),		M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(DOWNSTAIR)},
	},

	//第20层
	{
	 	{ M0(SHADOW_SOLDIER),M1(OF_CRYSTAL),M2(WHITE_SERGEANT),	M3(SMALL_SUPPLY),M4(UNDERWORLD_HEADER2),M5(R_KEY),M6(UNDERWORLD_HEADER2),		M7(SMALL_SUPPLY),M8(WHITE_SERGEANT),M9(OF_CRYSTAL),	M10(SHADOW_SOLDIER)},

	 	{ M0(BIG_SUPPLY),	M1(STAR),		M2(Y_KEY),		M3(STAR),		M4(B_KEY),		M5(STAR),		M6(B_KEY),		M7(STAR),		M8(Y_KEY),		M9(STAR),		M10(BIG_SUPPLY)},

	 	{ M0(STAR),			M1(DF_CRYSTAL),	M2(WHITE_SERGEANT),	M3(FLOOR),	M4(UPWORLD_SOLDIER2),M5(FLOOR),	M6(UPWORLD_SOLDIER2),M7(FLOOR),	M8(WHITE_SERGEANT),M9(DF_CRYSTAL),M10(STAR)},

	 	{ M0(SMALL_SUPPLY),	M1(STAR),		M2(Y_KEY),		M3(STAR),		M4(FLOOR),		M5(DOWNSTAIR),	M6(FLOOR),		M7(STAR),		M8(Y_KEY),		M9(STAR),		M10(SMALL_SUPPLY)},

	 	{ M0(UNDERWORLD_HEADER2),M1(B_KEY),	M2(UNDERWORLD_HEADER2),M3(FLOOR),M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(UNDERWORLD_HEADER2),M9(B_KEY),M10(UNDERWORLD_HEADER2)},

	 	{ M0(R_KEY),		M1(STAR),		M2(FLOOR),		M3(STAR),		M4(FLOOR),		M5(STAR),		M6(FLOOR),		M7(STAR),		M8(FLOOR),		M9(STAR),		M10(R_KEY)},

	 	{ M0(UNDERWORLD_HEADER2),M1(B_KEY),	M2(UPWORLD_SOLDIER2),M3(FLOOR),	M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(UPWORLD_SOLDIER2),M9(B_KEY),	M10(UNDERWORLD_HEADER2)},

	 	{ M0(SMALL_SUPPLY),	M1(STAR),		M2(Y_KEY),		M3(STAR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(STAR),		M8(Y_KEY),		M9(STAR),		M10(SMALL_SUPPLY)},

	 	{ M0(STAR),			M1(DF_CRYSTAL),	M2(WHITE_SERGEANT),M3(FLOOR),	M4(UPWORLD_SOLDIER2),M5(FLOOR),	M6(UPWORLD_SOLDIER2),M7(FLOOR),	M8(WHITE_SERGEANT),M9(DF_CRYSTAL),M10(STAR)},

	 	{ M0(BIG_SUPPLY),	M1(STAR),		M2(Y_KEY),		M3(STAR),		M4(B_KEY),		M5(STAR),		M6(B_KEY),		M7(STAR),		M8(Y_KEY),		M9(STAR),		M10(BIG_SUPPLY)},

	 	{ M0(SHADOW_SOLDIER),	M1(OF_CRYSTAL),	M2(WHITE_SERGEANT),M3(SMALL_SUPPLY),M4(UNDERWORLD_HEADER2),M5(R_KEY),M6(UNDERWORLD_HEADER2),M7(SMALL_SUPPLY),M8(WHITE_SERGEANT),M9(OF_CRYSTAL),M10(SHADOW_SOLDIER)},
	},

	//第21层
	{
	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(FLOOR),		M3(FLOOR),		M4(STAR),		M5(MASTER2),		M6(STAR),		M7(FLOOR),		M8(FLOOR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(FLOOR),		M2(FLOOR),		M3(STAR),		M4(STAR),		M5(UPWORLD_PRIEST2),	M6(STAR),	M7(STAR),		M8(FLOOR),		M9(FLOOR),		M10(STAR)},

	 	{ M0(STAR),			M1(FLOOR),		M2(FLOOR),		M3(FLOOR),		M4(STAR),		M5(UPWORLD_PRIEST2),	M6(STAR),	M7(FLOOR),		M8(FLOOR),		M9(FLOOR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(FLOOR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(FLOOR),		M4(FLOOR),		M5(FLOOR),		M6(FLOOR),		M7(FLOOR),		M8(FLOOR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(FLOOR),		M4(FLOOR),		M5(STAR),		M6(FLOOR),		M7(FLOOR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(UNKEY_DOOR),	M5(DOWNSTAIR),	M6(UNKEY_DOOR),	M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},

	 	{ M0(STAR),			M1(STAR),		M2(STAR),		M3(STAR),		M4(STAR),		M5(STAR),		M6(STAR),		M7(STAR),		M8(STAR),		M9(STAR),		M10(STAR)},
	},

};
#undef F
#undef W
#undef M0
#undef M1
#undef M2
#undef M3
#undef M4
#undef M5
#undef M6
#undef M7
#undef M8
#undef M9
#undef M10

