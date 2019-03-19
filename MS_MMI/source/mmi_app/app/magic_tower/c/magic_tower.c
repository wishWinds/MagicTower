#include "mmk_type.h"
#include "window_parse.h"
#include "magic_tower.h"
#include "mmi_id.h"
#include "guistring.h"
#include "mmidisplay_data.h"
#include "mmiset.h"
#include "mmivp_export.h"

#define HERO_ANIM_SLEEP		100
#define DOOR_ANIM_TIEMR		60
#define MAP_ANIM_TIMER		300
#define FIGHT_ANIM_TIMER	200
#define SPEED_TIMER			50
#define DIALOG_TIMER		300
#define FIGHT_SLEEP			250
//****************************************************************************//
//实时数据
//****************************************************************************//
LOCAL MT_GAME_SAVE_T	s_game_info = {0}; 

//****************************************************************************//
//UI效果量
//****************************************************************************//
//游戏场景控制着“消息”的处理主体
typedef enum
{
	OPEN_SCENE,
	VOICE_SCENE = OPEN_SCENE,
	MENU_SCENE,
	INSTRUCTION_SCENE,
	HELP_SCENE,
	ABOUT_SCENE,
	MAIN_SCENE,
	FIGHT_SCENE,
	STORE_SCENE,
	DIALOG_SCENE,
	TOOLTIP_SCENE,
	ENEMY_INFO_SCENE,
	EXIT_QUERY_SCENE,
}GAME_SCENE;

typedef enum
{
	RING_NULL,
	RING_MENU,
	RING_ZERO_FLOOR,
	RING_GAME,
	RING_PRINCESS,
	RING_BOSS,
	RING_MAX
}RING_E;

typedef struct 
{
	GUI_LCD_DEV_INFO layer_bg;
	GUI_LCD_DEV_INFO layer_inst;
	GUI_LCD_DEV_INFO layer_info;
	GUI_LCD_DEV_INFO layer_map;
	GUI_LCD_DEV_INFO layer_fight;
	GUI_LCD_DEV_INFO layer_store;
	GUI_LCD_DEV_INFO layer_dialog;
	GUI_LCD_DEV_INFO layer_tool_tip;
	GUI_LCD_DEV_INFO layer_enemy_info;
	GUI_LCD_DEV_INFO layer_tip;
	GUI_LCD_DEV_INFO layer_exit_query;

	//open & end
	uint8			voice_select;
	uint8			menu_select;
	BOOLEAN			is_start_from_save;
	uint8			inst_timer;
	int16			inst_y;
	//door animation
	BOOLEAN			is_door_running;
	uint8			move_direction;	//0:up	1:right	2:down	3:left
	POS_T			door_anim_pos;
	MT_UNIT_E		door_type;
	uint8			door_anim_timer;
	BOOLEAN			is_first_door_anim;

	//map
	uint8			map_anim_timer;
	uint8			speed_timer;
	
	//fight
	BOOLEAN			is_new_fight;
	uint8			fight_timer;
	MT_UNIT_E		cur_enemy;
	MT_LIFE_T		end_life;
// 	int32			cur_enemy_hp;
// 	int32			cur_hero_hp;

	//store
	MT_UNIT_E		store_id;
	uint8			store_index;			//
	int8			store_select_item;

	//dialog
	uint16			dialog_id;
	uint16			talk_index;
	uint8			dialog_anim_timer;

	//enemy_info
	uint8			enemy_info_timer;
	MT_UNIT_E		display_unit_id[8];
	uint8			total_num;

	//exit
	uint8			save_select;


	GAME_SCENE		scene;
	BOOLEAN			is_allow_sound;
	RING_E			ring_id;
}UI_DATA_T;

LOCAL const uint32		s_ring_id[RING_MAX] = {NULL,R_MT_MENU_BG_MUSIC,R_MT_ZERO_FLOOR,R_MT_GAME_BG_MUSIC,R_MT_PRINCESS,R_MT_BOSS};
LOCAL UI_DATA_T			s_ui_data = {0};
LOCAL uint8				s_frame_mark = 0;
LOCAL BOOLEAN			s_is_cheat_mode = FALSE;

//****************************************************************************//
//函数
//****************************************************************************//
LOCAL void				PlayRing(RING_E ring_id)
{
	MMIAUD_RING_DATA_INFO_T     ring_data = {NULL, 0, NULL};

	if (s_ui_data.ring_id != ring_id)
	{
		s_ui_data.ring_id = ring_id;
		MMI_GetRingInfo(s_ring_id[s_ui_data.ring_id], &ring_data);
	
		MMIAPISET_StopAllRing(TRUE);
		if (MMIAPISET_IsPermitPlayRing(MMISET_RING_TYPE_OTHER) && (s_ui_data.is_allow_sound))
		{
			MMIAPISET_PlayRingByPtr(MMISET_RING_TYPE_OTHER,//MMISET_RING_TYPE_OTHER
				1,
				(uint8*)ring_data.data_ptr,
				ring_data.data_len,
				0xffff,
				ring_data.type,
				NULL
				);
		}
	}
	else
	{
	}

}
LOCAL void				SaveGame(void)
{
	uint32			byte_to_write = sizeof(MT_GAME_SAVE_T);
	uint32			byte_written;
	SFS_HANDLE	save_file = 0;
	wchar*		file_name = L"D:\\magic_tower\\game.dat";
	
	s_game_info.save_mark = 0x12345678;
	save_file = SFS_CreateFile(file_name,SFS_MODE_OPEN_ALWAYS|SFS_MODE_WRITE,NULL,NULL);
	SFS_WriteFile(save_file,&s_game_info,byte_to_write,&byte_written,NULL);
	SFS_CloseFile(save_file);
}
LOCAL void				ReadGame(void)
{
	MT_GAME_SAVE_T	game_save = {0};
	uint32			byte_to_read = sizeof(MT_GAME_SAVE_T);
	uint32			byte_readed;
	SFS_HANDLE	save_file = 0;
	wchar*		file_name = L"D:\\magic_tower\\game.dat";
	
	save_file = SFS_CreateFile(file_name,SFS_MODE_OPEN_ALWAYS|SFS_MODE_READ,NULL,NULL);
	SFS_ReadFile(save_file,&game_save,byte_to_read,&byte_readed,NULL);
	if (game_save.save_mark == 0x12345678)
	{
		memcpy(&s_game_info,&game_save,sizeof(MT_GAME_SAVE_T));
		s_ui_data.is_start_from_save = TRUE;
	}
	SFS_CloseFile(save_file);

}
LOCAL void				EndAbout(void)
{
	BOOLEAN		DrawMenu();

	s_ui_data.scene = MENU_SCENE;
	PlayRing(RING_MENU);
	DrawMenu();
}

LOCAL void				ExitGame(void)
{

	MMIDEFAULT_AllowTurnOffBackLight(TRUE);
	MMIAPISET_StopAllRing(TRUE);
}

LOCAL void				StartGameUI(void)
{
	UILAYER_APPEND_BLT_T	layer_append = {0};

	layer_append.layer_level	= UILAYER_LEVEL_NORMAL;
	layer_append.lcd_dev_info	= s_ui_data.layer_info;
	UILAYER_AppendBltLayer(&layer_append);
	layer_append.layer_level	= UILAYER_LEVEL_NORMAL;
	layer_append.lcd_dev_info	= s_ui_data.layer_map;
	UILAYER_AppendBltLayer(&layer_append);

	s_frame_mark = 0;
	s_is_cheat_mode = FALSE;
	s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
}
LOCAL void				QuitGameUI(void)
{
	UILAYER_RemoveBltLayer(&s_ui_data.layer_dialog);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_enemy_info);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_exit_query);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_fight);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_info);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_map);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_tip);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_tool_tip);
	MMK_StopTimer(s_ui_data.dialog_anim_timer);
	MMK_StopTimer(s_ui_data.door_anim_timer);
	MMK_StopTimer(s_ui_data.enemy_info_timer);
	MMK_StopTimer(s_ui_data.fight_timer);
	MMK_StopTimer(s_ui_data.inst_timer);
	MMK_StopTimer(s_ui_data.map_anim_timer);
	MMK_StopTimer(s_ui_data.speed_timer);
}
LOCAL void				UpdateRectIm(POS_T unit_pos)
{
	GUI_RECT_T update_rect = {0};
	uint16		item_index = 0;
	MMI_IMAGE_ID_T image = 0;
	GUI_POINT_T	display_point = {0};
	GUI_POINT_T	start_point = MT_MAP_START_POINT;
	
	item_index	= s_game_info.map_info[s_game_info.state_info.floor][unit_pos.y][unit_pos.x];
	image		= s_mt_unit_pro[item_index].icon[0];
	display_point.x		= unit_pos.x*MT_MAP_UNIT_WIDTH + start_point.x;
	display_point.y		= unit_pos.y*MT_MAP_UNIT_HEIGHT + start_point.y;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,image,&s_ui_data.layer_map);
	update_rect.left	= display_point.x;
	update_rect.right	= update_rect.left	+ MT_MAP_UNIT_WIDTH - 1;
	update_rect.top		= display_point.y;
	update_rect.bottom	= update_rect.top	+ MT_MAP_UNIT_HEIGHT - 1;
	GUILCD_InvalidateRect(0,update_rect,0);
}
LOCAL BOOLEAN		DrawExitQuery()
{
	UILAYER_APPEND_BLT_T	layer_append = {0};
	GUI_POINT_T				dis_point = MT_SAVE_DIALOG_POINT;
	GUI_RECT_T				rect[3] = {MT_SAVE_RECT_YES,MT_SAVE_RECT_NO,MT_SAVE_RECT_CANCEL};

	layer_append.layer_level	= UILAYER_LEVEL_HIGH;
	layer_append.lcd_dev_info	= s_ui_data.layer_exit_query;
	UILAYER_AppendBltLayer(&layer_append);

	UILAYER_SetLayerPosition(&s_ui_data.layer_exit_query,dis_point.x,dis_point.y);
	GUIRES_DisplayImg(&dis_point,NULL,NULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_SAVE_QUERY,&s_ui_data.layer_exit_query);
	LCD_DrawRect(&s_ui_data.layer_exit_query,rect[s_ui_data.save_select],MMI_WHITE_COLOR);
}
LOCAL BOOLEAN		DrawEnd()
{

}
LOCAL BOOLEAN		DrawBG()
{
	GUI_POINT_T		dis_point = {0};
	
	GUIRES_DisplayImg(&dis_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_BG,&s_ui_data.layer_bg);
}

LOCAL BOOLEAN		DrawInfo()
{
	MMI_WIN_ID_T	win_id			= MMIMT_MAIN_WIN_ID;
	GUI_POINT_T		start_point		= MT_INFO_START_POINT;
	GUI_POINT_T		display_point	= {0};
	GUI_RECT_T		display_rect	= {0};
	uint16			img_width		= 0;
	uint16			img_height		= 0;
	MMI_STRING_T	display_str		= {0};
	GUISTR_STYLE_T	str_style		= {0};
	GUISTR_STATE_T	sar_state		= GUISTR_STATE_ALIGN | GUISTR_STATE_SINGLE_LINE | GUISTR_STATE_ELLIPSIS/* | GUISTR_STATE_BOLD*/;
	char			value_str[7]	= {0};
	wchar			value_wstr[7]	= {0};

	wchar			level_str[2] = {0x7ea7,0x00};
	wchar			floor_str1[8]	= {0x7b2c,0x0020,0x0020,0x0000,0x0020,0x0020,0x5c42,0x0000};
	wchar			floor_str2[9]	= {0x7b2c,0x0020,0x0020,0x0000,0x0000,0x0020,0x0020,0x5c42,0x0000};
	const uint16		name_str[3]		= {0x540d,0x79f0,0};
	const uint16		of_str[3]		= {0x653b,0x51fb,0};
	const uint16		coin_str[3]	= {0x91d1,0x5e01,0};
	const uint16		experience_str[3] = {0x7ecf,0x9a8c,0};
	const uint16		hp_str[3]		= {0x751f,0x547d,0};
	const uint16		df_str[3]		= {0x9632,0x5fa1,0};

	UILAYER_Clear(&s_ui_data.layer_info);
	UILAYER_SetLayerPosition(&s_ui_data.layer_info,0,0);
	
	//绘制英雄图片
	GUIRES_GetImgWidthHeight(&img_width,&img_height,IMAGE_MT_HERO_D0,win_id);
	display_rect.left	= (MT_INFO_HERO_IMG_WIDTH/2 -  img_width)/2;
	display_rect.right	= display_rect.left + img_width - 1;
	display_rect.top	= (MT_INFO_HERO_IMG_HEIGHT -  img_height)/2;
	display_rect.bottom = display_rect.top	+ img_height - 1;
	GUIRES_DisplayImg(PNULL,&display_rect,PNULL,win_id,IMAGE_MT_HERO_D1,&s_ui_data.layer_info);
	
	//绘制英雄等级
	display_rect.left	= MT_INFO_HERO_IMG_WIDTH/2;
	display_rect.right	= MT_INFO_HERO_IMG_WIDTH - 1;
	display_rect.top	= 0;
	display_rect.bottom	= MT_INFO_HERO_IMG_HEIGHT - 1;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_LEVEL_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	memset(value_str,0x00,sizeof(value_str));
	memset(value_wstr,0x00,sizeof(value_wstr));
	sprintf(value_str,"%d ",s_game_info.state_info.level);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = level_str;
	display_str.wstr_len = 1;
	MMIAPICOM_Wstrncat(value_wstr,display_str.wstr_ptr,display_str.wstr_len);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	//绘制楼层
	display_rect.left	= 0;
	display_rect.right	= display_rect.left		+ MT_INFO_ITEM_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ MT_INFO_HERO_MARIN + 1;
	display_rect.bottom	= display_rect.top	+ MT_INFO_ITEM_LABEL_HEIGHT - 1;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_FLOOR_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
// 	memset(value_str,0x00,sizeof(value_str));
// 	memset(value_wstr,0x00,sizeof(value_wstr));
// 	MMI_GetLabelTextByLang(TXT_MT_THE,&display_str);
// 	MMIAPICOM_Wstrncpy(value_wstr,display_str.wstr_ptr,display_str.wstr_len);
// 	sprintf(value_str," %d ",s_game_info.state_info.floor);
// 	MMIAPICOM_StrToWstr(value_str,value_wstr+display_str.wstr_len);
// 	display_str.wstr_ptr = 0;
// 	display_str.wstr_len = 0;
// 	MMI_GetLabelTextByLang(TXT_MT_FLOOR,&display_str);
// 	MMIAPICOM_Wstrncat(value_wstr,display_str.wstr_ptr,display_str.wstr_len);
// 	display_str.wstr_ptr = value_wstr;
// 	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
// 	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	if (s_game_info.state_info.floor <= 9)
	{
		floor_str1[3] = s_game_info.state_info.floor + '0';
		display_str.wstr_ptr = floor_str1;
		display_str.wstr_len = MMIAPICOM_Wstrlen(floor_str1);
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	}
	else if ((s_game_info.state_info.floor >= 10) && (s_game_info.state_info.floor <= 19))
	{
		floor_str2[3] = '1';
		floor_str2[4] = s_game_info.state_info.floor - 10 + '0';
		display_str.wstr_ptr = floor_str2;
		display_str.wstr_len = MMIAPICOM_Wstrlen(floor_str2);
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	}
	else if ((s_game_info.state_info.floor >= 20) && (s_game_info.state_info.floor <= (MT_MAP_FLOOR_NUM - 1)))
	{
		floor_str2[3] = '2';
		floor_str2[4] = s_game_info.state_info.floor - 20 + '0';
		display_str.wstr_ptr = floor_str2;
		display_str.wstr_len = MMIAPICOM_Wstrlen(floor_str2);
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	}
	
	//绘制生命
	display_rect.left	= 0;
	display_rect.right	= display_rect.left		+ MT_INFO_ITEM_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ MT_INFO_FLOOR_MARIN + 1;
	display_rect.bottom	= display_rect.top	+ MT_INFO_ITEM_LABEL_HEIGHT - 1;
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_INFO_ITEM_LABEL_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
// 	MMI_GetLabelTextByLang(TXT_MT_HEALTH,&display_str);
	display_str.wstr_ptr = hp_str;
	display_str.wstr_len = 2;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom =  display_rect.top		+ MT_INFO_ITEM_VALUE_HEIGHT;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_ITEM_VALUE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	memset(value_str,0x00,sizeof(value_str));
	memset(value_wstr,0x00,sizeof(value_wstr));
	sprintf(value_str,"%d",s_game_info.hero_info.health);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	//绘制攻击
	// 	display_rect.left	= 0;
	// 	display_rect.right	= display_rect.left		+ MT_INFO_ITEM_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom	= display_rect.top	+ MT_INFO_ITEM_LABEL_HEIGHT - 1;
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_INFO_ITEM_LABEL_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
// 	MMI_GetLabelTextByLang(TXT_MT_OFFENSIVE,&display_str);
	display_str.wstr_ptr = of_str;
	display_str.wstr_len = 2;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom =  display_rect.top		+ MT_INFO_ITEM_VALUE_HEIGHT;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_ITEM_VALUE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	sprintf(value_str,"%d",s_game_info.hero_info.offensive);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	//绘制防御
	// 	display_rect.left	= 0;
	// 	display_rect.right	= display_rect.left		+ MT_INFO_ITEM_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom	= display_rect.top	+ MT_INFO_ITEM_LABEL_HEIGHT - 1;
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_INFO_ITEM_LABEL_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
// 	MMI_GetLabelTextByLang(TXT_MT_DEFENSIVE,&display_str);
	display_str.wstr_ptr = df_str;
	display_str.wstr_len = 2;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom =  display_rect.top		+ MT_INFO_ITEM_VALUE_HEIGHT;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_ITEM_VALUE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	sprintf(value_str,"%d",s_game_info.hero_info.defensive);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	//绘制金币
	// 	display_rect.left	= 0;
	// 	display_rect.right	= display_rect.left		+ MT_INFO_ITEM_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom	= display_rect.top	+ MT_INFO_ITEM_LABEL_HEIGHT - 1;
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_INFO_ITEM_LABEL_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
// 	MMI_GetLabelTextByLang(TXT_MT_COIN,&display_str);
	display_str.wstr_ptr = coin_str;
	display_str.wstr_len = 2;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom =  display_rect.top		+ MT_INFO_ITEM_VALUE_HEIGHT;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_ITEM_VALUE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	sprintf(value_str,"%d",s_game_info.hero_info.coin);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	//绘制经验
	// 	display_rect.left	= 0;
	// 	display_rect.right	= display_rect.left		+ MT_INFO_ITEM_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom	= display_rect.top	+ MT_INFO_ITEM_LABEL_HEIGHT - 1;
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_INFO_ITEM_LABEL_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
// 	MMI_GetLabelTextByLang(TXT_MT_EXPERIENCE,&display_str);
	display_str.wstr_ptr = experience_str;
	display_str.wstr_len = 2;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom =  display_rect.top		+ MT_INFO_ITEM_VALUE_HEIGHT;
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_INFO_ITEM_VALUE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	sprintf(value_str,"%d",s_game_info.hero_info.experience);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

	//绘制钥匙
	//钥匙图片
	display_rect.left	= 0;
	display_rect.right	= display_rect.left		+ MT_MAP_UNIT_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ MT_INFO_ITEM_HEY_MARIN + 1;
	display_rect.bottom = display_rect.top		+ MT_MAP_UNIT_HEIGHT - 1;
	GUIRES_DisplayImg(PNULL,&display_rect,PNULL,win_id,IMAGE_MT_Y_KEY,&s_ui_data.layer_info);
	display_rect.left	= display_rect.right + 1;
	display_rect.right	= display_rect.left		+ MT_MAP_UNIT_WIDTH - 1;
	GUIRES_DisplayImg(PNULL,&display_rect,PNULL,win_id,IMAGE_MT_B_KEY,&s_ui_data.layer_info);
	display_rect.left	= display_rect.right + 1;
	display_rect.right	= display_rect.left		+ MT_MAP_UNIT_WIDTH - 1;
	GUIRES_DisplayImg(PNULL,&display_rect,PNULL,win_id,IMAGE_MT_R_KEY,&s_ui_data.layer_info);
	
	
	//钥匙数量
	display_rect.left	= 0;
	display_rect.right	= display_rect.left		+ MT_MAP_UNIT_WIDTH - 1;
	display_rect.top	= display_rect.bottom	+ 1;
	display_rect.bottom	= display_rect.top		+ MT_MAP_UNIT_HEIGHT - 1;
	sprintf(value_str,"%d",s_game_info.state_info.yellow_key_num);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.left	= display_rect.right + 1;
	display_rect.right	= display_rect.left		+ MT_MAP_UNIT_WIDTH - 1;
	sprintf(value_str,"%d",s_game_info.state_info.blue_key_num);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	display_rect.left	= display_rect.right + 1;
	display_rect.right	= display_rect.left		+ MT_MAP_UNIT_WIDTH - 1;
	sprintf(value_str,"%d",s_game_info.state_info.red_key_num);
	MMIAPICOM_StrToWstr(value_str,value_wstr);
	display_str.wstr_ptr = value_wstr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	
	UILAYER_SetLayerPosition(&s_ui_data.layer_info,start_point.x,start_point.y);
}

LOCAL BOOLEAN		DrawMap()
{
	GUI_POINT_T		start_point = MT_MAP_START_POINT;
	uint8			row			= 0;
	uint8			column		= 0;
	uint16			item_index	= 0;
	MMI_IMAGE_ID_T	image		= 0;
	GUI_RECT_T		display_rect	= {0};
	GUI_POINT_T		display_point	= {0};
	UILAYER_SetLayerPosition(&s_ui_data.layer_map,0,0);
	for (row=0; row<MT_MAP_ROW_NUM; row++)
	{
		for (column=0; column<MT_MAP_COLUMN_NUM; column++)
		{
			item_index	= s_game_info.map_info[s_game_info.state_info.floor][row][column];
			image		= s_mt_unit_pro[item_index].icon[s_frame_mark];
			if ( (image != IMAGE_NULL) && 
				!((item_index >= MAP_UNIT_UNKEY_DOOR) && (item_index <= MAP_UNIT_R_DOOR) && s_ui_data.is_door_running)
				)
			{
				// 				display_rect.left	= column*MT_MAP_UNIT_WIDTH;
				// 				display_rect.right	= display_rect.left + MT_MAP_UNIT_WIDTH - 1;
				// 				display_rect.top	= row*MT_MAP_UNIT_HEIGHT;
				// 				display_rect.bottom = display_rect.top + MT_MAP_UNIT_HEIGHT - 1;
				display_point.x		= column*MT_MAP_UNIT_WIDTH;
				display_point.y		= row*MT_MAP_UNIT_HEIGHT;
				GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,image,&s_ui_data.layer_map);
			}
		}
	}
	
	display_point.x		= s_game_info.state_info.hero_pos.x*MT_MAP_UNIT_WIDTH;
	display_point.y		= s_game_info.state_info.hero_pos.y*MT_MAP_UNIT_HEIGHT;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_anim_hero[s_ui_data.move_direction][1],&s_ui_data.layer_map);
	
	UILAYER_SetLayerPosition(&s_ui_data.layer_map,start_point.x,start_point.y);
	
}

LOCAL BOOLEAN		DrawAll()
{
	DrawBG();
	DrawInfo();
	DrawMap();
	
}

LOCAL BOOLEAN		DrawMenu()
{
	GUI_POINT_T dis_point = {0};
	const GUI_RECT_T select_rect[5] = {MT_START_MENU_RECT_START,MT_START_MENU_RECT_READ,
										MT_START_MENU_RECT_HELP,MT_START_MENU_RECT_ABOUT,
										MT_START_MENU_RECT_EXIT};
	
	GUIRES_DisplayImg(&dis_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_START_MENU,&s_ui_data.layer_bg);
	LCD_DrawRect(&s_ui_data.layer_bg,select_rect[s_ui_data.menu_select],MMI_WHITE_COLOR);
}

LOCAL BOOLEAN		DrawVoice()
{
	GUI_POINT_T dis_point = {0};
	const GUI_RECT_T select_rect[2] = {MT_START_VOICE_RECT_YEW,MT_START_VOICE_RECT_NO};
	
	GUIRES_DisplayImg(&dis_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_START_VOICE,&s_ui_data.layer_bg);
	LCD_DrawRect(&s_ui_data.layer_bg,select_rect[s_ui_data.voice_select],MMI_WHITE_COLOR);
	
}

LOCAL void DisplayInstAnim()
{
	uint16 img_width = 0;
	uint16 img_height = 0;
	GUI_POINT_T	dis_point = {0};
	GUI_RECT_T	dis_rect = {0};
	GUI_RECT_T	img_rect = {0};
	GUI_RECT_T	scr_rect = {0,0,319,239};

	GUIRES_GetImgWidthHeight(&img_width,&img_height,IMAGE_MT_INST,MMIMT_MAIN_WIN_ID);

	dis_rect.left = 0;
	dis_rect.right = 319;
	dis_rect.top = MAX(MIN(s_ui_data.inst_y,239),0);
	dis_rect.bottom = 239;



	img_rect.left = 0;
	img_rect.right = 319;
	img_rect.top = MAX(0,-s_ui_data.inst_y);
	img_rect.bottom = img_rect.top + MIN((239 - s_ui_data.inst_y),239);
	LCD_FillRect(&s_ui_data.layer_bg,scr_rect,MMI_BLACK_COLOR);
	GUIRES_DisplayImg(NULL,&dis_rect,&img_rect,MMIMT_MAIN_WIN_ID,IMAGE_MT_INST,&s_ui_data.layer_bg);
	GUIRES_DisplayImg(&dis_point,NULL,NULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_INST_COVER,&s_ui_data.layer_bg);

	if (s_ui_data.inst_y > 160 - img_height)
	{
		s_ui_data.inst_y -= 2;
	}
}

LOCAL void DisplayEnd()
{

}

LOCAL void DisplayTip(char* str_ptr)
{
	UILAYER_APPEND_BLT_T	layer_append = {0};
	GUI_POINT_T				fix_point	= MT_TIP_START_POINT;
	GUI_POINT_T				display_point = {0};
	MMI_STRING_T			display_str = {0};
	uint16					gb_len = 0;
	GUISTR_STYLE_T			str_style		= {0};
	GUISTR_STATE_T			sar_state		= GUISTR_STATE_ALIGN | GUISTR_STATE_SINGLE_LINE | GUISTR_STATE_ELLIPSIS/* | GUISTR_STATE_BOLD*/;
	GUI_RECT_T				display_rect	= {0};
	GUI_RECT_T				update_rect		= {0};

	MMK_StopTimer(s_ui_data.map_anim_timer);
	layer_append.layer_level = UILAYER_LEVEL_HIGH;
	layer_append.lcd_dev_info = s_ui_data.layer_tip;
	UILAYER_AppendBltLayer(&layer_append);
	UILAYER_Clear(&s_ui_data.layer_tip);
	UILAYER_SetLayerPosition(&s_ui_data.layer_tip,0,0);

	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_TIP_BG,&s_ui_data.layer_tip);
// 	display_str.wstr_len = _mbslen(str_ptr);
	display_str.wstr_len = 2*strlen(str_ptr);
	display_str.wstr_ptr = SCI_ALLOC_APP(display_str.wstr_len*2 + 2);
	memset(display_str.wstr_ptr,0x00,display_str.wstr_len*2 + 2);
	GUI_GB2UCS(display_str.wstr_ptr,str_ptr,strlen(str_ptr));
	display_str.wstr_len = MMIAPICOM_Wstrlen(display_str.wstr_ptr);
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_TIP_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	display_rect.left	= 0;
	display_rect.right	= display_rect.left + MT_TIP_WIDTH - 1;
	display_rect.top	= 0;
	display_rect.bottom	= display_rect.top + MT_TIP_HEIGHT - 1;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_tip,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

	display_rect.left	= fix_point.x;
	display_rect.right	= display_rect.left + MT_TIP_WIDTH - 1;
	display_rect.top	= fix_point.y;
	display_rect.bottom	= fix_point.y + 8 + MT_TIP_HEIGHT - 1;

// 	UILAYER_WeakLayerAlpha(&s_ui_data.layer_tip,0);
	display_point = fix_point;
	UILAYER_SetLayerPosition(&s_ui_data.layer_tip,display_point.x,display_point.y);
// 	MMITHEME_StoreUpdateRect(&s_ui_data.layer_tip,display_rect);
// 	MMITHEME_UpdateRect();
	GUILCD_InvalidateRect(0,display_rect,0);
	SCI_SLEEP(100);

// 	UILAYER_WeakLayerAlpha(&s_ui_data.layer_tip,10);
	display_point.y += 3;
	UILAYER_SetLayerPosition(&s_ui_data.layer_tip,display_point.x,display_point.y);
// 	MMITHEME_StoreUpdateRect(&s_ui_data.layer_tip,display_rect);
// 	MMITHEME_UpdateRect();
	GUILCD_InvalidateRect(0,display_rect,0);
	SCI_SLEEP(100);

// 	UILAYER_WeakLayerAlpha(&s_ui_data.layer_tip,20);
	display_point.y	+= 5;
	UILAYER_SetLayerPosition(&s_ui_data.layer_tip,display_point.x,display_point.y);
// 	MMITHEME_StoreUpdateRect(&s_ui_data.layer_tip,display_rect);
// 	MMITHEME_UpdateRect();
	GUILCD_InvalidateRect(0,display_rect,0);
	SCI_SLEEP(450);

// 	UILAYER_WeakLayerAlpha(&s_ui_data.layer_tip,120);
	display_point.y -= 5;
	UILAYER_SetLayerPosition(&s_ui_data.layer_tip,display_point.x,display_point.y);
// 	MMITHEME_StoreUpdateRect(&s_ui_data.layer_tip,display_rect);
// 	MMITHEME_UpdateRect();
	GUILCD_InvalidateRect(0,display_rect,0);
	SCI_SLEEP(100);

// 	UILAYER_WeakLayerAlpha(&s_ui_data.layer_tip,50);
	display_point.y -= 3;
	UILAYER_SetLayerPosition(&s_ui_data.layer_tip,display_point.x,display_point.y);
// 	MMITHEME_StoreUpdateRect(&s_ui_data.layer_tip,display_rect);
// 	MMITHEME_UpdateRect();
	GUILCD_InvalidateRect(0,display_rect,0);
	SCI_SLEEP(100);

	UILAYER_RemoveBltLayer(&s_ui_data.layer_tip);
	SCI_FREE(display_str.wstr_ptr);
	s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
}

LOCAL void DisplayEnemyInfo()
{
	uint8		i = 0;
	GUI_POINT_T			layer_point	= MT_MAP_START_POINT;
	GUI_POINT_T			display_point = {0};
	const GUI_POINT_T	icon2_point		= {7,8};
	MMI_IMAGE_ID_T		image_id	= IMAGE_NULL;
	const uint8			item_marin		= 26;
	static	uint8		frame			= 0;


	for (i=0; i<s_ui_data.total_num; i++)
	{
		display_point.x = layer_point.x + icon2_point.x;
		display_point.y = layer_point.y + icon2_point.y + i*item_marin;
		image_id = s_mt_unit_pro[s_ui_data.display_unit_id[i]].icon[frame];

		if (image_id != IMAGE_NULL)
			GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,image_id,&s_ui_data.layer_enemy_info);
	}
	frame = (++frame)%2;

}
LOCAL void SetEnemyInfo()
{
	uint8			i					= 0;
	BOOLEAN			is_exist			= FALSE;
	uint8			total_num			= 0;
	uint8			row					= 0;
	uint8			column				= 0;
	MT_UNIT_E		temp_unit_id		= 0;
	MMI_IMAGE_ID_T	image_id			= IMAGE_NULL;

	const GUI_POINT_T icon1_point		= {6,7};
	const GUI_POINT_T icon2_point		= {7,8};
	const GUI_RECT_T  name0_rect		= {30,7,52,17};
	const GUI_RECT_T  name1_rect		= {53,7,101,17};
	const GUI_RECT_T  of0_rect			= {102,7,124,17};
	const GUI_RECT_T  of1_rect			= {125,7,149,17};
	const GUI_RECT_T  coin0_rect		= {150,7,179,17};
	const GUI_RECT_T  coin1_rect		= {180,7,219,17};

	const GUI_RECT_T  hp0_rect			= {30,18,52,30};
	const GUI_RECT_T  hp1_rect			= {53,18,101,30};
	const GUI_RECT_T  df0_rect			= {102,18,124,30};
	const GUI_RECT_T  df1_rect			= {125,18,149,30};
	const GUI_RECT_T  lost0_rect		= {150,18,179,30};
	const GUI_RECT_T  lost1_rect		= {180,18,219,30};
	const uint8		  item_marin		= 26;
	const uint16		name_str[3]		= {0x540d,0x79f0,0};
	const uint16		of_str[3]		= {0x653b,0x51fb,0};
	const uint16		coin_str[4]	= {0x91d1,0x00b7,0x7ecf,0};
	const uint16		hp_str[3]		= {0x751f,0x547d,0};
	const uint16		df_str[3]		= {0x9632,0x5fa1,0};
	const uint16		lost_str[3]		= {0x635f,0x5931,0};
	const uint16		jiangefu[2]		= {0x00b7,0};
	GUI_POINT_T			display_point = {0};
	GUI_POINT_T			layer_point	= MT_MAP_START_POINT;
	GUI_RECT_T			display_rect  = {0};
	MMI_STRING_T		display_str   = {0};
	GUISTR_STYLE_T		str_style		= {0};
	GUISTR_STATE_T		sar_state		= GUISTR_STATE_ALIGN | GUISTR_STATE_SINGLE_LINE | GUISTR_STATE_ELLIPSIS/* | GUISTR_STATE_BOLD*/;
	char				temp_str[10]	= {0};
	char				temp_str1[10]	= {0};
	wchar				temp_wstr[10] = {0};
	wchar				temp_wstr1[10] = {0};
	UILAYER_APPEND_BLT_T layer_append = {0};
	
	layer_append.layer_level = UILAYER_LEVEL_NORMAL;
	layer_append.lcd_dev_info = s_ui_data.layer_enemy_info;
	UILAYER_AppendBltLayer(&layer_append);
	UILAYER_SetLayerPosition(&s_ui_data.layer_enemy_info,0,0);

	memset(s_ui_data.display_unit_id,0x00,sizeof(s_ui_data.display_unit_id));
	//获取需要显示的数组
	for (row=0; row<MT_MAP_ROW_NUM; row++)
	{
		for (column=0; column<MT_MAP_COLUMN_NUM; column++)
		{
			temp_unit_id = s_game_info.map_info[s_game_info.state_info.floor][row][column];
			if ((total_num <=7)&&(temp_unit_id > MAP_UNIT_HERO)&&(temp_unit_id <= MAP_UNIT_MASTER2))
			{
				is_exist = FALSE;
				for (i=0; i<8; i++)
				{
					if (s_ui_data.display_unit_id[i] == temp_unit_id)
					{
						is_exist = TRUE;
						break;
					}
				}
				if (!is_exist)
				{
					s_ui_data.display_unit_id[total_num] = temp_unit_id;
					total_num++;
				}
			}
		}
	}

	//开始显示
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_EF_BG,&s_ui_data.layer_enemy_info);
	s_ui_data.total_num = total_num;
	for (i=0; i<total_num; i++)
	{
		//画边框
		display_point.x = icon1_point.x;
		display_point.y = icon1_point.y + i*item_marin;
		GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_EF_ICON_FRAME,&s_ui_data.layer_enemy_info);

		//画图片
		display_point.x += 1;
		display_point.y += 1;
		image_id = s_mt_unit_pro[s_ui_data.display_unit_id[i]].icon[0];
		if (image_id != IMAGE_NULL)
			GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,image_id,&s_ui_data.layer_enemy_info);

		//画名称标签
		display_rect = name0_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		display_str.wstr_ptr = name_str;
		display_str.wstr_len = 2;
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画怪物名称
		display_rect = name1_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		memset(temp_wstr,0x00,sizeof(temp_wstr));
		GUI_GB2UCS(temp_wstr,s_mt_unit_pro[s_ui_data.display_unit_id[i]].name_str,strlen(s_mt_unit_pro[s_ui_data.display_unit_id[i]].name_str));
		display_str.wstr_ptr = temp_wstr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(temp_wstr);
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画攻击标签
		display_rect = of0_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		display_str.wstr_ptr = of_str;
		display_str.wstr_len = 2;
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画攻击数值
		display_rect = of1_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		memset(temp_wstr,0x00,sizeof(temp_wstr));
		sprintf(temp_str,"%d",s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.offensive);
		MMIAPICOM_StrToWstr(temp_str,temp_wstr);
		display_str.wstr_ptr = temp_wstr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(temp_wstr);
		str_style.align		= ALIGN_RIGHT;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画金币和经验标签
		display_rect = coin0_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		display_str.wstr_ptr = coin_str;
		display_str.wstr_len = 3;
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画金币和经验值
		display_rect = coin1_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		memset(temp_wstr,0x00,sizeof(temp_wstr));
		memset(temp_str,0x00,sizeof(temp_str));
		sprintf(temp_str,"%d",s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.coin);
		MMIAPICOM_StrToWstr(temp_str,temp_wstr);
		MMIAPICOM_Wstrcat(temp_wstr,jiangefu);
		memset(temp_str1,0x00,sizeof(temp_str1));
		memset(temp_wstr1,0x00,sizeof(temp_wstr1));
		sprintf(temp_str1,"%d",s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.experience);
		MMIAPICOM_StrToWstr(temp_str1,temp_wstr1);
		MMIAPICOM_Wstrcat(temp_wstr,temp_wstr1);
		display_str.wstr_ptr = temp_wstr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(temp_wstr);
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画生命标签
		display_rect = hp0_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		display_str.wstr_ptr = hp_str;
		display_str.wstr_len = 2;
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画生命值
		display_rect = hp1_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		memset(temp_str,0x00,sizeof(temp_str));
		memset(temp_wstr,0x00,sizeof(temp_wstr));
		sprintf(temp_str,"%d",s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.health);
		MMIAPICOM_StrToWstr(temp_str,temp_wstr);
		display_str.wstr_ptr = temp_wstr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(temp_wstr);
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画防御标签
		display_rect = df0_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		display_str.wstr_ptr = df_str;
		display_str.wstr_len = 2;
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
		
		//画防御数值
		display_rect = df1_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		memset(temp_str,0x00,sizeof(temp_str));
		memset(temp_wstr,0x00,sizeof(temp_wstr));
		sprintf(temp_str,"%d",s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.defensive);
		MMIAPICOM_StrToWstr(temp_str,temp_wstr);
		display_str.wstr_ptr = temp_wstr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(temp_wstr);
		str_style.align		= ALIGN_RIGHT;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画损失标签
		display_rect = lost0_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		display_str.wstr_ptr = lost_str;
		display_str.wstr_len = 2;
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

		//画损失数值
		{

			int16	hero_damage		= s_game_info.hero_info.offensive - s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.defensive;
			int16	enemy_damage	= s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.offensive - s_game_info.hero_info.defensive;
			int32	hero_hp			= s_game_info.hero_info.health;
			int32	enemy_hp		= s_mt_unit_pro[s_ui_data.display_unit_id[i]].life.health;
			uint16	hero_dead_times	= 0;	
			uint16	enemy_dead_times= 0;
			BOOLEAN	is_able_fight	= FALSE;
			
			memset(temp_str,0x00,sizeof(temp_str));
			if (hero_damage > 0)
			{
				if (enemy_damage > 0)
				{
					hero_dead_times = hero_hp/enemy_damage;
					if (hero_hp%enemy_damage != 0)
						hero_dead_times++;
					
					enemy_dead_times = enemy_hp/hero_damage;
					if (enemy_hp/hero_damage != 0)
						enemy_dead_times++;
					
// 					if (enemy_dead_times <= hero_dead_times)
// 					{
						if ((enemy_dead_times == 1)||(enemy_dead_times == 0))
							sprintf(temp_str,"%d",0);
						else
							sprintf(temp_str,"%d",(enemy_dead_times-1)*enemy_damage);
// 					}
// 					else
// 						sprintf(temp_str,"%s","???");
				}
				else
					sprintf(temp_str,"%d",0);
			}
			else
				sprintf(temp_str,"%s","???");
		}
		MMIAPICOM_StrToWstr(temp_str,temp_wstr);
		display_str.wstr_ptr = temp_wstr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(temp_wstr);
		str_style.align		= ALIGN_HVMIDDLE;
		str_style.font		= MT_ENEMY_INFO_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		display_rect = lost1_rect;
		display_rect.top += i*item_marin;
		display_rect.bottom += i*item_marin;
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_enemy_info,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
	}

	UILAYER_SetLayerPosition(&s_ui_data.layer_enemy_info,layer_point.x,layer_point.y);

}
LOCAL void				DisplayToolTip(MT_UNIT_E unit_id)
{
	GUI_POINT_T		display_point = MT_TOOLTIP_START_POINT;
	MMI_IMAGE_ID_T	image		  = s_mt_unit_pro[unit_id].icon_fight;
	UILAYER_APPEND_BLT_T layer_append = {0};

	layer_append.layer_level = UILAYER_LEVEL_HIGH;
	layer_append.lcd_dev_info = s_ui_data.layer_tool_tip;
	UILAYER_AppendBltLayer(&layer_append);
	UILAYER_SetLayerPosition(&s_ui_data.layer_tool_tip,display_point.x,display_point.y);
	UILAYER_Clear(&s_ui_data.layer_tool_tip);

	if (image != IMAGE_NULL)
		GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,image,&s_ui_data.layer_tool_tip);

	switch (unit_id)
	{
	case MAP_UNIT_TOOL_CROSS:
			s_game_info.state_info.is_get_cross = TRUE;
		break;
	case MAP_UNIT_TOOL_JUMP:
			s_game_info.state_info.is_get_jump = TRUE;
		break;
	case MAP_UNIT_TOOL_LOOK:
			s_game_info.state_info.is_get_look = TRUE;
		break;
	case MAP_UNIT_HAMMER_18FLOOR:
			s_game_info.state_info.is_get_hammer18 = TRUE;
			break;
	case MAP_UNIT_TOOL_WARTER:
			s_game_info.hero_info.health *= 2;
			break;
	default:
		SCI_ASSERT(FALSE);
		break;
	}
}
LOCAL void				DisplayDialog(MT_UNIT_E dialog_id)
{
	uint16					index			= dialog_id - MAP_UNIT_NPC_0_1;
	static MMI_IMAGE_ID_T	bg_anim[2]		= {IMAGE_MT_DIALOG_BG0,IMAGE_MT_DIALOG_BG2};
	static uint8			frame_mark		= 0;
	GUI_POINT_T				point[2]		= {0};
	GUI_POINT_T				start_point		= {0};
	GUI_POINT_T				display_point	= {0};
	GUI_POINT_T				head_point		= MT_DIALOG_HEAD_POINT;
	GUI_RECT_T				title_rect		= MT_DIALOG_TITLE_RECT;
	GUI_RECT_T				content_rect	= MT_DIALOG_CONTENT_RECT;
	GUI_RECT_T				display_rect	= {0};
	SINGLE_DIALOG_T*		current_dialog_ptr	= s_dialog[index].dialog_ptr + s_ui_data.talk_index;
	const MT_UNIT_E			first_unit			= s_dialog[index].dialog_ptr->dialog_host;
	GUISTR_STYLE_T			str_style		= {0};
	GUISTR_STATE_T			sar_state		= GUISTR_STATE_ALIGN | GUISTR_STATE_WORDBREAK  /*| GUISTR_STATE_BOLD*/;
	MMI_STRING_T			display_str		= {0};
	uint16					content_str_len = 0;
	wchar*					content_str_ptr = PNULL;
	UILAYER_APPEND_BLT_T	layer_append = {0};
	wchar					name_str[10] = {0};
	uint16					name_len = 0;

	layer_append.layer_level = UILAYER_LEVEL_NORMAL;
	layer_append.lcd_dev_info = s_ui_data.layer_dialog;
	UILAYER_AppendBltLayer(&layer_append);

	point[0] = s_dialog[index].dialog_pos[0];
	point[1] = s_dialog[index].dialog_pos[1];

	if (current_dialog_ptr->dialog_host == first_unit)
		start_point = point[0];
	else
		start_point = point[1];

	//画背景
	display_point = start_point;
	UILAYER_SetLayerPosition(&s_ui_data.layer_dialog,display_point.x,display_point.y);
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,bg_anim[frame_mark%2],&s_ui_data.layer_dialog);

	//画icon
	display_point.x += head_point.x;
	display_point.y += head_point.y;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_mt_unit_pro[current_dialog_ptr->dialog_host].icon[frame_mark%2],&s_ui_data.layer_dialog);

	//画title
	display_rect.left	= title_rect.left	+ start_point.x;
	display_rect.right	= title_rect.right	+ start_point.x;
	display_rect.top	= title_rect.top	+ start_point.y;
	display_rect.bottom = title_rect.bottom	+ start_point.y;
	name_len = strlen(s_mt_unit_pro[current_dialog_ptr->dialog_host].name_str);
	GUI_GB2UCS(name_str,s_mt_unit_pro[current_dialog_ptr->dialog_host].name_str,name_len);
	display_str.wstr_ptr = name_str;
	display_str.wstr_len = MMIAPICOM_Wstrlen(name_str);
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_DIALOG_TITLE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_dialog,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

	//画content
	display_rect.left	= content_rect.left	+ start_point.x;
	display_rect.right	= content_rect.right	+ start_point.x;
	display_rect.top	= content_rect.top	+ start_point.y;
	display_rect.bottom = content_rect.bottom	+ start_point.y;
// 	content_str_len		= _mbslen(current_dialog_ptr->dialog_str);
	content_str_len		= 2*strlen(current_dialog_ptr->dialog_str);
	content_str_ptr		= SCI_ALLOC_APP(content_str_len*2 + 2);
	memset(content_str_ptr,0x00,content_str_len*2 + 2);
	GUI_GB2UCS(content_str_ptr,current_dialog_ptr->dialog_str,strlen(current_dialog_ptr->dialog_str));
	display_str.wstr_ptr = content_str_ptr;
// 	display_str.wstr_len = content_str_len;
	display_str.wstr_len = MMIAPICOM_Wstrlen(content_str_ptr);
	str_style.align		= ALIGN_LEFT;
	str_style.font		= MT_DIALOG_CONTENT_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_dialog,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

	frame_mark = ++frame_mark%2;
	SCI_FREE(content_str_ptr);

}
LOCAL void				DisplayStore(uint8 select_item)
{
	uint8			i			= 0;
	GUI_POINT_T		start_point = {0};
	GUI_POINT_T		display_point = {0};
	GUI_RECT_T		tip_rect	= MT_STORE_TIP_RECT;
	GUI_POINT_T		opion_point= MT_STORE_OPTION_START_POINT;
	GUI_RECT_T		display_rect= {0};
	uint16			tip_len		= 29;
	STORE_T*		store_ptr = &s_store[s_ui_data.store_id - MAP_UNIT_STORE3_0];
	STORE_OPTION*	store_opt_ptr = PNULL;
	uint16			option_str_len = 0;
	uint16*			wstr_ptr	= PNULL;
	MMI_STRING_T	display_str = {0};
	GUISTR_STYLE_T	str_style		= {0};
	GUISTR_STATE_T	sar_state		= GUISTR_STATE_ALIGN | GUISTR_STATE_WORDBREAK  /*| GUISTR_STATE_BOLD*/;
	UILAYER_APPEND_BLT_T	layer_append = {0};

	layer_append.layer_level = UILAYER_LEVEL_NORMAL;
	layer_append.lcd_dev_info = s_ui_data.layer_store;
	UILAYER_AppendBltLayer(&layer_append);

	store_opt_ptr = &store_ptr->store_option;

	start_point = store_ptr->start_point;
	UILAYER_SetLayerPosition(&s_ui_data.layer_store,start_point.x,start_point.y);

	//画背景
	display_point = start_point;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_STORE_INFO_BG,&s_ui_data.layer_store);

	//画头像
	display_point.x += 4;
	display_point.y += 7;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,store_ptr->head_img,&s_ui_data.layer_store);

	//画商店的tip
	tip_rect.left += start_point.x;
	tip_rect.right += start_point.x;
	tip_rect.top += start_point.y;
	tip_rect.bottom += start_point.y;
// 	tip_len = _mbslen(tip);
	tip_len = 2*strlen((*store_opt_ptr)[0]);
	SCI_TRACE_LOW("[magic tower len0: %d",tip_len);
	wstr_ptr = SCI_ALLOC_APP((tip_len+1)*2);
	memset(wstr_ptr,0x00,(tip_len+1)*2);
	GUI_GB2UCS(wstr_ptr,(*store_opt_ptr)[0],strlen((*store_opt_ptr)[0]));
	display_str.wstr_ptr = wstr_ptr;
	display_str.wstr_len = MMIAPICOM_Wstrlen(wstr_ptr);
	str_style.align		= ALIGN_TOP;
	str_style.font		= MT_STORE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_store,&tip_rect,&tip_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);


	//画商店的选项
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_STORE_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	display_rect.left	= start_point.x + opion_point.x;
	display_rect.right	= display_rect.left + MT_STORE_WIDTH - 1;
	sar_state			= GUISTR_STATE_ALIGN | GUISTR_STATE_SINGLE_LINE | GUISTR_STATE_ELLIPSIS;
	for (i=1; i<5; i++)
	{
		display_rect.top	= start_point.y + opion_point.y + (i-1)*MT_STORE_OPTION_MARIN;
		display_rect.bottom = display_rect.top + MT_STORE_OPTION_MARIN - 1;
		str_style.font		= MT_STORE_FONT;
		str_style.font_color= MMI_WHITE_COLOR;
		if (select_item+1 == i)
		{
			str_style.font		= MT_STORE_FONT + 2;
			str_style.font_color= MT_STORE_HILIGHT_COLOR;
		}
		memset(wstr_ptr,0x00,tip_len*2 + 2);
// 		option_str_len = _mbslen(option_str[i]);
		option_str_len = strlen((*store_opt_ptr)[i]);
		GUI_GB2UCS(wstr_ptr,(*store_opt_ptr)[i],strlen((*store_opt_ptr)[i]));
		display_str.wstr_ptr = wstr_ptr;
		display_str.wstr_len = MMIAPICOM_Wstrlen(wstr_ptr);
		GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_store,&display_rect,&display_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

	}
	SCI_FREE(wstr_ptr);
	
}

LOCAL void				HandleFightEnd()
{
	MT_UNIT_E enemy			= s_ui_data.cur_enemy;

	MMK_StopTimer(s_ui_data.fight_timer);
	UILAYER_RemoveBltLayer(&s_ui_data.layer_fight);
	s_game_info.hero_info.health = s_ui_data.end_life.health;
	s_game_info.hero_info.coin	 = s_ui_data.end_life.coin;
	s_game_info.hero_info.experience = s_ui_data.end_life.experience;

	//待fight场景结束，重新恢复map定时器，此时让frame=0，这样，首先画第0桢，
	s_frame_mark = 0;
// 	s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
	
	s_ui_data.is_new_fight = FALSE;
	s_ui_data.scene = MAIN_SCENE;
	DrawInfo();

	if (enemy == MAP_UNIT_MASTER)
	{
		BOOLEAN	MoveUp();
		s_game_info.map_info[19][6][5] = MAP_UNIT_NPC_19_2;
		MoveUp();
	}
	else if (enemy == MAP_UNIT_MASTER2)
	{
		BOOLEAN	MoveUp();
		s_game_info.map_info[21][1][5] = MAP_UNIT_NPC_21_1;
		MoveUp();
	}

}

LOCAL void				DisplayFight()
{
	MT_UNIT_E		enemy = s_ui_data.cur_enemy;
	UILAYER_APPEND_BLT_T	layer_append = {0};
// 	int32 hp1 = s_mt_unit_pro[enemy].life.health;
// 	int16 of1 = s_mt_unit_pro[enemy].life.offensive;
// 	int16 df1 = s_mt_unit_pro[enemy].life.defensive;
// 	int32 hp2 = s_game_info.hero_info.health;
// 	int16 of2 = s_game_info.hero_info.offensive;
// 	int16 df2 =	s_game_info.hero_info.defensive;
	static int32	value_array[6]	= {0};
	GUI_RECT_T		client_rect		= {0};
	GUI_POINT_T		display_point	= {0};
	GUI_POINT_T		enemy_point		= MT_FIGHT_ENEMY_POINT;
	GUI_POINT_T		hero_point		= MT_FIGHT_HERO_POINT;
	GUI_POINT_T		start_point		= MT_FIGHT_START_POINT;
	GUI_POINT_T		hp1_point		= MT_FIGHT_VALUE_POINT_HP1;
	GUI_POINT_T		of1_point		= MT_FIGHT_VALUE_POINT_OF1;
	GUI_POINT_T		df1_point		= MT_FIGHT_VALUE_POINT_DF1;
	GUI_POINT_T		hp2_point		= MT_FIGHT_VALUE_POINT_HP2;
	GUI_POINT_T		of2_point		= MT_FIGHT_VALUE_POINT_OF2;
	GUI_POINT_T		df2_point		= MT_FIGHT_VALUE_POINT_DF2;
	GUI_POINT_T		point_array[6]	= {MT_FIGHT_VALUE_POINT_HP1,MT_FIGHT_VALUE_POINT_OF1,MT_FIGHT_VALUE_POINT_DF1,MT_FIGHT_VALUE_POINT_HP2,MT_FIGHT_VALUE_POINT_OF2,MT_FIGHT_VALUE_POINT_DF2};
	uint8			i				= 0;
	GUI_RECT_T		img_rect		= {0};
	GUI_RECT_T		txt_rect		= {0};
	MMI_STRING_T	display_str		= {0};
	char			value_str[10]	= {0};
	wchar			value_wstr[10]	= {0};
	GUISTR_STYLE_T	str_style		= {0};
	GUISTR_STATE_T	sar_state		= GUISTR_STATE_ALIGN | GUISTR_STATE_SINGLE_LINE | GUISTR_STATE_ELLIPSIS/* | GUISTR_STATE_BOLD*/;

	if (s_ui_data.is_new_fight)
	{
		value_array[0] = s_mt_unit_pro[enemy].life.health;
		value_array[1] = s_mt_unit_pro[enemy].life.offensive;
		value_array[2] = s_mt_unit_pro[enemy].life.defensive;
		value_array[3] = s_game_info.hero_info.health;
		value_array[4] = s_game_info.hero_info.offensive;
		value_array[5] = s_game_info.hero_info.defensive;

// 		s_ui_data.cur_enemy_hp = value_array[0];
// 		s_ui_data.cur_hero_hp  = value_array[3];
		s_ui_data.is_new_fight = FALSE;
	}

	client_rect.left				= start_point.x;
	client_rect.right				= client_rect.left	+ MT_FIGHT_WIDTH - 1;
	client_rect.top					= start_point.y;
	client_rect.bottom				= client_rect.top	+ MT_FIGHT_HEIGHT - 1;
	layer_append.layer_level		= UILAYER_LEVEL_NORMAL;
	layer_append.lcd_dev_info		= s_ui_data.layer_fight;
	UILAYER_AppendBltLayer(&layer_append);
	UILAYER_SetLayerPosition(&s_ui_data.layer_fight,start_point.x,start_point.y);
	GUIRES_DisplayImg(&start_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,IMAGE_MT_FIGHT_BG,&s_ui_data.layer_fight);
	enemy_point.x		+= start_point.x;
	enemy_point.y		+= start_point.y;
	GUIRES_DisplayImg(&enemy_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_mt_unit_pro[enemy].icon_fight,&s_ui_data.layer_fight);
	hero_point.x		+= start_point.x;
	hero_point.y		+= start_point.y;
	GUIRES_DisplayImg(&hero_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_mt_unit_pro[MAP_UNIT_HERO].icon_fight,&s_ui_data.layer_fight);
	
	str_style.align		= ALIGN_HVMIDDLE;
	str_style.font		= MT_FIGHT_FONT;
	str_style.font_color= MMI_WHITE_COLOR;
	display_str.wstr_ptr= value_wstr;
	
// 	//hp1
// 	img_rect.left	= hp1_point.x;
// 	img_rect.right	= img_rect.left	+ MT_FIGHT_VALUE_WIDTH - 1;
// 	img_rect.top	= hp1_point.y;
// 	img_rect.bottom = img_rect.top	+ MT_FIGHT_VALUE_HEIGHT - 1;
// 
// 	txt_rect.left	= hp1_point.x	+ start_point.x;
// 	txt_rect.right	= txt_rect.left	+ MT_FIGHT_VALUE_WIDTH - 1;
// 	txt_rect.top	= hp1_point.y	+ start_point.y;
// 	txt_rect.bottom = txt_rect.top	+ MT_FIGHT_VALUE_HEIGHT - 1;
// 	GUIRES_DisplayImg(PNULL,&txt_rect,&img_rect,MMIMT_MAIN_WIN_ID,IMAGE_MT_FIGHT_BG,&s_ui_data.layer_fight);
// 	memset(value_str,0x00,sizeof(value_str));
// 	memset(value_wstr,0x00,sizeof(value_wstr));
// 	sprintf(value_str,"%d ",hp1);
// 	MMIAPICOM_StrToWstr(value_str,value_wstr);
// 	display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
// 	GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_fight,&txt_rect,&txt_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);

// 	while (1)
// 	{
		for (i=0; i<6; i++)
		{
			img_rect.left	= point_array[i].x;
			img_rect.right	= img_rect.left	+ MT_FIGHT_VALUE_WIDTH - 1;
			img_rect.top	= point_array[i].y;
			img_rect.bottom = img_rect.top	+ MT_FIGHT_VALUE_HEIGHT - 1;
			
			txt_rect.left	= point_array[i].x	+ start_point.x;
			txt_rect.right	= txt_rect.left	+ MT_FIGHT_VALUE_WIDTH - 1;
			txt_rect.top	= point_array[i].y	+ start_point.y;
			txt_rect.bottom = txt_rect.top	+ MT_FIGHT_VALUE_HEIGHT - 1;
			GUIRES_DisplayImg(PNULL,&txt_rect,&img_rect,MMIMT_MAIN_WIN_ID,IMAGE_MT_FIGHT_BG,&s_ui_data.layer_fight);
			memset(value_str,0x00,sizeof(value_str));
			memset(value_wstr,0x00,sizeof(value_wstr));
			sprintf(value_str,"%d ",value_array[i]);
			MMIAPICOM_StrToWstr(value_str,value_wstr);
			display_str.wstr_len = MMIAPICOM_Wstrlen(value_wstr);
			GUISTR_DrawTextToLCDInRect(&s_ui_data.layer_fight,&txt_rect,&txt_rect,&display_str,&str_style,sar_state,GUISTR_TEXT_DIR_LTR);
		}
		MMITHEME_StoreUpdateRect(&s_ui_data.layer_fight,client_rect);
		if (value_array[0] == 0)
			MMITHEME_UpdateRect();

		if (value_array[0] > 0)
		{
			value_array[0] -= value_array[4] - value_array[2];

			if (value_array[0] <= 0)
				value_array[0] = 0;
			else
			{
				if ((value_array[1] - value_array[5]) > 0)
					value_array[3] -= value_array[1] - value_array[5];
			}
			s_ui_data.fight_timer = MMK_CreateTimer(FIGHT_ANIM_TIMER,FALSE);
		}
		else if (value_array[0] == 0)
		{
			HandleFightEnd();
		}
// 		SCI_SLEEP(FIGHT_SLEEP);
// 	}

// 	UILAYER_RemoveBltLayer(&s_ui_data.layer_fight);
// 	MMITHEME_StoreUpdateRect(&s_ui_data.layer_map,client_rect);
// 	MMITHEME_UpdateRect();
		

}
LOCAL BOOLEAN			HandleFightStart()
{
	MT_UNIT_E enemy			= s_ui_data.cur_enemy;
	int16	hero_damage		= s_game_info.hero_info.offensive - s_mt_unit_pro[enemy].life.defensive;
	int16	enemy_damage	= s_mt_unit_pro[enemy].life.offensive - s_game_info.hero_info.defensive;
	int32	hero_hp			= s_game_info.hero_info.health;
	int32	enemy_hp		= s_mt_unit_pro[enemy].life.health;
	uint16	hero_dead_times	= 0;	
	uint16	enemy_dead_times= 0;
	BOOLEAN	is_able_fight	= FALSE;

	if (hero_damage > 0)
	{
		if (enemy_damage > 0)
		{
			hero_dead_times = hero_hp/enemy_damage;
			if (hero_hp%enemy_damage != 0)
				hero_dead_times++;
			
			enemy_dead_times = enemy_hp/hero_damage;
			if (enemy_hp/hero_damage != 0)
				enemy_dead_times++;
			
			if (enemy_dead_times <= hero_dead_times)
				is_able_fight = TRUE;
			else
				is_able_fight = FALSE;
		}
		else
		{
			is_able_fight = TRUE;
			enemy_dead_times = 1;
		}
	}
	else
		is_able_fight = FALSE;


	if (is_able_fight)
	{
		s_ui_data.scene = FIGHT_SCENE;
		{
			s_ui_data.cur_enemy = enemy;
			hero_hp -= (enemy_dead_times - 1)*enemy_damage;
			s_ui_data.end_life.health = hero_hp;
			s_ui_data.end_life.coin = s_game_info.hero_info.coin + s_mt_unit_pro[enemy].life.coin;
			s_ui_data.end_life.experience = s_game_info.hero_info.experience + s_mt_unit_pro[enemy].life.experience;
		}
		s_ui_data.is_new_fight = TRUE;
		DisplayFight();
// 		if (enemy == MAP_UNIT_MASTER)
// 		{
// 			BOOLEAN	MoveUp();
// 			s_game_info.map_info[19][6][5] = MAP_UNIT_NPC_19_2;
// 			MoveUp();
// 		}
// 		else if (enemy == MAP_UNIT_MASTER2)
// 		{
// 			BOOLEAN	MoveUp();
// 			s_game_info.map_info[21][1][5] = MAP_UNIT_NPC_21_1;
// 			MoveUp();
// 		}
// 		//待fight场景结束，重新恢复map定时器，此时让frame=0，这样，首先画第0桢，
// 		s_frame_mark = 0;
// 		s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
	}
	else
	{

	}

	return is_able_fight;
}
LOCAL BOOLEAN		DisplayAnimDoor(MT_UNIT_E door,POS_T door_pos)
{
	static uint8			i	= 0;
	GUI_POINT_T display_point	= {0};
	MMI_IMAGE_ID_T*		img_ptr = PNULL;
	GUI_POINT_T		start_point = MT_MAP_START_POINT;
	GUI_RECT_T		update_rect = {0};

	if (s_ui_data.is_first_door_anim)
	{
		i = 0;
		s_ui_data.is_first_door_anim = FALSE;
	}
	else
		i++;
	
	if (door == MAP_UNIT_UNKEY_DOOR)
		img_ptr = s_anim_ul_door;
	else if (door == MAP_UNIT_Y_DOOR)
		img_ptr = s_anim_y_door;
	else if (door == MAP_UNIT_B_DOOR)
		img_ptr = s_anim_b_door;
	else if (door == MAP_UNIT_R_DOOR)
		img_ptr = s_anim_r_door;
	else if (door == MAP_UNIT_S_DOOR)
		img_ptr = s_anim_s_door;

	display_point.x		= door_pos.x*MT_MAP_UNIT_WIDTH + start_point.x;
	display_point.y		= door_pos.y*MT_MAP_UNIT_HEIGHT+ start_point.y;
	update_rect.left = display_point.x;
	update_rect.right	= update_rect.left	+ MT_MAP_UNIT_WIDTH - 1;
	update_rect.top		= display_point.y;
	update_rect.bottom	= update_rect.top	+ MT_MAP_UNIT_HEIGHT - 1;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,*(img_ptr+i),&s_ui_data.layer_map);
// 		MMITHEME_StoreUpdateRect(&s_ui_data.layer_map,update_rect);
// 		MMITHEME_UpdateRect();
// 		LCD_InvalidateRect(0,update_rect.left,update_rect.top,update_rect.right,update_rect.bottom);
	GUILCD_InvalidateRect(0,update_rect,0);
	if (i == 3)
	{
		s_game_info.map_info[s_game_info.state_info.floor][door_pos.y][door_pos.x] = MAP_UNIT_FLOOR;
		UpdateRectIm(door_pos);
		MMK_StopTimer(s_ui_data.door_anim_timer);
		s_ui_data.is_door_running = FALSE;
	}
}

LOCAL void DisplayHeroMove(POS_T next_pos)
{
	GUI_RECT_T update_rect = {0};
	GUI_POINT_T start_point = MT_MAP_START_POINT;
	GUI_POINT_T display_point = {0};

	display_point.x		= s_game_info.state_info.hero_pos.x*MT_MAP_UNIT_WIDTH + start_point.x;
	display_point.y		= s_game_info.state_info.hero_pos.y*MT_MAP_UNIT_HEIGHT + start_point.y;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_mt_unit_pro[MAP_UNIT_FLOOR].icon[0],&s_ui_data.layer_map);
	update_rect.left = display_point.x;
	update_rect.right = update_rect.left + MT_MAP_UNIT_WIDTH - 1;
	update_rect.top		= display_point.y;
	update_rect.bottom	= update_rect.top + MT_MAP_UNIT_HEIGHT - 1;
	GUILCD_InvalidateRect(0,update_rect,0);
	display_point.x		= next_pos.x*MT_MAP_UNIT_WIDTH + start_point.x;
	display_point.y		= next_pos.y*MT_MAP_UNIT_HEIGHT + start_point.y;
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_anim_hero[s_ui_data.move_direction][0],&s_ui_data.layer_map);
	update_rect.left = display_point.x;
	update_rect.right = update_rect.left + MT_MAP_UNIT_WIDTH - 1;
	update_rect.top		= display_point.y;
	update_rect.bottom	= update_rect.top + MT_MAP_UNIT_HEIGHT - 1;
	GUILCD_InvalidateRect(0,update_rect,0);
	GUIRES_DisplayImg(&display_point,PNULL,PNULL,MMIMT_MAIN_WIN_ID,s_anim_hero[s_ui_data.move_direction][1],&s_ui_data.layer_map);
	update_rect.left = display_point.x;
	update_rect.right = update_rect.left + MT_MAP_UNIT_WIDTH - 1;
	update_rect.top		= display_point.y;
	update_rect.bottom	= update_rect.top + MT_MAP_UNIT_HEIGHT - 1;
	SCI_SLEEP(HERO_ANIM_SLEEP);
	GUILCD_InvalidateRect(0,update_rect,0);
}

LOCAL BOOLEAN		HandleMove(POS_T cur_pos,POS_T next_pos)
{
	BOOLEAN		ret = TRUE;
	BOOLEAN		is_need_repaint_info	= TRUE;//TRUE代表需要更新info信息
	BOOLEAN		is_need_paint_next	= TRUE;//TRUE代表下一个位置需要立即刷新，而不是等到timer到时才刷新。有动画显示的项目也不需要立即刷新。
	MT_UNIT_E	unit_id			= MAP_UNIT_NULL;
	POS_T		update_pos		= {0};

	unit_id = s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x];
	if (unit_id != MAP_UNIT_WALL)
	{
		if(unit_id == MAP_UNIT_FLOOR)
		{
			DisplayHeroMove(next_pos);
			s_game_info.state_info.hero_pos.x = next_pos.x;
			s_game_info.state_info.hero_pos.y = next_pos.y;
			is_need_repaint_info = FALSE;
			is_need_paint_next = FALSE;
		}
		else if (unit_id == MAP_UNIT_UPSTAIR)
		{
			s_game_info.state_info.floor++;
			if (s_game_info.state_info.floor == 0)
			{
				PlayRing(RING_ZERO_FLOOR);
			}
			else if (s_game_info.state_info.floor == 18)
			{
				PlayRing(RING_PRINCESS);
			}
			else if (s_game_info.state_info.floor == 21)
			{
				PlayRing(RING_BOSS);
			}
			else
			{
				PlayRing(RING_GAME);
			}
			if (s_game_info.state_info.floor > s_game_info.state_info.achieve_floor)
				s_game_info.state_info.achieve_floor = s_game_info.state_info.floor;
			s_game_info.state_info.hero_pos.x = s_hero_pos[s_game_info.state_info.floor][0].x;
			s_game_info.state_info.hero_pos.y = s_hero_pos[s_game_info.state_info.floor][0].y;
			s_frame_mark = 0;
			s_ui_data.move_direction = 2;
			is_need_paint_next = FALSE;
		}
		else if (unit_id == MAP_UNIT_DOWNSTAIR)
		{
			s_game_info.state_info.floor--;
			if (s_game_info.state_info.floor == 0)
			{
				PlayRing(RING_ZERO_FLOOR);
			}
			else if (s_game_info.state_info.floor == 18)
			{
				PlayRing(RING_PRINCESS);
			}
			else if (s_game_info.state_info.floor == 21)
			{
				PlayRing(RING_BOSS);
			}
			else
			{
				PlayRing(RING_GAME);
			}
			s_game_info.state_info.hero_pos.x = s_hero_pos[s_game_info.state_info.floor][1].x;
			s_game_info.state_info.hero_pos.y = s_hero_pos[s_game_info.state_info.floor][1].y;
			s_frame_mark = 0;
			s_ui_data.move_direction = 2;
			is_need_paint_next = FALSE;
		}
		else if (unit_id == MAP_UNIT_Y_DOOR)
		{
			//门存在动画，自己会自动刷新完门的区域，不需要调用立即刷新。
			if (s_game_info.state_info.yellow_key_num >= 1)
			{
				s_ui_data.door_anim_timer = MMK_CreateTimer(DOOR_ANIM_TIEMR,TRUE);
				s_ui_data.door_anim_pos.x = next_pos.x;
				s_ui_data.door_anim_pos.y = next_pos.y;
				s_ui_data.door_type		  = MAP_UNIT_Y_DOOR;
				s_ui_data.is_door_running  = TRUE;
				s_ui_data.is_first_door_anim	  = TRUE;
				s_game_info.state_info.yellow_key_num--;
				is_need_paint_next = FALSE;
			}
		}
		
		else if (unit_id == MAP_UNIT_B_DOOR)
		{
			if (s_game_info.state_info.blue_key_num >= 1)
			{
				s_ui_data.door_anim_timer = MMK_CreateTimer(DOOR_ANIM_TIEMR,TRUE);
				s_ui_data.door_anim_pos.x = next_pos.x;
				s_ui_data.door_anim_pos.y = next_pos.y;
				s_ui_data.door_type		  = MAP_UNIT_B_DOOR;
				s_ui_data.is_door_running  = TRUE;
				s_ui_data.is_first_door_anim	  = TRUE;
				s_game_info.state_info.blue_key_num--;
				is_need_paint_next = FALSE;
			}
		}
		
		else if (unit_id == MAP_UNIT_R_DOOR)
		{
			if (s_game_info.state_info.red_key_num >= 1)
			{
				s_ui_data.door_anim_timer = MMK_CreateTimer(DOOR_ANIM_TIEMR,TRUE);
				s_ui_data.door_anim_pos.x = next_pos.x;
				s_ui_data.door_anim_pos.y = next_pos.y;
				s_ui_data.door_type		  = MAP_UNIT_R_DOOR;
				s_ui_data.is_door_running  = TRUE;
				s_ui_data.is_first_door_anim	  = TRUE;
				s_game_info.state_info.red_key_num--;
				is_need_paint_next = FALSE;
			}
		}
		
		else if (unit_id == MAP_UNIT_UNKEY_DOOR)
		{
			BOOLEAN		is_allow_open	= TRUE;
			uint8		i				= 0;
			uint8		j				= 0;
			uint8		sergeant_num	= 0;
			if (s_game_info.state_info.floor == 7)
			{
				for (i=0; i<MT_MAP_ROW_NUM; i++)
				{
					for (j=0; j<MT_MAP_COLUMN_NUM; j++)
					{
						if (s_game_info.map_info[7][i][j] == MAP_UNIT_WHITE_SERGEANT)
							sergeant_num++;
					}
				}
				if (sergeant_num > 0)
					is_allow_open = FALSE;
				
			}
			else if (s_game_info.state_info.floor == 21)
			{
				is_allow_open = FALSE;
			}

			if (is_allow_open)
			{
				s_ui_data.door_anim_timer = MMK_CreateTimer(DOOR_ANIM_TIEMR,TRUE);
				s_ui_data.door_anim_pos.x = next_pos.x;
				s_ui_data.door_anim_pos.y = next_pos.y;
				s_ui_data.door_type		  = MAP_UNIT_UNKEY_DOOR;
				s_ui_data.is_door_running  = TRUE;
				s_ui_data.is_first_door_anim	  = TRUE;
				is_need_paint_next = FALSE;
			}
		}
		
		else if (unit_id == MAP_UNIT_S_DOOR)
		{
// 			s_ui_data.door_anim_timer = MMK_CreateTimer(DOOR_ANIM_TIEMR,TRUE);
// 			s_ui_data.door_anim_pos.x = next_pos.x;
// 			s_ui_data.door_anim_pos.y = next_pos.y;
// 			s_ui_data.door_type		  = MAP_UNIT_S_DOOR;
// 			s_ui_data.is_door_running  = TRUE;
// 			s_ui_data.is_first_door_anim	  = TRUE;
// 			is_need_paint_next = FALSE;
		}
		//物品
		else if (unit_id == MAP_UNIT_Y_KEY)
		{
			s_game_info.state_info.yellow_key_num++;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_Y_KEY].add_value);
		}
		
		else if (unit_id == MAP_UNIT_B_KEY)
		{
			s_game_info.state_info.blue_key_num++;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_B_KEY].add_value);
		}
		
		else if (unit_id == MAP_UNIT_R_KEY)
		{
			s_game_info.state_info.red_key_num++;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_R_KEY].add_value);
		}

		else if (unit_id == MAP_UNIT_BIG_KEY)
		{
			s_game_info.state_info.yellow_key_num++;
			s_game_info.state_info.blue_key_num++;
			s_game_info.state_info.red_key_num++;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_BIG_KEY].add_value);
		}
		
		else if (unit_id == MAP_UNIT_SMALL_SUPPLY)
		{
			s_game_info.hero_info.health += 200;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SMALL_SUPPLY].add_value);
		}
		
		else if (unit_id == MAP_UNIT_BIG_SUPPLY)
		{
			s_game_info.hero_info.health += 500;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_BIG_SUPPLY].add_value);
		}
		
		else if (unit_id == MAP_UNIT_OF_CRYSTAL)
		{
			s_game_info.hero_info.offensive += 3;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_OF_CRYSTAL].add_value);
		}
		
		else if (unit_id == MAP_UNIT_DF_CRYSTAL)
		{
			s_game_info.hero_info.defensive += 3;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_DF_CRYSTAL].add_value);
		}

		else if (unit_id == MAP_UNIT_SWORD_A)
		{
			s_game_info.hero_info.offensive += 10;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SWORD_A].add_value);
		}

		else if (unit_id == MAP_UNIT_SWORD_B)
		{
			s_game_info.hero_info.offensive += 70;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SWORD_B].add_value);
		}

		else if (unit_id == MAP_UNIT_SWORD_C)
		{
			s_game_info.hero_info.offensive += 150;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SWORD_C].add_value);
		}

		else if (unit_id == MAP_UNIT_SHIELD_A)
		{
			s_game_info.hero_info.defensive += 10;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SHIELD_A].add_value);
		}

		else if (unit_id == MAP_UNIT_SHIELD_B)
		{
			s_game_info.hero_info.defensive += 10;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SHIELD_B].add_value);
		}

		else if (unit_id == MAP_UNIT_SHIELD_C)
		{
			s_game_info.hero_info.defensive += 190;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SHIELD_C].add_value);
		}

		else if (unit_id == MAP_UNIT_MONEY)
		{
			s_game_info.hero_info.coin += 300;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_MONEY].add_value);
		}

		else if (unit_id == MAP_UNIT_LEVEL_UP)
		{
			s_game_info.state_info.level++;
			s_game_info.hero_info.health += 1000;
			s_game_info.hero_info.offensive += 10;
			s_game_info.hero_info.defensive += 10;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_LEVEL_UP].add_value);
		}

		else if (unit_id == MAP_UNIT_BIG_LEVEL_UP)
		{
			s_game_info.state_info.level += 3;
			s_game_info.hero_info.health += 3*1000;
			s_game_info.hero_info.offensive += 3*10;
			s_game_info.hero_info.defensive += 3*10;
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_BIG_LEVEL_UP].add_value);
		}

		//NPC(不包括NPC商人)
		else if ((unit_id >= MAP_UNIT_NPC_0_1) && (unit_id <= MAP_UNIT_NPC_21_1))
		{
			BOOLEAN			is_allow_dialog = TRUE;

			if ( ((unit_id == MAP_UNIT_NPC_4_2)&&(!s_game_info.state_info.is_get_hammer18))
				|| ((unit_id == MAP_UNIT_NPC_0_2)&&(!s_game_info.state_info.is_get_cross)) )
				is_allow_dialog = FALSE;

			//下个场景的初始化操作。
			if (unit_id == MAP_UNIT_NPC_15_1_0)
			{
				if (s_game_info.hero_info.experience >= 500)
					unit_id = MAP_UNIT_NPC_15_1_1;
			}
			else if (unit_id == MAP_UNIT_NPC_15_2_0)
			{
				if (s_game_info.hero_info.coin >= 500)
					unit_id = MAP_UNIT_NPC_15_2_1;
			}
			else if (unit_id == MAP_UNIT_NPC_16_1)
			{
// 				s_mt_unit_pro[MAP_UNIT_NPC_16_1].icon[0] = IMAGE_MT_RED_SERGEANT0;
// 				s_mt_unit_pro[MAP_UNIT_NPC_16_1].icon[1] = IMAGE_MT_RED_SERGEANT1;
			}
			if (is_allow_dialog)
			{
// 				MMK_StopTimer(s_ui_data.map_anim_timer);
// 				s_ui_data.map_anim_timer = 0;
				MMK_StopTimer(s_ui_data.speed_timer);
				s_ui_data.speed_timer = 0;
				
				s_ui_data.dialog_id = unit_id;
				s_ui_data.talk_index = 0;
				s_ui_data.dialog_anim_timer = MMK_CreateTimer(DIALOG_TIMER,TRUE);
				s_ui_data.scene = DIALOG_SCENE;
			}
		}
		
		//商人和商店
		else if ((unit_id >= MAP_UNIT_STORE3_0) && (unit_id <= MAP_UNIT_NPC_13_1))
		{
			//进入商店相当于进入一个新的场景，用户的交互全交给商店场景完成，
			//因此前一个场景必须暂停，与之相关的状态变量和定时器等需要进行处理，然后对下一个场景进行初始化。
			//待商店场景结束时，需要对需恢复的场景进行初始化。
			//总结：场景的切换需要进行2个操作，1：当前场景的挂起操作。2：下一个场景的初始化操作。

			//当前场景的挂起操作。
			//挂起的定义：停止一切操作，终止所有即时事件和循环事件（包括定时器事件）
// 			MMK_StopTimer(s_ui_data.map_anim_timer);
// 			s_ui_data.map_anim_timer = 0;
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;
			
			s_ui_data.store_id = unit_id;
			s_ui_data.store_select_item = 0;
			DisplayStore(s_ui_data.store_select_item);
			s_ui_data.scene = STORE_SCENE;
		}

		//工具
		else if ((unit_id >= MAP_UNIT_TOOL_LOOK) && (unit_id <= MAP_UNIT_TOOL_WARTER))
		{
// 			MMK_StopTimer(s_ui_data.map_anim_timer);
// 			s_ui_data.map_anim_timer = 0;
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;


			DisplayToolTip(unit_id);
			s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			s_ui_data.scene = TOOLTIP_SCENE;
			is_need_paint_next = FALSE;
			is_need_repaint_info = FALSE;
		}
		//怪物
		else if (unit_id > MAP_UNIT_HERO)
		{
			s_ui_data.cur_enemy = unit_id;

			if (HandleFightStart())
			{
// 			MMK_StopTimer(s_ui_data.map_anim_timer);
// 			s_ui_data.map_anim_timer = 0;
				MMK_StopTimer(s_ui_data.speed_timer);
				s_ui_data.speed_timer = 0;
				s_game_info.map_info[s_game_info.state_info.floor][cur_pos.y][cur_pos.x] = MAP_UNIT_FLOOR;
				s_game_info.map_info[s_game_info.state_info.floor][next_pos.y][next_pos.x] = MAP_UNIT_FLOOR;
			}
		}
		else
		{
// 			SCI_ASSERT(FALSE);
			ret = FALSE;
			is_need_repaint_info = FALSE;
			is_need_paint_next = FALSE;
		}
	}
	else
		ret = FALSE;

	if (is_need_paint_next == TRUE)
	{
		UpdateRectIm(next_pos);
	}
	if (ret)
	{
		DrawInfo();
	}

	return ret;
}

LOCAL BOOLEAN		MoveLeft()
{

	BOOLEAN		ret = TRUE;
	POS_T		pos = s_game_info.state_info.hero_pos;
	POS_T		pos_next = pos;
	
	if ( (--pos_next.x) < 0)
		return FALSE;
	else
		ret = HandleMove(pos,pos_next);
	
	return ret;
}

LOCAL BOOLEAN		MoveRight()
{

	BOOLEAN		ret = TRUE;
	POS_T		pos = s_game_info.state_info.hero_pos;
	POS_T		pos_next = pos;
	MT_UNIT_E	unit_id = MAP_UNIT_NULL;
	
	if ( (++pos_next.x) > (MT_MAP_COLUMN_NUM - 1))
		return FALSE;
	else
		ret = HandleMove(pos,pos_next);
	
	return ret;
}

LOCAL BOOLEAN		MoveUp()
{
	BOOLEAN		ret = TRUE;
	POS_T		pos = s_game_info.state_info.hero_pos;
	POS_T		pos_next = pos;
	MT_UNIT_E	unit_id = MAP_UNIT_NULL;
	
	if (--pos_next.y < 0)
		return FALSE;
	else
		ret = HandleMove(pos,pos_next);

	return ret;

}

LOCAL BOOLEAN		MoveDown()
{

	BOOLEAN		ret = TRUE;
	POS_T		pos = s_game_info.state_info.hero_pos;
	POS_T		pos_next = pos;
	MT_UNIT_E	unit_id = MAP_UNIT_NULL;
	
	if (++pos_next.y > (MT_MAP_ROW_NUM - 1))
		return FALSE;
	else
		ret = HandleMove(pos,pos_next);

	
	return ret;
}
LOCAL void InitModuleExit()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	uint16					img_width = 0;
	uint16					img_height = 0;

	GUIRES_GetImgWidthHeight(&img_width,&img_height,IMAGE_MT_SAVE_QUERY,MMIMT_MAIN_WIN_ID);
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= img_width;
	layer_create.height			= img_height;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_exit_query);
}
LOCAL void InitModuleTip()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_TIP_WIDTH;
	layer_create.height			= MT_TIP_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_tip);
	
}
LOCAL void InitModuleEnemyInfo()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_MAP_WIDTH;
	layer_create.height			= MT_MAP_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_enemy_info);

}
LOCAL void InitModuleToolTip()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= FALSE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_TOOLTIP_WIDTH;
	layer_create.height			= MT_TOOLTIP_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_tool_tip);

}
LOCAL BOOLEAN InitModuleDialog()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_DIALOG_WIDTH;
	layer_create.height			= MT_DIALOG_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_dialog);
	
}

LOCAL BOOLEAN InitModuleStore()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_STORE_WIDTH;
	layer_create.height			= MT_STORE_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_store);

}
LOCAL BOOLEAN InitModuleFight()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_FIGHT_WIDTH;
	layer_create.height			= MT_FIGHT_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_fight);

}
LOCAL BOOLEAN InitModuleMap()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= TRUE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_MAP_WIDTH;
	layer_create.height			= MT_MAP_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_map);

// 	layer_append.layer_level	= UILAYER_LEVEL_NORMAL;
// 	layer_append.lcd_dev_info	= s_ui_data.layer_map;
// 	UILAYER_AppendBltLayer(&layer_append);

	memcpy(&s_game_info.map_info,&s_mt_fit_map,sizeof(s_mt_fit_map));
	s_game_info.state_info.hero_pos.x = s_hero_pos[s_game_info.state_info.floor][0].x;
	s_game_info.state_info.hero_pos.y = s_hero_pos[s_game_info.state_info.floor][0].y;
	s_ui_data.move_direction = 2;
	s_frame_mark = 0;
}

LOCAL BOOLEAN InitModuleInfo()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= FALSE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= MT_INFO_WIDTH;
	layer_create.height			= MT_INFO_HEIGHT;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_info);

// 	layer_append.layer_level	= UILAYER_LEVEL_NORMAL;
// 	layer_append.lcd_dev_info	= s_ui_data.layer_info;
// 	UILAYER_AppendBltLayer(&layer_append);

// 	s_game_info.hero_info.health	= 1000;
// 	s_game_info.hero_info.experience= 1000;
// 	s_game_info.hero_info.offensive	= 2000/*0x7f7f*/;
// 	s_game_info.hero_info.defensive	= 2000/*0x7f7f*/;
// 	s_game_info.hero_info.coin		= 1000;
	memcpy(&s_game_info.hero_info,&s_mt_hero_info_hard,sizeof(MT_LIFE_T));
	s_game_info.state_info.level			= 1;
// 	s_game_info.state_info.floor			= 0;
// 	s_game_info.state_info.yellow_key_num	= 10;
// 	s_game_info.state_info.blue_key_num		= 10;
// 	s_game_info.state_info.red_key_num		= 10;
}
LOCAL BOOLEAN InitModuleInst()
{
	UILAYER_CREATE_T		layer_create = {0};
	UILAYER_APPEND_BLT_T	layer_append = {0};
	
	layer_create.is_bg_layer	= FALSE;
	layer_create.owner_handle	= MMIMT_MAIN_WIN_ID,
	layer_create.width			= 320;
	layer_create.height			= 240;
	UILAYER_CreateLayer(&layer_create,&s_ui_data.layer_inst);

}
LOCAL BOOLEAN InitModuleBG()
{
	GUI_LCD_DEV_INFO	*lcd_dev_ptr = PNULL;

	lcd_dev_ptr = MMITHEME_GetDefaultLcdDev();
	s_ui_data.layer_bg = *lcd_dev_ptr;
}

LOCAL BOOLEAN InitSave()
{
	wchar*		file_name1 = L"D:\\magic_tower\\game.dat";
	SFS_HANDLE save_file = 0;

	save_file = MMIFILE_CreateFile(file_name1,SFS_MODE_CREATE_NEW|SFS_MODE_READ,NULL,NULL);
	SFS_CloseFile(save_file);
}

LOCAL BOOLEAN InitEnd()
{

}
LOCAL BOOLEAN InitOpen()
{
	s_ui_data.scene = OPEN_SCENE;
}

LOCAL BOOLEAN InitModuleAll()
{
	InitOpen();
	InitSave();
	InitEnd();
	InitModuleBG();
// 	InitModuleInst();
	InitModuleInfo();
	InitModuleMap();
	InitModuleFight();
	InitModuleStore();
	InitModuleDialog();
	InitModuleToolTip();
	InitModuleEnemyInfo();
	InitModuleTip();
	InitModuleExit();
}

LOCAL BOOLEAN Init()
{
	MMI_WIN_ID_T win_id = MMIMT_MAIN_WIN_ID;

	MMK_SetWinMoveStyle(win_id,MOVE_FORBIDDEN);
	MMK_SetWinAngle(win_id,LCD_ANGLE_90,FALSE);
	memset(&s_ui_data,0x00,sizeof(UI_DATA_T));
	memset(&s_game_info,0x00,sizeof(MT_GAME_SAVE_T));
	
	MMIDEFAULT_AllowTurnOffBackLight(FALSE);

	InitModuleAll();

}
LOCAL void			HandleStoreResult()
{
	switch(s_ui_data.store_id)
	{
	case MAP_UNIT_STORE3_0:
	case MAP_UNIT_STORE3_1:
	case MAP_UNIT_STORE3_2:
		if (s_ui_data.store_select_item == 0)
		{
			if (s_game_info.hero_info.coin >= 25)
			{	
				s_game_info.hero_info.health += 800;
				s_game_info.hero_info.coin   -= 25;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 1)
		{
			if (s_game_info.hero_info.coin >= 25)
			{
				s_game_info.hero_info.offensive += 4;
				s_game_info.hero_info.coin   -= 25;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 2)
		{
			if (s_game_info.hero_info.coin >= 25)
			{
				s_game_info.hero_info.defensive += 4;
				s_game_info.hero_info.coin   -= 25;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 3)
		{
			s_ui_data.store_select_item = 0;
			UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
			
// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;

	case MAP_UNIT_NPC_5_1:
		if (s_ui_data.store_select_item == 0)
		{
			if (s_game_info.hero_info.experience >= 100)
			{	
				s_game_info.state_info.level++;
				s_game_info.hero_info.health += 1000;
				s_game_info.hero_info.offensive += 7;
				s_game_info.hero_info.defensive += 7;
				s_game_info.hero_info.experience   -= 100;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 1)
		{
			if (s_game_info.hero_info.experience >= 30)
			{
				s_game_info.hero_info.offensive += 5;
				s_game_info.hero_info.experience   -= 30;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 2)
		{
			if (s_game_info.hero_info.experience >= 30)
			{
				s_game_info.hero_info.defensive += 5;
				s_game_info.hero_info.experience  -= 30;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 3)
		{
			s_ui_data.store_select_item = 0;
			UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
			
// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;

	case MAP_UNIT_NPC_5_2:
		if (s_ui_data.store_select_item == 0)
		{
			if (s_game_info.hero_info.coin >= 10)
			{	
				s_game_info.hero_info.coin -= 10;;
				s_game_info.state_info.yellow_key_num++;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 1)
		{
			if (s_game_info.hero_info.coin >= 50)
			{
				s_game_info.hero_info.coin -= 50;
				s_game_info.state_info.blue_key_num++;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 2)
		{
			if (s_game_info.hero_info.coin >= 100)
			{
				s_game_info.hero_info.coin -= 100;
				s_game_info.state_info.red_key_num++;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 3)
		{
			s_ui_data.store_select_item = 0;
			UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
			
// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;
		
	case MAP_UNIT_STORE11_0:
	case MAP_UNIT_STORE11_1:
	case MAP_UNIT_STORE11_2:
		if (s_ui_data.store_select_item == 0)
		{
			if (s_game_info.hero_info.coin >= 100)
			{	
				s_game_info.hero_info.health += 4000;
				s_game_info.hero_info.coin   -= 100;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 1)
		{
			if (s_game_info.hero_info.coin >= 100)
			{
				s_game_info.hero_info.offensive += 20;
				s_game_info.hero_info.coin   -= 100;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 2)
		{
			if (s_game_info.hero_info.coin >= 100)
			{
				s_game_info.hero_info.defensive += 20;
				s_game_info.hero_info.coin   -= 100;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 3)
		{
			s_ui_data.store_select_item = 0;
			UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
			
// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;

	case MAP_UNIT_NPC_12_1:
		if (s_ui_data.store_select_item == 0)
		{
			if (s_game_info.state_info.yellow_key_num >= 1)
			{	
				s_game_info.state_info.yellow_key_num--;
				s_game_info.hero_info.coin   += 7;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 1)
		{
			if (s_game_info.state_info.blue_key_num >= 1)
			{
				s_game_info.state_info.blue_key_num--;
				s_game_info.hero_info.coin   += 35;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 2)
		{
			if (s_game_info.state_info.red_key_num >= 1)
			{
				s_game_info.state_info.red_key_num--;
				s_game_info.hero_info.coin   += 70;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 3)
		{
			s_ui_data.store_select_item = 0;
			UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
			
// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;
		
	case MAP_UNIT_NPC_13_1:
		if (s_ui_data.store_select_item == 0)
		{
			if (s_game_info.hero_info.experience >= 270)
			{	
				s_game_info.state_info.level += 3;
				s_game_info.hero_info.health += 3*1000;
				s_game_info.hero_info.offensive += 3*7;
				s_game_info.hero_info.defensive += 3*7;
				s_game_info.hero_info.experience  -= 270;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 1)
		{
			if (s_game_info.hero_info.experience >= 95)
			{
				s_game_info.hero_info.offensive += 17;
				s_game_info.hero_info.experience   -= 95;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 2)
		{
			if (s_game_info.hero_info.experience >= 95)
			{
				s_game_info.hero_info.defensive += 17;
				s_game_info.hero_info.experience  -= 95;
				DrawInfo();
			}
		}
		else if (s_ui_data.store_select_item == 3)
		{
			s_ui_data.store_select_item = 0;
			UILAYER_RemoveBltLayer(&s_ui_data.layer_store);
			
// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;

	default:
		SCI_ASSERT(FALSE);
		break;
	}

}
LOCAL void			HandleDialogResult()
{
	POS_T		update_pos = {0};

	switch(s_ui_data.dialog_id)
	{
	case MAP_UNIT_NPC_0_1:
		s_game_info.map_info[0][8][5] = MAP_UNIT_FLOOR;
		s_game_info.map_info[0][8][4] = MAP_UNIT_NPC_0_2;
		update_pos.x = 5;
		update_pos.y = 8;
		UpdateRectIm(update_pos);
		update_pos.x = 4;
		update_pos.y = 8;
		UpdateRectIm(update_pos);
		s_game_info.state_info.yellow_key_num++;
		s_game_info.state_info.blue_key_num++;
		s_game_info.state_info.red_key_num++;
		break;

	case MAP_UNIT_NPC_0_2:
		s_game_info.map_info[20][7][5] = MAP_UNIT_UPSTAIR;
		s_game_info.map_info[0][8][4] = MAP_UNIT_FLOOR;
		UpdateRectIm(update_pos);
		update_pos.x = 4;
		update_pos.y = 8;
		UpdateRectIm(update_pos);
		s_game_info.hero_info.health *= 1.5;
		s_game_info.hero_info.offensive *= 1.5;
		s_game_info.hero_info.defensive *= 1.5;
		DrawInfo();
		break;
	case MAP_UNIT_NPC_2_1:
		DisplayTip(s_other_tip[0]);
		s_game_info.map_info[2][10][7] = MAP_UNIT_FLOOR;
		update_pos.x = 7;
		update_pos.y = 10;
		UpdateRectIm(update_pos);
		s_game_info.hero_info.offensive += 30;
		DrawInfo();
		break;
	case MAP_UNIT_NPC_2_2:
		DisplayTip(s_other_tip[1]);
		s_game_info.map_info[2][10][9] = MAP_UNIT_FLOOR;
		update_pos.x = 9;
		update_pos.y = 10;
		UpdateRectIm(update_pos);
		s_game_info.hero_info.defensive += 30;
		DrawInfo();
		break;
	case MAP_UNIT_NPC_4_1:
		s_game_info.map_info[2][6][1] = MAP_UNIT_FLOOR;
		s_game_info.map_info[4][0][5] = MAP_UNIT_NPC_4_2;
		break;

	case MAP_UNIT_NPC_4_2:
		s_game_info.map_info[4][0][5] = MAP_UNIT_FLOOR;
		update_pos.x = 5;
		update_pos.y = 0;
		UpdateRectIm(update_pos);
		s_game_info.map_info[18][8][5] = MAP_UNIT_FLOOR;
		s_game_info.map_info[18][9][5] = MAP_UNIT_FLOOR;
// 		s_game_info.map_info[18][10][10] = MAP_UNIT_UPSTAIR;
		break;

	case MAP_UNIT_NPC_15_1_0:
		break;

	case MAP_UNIT_NPC_15_1_1:
		s_game_info.hero_info.experience -= 500;
		s_game_info.hero_info.offensive  += 120;
		s_game_info.map_info[15][3][4] = MAP_UNIT_FLOOR;
		DisplayTip(s_other_tip[2]);
		update_pos.x = 3;
		update_pos.y = 4;
		UpdateRectIm(update_pos);
		DrawInfo();
		break;

	case MAP_UNIT_NPC_15_2_0:
		break;
		
	case MAP_UNIT_NPC_15_2_1:
		s_game_info.hero_info.experience -= 500;
		s_game_info.hero_info.offensive  += 120;
		s_game_info.map_info[15][3][6] = MAP_UNIT_FLOOR;
		DisplayTip(s_other_tip[3]);
		update_pos.x = 6;
		update_pos.y = 3;
		UpdateRectIm(update_pos);
		DrawInfo();
		break;

	case MAP_UNIT_NPC_16_1:
		s_game_info.map_info[16][4][5] = MAP_UNIT_FLOOR;
		break;

	case MAP_UNIT_NPC_18_1:
		s_game_info.map_info[18][10][10] = MAP_UNIT_UPSTAIR;
		update_pos.x = 10;
		update_pos.y = 10;
		UpdateRectIm(update_pos);
		break;

	case MAP_UNIT_NPC_19_1:
		s_game_info.map_info[19][7][5] = MAP_UNIT_FLOOR;
		break;

	case MAP_UNIT_NPC_19_2:
		s_game_info.map_info[19][6][5] = MAP_UNIT_FLOOR;
		break;

	case MAP_UNIT_NPC_21_1:
		DisplayEnd();
		break;

	default:
		SCI_ASSERT(FALSE);
		break;
	}

}
LOCAL MMI_RESULT_E HandleMTWinMsg(	MMI_WIN_ID_T	win_id,
									uint32			msg_id,
									DPARAM			param)
{
	MMI_RESULT_E	recode = MMI_RESULT_TRUE;
	BOOLEAN			ret	   = FALSE;
	POS_T			update_pos		= {0};

	switch(msg_id)
	{
	case MSG_KEYDOWN_3:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (s_ui_data.is_allow_sound == TRUE)
			{
				s_ui_data.is_allow_sound = FALSE;
				MMIAPISET_StopAllRing(TRUE);
				DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SOUND_OFF].add_value);
			}
			else
			{
				s_ui_data.is_allow_sound = TRUE;
				s_ui_data.ring_id = 0;
				PlayRing(RING_GAME);
				DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SOUND_ON].add_value);
			}
		}
		break;

	case MSG_KEYLONG_HASH:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			SaveGame();
			DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_SAVE_TIP].add_value);
		}
		break;

	case MSG_KEYLONG_STAR:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (s_is_cheat_mode == FALSE)
			{
				s_is_cheat_mode = TRUE;
				DisplayTip((char*)s_mt_unit_pro[MAP_UNIT_CHEAT_TIP].add_value);
			}
		}
		break;

	case MSG_APP_STAR:
		if (s_is_cheat_mode == TRUE)
		{
			s_game_info.hero_info.health	+= 300;
			s_game_info.hero_info.defensive += 10;
			s_game_info.hero_info.offensive += 10;
			s_game_info.state_info.yellow_key_num	+= 2;
			s_game_info.state_info.blue_key_num		+= 2;
			s_game_info.state_info.red_key_num		+= 2;
			s_game_info.hero_info.coin		+= 10;
			s_game_info.hero_info.experience+= 10;
			DrawInfo();
		}
		break;

	case MSG_APP_1:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if ((s_game_info.state_info.floor > 0) && (s_is_cheat_mode ||(s_game_info.state_info.is_get_jump)))
			{
				s_frame_mark = 0;
				s_game_info.state_info.floor--;
				if (s_game_info.state_info.floor == 0)
				{
					PlayRing(RING_ZERO_FLOOR);
				}
				else if (s_game_info.state_info.floor != 0)
				{
					PlayRing(RING_GAME);
				}
				s_game_info.state_info.hero_pos.x = s_hero_pos[s_game_info.state_info.floor][1].x;
				s_game_info.state_info.hero_pos.y = s_hero_pos[s_game_info.state_info.floor][1].y;
				s_ui_data.move_direction = 2;
				DrawInfo();
			}
		}
		break;

	case MSG_APP_4:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (((s_game_info.state_info.floor < s_game_info.state_info.achieve_floor) && (s_game_info.state_info.is_get_jump))
				||((s_game_info.state_info.floor < (MT_MAP_FLOOR_NUM-1)) && (s_is_cheat_mode)))
			{
				s_frame_mark = 0;
				s_game_info.state_info.floor++;
				if (s_game_info.state_info.floor == 0)
				{
					PlayRing(RING_ZERO_FLOOR);
				}
				else if (s_game_info.state_info.floor != 0)
				{
					PlayRing(RING_GAME);
				}
				s_game_info.state_info.hero_pos.x = s_hero_pos[s_game_info.state_info.floor][0].x;
				s_game_info.state_info.hero_pos.y = s_hero_pos[s_game_info.state_info.floor][0].y;
				s_ui_data.move_direction = 2;
				DrawInfo();
			}
		}
		break;

	case MSG_APP_0:
		if ((s_ui_data.scene == MAIN_SCENE) && (s_is_cheat_mode ||(s_game_info.state_info.is_get_look)))
		{
			MMK_StopTimer(s_ui_data.map_anim_timer);
			s_ui_data.map_anim_timer = 0;
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;

			SetEnemyInfo();
			DisplayEnemyInfo();
			s_ui_data.enemy_info_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = ENEMY_INFO_SCENE;
		}
		else if (s_ui_data.scene == ENEMY_INFO_SCENE)
		{
			MMK_StopTimer(s_ui_data.enemy_info_timer);
			UILAYER_RemoveBltLayer(&s_ui_data.layer_enemy_info);
			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;

	case MSG_OPEN_WINDOW:
		Init();
		break;

	case MSG_LOSE_FOCUS:
		QuitGameUI();
		break;

	case MSG_GET_FOCUS:
		{
			UILAYER_APPEND_BLT_T layer_append = {0};

			MMK_SetWinAngle(win_id,LCD_ANGLE_90,FALSE);
			StartGameUI();
			PlayRing(s_ui_data.ring_id);
// 			layer_append.lcd_dev_info = s_ui_data.layer_info;
// 			layer_append.layer_level  = UILAYER_LEVEL_NORMAL;
// 			UILAYER_AppendBltLayer(&layer_append);
// 			layer_append.lcd_dev_info = s_ui_data.layer_map;
// 			UILAYER_AppendBltLayer(&layer_append);
// 			s_ui_data.scene = MAIN_SCENE;
// 			s_frame_mark = 0;
		}
		break;

	case MSG_FULL_PAINT:
		if (s_ui_data.scene == OPEN_SCENE)
		{
			DrawVoice();
		}
		else if (s_ui_data.scene == MENU_SCENE)
		{
			DrawMenu();
		}
		else
		{
			DrawAll();
		}
		
		break;

	case MSG_APP_UP:
	case MSG_APP_6:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 0;
				MoveUp();
			}
		}
		else if (s_ui_data.scene == STORE_SCENE)
		{
			s_ui_data.store_select_item --;
			if (s_ui_data.store_select_item < 0)
				s_ui_data.store_select_item = 3;
			DisplayStore(s_ui_data.store_select_item);
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		else if (s_ui_data.scene == MENU_SCENE)
		{
			if (s_ui_data.menu_select == 0)
				s_ui_data.menu_select = 4;
			else
				s_ui_data.menu_select--;

			s_ui_data.menu_select %= 5; 
			DrawMenu();
		}
		break;

	case MSG_KEYLONG_UP:
	case MSG_KEYLONG_6:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 0;
				if (s_ui_data.speed_timer == 0)
				{
					s_ui_data.speed_timer = MMK_CreateTimer(SPEED_TIMER,TRUE);
				}
			}
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;
	case MSG_KEYPRESSUP_UP:
	case MSG_KEYPRESSUP_6:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;

	case MSG_APP_LEFT:
	case MSG_APP_2:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 3;
				MoveLeft();
			}
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		else if (s_ui_data.scene == VOICE_SCENE)
		{
			if (s_ui_data.voice_select == 0)
				s_ui_data.voice_select = 1;
			else
				s_ui_data.voice_select--;
			s_ui_data.voice_select %= 2; 
			DrawVoice();
		}
		else if (s_ui_data.scene == EXIT_QUERY_SCENE)
		{
			s_ui_data.save_select--;
			s_ui_data.save_select %= 3;
			DrawExitQuery();
		}
		break;
	case MSG_KEYLONG_LEFT:
	case MSG_KEYLONG_2:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 3;
				if (s_ui_data.speed_timer == 0)
				{
					s_ui_data.speed_timer = MMK_CreateTimer(SPEED_TIMER,TRUE);
				}
			}
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;
	case MSG_KEYPRESSUP_LEFT:
	case MSG_KEYPRESSUP_2:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;

	case MSG_APP_DOWN:
	case MSG_APP_5:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 2;
				MoveDown();
			}
		}
		else if (s_ui_data.scene == STORE_SCENE)
		{
			s_ui_data.store_select_item ++;
			if (s_ui_data.store_select_item > 3)
				s_ui_data.store_select_item = 0;
			DisplayStore(s_ui_data.store_select_item);
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		else if (s_ui_data.scene == MENU_SCENE)
		{
			s_ui_data.menu_select++;
			s_ui_data.menu_select %= 5; 
			DrawMenu();
		}
		break;

	case MSG_KEYLONG_DOWN:
	case MSG_KEYLONG_5:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 2;
				if (s_ui_data.speed_timer == 0)
				{
					s_ui_data.speed_timer = MMK_CreateTimer(SPEED_TIMER,TRUE);
				}
			}
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;
	case MSG_KEYPRESSUP_DOWN:
	case MSG_KEYPRESSUP_5:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;

	case MSG_APP_RIGHT:
	case MSG_APP_8:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 1;
				MoveRight();
			}
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		else if (s_ui_data.scene == VOICE_SCENE)
		{
			s_ui_data.voice_select++;
			s_ui_data.voice_select %= 2; 
			DrawVoice();
		}
		else if (s_ui_data.scene == EXIT_QUERY_SCENE)
		{
			s_ui_data.save_select++;
			s_ui_data.save_select %= 3;
			DrawExitQuery();
		}
		break;
	case MSG_KEYLONG_RIGHT:
	case MSG_KEYLONG_8:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			if (!s_ui_data.is_door_running)
			{
				s_ui_data.move_direction = 1;
				if (s_ui_data.speed_timer == 0)
				{
					s_ui_data.speed_timer = MMK_CreateTimer(SPEED_TIMER,TRUE);
				}
			}
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;
	case MSG_KEYPRESSUP_RIGHT:
	case MSG_KEYPRESSUP_8:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			MMK_StopTimer(s_ui_data.speed_timer);
			s_ui_data.speed_timer = 0;
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		break;

	case MSG_TP_PRESS_UP:
		break;

	case MSG_APP_OK:
	case MSG_APP_WEB:
		if (s_ui_data.scene == MAIN_SCENE)
		{

		}
		else if (s_ui_data.scene == STORE_SCENE)
		{
			HandleStoreResult();
		}
		else if (s_ui_data.scene == DIALOG_SCENE)
		{
			s_ui_data.talk_index++;
			if (s_ui_data.talk_index >= s_dialog[s_ui_data.dialog_id - MAP_UNIT_NPC_0_1].dislog_num)
			{
				MMK_StopTimer(s_ui_data.dialog_anim_timer);
				UILAYER_RemoveBltLayer(&s_ui_data.layer_dialog);
				
				HandleDialogResult();
// 				s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
				s_ui_data.scene = MAIN_SCENE;
			}

		}
		else if(s_ui_data.scene == TOOLTIP_SCENE)
		{
			UILAYER_RemoveBltLayer(&s_ui_data.layer_tool_tip);
			s_frame_mark = 0;
			DrawAll();

// 			s_ui_data.map_anim_timer = MMK_CreateTimer(MAP_ANIM_TIMER,TRUE);
			s_ui_data.scene = MAIN_SCENE;
		}
		else if (s_ui_data.scene == FIGHT_SCENE)
		{
			HandleFightEnd();
		}
		else if (s_ui_data.scene == VOICE_SCENE)
		{
			if (s_ui_data.voice_select == 0)
				s_ui_data.is_allow_sound = TRUE;
			else
				s_ui_data.is_allow_sound = FALSE;

			s_ui_data.scene = MENU_SCENE;
			PlayRing(RING_MENU);
			DrawMenu();
		}
		else if (s_ui_data.scene == MENU_SCENE)
		{
			if (s_ui_data.menu_select == 0)
			{
				if (s_ui_data.is_start_from_save == FALSE)
				{
					s_ui_data.scene = INSTRUCTION_SCENE;
					s_ui_data.inst_y = 238;
					s_ui_data.inst_timer = MMK_CreateTimer(INSTRUCTION_TIMER,TRUE);
				}
				else
				{
					s_ui_data.scene = MAIN_SCENE;
					if (s_game_info.state_info.floor == 0)
						PlayRing(RING_ZERO_FLOOR);
					else
						PlayRing(RING_GAME);
					StartGameUI();
					DrawAll();
				}
			}
			else if (s_ui_data.menu_select == 1)
			{
				ReadGame();
			}
			else if (s_ui_data.menu_select == 2)
			{
				GUI_POINT_T dis_point = {0};

				GUIRES_DisplayImg(&dis_point,PNULL,PNULL,win_id,IMAGE_MT_HELP,&s_ui_data.layer_bg);
				s_ui_data.scene = HELP_SCENE;
			}
			else if (s_ui_data.menu_select == 3)
			{
				s_ui_data.scene = ABOUT_SCENE;

#ifdef VIDEO_PLAYER_SUPPORT   
				{
					MMIAUD_RING_DATA_INFO_T         file_info = {0};/*lint !e64*/ 
					uint8                           power_midi_volume = MMISET_VOL_TWO;
					VP_PLAY_PARAM_T                 play_param  = {0};
					MMISET_POWER_ON_OFF_ANIM_INFO_T power_on_off_anim_info = {0};
					GUI_RECT_T						full_rect = {0};

// 					MMI_GetRingInfo(R_MT_ABOUT, &file_info); 
					play_param.play_type = VP_PLAY_FROM_FILE;
					play_param.mode = VP_REPEAT_PLAY_MODE_CLOSE;
					play_param.full_path_ptr = L"E:\\about.mp4"/*L"D:\\magic_tower\\about.mp4"*/;
					play_param.full_path_len = MMIAPICOM_Wstrlen(L"E:\\about.mp4"/*L"D:\\magic_tower\\about.mp4"*/);
					play_param.vol = power_midi_volume;
					if(!MMIAPIVP_Play(&play_param, EndAbout, 0))
					{
						EndAbout();
					}
				}
#endif

			}
			else if (s_ui_data.menu_select == 4)
			{
				MMK_CloseWin(win_id);
			}
		}
		else if (s_ui_data.scene == HELP_SCENE)
		{
			s_ui_data.scene = MENU_SCENE;
			PlayRing(RING_MENU);
			DrawMenu();
		}
		else if (s_ui_data.scene == ABOUT_SCENE)
		{
			s_ui_data.scene = MENU_SCENE;
			PlayRing(RING_MENU);
			DrawMenu();
		}
		else if (s_ui_data.scene == EXIT_QUERY_SCENE)
		{
			if (s_ui_data.save_select == 0)
			{
				UILAYER_RemoveBltLayer(&s_ui_data.layer_exit_query);
				SaveGame();
				QuitGameUI();
				PlayRing(RING_MENU);
				DrawMenu();
				s_ui_data.scene = MENU_SCENE;
			}
			else if (s_ui_data.save_select == 1)
			{
				UILAYER_RemoveBltLayer(&s_ui_data.layer_exit_query);
				QuitGameUI();
				PlayRing(RING_MENU);
				DrawMenu();
				s_ui_data.scene = MENU_SCENE;
			}
			else
			{
				UILAYER_RemoveBltLayer(&s_ui_data.layer_exit_query);
				s_ui_data.scene = MAIN_SCENE;
			}
		}
		else if (s_ui_data.scene == INSTRUCTION_SCENE)
		{
			MMK_StopTimer(s_ui_data.inst_timer);

			s_ui_data.scene = MAIN_SCENE;
			if (s_game_info.state_info.floor == 0)
				PlayRing(RING_ZERO_FLOOR);
			else
				PlayRing(RING_GAME);
			StartGameUI();
			DrawAll();
		}
		break;

	case MSG_APP_CANCEL:
		if (s_ui_data.scene == MAIN_SCENE)
		{
			s_ui_data.scene = EXIT_QUERY_SCENE;
			DrawExitQuery();
		}
		else if (s_ui_data.scene == EXIT_QUERY_SCENE)
		{
			UILAYER_RemoveBltLayer(&s_ui_data.layer_exit_query);
			s_ui_data.scene = MAIN_SCENE;
		}
		break;

	case MSG_CLOSE_WINDOW:
		ExitGame();
		break;

	case MSG_TIMER:
		//快速移动定时器
		if (*(uint8*)param == s_ui_data.speed_timer)
		{
			switch(s_ui_data.move_direction)
			{
			case 0:
				MoveUp();
				break;

			case 1:
				MoveRight();
				break;

			case 2:
				MoveDown();
				break;

			case 3:
				MoveLeft();
				break;
			}
		}
		else if (*(uint8*)param == s_ui_data.map_anim_timer)
		{
			DrawMap();
			s_frame_mark = (s_frame_mark + 1)%2;
		}
		else if (*(uint8*)param == s_ui_data.door_anim_timer)
		{
			DisplayAnimDoor(s_ui_data.door_type,s_ui_data.door_anim_pos);
		}
		else if (*(uint8*)param == s_ui_data.dialog_anim_timer)
		{
			DisplayDialog(s_ui_data.dialog_id);
		}
		else if (*(uint8*)param == s_ui_data.enemy_info_timer)
		{
			DisplayEnemyInfo();
		}
		else if (*(uint8*)param == s_ui_data.fight_timer)
		{
			DisplayFight();
		}
		else if (*(uint8*)param == s_ui_data.inst_timer)
		{
			DisplayInstAnim();
		}
		break;
	default:
		recode = MMI_RESULT_FALSE;
		break;
	}

	return recode;
}

WINDOW_TABLE(MMIMT_MAIN_WIN_TAB) = 
{
	WIN_ID(MMIMT_MAIN_WIN_ID),
	WIN_FUNC(HandleMTWinMsg),
	END_WIN,
};

PUBLIC void MMIMT_Open()
{
	MMK_CreateWin(MMIMT_MAIN_WIN_TAB,PNULL);
}