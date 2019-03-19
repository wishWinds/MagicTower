
#include "mmk_type.h"
#include "mmi_text.h"
#include "mmi_common.h"
#include "magic_tower_img.h"
#include "magic_tower_text.h"
#include "magic_tower_ring.h"
//****************************************************************************//
//��ͼ������Ϣ
//****************************************************************************//
#define MT_MAP_FLOOR_NUM			22
#define MT_MAP_ROW_NUM				11
#define MT_MAP_COLUMN_NUM			11

#define MT_MAP_UNIT_WIDTH			20
#define MT_MAP_UNIT_HEIGHT			20

#define MT_MAP_UNIT_WIDTH_F			32
#define MT_MAP_UNIT_HEIGHT_F		32
//****************************************************************************//
//ģ����Ϣ (��Ϸ��UI����Ϊ3��ģ�飺����ģ�飻��ǰ��Ϣ��ʾģ�飻��ͼģ��)
//****************************************************************************//
//��ǰ��Ϣ��ʾģ��
#define MT_INFO_WIDTH					60
#define MT_INFO_HEIGHT					220
	//���
#define MT_INFO_START_POINT				{10,10}
	//ͼƬ���
#define MT_INFO_HERO_IMG_WIDTH			60
#define MT_INFO_HERO_IMG_HEIGHT			30
#define MT_INFO_LEVEL_FONT				12
#define MT_INFO_HERO_MARIN				2
	//����
#define MT_INFO_FLOOR_FONT				13
#define MT_INFO_FLOOR_MARIN				2
	//item���
#define MT_INFO_ITEM_LABEL_FONT			12
#define MT_INFO_ITEM_VALUE_FONT			15
#define MT_INFO_ITEM_WIDTH				60
#define MT_INFO_ITEM_LABEL_HEIGHT		13
#define MT_INFO_ITEM_VALUE_HEIGHT		12
	//key���
#define MT_INFO_ITEM_HEY_MARIN			2
#define MT_INFO_KEY_FONT				15
#define MT_INFO_KEY_HEIGHT				20
#define MT_INFO_KEY_WIDTH				60

//��ͼģ��
#define MT_MAP_START_POINT			{90,10}
#define MT_MAP_WIDTH				220
#define MT_MAP_HEIGHT				220

//Fightģ��
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

//STOREģ��
#define MT_STORE_WIDTH				130
#define MT_STORE_HEIGHT				130
#define MT_STORE_TIP_RECT			{25,6,124,35}
#define MT_STORE_FONT				10
#define MT_STORE_HILIGHT_COLOR		MMI_BLUE_COLOR
#define MT_STORE_OPTION_START_POINT {0,45}
#define MT_STORE_OPTION_MARIN		20

//DIALOGģ��
#define MT_DIALOG_WIDTH				150
#define MT_DIALOG_HEIGHT			60
#define MT_DIALOG_HEAD_POINT		{6,6}
#define MT_DIALOG_TITLE_RECT		{30,6,140,19}
#define MT_DIALOG_CONTENT_RECT		{30,20,140,53}
#define MT_DIALOG_TITLE_FONT		15
#define MT_DIALOG_CONTENT_FONT		13

//tool tipģ��
#define MT_TOOLTIP_WIDTH			240
#define MT_TOOLTIP_HEIGHT			71
#define MT_TOOLTIP_START_POINT		{80,70}

//enemy info ģ��
#define MT_ENEMY_INFO_FRAME_WIDTH	22
#define MT_ENEMY_INFO_FRAME_HEIGHT	22
#define MT_ENEMY_INFO_FONT			11

//TIPģ��(�����ַ�����ʾ,������tool tipģ��)
#define MT_TIP_WIDTH				206
#define MT_TIP_HEIGHT				46
#define MT_TIP_START_POINT			{97,75}
#define MT_TIP_FONT					16

//����ģ��
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
//UIЧ����
//****************************************************************************//
#define MT_UNIT_ANIM_FRAME_NUM	2
#define INSTRUCTION_TIMER		100

//****************************************************************************//
//�Զ�����������
//****************************************************************************//
typedef uint16 MAP[MT_MAP_FLOOR_NUM][MT_MAP_ROW_NUM][MT_MAP_COLUMN_NUM];

//����Ԫ�ص��ܺ�
typedef enum
{
	MAP_UNIT_NULL,

	//��ͼ�еĹ̶�Ԫ��
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
	//�̵�,����NPC����
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

	//NPC,����������
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
	MAP_UNIT_NPC_16_1,				//����ħ��
	MAP_UNIT_NPC_18_1,				//����
	MAP_UNIT_NPC_19_1,				//MASTER
	MAP_UNIT_NPC_19_2,				//MASTER
	MAP_UNIT_NPC_21_1,				//MASTER
	//����Ʒ
	MAP_UNIT_Y_KEY,					//Կ��
	MAP_UNIT_B_KEY,
	MAP_UNIT_R_KEY,
	MAP_UNIT_BIG_KEY,
	
	MAP_UNIT_OF_CRYSTAL,			//����			OFFENSIVE CRYSTAL									
	MAP_UNIT_DF_CRYSTAL,			//				DEFENSIVE CRYSTAL
	MAP_UNIT_LEVEL_UP,
	MAP_UNIT_BIG_LEVEL_UP,

	MAP_UNIT_MONEY,					//���
	
	MAP_UNIT_SWORD_A,				//����
	MAP_UNIT_SHIELD_A,
	MAP_UNIT_SWORD_B,
	MAP_UNIT_SHIELD_B,
	MAP_UNIT_SWORD_C,
	MAP_UNIT_SHIELD_C,

	MAP_UNIT_SMALL_SUPPLY,			//����ֵ
	MAP_UNIT_BIG_SUPPLY,
	
	MAP_UNIT_TOOL_LOOK,				//����Ʒ
	MAP_UNIT_TOOL_CROSS,
	MAP_UNIT_TOOL_JUMP,
	MAP_UNIT_HAMMER,
	MAP_UNIT_HAMMER_18FLOOR,
	MAP_UNIT_TOOL_WARTER,

	//Ӣ�ۡ�����
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


//����Ӣ�ۺ͹���Ĺ���������
typedef struct
{
	int32	health;
	int16	offensive;
	int16	defensive;
	uint32	coin;
	uint16	experience;
}MT_LIFE_T;

//ÿ��Ԫ�����ԵĽṹ��
typedef struct
{
	MT_UNIT_E		unit_id;
	wchar*			name_str;							//�������е�Ԫ�ض���Ҫһ�����֣������ǽ��
	MMI_IMAGE_ID_T	icon[MT_UNIT_ANIM_FRAME_NUM];		//��������Ԫ�ض��ж��ͼƬ�壬  �����ǽ��
	MMI_IMAGE_ID_T	icon_fight;							//Fight�����е�ͼƬ
	MT_LIFE_T		life;								//��������Ԫ�ض����й������ԣ�  �����ǽ��NPC��
	void*			add_value;							//����Ԫ�صĸ���ֵ
}MT_UNIT_PRO_T;

//��ͼ����.ÿ�����־һ��20*20�ľ�������.
//ע��:	x��Ӧ��ͼ�е���,y��Ӧ��ͼ�е���.
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
//��ǰ��Ϸ״̬�ı�־��
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

//������Ϸʱ��Ҫ���������
typedef struct  
{
	uint32		save_mark;
	MAP			map_info;
	MT_LIFE_T	hero_info;
	MT_STATE_T	state_info;
}MT_GAME_SAVE_T;

// {	MAP_UNIT_NULL,				TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},

//����Ԫ�ص����� ����MT_UNIT_Eö������һһ��Ӧ
//У��ʱ������VA��ʾ��ö�ٱ���ֵ�������м��.
#define TXT_NULL	NULL
LOCAL const MT_UNIT_PRO_T s_mt_unit_pro[MAP_UNIT_MAX] = 
{
	{	MAP_UNIT_NULL,				NULL,			{IMAGE_NULL,IMAGE_NULL},					IMAGE_NULL,{0},					{0}},

	//��ͼ�еĹ̶�Ԫ��
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

	{	MAP_UNIT_NPC_0_1,			"����",			{IMAGE_MT_NPC_D0,IMAGE_MT_NPC_D1},			IMAGE_MT_NPC_D_F,{0},			{0}},
	{	MAP_UNIT_NPC_0_2,			"����",			{IMAGE_MT_NPC_D0,IMAGE_MT_NPC_D1},			IMAGE_MT_NPC_D_F,{0},			{0}	},
	{	MAP_UNIT_NPC_2_1,			"��������",		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_2_2,			"����",			{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_4_1,			"С͵",			{IMAGE_MT_NPC_C0,IMAGE_MT_NPC_C1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_4_2,			"С͵",			{IMAGE_MT_NPC_C0,IMAGE_MT_NPC_C1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_1_0,		"��������",		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_1_1,		"��������",		{IMAGE_MT_NPC_A0,IMAGE_MT_NPC_A1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_2_0,		"����",			{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_15_2_1,		"����",			{IMAGE_MT_NPC_B0,IMAGE_MT_NPC_B1},			IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_16_1,			"����ħ��",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_18_1,			"����",			{IMAGE_MT_PRINCESS0,IMAGE_MT_PRINCESS1},	IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_19_1,			"ڤ��ħ��",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_19_2,			"ڤ��ħ��",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	{	MAP_UNIT_NPC_21_1,			"ڤ��ħ��",		{IMAGE_MT_FLOOR,IMAGE_NULL},				IMAGE_NULL,{0},					{0}},
	//����Ʒ
	{	MAP_UNIT_Y_KEY,				TXT_NULL,		{IMAGE_MT_Y_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ�һ�� ��Կ��"},
	{	MAP_UNIT_B_KEY,				TXT_NULL,		{IMAGE_MT_B_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ�һ�� ��Կ��"},
	{	MAP_UNIT_R_KEY,				TXT_NULL,		{IMAGE_MT_R_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ�һ�� ��Կ��"},
	{	MAP_UNIT_BIG_KEY,			TXT_NULL,		{IMAGE_MT_BIG_KEY,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ�һ�Ѵ�Կ��,ÿ��Կ�׼�1"},
	{	MAP_UNIT_OF_CRYSTAL,		TXT_NULL,		{IMAGE_MT_OF_CRYSTAL,IMAGE_NULL},			IMAGE_NULL,{0},					"�õ�����ˮ��,��������3"},
	{	MAP_UNIT_DF_CRYSTAL,		TXT_NULL,		{IMAGE_MT_DF_CRYSTAL,IMAGE_NULL},			IMAGE_NULL,{0},					"�õ�����ˮ��,��������3"},
	{	MAP_UNIT_LEVEL_UP,			TXT_NULL,		{IMAGE_MT_LEVEL_A,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� С����,�ȼ���1"},
	{	MAP_UNIT_BIG_LEVEL_UP,		TXT_NULL,		{IMAGE_MT_LEVEL_A,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� �����,�ȼ���3"},
	{	MAP_UNIT_MONEY,				TXT_NULL,		{IMAGE_MT_MONEY,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� ��Բ,��Ҽ�300"},
	{	MAP_UNIT_SWORD_A,			TXT_NULL,		{IMAGE_MT_SWORD_A,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� ����,��������10"},
	{	MAP_UNIT_SHIELD_A,			TXT_NULL,		{IMAGE_MT_SHIELD_A,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� ����,��������10"},
	{	MAP_UNIT_SWORD_B,			TXT_NULL,		{IMAGE_MT_SWORD_B,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� ��潣,��������70"},
	{	MAP_UNIT_SHIELD_B,			TXT_NULL,		{IMAGE_MT_SHIELD_B,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� �ƽ��,��������85"},
	{	MAP_UNIT_SWORD_C,			TXT_NULL,		{IMAGE_MT_SWORD_C,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� �ǹ���,������150"},
	{	MAP_UNIT_SHIELD_C,			TXT_NULL,		{IMAGE_MT_SHIELD_C,IMAGE_NULL},				IMAGE_NULL,{0},					"�õ� ��â���,������190"},
	{	MAP_UNIT_SMALL_SUPPLY,		TXT_NULL,		{IMAGE_MT_SMALL_SUPPLY,IMAGE_NULL},			IMAGE_NULL,{0},					"�õ� СѪƿ,����ֵ��200"},
	{	MAP_UNIT_BIG_SUPPLY,		TXT_NULL,		{IMAGE_MT_BIG_SUPPLY,IMAGE_NULL},			IMAGE_NULL,{0},					"�õ� ��Ѫƿ,����ֵ��500"},
	{	MAP_UNIT_TOOL_LOOK,			TXT_NULL,		{IMAGE_MT_TOOL_LOOK,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_LOOK,{0},					{0}},
	{	MAP_UNIT_TOOL_CROSS,		TXT_NULL,		{IMAGE_MT_TOOL_CROSS,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_CROSS,{0},				{0}},
	{	MAP_UNIT_TOOL_JUMP,			TXT_NULL,		{IMAGE_MT_TOOL_JUMP,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_JUMP,{0},					{0}},
	{	MAP_UNIT_HAMMER,			TXT_NULL,		{IMAGE_MT_TOOL_HAMMER_A,IMAGE_NULL},		IMAGE_NULL,{0},								{0}},
	{	MAP_UNIT_HAMMER_18FLOOR,	TXT_NULL,		{IMAGE_MT_TOOL_HAMMER_B,IMAGE_NULL},		IMAGE_MT_TOOL_TIP_18,{0},					{0}},
	{	MAP_UNIT_TOOL_WARTER,		TXT_NULL,		{IMAGE_MT_TOOL_WARTER,IMAGE_NULL},			IMAGE_MT_TOOL_TIP_WARTER,{0},				{0}},

	//Ӣ�ۡ�����
	{	MAP_UNIT_GIRL,				"����",			{IMAGE_MT_NPC_D0,IMAGE_MT_NPC_D1},								IMAGE_MT_NPC_D_F,				{0},									{0}	},
	{	MAP_UNIT_PRINCESS,			"����",			{IMAGE_MT_PRINCESS0,IMAGE_MT_PRINCESS1},						IMAGE_MT_PRINCESS_F,			{0},									{0}	},
	{	MAP_UNIT_HERO,				"��ʿ",			{IMAGE_MT_HERO_D1,IMAGE_MT_HERO_D1},							IMAGE_MT_HERO_F,				{0},									{0}	},
		//��һ�� 1~10��
	{	MAP_UNIT_GREEN_SLIME,		"��ʷ��ķ",		{IMAGE_MT_GREEN_SLIME0,IMAGE_MT_GREEN_SLIME1},					IMAGE_MT_GREEN_SLIME_F,			{50,20,1,1,1},							{0}	},
	{	MAP_UNIT_RED_SLIME,			"��ʷ��ķ",		{IMAGE_MT_RED_SLIME0,IMAGE_MT_RED_SLIME1},						IMAGE_MT_RED_SLIME_F,			{70,15,2,2,2},							{0}	},
	{	MAP_UNIT_CYAN_SLIME,		"��ʷ��ķ",		{IMAGE_MT_CYAN_SLIME0,IMAGE_MT_CYAN_SLIME1},					IMAGE_MT_CYAN_SLIME_F,			{200,35,10,5,5},						{0}	},
	{	MAP_UNIT_SLIME_LORD,		"ʷ��ķ��",		{IMAGE_MT_SLIME_LORD0,IMAGE_MT_SLIME_LORD1},					IMAGE_MT_SLIME_LORD_F,			{700,250,125,32,30},					{0}	},
	{	MAP_UNIT_SKELETON_A,		"���öӳ�",		{IMAGE_MT_SKELETON_A0,IMAGE_MT_SKELETON_A1},					IMAGE_MT_SKELETON_A_F,			{400,90,50,15,12},						{0}	},
	{	MAP_UNIT_SKELETON_B,		"����ʿ��",		{IMAGE_MT_SKELETON_B0,IMAGE_MT_SKELETON_B1},					IMAGE_MT_SKELETON_B_F,			{150,40,20,8,6},						{0}	},
	{	MAP_UNIT_SKELETON_C,		"������",		{IMAGE_MT_SKELETON_C0,IMAGE_MT_SKELETON_C1},					IMAGE_MT_SKELETON_C_F,			{110,25,5,5,4},							{0}	},
	{	MAP_UNIT_BAT,				"С����",		{IMAGE_MT_BAT0,IMAGE_MT_BAT1},									IMAGE_MT_BAT_F,					{100,20,5,3,3},							{0}	},
	{	MAP_UNIT_BIG_BAT,			"������",		{IMAGE_MT_BIG_BAT0,IMAGE_MT_BIG_BAT1},							IMAGE_MT_BIG_BAT_F,				{150,65,30,10,8},						{0}	},
	{	MAP_UNIT_VAMPIRE_BAT,		"��Ѫ����",		{IMAGE_MT_VAMPIRE_BAT0,IMAGE_MT_VAMPIRE_BAT1},					IMAGE_MT_VAMPIRE_BAT_F,			{550,160,90,25,20},						{0}	},
	{	MAP_UNIT_PRIEST,			"��ʦ",			{IMAGE_MT_PRIEST0,IMAGE_MT_PRIEST1},							IMAGE_MT_PRIEST_F,				{125,50,25,10,7},						{0}	},
	{	MAP_UNIT_SUPER_PRIEST,		"�߼���ʦ",		{IMAGE_MT_SUPER_PRIEST0,IMAGE_MT_SUPER_PRIEST1},				IMAGE_MT_SUPER_PRIEST_F,		{100,200,110,30,25},					{0}	},
	{	MAP_UNIT_SORCERER,			"��ʿ",			{IMAGE_MT_SORCERER0,IMAGE_MT_SORCERER1},						IMAGE_MT_SORCERER_F,			{250,120,70,20,17},						{0}	},
	{	MAP_UNIT_SUPER_SORCERER,	"�߼���ʿ",		{IMAGE_MT_SUPER_SORCERER0,IMAGE_MT_SUPER_SORCERER1},			IMAGE_MT_SUPER_SORCERER_F,		{500,400,260,47,45},					{0}	},
	{	MAP_UNIT_GUARD_A,			"�߼�����",		{IMAGE_MT_GUARD_A0,IMAGE_MT_GUARD_A1},							IMAGE_MT_GUARD_A_F,				{1500,560,460,60,60},					{0}	},
	{	MAP_UNIT_GUARD_B,			"�м�����",		{IMAGE_MT_GUARD_B0,IMAGE_MT_GUARD_B1},							IMAGE_MT_GUARD_B_F,				{1250,500,400,55,55},					{0}	},
	{	MAP_UNIT_GUARD_C,			"��������",		{IMAGE_MT_GUARD_C0,IMAGE_MT_GUARD_C1},							IMAGE_MT_GUARD_C_F,				{450,150,90,22,19},						{0}	},
	{	MAP_UNIT_ZOMBIE,			"��ʬ",			{IMAGE_MT_ZOMBIE0,IMAGE_MT_ZOMBIE1},							IMAGE_MT_ZOMBIE_F,				{300,75,45,13,10},						{0}	},
	{	MAP_UNIT_SUPER_ZOMBIE,		"�߼���ʬ",		{IMAGE_MT_SUPER_ZOMBIE0,IMAGE_MT_SUPER_ZOMBIE1},				IMAGE_MT_SUPER_ZOMBIE_F,		{900,450,330,50,50},					{0}	},
	{	MAP_UNIT_ROCK,				"ʯͷ��",		{IMAGE_MT_ROCK0,IMAGE_MT_ROCK1},								IMAGE_MT_ROCK_F,				{500,115,65,15,15},						{0}	},
	{	MAP_UNIT_SWORDSMAN,			"˫�ֽ�ʿ",		{IMAGE_MT_SWORDSMAN0,IMAGE_MT_SWORDSMAN1},						IMAGE_MT_SWORDSMAN_F,			{1200,620,520,65,75},					{0}	},
	{	MAP_UNIT_UNDERWORLD_SOLDIER,"ڤ��ʿ",		{IMAGE_MT_UNDERWORLD_SOLDIER0,IMAGE_MT_UNDERWORLD_SOLDIER1},	IMAGE_MT_UNDERWORLD_SOLDIER_F,	{2000,680,590,70,65},					{0}	},
	{	MAP_UNIT_UNDERWORLD_HEADER,	"ڤ�ӳ�",		{IMAGE_MT_UNDERWORLD_HEADER0,IMAGE_MT_UNDERWORLD_HEADER1},		IMAGE_MT_UNDERWORLD_HEADER_F,	{2500,900,850,84,75},					{0}	},
	{	MAP_UNIT_UNDERWORLD_HEADER2,"ڤ�ӳ�",		{IMAGE_MT_UNDERWORLD_HEADER0,IMAGE_MT_UNDERWORLD_HEADER1},		IMAGE_MT_UNDERWORLD_HEADER_F,	{3333,1200,1133,112,100},				{0}	},
	{	MAP_UNIT_GOLD_GUARD,		"����ʿ",		{IMAGE_MT_GOLD_GUARD0,IMAGE_MT_GOLD_GUARD1},					IMAGE_MT_GOLD_GUARD_F,			{850,350,200,45,40},					{0}	},
	{	MAP_UNIT_GUARD_HEADER,		"��ʿ�ӳ�",		{IMAGE_MT_GUARD_HEADER0,IMAGE_MT_GUARD_HEADER1},				IMAGE_MT_GUARD_HEADER_F,		{900,750,650,77,70},					{0}	},
	{	MAP_UNIT_UPWORLD_SOLDIER,	"����ʿ",		{IMAGE_MT_UPWORLD_SOLDIER0,IMAGE_MT_UPWORLD_SOLDIER1},			IMAGE_MT_UPWORLD_SOLDIER_F,		{1200,980,900,88,75},					{0}	},
	{	MAP_UNIT_UPWORLD_SOLDIER2,	"����ʿ",		{IMAGE_MT_UPWORLD_SOLDIER0,IMAGE_MT_UPWORLD_SOLDIER1},			IMAGE_MT_UPWORLD_SOLDIER_F,		{1600,1300,1200,117,100},				{0}	},
	{	MAP_UNIT_UPWORLD_PRIEST,	"�鷨ʦ",		{IMAGE_MT_UPWORLD_PRIEST0,IMAGE_MT_UPWORLD_PRIEST1},			IMAGE_MT_UPWORLD_PRIEST_F,		{1500,830,730,80,70},					{0}	},
	{	MAP_UNIT_UPWORLD_PRIEST2,	"�鷨ʦ",		{IMAGE_MT_UPWORLD_PRIEST0,IMAGE_MT_UPWORLD_PRIEST1},			IMAGE_MT_UPWORLD_PRIEST_F,		{2000,1106,973,106,93},					{0}	},
	{	MAP_UNIT_SHADOW_SOLDIER,	"Ӱ��սʿ",		{IMAGE_MT_SHADOW_SOLDIER0,IMAGE_MT_SHADOW_SOLDIER1},			IMAGE_MT_SHADOW_SOLDIER_F,		{3100,1150,1050,92,80},					{0}	},
	{	MAP_UNIT_WHITE_SERGEANT,	"������ʿ",		{IMAGE_MT_WHITE_SERGEANT0,IMAGE_MT_WHITE_SERGEANT1},			IMAGE_MT_WHITE_SERGEANT_F,		{1300,300,150,40,35},					{0}	},
	{	MAP_UNIT_RED_SERGEANT,		"������ʿ",		{IMAGE_MT_RED_SERGEANT0,IMAGE_MT_RED_SERGEANT1},				IMAGE_MT_RED_SERGEANT_F,		{15000,1000,1000,100,100},				{0}	},
	{	MAP_UNIT_RED_SERGEANT2,		"����ħ��",		{IMAGE_MT_RED_SERGEANT0,IMAGE_MT_RED_SERGEANT1},				IMAGE_MT_RED_SERGEANT_F,		{20000,1333,1333,133,133},				{0}	},
	{	MAP_UNIT_SPIDER,			"ѪӰ",			{IMAGE_MT_SPIDER0,IMAGE_MT_SPIDER1},							IMAGE_MT_SPIDER_F,				{99999,5000,4000,0,0},					{0}	},
	{	MAP_UNIT_DRAGON,			"ħ��",			{IMAGE_MT_DRAGON0,IMAGE_MT_DRAGON1},							IMAGE_MT_DRAGON_F,				{99999,9999,5000,0,0},					{0}	},
	{	MAP_UNIT_MASTER,			"ħ��",			{IMAGE_MT_MASTER0,IMAGE_MT_MASTER1},							IMAGE_MT_MASTER_F,				{30000,1700,1500,250,220},				{0}	},
	{	MAP_UNIT_MASTER2,			"ħ��",			{IMAGE_MT_MASTER0,IMAGE_MT_MASTER1},							IMAGE_MT_MASTER_F,				{4500,2550,2250,312,275},				{0}	},
	{	MAP_UNIT_CHEAT_TIP,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"����ģʽ�ѿ���"},
	{	MAP_UNIT_SAVE_TIP,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"��Ϸ�ѱ���"},
	{	MAP_UNIT_SOUND_ON,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"���֣���"},
	{	MAP_UNIT_SOUND_OFF,			TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},					"���֣���"},
	{	NULL,						TXT_NULL,		{IMAGE_NULL,IMAGE_NULL},										IMAGE_NULL,						{0},									{0}	},

};
#undef TXT_NULL
//��ʼӢ����Ϣ
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

// �Ի�����
	//ÿ��������ò�Ҫ����33���ֽ�.
LOCAL const SINGLE_DIALOG_T s_dialog_0_1[42] = 
{
	{MAP_UNIT_HERO,"  ......"},
	{MAP_UNIT_NPC_0_1,"  ������!"},
	{MAP_UNIT_HERO,"  ......\n����˭?��������?"},
	{MAP_UNIT_NPC_0_1,"  �������������,�ղ��㱻�����"},
	{MAP_UNIT_NPC_0_1,"С�ִ�����."},
	{MAP_UNIT_HERO,"  ...\n��,��,�ҵĽ���?"},
	{MAP_UNIT_NPC_0_1,"  ��Ľ�������������,��ֻ���ü�"},
	{MAP_UNIT_NPC_0_1,"����ȳ���."},
	{MAP_UNIT_HERO,"  ��,������?�������ȹ�����."},
	{MAP_UNIT_NPC_0_1,"  ������������,��������ȥ�Ǵ򲻹�"},
	{MAP_UNIT_NPC_0_1,"��������ֵ�."},
	{MAP_UNIT_HERO,"  ������ô��?�Ҵ�Ӧ�˹���һ��Ҫ"},
	{MAP_UNIT_HERO,"�ѹ����ͳ�����."},
	{MAP_UNIT_NPC_0_1,"  ���İ�,�Ұ��ҵ����������,���"},
	{MAP_UNIT_NPC_0_1,"���Դ�Ӯ��Щ������.����,"},
	{MAP_UNIT_NPC_0_1,"����Ȱ���ȥ��һ������,�ҵ�����"},
	{MAP_UNIT_NPC_0_1,"����������."},
	{MAP_UNIT_HERO,"  �Ҷ���?��ʲô����?"},
	{MAP_UNIT_NPC_0_1,"  ��һ��ʮ�ּ�,�м���һ�ź�ɫ��"},
	{MAP_UNIT_NPC_0_1,"��ʯ."},
	{MAP_UNIT_NPC_0_1,"  �ұ������������ػ���,"},
	{MAP_UNIT_NPC_0_1,"�ɲ���ǰ,�ӱ�������һ����ħ,"},
	{MAP_UNIT_NPC_0_1,"����ռ����������,�����ҵ�ħ��"},
	{MAP_UNIT_NPC_0_1,"���������ʮ�ּ�����,�������"},
	{MAP_UNIT_NPC_0_1,"����������,���ҵ�ħ���������"},
	{MAP_UNIT_NPC_0_1,"�ָ�,��ʱ���ұ���԰����������"},
	{MAP_UNIT_NPC_0_1,"ȥ�ȹ�����."},
	{MAP_UNIT_NPC_0_1,"  Ҫ��ס:ֻ�����ҵ�ħ���ſ���"},
	{MAP_UNIT_NPC_0_1,"��21�����."},
	{MAP_UNIT_HERO,"  ......\n�ð�,�����Կ�."},
	{MAP_UNIT_NPC_0_1,"  �ղ���ȥ������,��Ľ�������3¥,"},
	{MAP_UNIT_NPC_0_1,"��Ķ���5¥,���Ǹ�ʮ�ּܱ�����"},
	{MAP_UNIT_NPC_0_1,"7¥,�����ȥȡ����Ľ��Ͷ�."},
	{MAP_UNIT_NPC_0_1,"  ����,�����������¥����,��"},
	{MAP_UNIT_NPC_0_1,"����˺ü�����ı���,����õ�"},
	{MAP_UNIT_NPC_0_1,"����,������Ը�������Ĺ���,"},
	{MAP_UNIT_NPC_0_1,"���зǳ���İ���."},
	{MAP_UNIT_HERO,"  ����,����ô��ȥ��?"},
	{MAP_UNIT_NPC_0_1,"  ��������3��Կ��,������ȥ,"},
	{MAP_UNIT_NPC_0_1,"�������滹�кܶ�������Կ��,"},
	{MAP_UNIT_NPC_0_1,"��һ��Ҫ��ϧʹ��."},
	{MAP_UNIT_NPC_0_1,"  �¸ҵ�ȥ��,��ʿ!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_0_2[8] = 
{
	{MAP_UNIT_HERO,"  ����,���Ѿ����Ǹ�ʮ�ּ��ҵ���."},
	{MAP_UNIT_GIRL,"  �����ĺܺ�.\n��ô,������"},
	{MAP_UNIT_GIRL,"�Ϳ�ʼ�������ǿ������!"},
	{MAP_UNIT_GIRL,"  �������仩......"},
	{MAP_UNIT_GIRL,"  ����,���Ѿ����������������!"},
	{MAP_UNIT_GIRL,"  ��ס:�����û���㹻��ʵ���Ļ�,"},
	{MAP_UNIT_GIRL,"��Ҫȥ��21��!������,�����б���"},
	{MAP_UNIT_GIRL,"�ķ�������ʧȥ����!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_2_1[] = 
{
	{MAP_UNIT_HERO,		"  ���Ѿ��þ���!"},
	{MAP_UNIT_NPC_2_1,	"  Ŷ,�ҵĺ���,����̫��л����!"},
	{MAP_UNIT_NPC_2_1,	"  ����ط���������,����Ŀ����"},
	{MAP_UNIT_NPC_2_1,	"��ȥ��."},
	{MAP_UNIT_HERO,		"  ���߰�,�һ���ȥ�ȱ���������Ĺ�"},
	{MAP_UNIT_HERO,		"��."},
	{MAP_UNIT_NPC_2_1,	"  Ŷ,�������ȹ�����,Ϊ�˱�ʾ�����"},
	{MAP_UNIT_NPC_2_1,	"��л,����������͸����,�⻹����"},
	{MAP_UNIT_NPC_2_1,	"�����ʱ���ù���,������ȥ���"},
	{MAP_UNIT_NPC_2_1,	"������!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_2_2[] = 
{
	{MAP_UNIT_HERO,		"  ���Ѿ��þ���!"},
	{MAP_UNIT_NPC_2_2,	"  Ŷ,����,����̫��л����!"},
	{MAP_UNIT_NPC_2_2,	"  ���Ǹ�����,��֪Ϊʲô��ץ������"},
	{MAP_UNIT_NPC_2_2,	"����."},
	{MAP_UNIT_HERO,		"  �������Ѿ�������!"},
	{MAP_UNIT_NPC_2_2,	"  Ŷ,�ԶԶ�,���Ѿ�������."},
	{MAP_UNIT_NPC_2_2,	"  ������������͸����,������׼��"},
	{MAP_UNIT_NPC_2_2,	"��Ǯ��.����������һ�����а���!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_4_1[26] = 
{
	{MAP_UNIT_HERO,		"  ���Ѿ��þ���"},
	{MAP_UNIT_NPC_4_1,	"  ��,������̫����,���ֿ�������"},
	{MAP_UNIT_NPC_4_1,	"����Ѱ����!"},
	{MAP_UNIT_NPC_4_1,	"  Ŷ,��û�����ҽ���,�ҽ�Jack,"},
	{MAP_UNIT_NPC_4_1,	"���⸽��������С͵,ʲô�����Ʊ�"},
	{MAP_UNIT_NPC_4_1,	"������͵��."},
	{MAP_UNIT_NPC_4_1,	"  ������������ɲ���̫��,�ս���"},
	{MAP_UNIT_NPC_4_1,	"�ͱ�ץ��."},
	{MAP_UNIT_NPC_4_1,	"  ��������Ҵ�����,���Ұ���"},
	{MAP_UNIT_NPC_4_1,	"��һ���°�."},
	{MAP_UNIT_HERO,		"  ���߰�,���滹�кܶ����,�ҿ���"},
	{MAP_UNIT_HERO,		"�˲�����."},
	{MAP_UNIT_NPC_4_1,	"  ��,��,�������µ�.��˵��,"},
	{MAP_UNIT_NPC_4_1,	"������ʲô?"},
	{MAP_UNIT_HERO,		"  ......\n��Ὺ����?"},
	{MAP_UNIT_NPC_4_1,	"  �ǵ�Ȼ."},
	{MAP_UNIT_HERO,		"  �Ǿ�������Ҵ򿪵ڶ�����Ű�!"},
	{MAP_UNIT_NPC_4_1,	"  �Ǹ���,����,������ܰ���?"},
	{MAP_UNIT_NPC_4_1,	"�ҵ�һ��Ƕ�˺�ɫ��ʯ������ͷ�Ļ�,"},
	{MAP_UNIT_NPC_4_1,	"�һ������ͨ��18���·"},
	{MAP_UNIT_HERO,		"  Ƕ�˺�ɫ��ʯ������ͷ?,�ð�,"},
	{MAP_UNIT_HERO,		"�Ұ�������."},
	{MAP_UNIT_NPC_4_1,	"  �ǳ���л��.һ���ҾͰѵڶ���"},
	{MAP_UNIT_NPC_4_1,	"���Ŵ�."},
	{MAP_UNIT_NPC_4_1,	"  ������ҵ��Ǹ�����ͷ�Ļ�,����"},
	{MAP_UNIT_NPC_4_1,	"����������!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_4_2[4] = 
{	
	{MAP_UNIT_HERO,		"  ��,�쿴,���ҵ���ʲô!"},
	{MAP_UNIT_NPC_4_2,	"  ̫����,���������Ȼ��������."},
	{MAP_UNIT_NPC_4_2,	"  �ð�,�����ȥ�����޺õ�18���"},
	{MAP_UNIT_NPC_4_2,	" ·��."},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_1_0[] = 
{	
	{MAP_UNIT_NPC_15_1_0,		"  ���,�¸ҵĺ���,����������������."},
	{MAP_UNIT_NPC_15_1_0,		"  �ҽ�����һ���ǳ��õı���,������"},
	{MAP_UNIT_NPC_15_1_0,		"ʹ��Ĺ���������120 ��.���������"},
	{MAP_UNIT_NPC_15_1_0,		"��� 500 �㾭�������н���,"},
	{MAP_UNIT_NPC_15_1_0,		"�㿼��һ���Ӱ�."},
	{MAP_UNIT_HERO,				"  ��,�������ڻ�û����ô��ľ���."},
	{MAP_UNIT_NPC_15_1_0,		"  �ǵ���ľ��鹻��������!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_1_1[] = 
{	
	{MAP_UNIT_NPC_15_1_1,		"  ���,�¸ҵĺ���,����������������."},
	{MAP_UNIT_NPC_15_1_1,		"  �ҽ�����һ���ǳ��õı���,������ʹ"},
	{MAP_UNIT_NPC_15_1_1,		"��Ĺ��������� 120 ��.���������"},
	{MAP_UNIT_NPC_15_1_1,		"��� 500 �㾭�������н���,"},
	{MAP_UNIT_NPC_15_1_1,		"�㿼��һ���Ӱ�."},
	{MAP_UNIT_HERO,				"  �ð�,�Ǿͽ������Ұ�!"},
	{MAP_UNIT_NPC_15_1_1,		" �Ǻð�,��ѽ��͸�����!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_2_0[] = 
{	
	{MAP_UNIT_NPC_15_2_1,		"  ����,��ӭ��ĵ���!��������һ����"},
	{MAP_UNIT_NPC_15_2_1,		"����˵�ǳ��õı���,ֻҪ�������Ǯ,"},
	{MAP_UNIT_NPC_15_2_1,		"�Ҿ�������."},
	{MAP_UNIT_HERO,				"  ʲô����?����Ǯ?"},
	{MAP_UNIT_NPC_15_2_1,		"  �������Ϸ����õĶ���,����ֵ"},
	{MAP_UNIT_NPC_15_2_1,		"��������120��,����ֻҪ��500��"},
	{MAP_UNIT_NPC_15_2_1,		"��ҾͿ�������."},
	{MAP_UNIT_NPC_15_2_1,		"  ��ô��?����500�������?"},
	{MAP_UNIT_HERO,				"  ��?�һ�û��."},
	{MAP_UNIT_NPC_15_2_1,		"  �ǵ�������500������������Ұ�!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_15_2_1[] = 
{	
	{MAP_UNIT_NPC_15_2_1,		"  ����,��ӭ��ĵ���!��������һ����"},
	{MAP_UNIT_NPC_15_2_1,		"����˵�ǳ��õı���,ֻҪ�������Ǯ,"},
	{MAP_UNIT_NPC_15_2_1,		"�Ҿ�������."},
	{MAP_UNIT_HERO,				"  ʲô����?����Ǯ?"},
	{MAP_UNIT_NPC_15_2_1,		"  �������Ϸ����õĶ���,����ֵ"},
	{MAP_UNIT_NPC_15_2_1,		"��������120��,����ֻҪ��500��"},
	{MAP_UNIT_NPC_15_2_1,		"��ҾͿ�������."},
	{MAP_UNIT_NPC_15_2_1,		"  ��ô��?����500�������?"},
	{MAP_UNIT_HERO,				"  ����500�����."},
	{MAP_UNIT_NPC_15_2_1,		"  ��,�ɽ�!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_16_1[] = 
{	
	{MAP_UNIT_HERO,			"  ......"},
	{MAP_UNIT_NPC_16_1,		"  ֹͣ��,�޴�������!"},
	{MAP_UNIT_HERO,			"  ��ֹͣ������!ħ��."},
	{MAP_UNIT_HERO,			"  ��˵,��������������?"},
	{MAP_UNIT_NPC_16_1,		"  �����Ӯ����˵��!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_18_1[] = 
{	
	{MAP_UNIT_HERO,			"  ����!��þ���!"},
	{MAP_UNIT_NPC_18_1,		"  ��,���������ҵ���?"},
	{MAP_UNIT_HERO,			"  �ǵ�,���Ƿ��˹����������������."},
	{MAP_UNIT_HERO,			"  ��������ҳ�ȥ��!"},
	{MAP_UNIT_NPC_18_1,		"  ��,�һ�������."},
	{MAP_UNIT_HERO,			"  Ϊʲô?���ﵽ���Ǵ��ħ."},
	{MAP_UNIT_NPC_18_1,		"  ������Ϊ�����浽�����ж�ħ,"},
	{MAP_UNIT_NPC_18_1,		"���ԲŲ����Ծ�������ȥ,��Ҫ����"},
	{MAP_UNIT_NPC_18_1,		"�Ǹ����ħ��ɱ��!"},
	{MAP_UNIT_NPC_18_1,		"  Ӣ�µ���ʿ,������ܹ����Ǹ�"},
	{MAP_UNIT_NPC_18_1,		"���ħɱ��,�Ҿͺ���һ���ȥ!"},
	{MAP_UNIT_HERO,			"  ���ħ?���Ѿ�ɱ����һ��ħ��!"},
	{MAP_UNIT_NPC_18_1,		"  ���ħ�������������,��ɱ��"},
	{MAP_UNIT_NPC_18_1,		"���Ǹ�����ֻ��һ��С��ħ."},
	{MAP_UNIT_HERO,			"  ��,�������,����ɱ���Ǹ����ħ"},
	{MAP_UNIT_HERO,			"������������!"},
	{MAP_UNIT_NPC_18_1,		"  ���ħ����ղ�ɱ�����Ǹ�������"},
	{MAP_UNIT_NPC_18_1,		"��.�������������,������ħ��"},
	{MAP_UNIT_NPC_18_1,		"���Ĺ������ͷ�������������"},
	{MAP_UNIT_NPC_18_1,		"����һ������,���С��!"},
	{MAP_UNIT_NPC_18_1,		"  ����һ��Ҫɱ����ħ��!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_19_1[] = 
{	
	{MAP_UNIT_HERO,			"  ��ħͷ,������ڵ���!"},
	{MAP_UNIT_NPC_19_1,		"  ������......\n��������˼."},
	{MAP_UNIT_NPC_19_1,		"  ����Ϊ�����Ǽһ����������,���"},
	{MAP_UNIT_NPC_19_1,		"���Դ����,�������㻹������!"},
	{MAP_UNIT_HERO,			"  �ϻ���˵,ȥ����!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_19_2[] = 
{	
	{MAP_UNIT_NPC_19_2,		"  ���������㻹��������"},
	{MAP_UNIT_NPC_19_2,		"  �б��µĻ�����21¥."},
	{MAP_UNIT_NPC_19_2,		"  ������,����Լ�ʶ��������ʵ��!"},
};
LOCAL const SINGLE_DIALOG_T s_dialog_21_1[] = 
{	
	{MAP_UNIT_NPC_21_1,		"  ��......\n  ��ô����"},
	{MAP_UNIT_NPC_21_1,		"  ����ô���ܻᱻ������?"},
	{MAP_UNIT_NPC_21_1,		"  ��,��Ҫ����........."},
};
//����MAP_UNIT_Eö�ٱ���˳����ͬ
LOCAL const DIALOG_T s_dialog[] = 
{
	{	{{160,120},{100,90}},	&s_dialog_0_1,	sizeof(s_dialog_0_1)/sizeof(SINGLE_DIALOG_T)},					//���0�����Ů�ĵ�һ�ζԻ�.
	{	{{160,120},{100,90}},	&s_dialog_0_2,	sizeof(s_dialog_0_2)/sizeof(SINGLE_DIALOG_T)},					//���0�����Ů�ĵ�һ�ζԻ�.
	{	{{160,120},{100,90}},	&s_dialog_2_1,	sizeof(s_dialog_2_1)/sizeof(SINGLE_DIALOG_T)},					//���4��ĵ����ĵ�һ�ζԻ�.
	{	{{160,120},{100,90}},	&s_dialog_2_2,	sizeof(s_dialog_2_2)/sizeof(SINGLE_DIALOG_T)},					//���4��ĵ����ĵ�һ�ζԻ�.
	{	{{160,120},{100,90}},	&s_dialog_4_1,	sizeof(s_dialog_4_1)/sizeof(SINGLE_DIALOG_T)},					//���4��ĵ����ĵ�һ�ζԻ�.
	{	{{160,120},{100,90}},	&s_dialog_4_2,	sizeof(s_dialog_4_2)/sizeof(SINGLE_DIALOG_T)},					//���4��ĵ����ĵ�һ�ζԻ�.
	{	{{77,99},{150,150}},	&s_dialog_15_1_0,sizeof(s_dialog_15_1_0)/sizeof(SINGLE_DIALOG_T)},				//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_15_1_1,sizeof(s_dialog_15_1_1)/sizeof(SINGLE_DIALOG_T)},				//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_15_2_0,sizeof(s_dialog_15_2_0)/sizeof(SINGLE_DIALOG_T)},				//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_15_2_1,sizeof(s_dialog_15_2_1)/sizeof(SINGLE_DIALOG_T)},				//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_16_1,	sizeof(s_dialog_16_1)/sizeof(SINGLE_DIALOG_T)},					//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_18_1,	sizeof(s_dialog_18_1)/sizeof(SINGLE_DIALOG_T)},					//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_19_1,	sizeof(s_dialog_19_1)/sizeof(SINGLE_DIALOG_T)},					//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_19_2,	sizeof(s_dialog_19_2)/sizeof(SINGLE_DIALOG_T)},					//���15����������˵ĶԻ�.
	{	{{77,99},{150,150}},	&s_dialog_21_1,	sizeof(s_dialog_21_1)/sizeof(SINGLE_DIALOG_T)},					//���15����������˵ĶԻ�.
};

//����MAP_UNIT_Eö�ٱ���˳����ͬ
LOCAL const	STORE_T s_store[] = 
{
	//��3����̵�
	{
		{
			"  ��Ҫ�������������?�������25�����,�����ѡ��һ��:",
			"���� 800 ������",
			"���� 4 �㹥����",
			"���� 4 �������",
			"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  ��Ҫ�������������?�������25�����,�����ѡ��һ��:",
			"���� 800 ������",
			"���� 4 �㹥����",
			"���� 4 �������",
			"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  ��Ҫ�������������?�������25�����,�����ѡ��һ��:",
			"���� 800 ������",
			"���� 4 �㹥����",
			"���� 4 �������",
			"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},

	//��5���ʹ�þ���ֵ���̵�
	{
		{
			"  ���,Ӣ�µ�����,ֻҪ�����㹻�ľ���,�ҾͿ���������ǿ��:",
			"����һ�� (��Ҫ100��)",
			"����5�㹥�� (��Ҫ30��)",
			"����5����� (��Ҫ30��)",
			"�뿪�̵�"
		},
		{125,60},		
		IMAGE_MT_NPC_A0,
	},
	//��5����Կ�׵��̵�
	{
		{
			"  ������һ�������������,ֻҪ���н��,�ҾͿ��԰���:",
			"���� 1 �ѻ�Կ�� ($ 10)",
			"���� 1 ����Կ�� ($ 50)",
			"���� 1 �Ѻ�Կ�� ($ 100)",
			"�뿪�̵�"
		},
		{155,55},		
		IMAGE_MT_NPC_B0,
	},
	//��11����̵�
	{
		{
			"  ��Ҫ�������������?�������100�����,�����ѡ��һ��:",
			"���� 4000 ������",
			"���� 20 �㹥����",
			"���� 20 �������",
			"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  ��Ҫ�������������?�������100�����,�����ѡ��һ��:",
			"���� 4000 ������",
			"���� 20 �㹥����",
			"���� 20 �������",
			"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	{
		{
			"  ��Ҫ�������������?�������100�����,�����ѡ��һ��:",
				"���� 4000 ������",
				"���� 20 �㹥����",
				"���� 20 �������",
				"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},

	//��Կ�׵�����
	{
		{
			"  Ŷ,��ӭ��ĵ���,���������ȱ�ٽ��,�ҿ��԰���:",
				"���� 1 �ѻ�Կ�� ($ 7)",
				"���� 1 ����Կ�� ($ 35)",
				"���� 1 �Ѻ�Կ�� ($ 70)",
				"�뿪�̵�"
		},
		{137,46},		
		IMAGE_MT_STORE_HEAD,
	},
	//��13��ʹ�þ��������
	{
		{
			"  ���,Ӣ�µ�����,ֻҪ�����㹻�ľ���,�ҾͿ���������ǿ��:",
			"�������� (��Ҫ270��)",
			"����17�㹥�� (��Ҫ95��)",
			"����17����� (��Ҫ95��)",
			"�뿪�̵�"
		},
		{125,60},		
		IMAGE_MT_NPC_A0,
	},

	{
		{
			"  ���,Ӣ�µ�����,ֻҪ�����㹻�ľ���,�ҾͿ���������ǿ��:",
				"�������� (��Ҫ270��)",
				"����17�㹥�� (��Ҫ95��)",
				"����17����� (��Ҫ95��)",
				"�뿪�̵�"
		},
		{125,60},		
		IMAGE_MT_NPC_A0,
	},

};

LOCAL const wchar*	s_other_tip[] = 
{
	"�õ� ͭ�� ������30",
	"�õ� ͭ�� ������30",
	"�õ� ʥ�⽣ ������120!",
	"�õ� �ǹ�� ������120"

};
//��������
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

//��ͼ����

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

 	//��0��
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

 	//��1��
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

	//��2��
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
		
	//��3��
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
	
	//��4��
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

	//��5��
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
	
	//��6��
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
	//��7��
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
	
	//��8��
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
	
	//��9��
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

	//��10��
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
	
	//��11��
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
	
	//��12��
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
	
	//��13��
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
	
	//��14��
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
	
	//��15��
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
	
	//��16��
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
	
	//��17��
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
	
	//��18��
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
	
	//��19��
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

	//��20��
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

	//��21��
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

