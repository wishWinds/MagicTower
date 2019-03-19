/*****************************************************************************
** File Name:      mainmenu_win.c                                            *
** Author:                                                                   *
** Date:           12/2003                                                   *
** Copyright:      2003 Spreadtrum, Incorporated. All Rights Reserved.       *
** Description:    This file is used to describe call log                    *
*****************************************************************************
**                         Important Edit History                            *
** --------------------------------------------------------------------------*
** DATE           NAME             DESCRIPTION                               *
** 05/2009       Jassmine           Creat
******************************************************************************/

#define MAINMENU_WIN_C

/**--------------------------------------------------------------------------*
 **                         Include Files                                    *
 **--------------------------------------------------------------------------*/
//#include "std_header.h"
#include "window_parse.h"
#include "guitext.h"
#include "mainapp.h"
#include "mmiset.h"
#include "mmistk.h"
#include "mmisms_api.h"
#include "mmicl.h"
#include "mmidc.h"
#include "mmipicview.h"
#include "mmialarm.h"
#include "mmigame.h"
#include "mmiebook.h"
#include "mmicalendar_main.h"
#include "mmirecord.h"
#include "mmiset_wintab.h"
#include "mmienvset_internal.h"
#include "mmiconnection.h"
#include "mmifm_export.h"
#include "mmikur.h"
#include "mmimtv_export.h"
#include "mmiatv_export.h"
#include "mmicountedtime_main.h"
#include "mmiphonesearch.h"
#include "mmigame_menutable.h"
#include "mmigame_link_internal.h"
#include "mmigame_boxman_internal.h"
//#include "mmidyna.h"
#include "mmimenu_data.h"
#include "mmi_appmsg.h"
#include "mmi_menutable.h"
#include "mmi_position.h"
#include "mmidisplay_data.h"
#include "mmitheme_special_func.h"
#include "mmicalc_main.h"
#include "mmiwclk_main.h"
#include "mmiacc_id.h"
#include "mmipub.h"
#include "mmisd_export.h"
#include "mmiudisk_export.h"
#ifdef BROWSER_SUPPORT
#include "mmibrowser_api.h"
#endif
#ifdef DL_SUPPORT
#include "mmidl_export.h"
#endif
#include "mmiphone.h"
#ifdef MMI_ENABLE_DCD
#include "mmidcd_export.h"
#endif
#ifdef CMCC_UI_STYLE
#include "mmics_export.h"
#endif
#ifdef JAVA_SUPPORT
#include "mmijava_export.h"
#endif
#include "mmipim_export.h"
#include "mmiunitconversion.h"

#ifdef QQ_SUPPORT
#include "mmiqq_export.h"
#endif
#ifdef ASP_SUPPORT
#include "mmiasp_api.h"
#endif
#ifdef SEARCH_SUPPORT
#include "mmisearch.h"
#endif
#ifdef VIDEO_PLAYER_SUPPORT
#include "mmivp_export.h"
#endif

#include "mmiconnection_menutable.h"

#ifdef WIFI_SUPPORT
#include "mmiwifi_api.h"
#endif

#ifdef PUSH_EMAIL_SUPPORT   //Added by yuanl  2010.5.10
#include "mmimail.h"
#endif /* PUSH_EMAIL_SUPPORT  */

#ifdef MOBILE_VIDEO_SUPPORT
#include "mmimv_export.h"
#endif

#ifdef  CMCC_UI_STYLE 
//ONLY FOR uplmn SETTING
#include "mmiengtd_win.h"   
#endif

#include "guistatusbar.h"

/**--------------------------------------------------------------------------*
 **                         MACRO DEFINITION                                 *
 **--------------------------------------------------------------------------*/


/**--------------------------------------------------------------------------*
 **                         STATIC DEFINITION                                *
 **--------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/*                          TYPE AND CONSTANT                                */
/*---------------------------------------------------------------------------*/
typedef enum
{
    BROWSER_URL_TYPE_DIANPING,//大众点评网
    BROWSER_URL_TYPE_KAIXIN,//开心农场
    BROWSER_URL_TYPE_CTRIP,//携程网
    BROWSER_URL_TYPE_BAIDU,// 百度	        
    BROWSER_URL_TYPE_SINA_BOLG,//新浪微博
    BROWSER_URL_TYPE_TAOBAO,// 淘宝
    BROWSER_URL_TYPE_YOUKU,//优酷
    BROWSER_URL_TYPE_RENREN,//人人网
    BROWSER_URL_TYPE_QIDIAN,//起点中文网

    BROWSER_URL_TYPE_MAX
}MAINMENU_BROWSER_URL_TYPE_E;

LOCAL const char* const s_mainmenu_browser_url[BROWSER_URL_TYPE_MAX] =
{
    "http://wap.dianping.com",
    "http://wap.kaixin001.com",
    "http://m.ctrip.com",
    "http://wap.baidu.com",
    "http://t.sina.com.cn",
    "http://wap.taobao.com",
    "http://3g.youku.com",
    "http://m.renren.com",
    "http://qidian.cn"
};

/**--------------------------------------------------------------------------*
 **                         EXTERNAL DEFINITION                              *
 **--------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*
 **                         GLOBAL DEFINITION                                *
 **--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                          LOCAL FUNCTION DECLARE                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/
// 	Description : main menu handle window message
//	Global resource dependence : 
//  Author:jassmine.meng
//	Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainMenuWinMsg(
                                        MMI_WIN_ID_T         win_id, 
                                        MMI_MESSAGE_ID_E     msg_id, 
                                        DPARAM               param
                                        );

/*****************************************************************************/
// 	Description : icon main second menu handle window message
//	Global resource dependence : 
//  Author:jassmine.meng
//	Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainSecondMenuWinMsg(
                                              MMI_WIN_ID_T         win_id, 
                                              MMI_MESSAGE_ID_E     msg_id, 
                                              DPARAM               param
                                              );

/*****************************************************************************/
//     Description : to handle the SMS menu option window message
//    Global resource dependence : 
//  Author:liming.deng
//    Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E  HandleMainMenuOptWinMsg(
                                            MMI_WIN_ID_T        win_id, 
                                            MMI_MESSAGE_ID_E    msg_id, 
                                            DPARAM                param
                                            );

/*****************************************************************************/
//     Description : to handle the SMS menu option window message
//    Global resource dependence : 
//  Author:liming.deng
//    Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E  HandleMainMenuMoveOptWinMsg(
                                                MMI_WIN_ID_T        win_id, 
                                                MMI_MESSAGE_ID_E    msg_id, 
                                                DPARAM                param
                                                );

/*****************************************************************************/
//  FUNCTION:     HandleMainMenuHelpWinMsg
//  Description :   handle help win msg
//  Global resource dependence : 
//  Author: xiaoqing.lu
//  Note:   
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainMenuHelpWinMsg( 
                                            MMI_WIN_ID_T win_id, 
                                            MMI_MESSAGE_ID_E msg_id, 
                                            DPARAM param
                                            );
                                            
/*****************************************************************************/
//  FUNCTION:     HandleBrowerUrlMenu
//  Description :   处理主菜单中通过browser 访问url的菜单项
//  Global resource dependence : 
//  Author: fen.xie
//  Note:   
/*****************************************************************************/
LOCAL void HandleBrowerUrlMenu(MAINMENU_BROWSER_URL_TYPE_E browser_url_type);

/**--------------------------------------------------------------------------*
 **                         CONSTANT VARIABLES                               *
 **--------------------------------------------------------------------------*/
//option page main menu window
WINDOW_TABLE(MAINMENU_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_WIN_ID),
    WIN_STATUSBAR,
    CREATE_MENU_CTRL(MENU_MAINMENU, MAINMENUWIN_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

//icon main menu window 
WINDOW_TABLE(MAINMENU_ICON_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_WIN_ID),
#if defined MAINLCD_SIZE_128X64 
    
#else        
    WIN_STATUSBAR,
#endif	
    CREATE_MENU_CTRL(MENU_MAINMENU_ICON, MAINMENUWIN_MENU_CTRL_ID),	
WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),

    END_WIN
};

//others main menu window
WINDOW_TABLE(MAINMENU_OTHERS_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_OTHERS_WIN_ID),
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(MENU_OTHERS, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

//others main menu window
WINDOW_TABLE(MAINMENU_SLIDE_OTHERS_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_OTHERS_WIN_ID),
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(SLIDE_MENU_OTHERS, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

// icon main menu window 
WINDOW_TABLE(MAINMENU_TITLE_ICON_WIN_TAB) = 
{
    //CLEAR_LCD,
    //WIN_PRIO( WIN_ONE_LEVEL ),
    WIN_FUNC((uint32)HandleMainMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_WIN_ID),
    WIN_STATUSBAR,
    CREATE_MENU_CTRL(MENU_MAINMENU_TITLE_ICON, MAINMENUWIN_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

// icon main menu window 
WINDOW_TABLE(MAINMENU_SLIDE_PAGE_WIN_TAB) = 
{
    //CLEAR_LCD,
    //WIN_PRIO( WIN_ONE_LEVEL ),
    WIN_FUNC((uint32)HandleMainMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_WIN_ID),
    WIN_STATUSBAR,
    CREATE_MENU_CTRL(MENU_MAINMENU_SLIDE_PAGE, MAINMENUWIN_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

// icon main menu window 
WINDOW_TABLE(MAINMENU_CUBE_WIN_TAB) =
{
    WIN_FUNC((uint32)HandleMainMenuWinMsg),
    WIN_ID(MAIN_MAINMENU_WIN_ID),
    WIN_STATUSBAR,
    CREATE_MENU_CTRL(MENU_MAINMENU_CUBE, MAINMENUWIN_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

//icon player menu window 
WINDOW_TABLE(MAINMENU_ICON_PLAYER_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_PLAYER_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(MENU_ICON_PLAYER, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

//icon tools main menu window 
WINDOW_TABLE(MAINMENU_ICON_TOOLS_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_TOOLS_WIN_ID),
#ifdef MAINLCD_SIZE_128X64    

#else
    WIN_STATUSBAR,    
    WIN_TITLE(TXT_NULL),
#endif    
    CREATE_MENU_CTRL(MENU_ICON_TOOLS, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    WIN_TIPS,
    END_WIN
};

#ifdef CMCC_UI_STYLE
/*移动服务*/
WINDOW_TABLE(MAINMENU_ICON_SERVICE_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_CMCC_SERVICE_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(MENU_ICON_SERVICE, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    WIN_TIPS,
    END_WIN
};

/*移动梦网*/
WINDOW_TABLE(MAINMENU_ICON_MONERNET_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_CMCC_MONERNET_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    //CREATE_MENU_CTRL(MENU_ICON_MONERNET, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    WIN_TIPS,
    END_WIN
};

/*我的收藏*/
WINDOW_TABLE(MAINMENU_ICON_MYFAVORITE_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_MY_FAVORITE_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(MENU_ICON_MY_FAVORITE, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    WIN_TIPS,
    END_WIN
};

/* 应用*/
WINDOW_TABLE(MAINMENU_ICON_APPS_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_APP_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(MENU_ICON_APPS, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    WIN_TIPS,
    END_WIN
};

#endif //CMCC_UI_STYLE
//icon pastime main menu window 
WINDOW_TABLE(MAINMENU_ICON_PASTIME_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),    
    WIN_ID(MAIN_MAINMENU_PASTIME_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(MENU_ICON_PASTIME, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

//icon settings main menu window 
WINDOW_TABLE(MAINMENU_ICON_SETTINGS_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),
    WIN_ID(MAIN_MAINMENU_SETTINGS_WIN_ID),
#ifdef MAINLCD_SIZE_128X64    

#else
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
#endif    
    CREATE_MENU_CTRL(MENU_SETTINGS_ICON, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

//icon settings main menu window 
WINDOW_TABLE(MAINMENU_SLIDE_ICON_SETTINGS_WIN_TAB) = 
{
    WIN_FUNC((uint32)HandleMainSecondMenuWinMsg),
    WIN_ID(MAIN_MAINMENU_SETTINGS_WIN_ID),
    WIN_STATUSBAR,
    WIN_TITLE(TXT_NULL),
    CREATE_MENU_CTRL(SLIDE_MENU_SETTINGS_ICON, MAINMENUWIN_SECOND_MENU_CTRL_ID),
	WIN_SOFTKEY(STXT_OK, TXT_NULL, STXT_RETURN),
    END_WIN
};

WINDOW_TABLE( MAINMENU_OPTMENU_WIN_TAB ) = 
{
    WIN_FUNC( (uint32)HandleMainMenuOptWinMsg),
    WIN_ID(MAIN_MAINMENU_OPT_WIN_ID),
    WIN_STYLE( WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_MAINMENU_OPT,MAIN_MAINMENU_OPT_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

WINDOW_TABLE( MAINMENU_MOVEOPTMENU_WIN_TAB ) = 
{
    WIN_FUNC( (uint32)HandleMainMenuMoveOptWinMsg),
    WIN_ID(MAIN_MAINMENU_MOVEOPT_WIN_ID),
    WIN_STYLE( WS_HAS_TRANSPARENT),
    CREATE_POPMENU_CTRL(MENU_MAINMENU_MOVE_OPT,MAIN_MAINMENU_MOVEOPT_CTRL_ID),
    WIN_SOFTKEY(STXT_OK,TXT_NULL,STXT_RETURN),
    END_WIN
};

WINDOW_TABLE( MAINMENU_HELP_WIN_TAB ) = 
{
    WIN_FUNC((uint32) HandleMainMenuHelpWinMsg ),    
    WIN_ID( MAIN_MAINMENU_HELP_WIN_ID ),
    WIN_TITLE(TXT_HELP),
    CREATE_TEXT_CTRL(MAIN_MAINMENU_HELP_CTRL_ID),
    WIN_SOFTKEY(TXT_NULL,TXT_NULL,STXT_RETURN),
    END_WIN
}; 


/**--------------------------------------------------------------------------*
 **                         FUNCTION DEFINITION                              *
 **--------------------------------------------------------------------------*/
/*****************************************************************************/
// 	Description : creat main menu
//	Global resource dependence : 
//  Author:jassmine.meng
//	Note: 
/*****************************************************************************/
PUBLIC void MMIAPIMENU_CreatMainMenu(void)
{
    GUIMENU_STYLE_E    menu_style = GUIMENU_STYLE_NULL;
    
    //get main menu style
    menu_style = MMIAPISET_GetMainmenuStyle();
    
    switch (menu_style)
    {
    case GUIMENU_STYLE_ICON:
        //set special effect
        MMITHEME_SetSpecialEffectDirty(MMITHEME_SPECIAL_MAINMENU);    
        
        //creat
        MMK_CreateWin((uint32*)MAINMENU_ICON_WIN_TAB, PNULL);
        break;  
        
    case GUIMENU_STYLE_OPTION_PAGE:
        MMK_CreateWin((uint32*)MAINMENU_WIN_TAB, PNULL);
        
        //主菜单进入时，设置选中当中的菜单项
        GUIMENU_SetFirstAndSelectedItem(0,
            MMIMENU_MAIN_OPTION_PAGE_DEFAULT_SEL,
            MAINMENUWIN_MENU_CTRL_ID);
        break;
        
    case GUIMENU_STYLE_TITLE_ICON:
        MMK_CreateWin((uint32*)MAINMENU_TITLE_ICON_WIN_TAB, PNULL);
        break;
        
    case GUIMENU_STYLE_SLIDE_PAGE:
        MMK_CreateWin((uint32*)MAINMENU_SLIDE_PAGE_WIN_TAB, PNULL);
        break;

    case GUIMENU_STYLE_CUBE:
        MMK_CreateWin((uint32*)MAINMENU_CUBE_WIN_TAB, PNULL);
        break;

    default:
        SCI_PASSERT(FALSE,("MMIAPIMENU_CreatMainMenu:menu style %d is error!",menu_style));
        break;
    }
}

/*****************************************************************************/
// 	Description : close main menu
//	Global resource dependence : 
//  Author:
//	Note: 
/*****************************************************************************/
PUBLIC void MMIAPIMENU_UpdateMainMenu(void)
{
	if(MMK_IsFocusWin(MAIN_MAINMENU_WIN_ID))
	{
		MMK_CloseWin(MAIN_MAINMENU_WIN_ID);
		MMIAPIMENU_CreatMainMenu();
	}
}
/*****************************************************************************/
// 	Description : main menu handle window message
//	Global resource dependence : 
//  Author:jassmine.meng
//	Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainMenuWinMsg(
                                        MMI_WIN_ID_T         win_id, 
                                        MMI_MESSAGE_ID_E     msg_id, 
                                        DPARAM               param
                                        )
{
    BOOLEAN                             is_menu_gray = TRUE;
    GUI_BG_T                            softkey_bg = {0};
    MMI_RESULT_E                        result = MMI_RESULT_TRUE;
    MMI_CTRL_ID_T                       ctrl_id = MAINMENUWIN_MENU_CTRL_ID;
    MMI_MENU_ID_T		                menu_id = 0;
    MMI_MENU_GROUP_ID_T	                group_id = 0;
   //  MMISET_DUALSYS_TYPE_E               e_dualsys_setting = MMISET_DAULSYS_ONLY_SIM1_ON;
    MMISET_VALIDATE_PRIVACY_RETURN_T    *result_info_ptr = PNULL;
	
    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
        if (MMIAPISTK_GetStkCardNum(PNULL, 0) > 0)
        {
            is_menu_gray = FALSE;
        }
        else
        {
            is_menu_gray = TRUE;
        }

#ifdef MAINLCD_SIZE_320X480
        MMIAPICOM_EnableGrayed(win_id, MENU_SLIDE_TOOLS, ID_COMMUNICATION_STK, is_menu_gray);
#else
        MMIAPICOM_EnableGrayed(win_id, MENU_SLIDE_COMMUNICATION, ID_COMMUNICATION_STK, is_menu_gray);
#endif
        MMIAPICOM_EnableGrayed(win_id, MENU_COMMUNICATION, ID_COMMUNICATION_STK, is_menu_gray);

        if (MMIAPISET_GetMultiSysSettingNum(PNULL, 0) > 1)
        {
            is_menu_gray = FALSE;
        }
        else
        {
            is_menu_gray = TRUE;
        }

        MMIAPICOM_EnableGrayed(win_id, MENU_SLIDE_TOOLS, ID_CONNECTION_GPRS, is_menu_gray);

        //set status bar
        MAIN_SetAllStbAppCallbackValid(TRUE);
        MMK_SetAtvCtrl(win_id, ctrl_id);
        GUIWIN_SetStbBgImageId(win_id, IMAGE_THEME_BG);
        GUIWIN_SetStbState(win_id, GUISTATUSBAR_STATE_EVENT, TRUE);

        //set softkey bg
        softkey_bg.bg_type = GUI_BG_IMG;
        softkey_bg.img_id  = IMAGE_THEME_BG;
        GUIWIN_SetSoftkeyCommonBg(win_id,&softkey_bg);
        break;

    case MSG_GET_FOCUS:
        MAIN_SetAllStbAppCallbackValid(TRUE);
        break;

    case MSG_NOTIFY_MENU_SET_STATUS:
        if (*(GUIMENU_MOVE_STATE_T*)param == GUIMENU_STATE_MOVE_SET)
        {
            GUIMENU_SetMenuMoveState(MAINMENUWIN_MENU_CTRL_ID, TRUE);
        }
        else if (*(GUIMENU_MOVE_STATE_T*)param == GUIMENU_STATE_MOVE_CANCEL)
        {
            GUIMENU_CancelMoveIcon(MAINMENUWIN_MENU_CTRL_ID);
        }
        else
        {
            result = MMI_RESULT_FALSE;
        }
        break;

    case MSG_LOSE_FOCUS:
        MAIN_SetAllStbAppCallbackValid(FALSE);
        break;

    case MSG_CTL_OK:
#ifdef TOUCH_PANEL_SUPPORT 
//         if (GUIMENU_IsMoveState(MAINMENUWIN_MENU_CTRL_ID))
//         {
//             SCI_TRACE_LOW("Create MAINMENU_MOVEOPTMENU_WIN_TAB!");
//             MMK_CreateWin((uint32*)MAINMENU_MOVEOPTMENU_WIN_TAB, PNULL);
//         }
//         else
//         {
//             SCI_TRACE_LOW("Create MAINMENU_OPTMENU_WIN_TAB!");
//             MMK_CreateWin((uint32*)MAINMENU_OPTMENU_WIN_TAB, PNULL);
//         }
//         break;
#endif
    case MSG_CTL_MIDSK:
    case MSG_CTL_PENOK:
        GUIMENU_GetId(ctrl_id, &group_id, &menu_id);
        switch (menu_id)
        {
        case ID_COMMUNICATION_DIAL:
            MMIIDLE_OpenDialWin(0,FALSE);
            break;
            
        case ID_COMMUNICATION_MESSAGE:
            MMIAPISMS_OpenMessageMainMenuWin();
            break;
            
        case ID_COMMUNICATION_BROWSER:
#ifdef BROWSER_SUPPORT
            {
                MMIBROWSER_ENTRY_PARAM entry_param = {0};
                
                entry_param.type = MMIBROWSER_ACCESS_MAINMENU;
                entry_param.dual_sys = MN_DUAL_SYS_MAX;
                entry_param.url_ptr = PNULL;
                entry_param.user_agent_ptr = PNULL;
                
                MMIBROWSER_Entry(&entry_param);
            }
#endif
            break;
            
        case ID_COMMUNICATION_CL:
            
            MMIAPICL_OpenMainMenuWindow();
            
            break;
            
        case ID_COMMUNICATION_PB:
            MMIAPIPB_OpenListAllGroupWin();
            break;
            
        case ID_COMMUNICATION_STK:            
            {
                uint16 sim_sys = MN_DUAL_SYS_1;
                uint32 sim_num = 0;

                if (MMIAPISET_GetFlyMode())
                {
                    MMIPHONE_AlertSimNorOKStatus();
                    break;
                }

                sim_num = MMIAPISTK_GetStkCardNum(&sim_sys, 1);
                if (sim_num == 0)
                {
                    MMIPHONE_AlertSimNorOKStatus();
                }
                else if (sim_num == 1)
                {
                    MMIAPISTK_EnterToplevelMenu((MN_DUAL_SYS_E)sim_sys);
                }
#ifndef MMI_MULTI_SIM_SYS_SINGLE
                else
                {
                    MMK_CreateWin((uint32*)MMISTK_SELECT_SIM_WIN_TAB, PNULL);
                }
#endif
            }
            break;
#ifdef  CAMERA_SUPPORT
        case ID_ENTERTAIMENT_CAMERA:
            if (MMIAPISET_IsOpenPrivacyProtect(MMISET_PROTECT_CAMER))
            {
                //validate privacy password
                MMIAPISET_ValidatePrivacyPwd(win_id,MMISET_PROTECT_CAMER_TYPE);
            }
            else
            {
                MMIAPIDC_OpenPhotoWin();	
            }
            break;
#endif
        case ID_ENTERTAIMENT_PLAYER:
            MMIAPIMP3_OpenPlayerMenuWin();
            break;
            
        case ID_PIC_VIEWER:
            MMIAPIPICVIEW_OpenPicViewer();
            break;
            
#ifdef GAME_SUPPORT
        case ID_ENTERTAIMENT_GAME:
            MMIAPIGAME_OpenMainMenuWindow();
            break;
#endif
            
        case ID_EBOOK:
            if( MMIAPISET_IsOpenPrivacyProtect(MMISET_PROTECT_EBOOK) )
            {
                MMIAPISET_ValidatePrivacyPwd( win_id,MMISET_PROTECT_EBOOK_TYPE );
            }
            else
            {
                MMIAPIEBOOK_ManagerWinMsg();
            }
            break;
#ifdef JAVA_SUPPORT            
        case ID_ENTERTAIMENT_GOLDHOUSE:
            MMIAPIJAVA_OpenMainMenu();
            break;
#endif
#ifdef GPS_SUPPORT
        case ID_CONNECTION_GPS:
            MMIAPIGPS_OpenMainWin();
            break;
#endif
            
        case ID_TOOLS_ALARM:
            MMIALM_OpenMainWin();
            break;
			
#ifdef ASP_SUPPORT
      case ID_TOOLS_ASP:
	    MMIAPIASP_EnterAsp();
	    //MMIASP_StartApplet(MMIASP_START_DEFAULT);
        break;
#endif
            
#ifdef  DCD_SUPPORT
        case ID_TOOLS_DCD:
            MMIAPIDCD_OpenMainWin();
            break;
#endif //DCD_SUPPORT
        case ID_TOOLS_CALENDAR:
            if(MMIAPISET_IsOpenPrivacyProtect(MMISET_PROTECT_CALENDAR))
            {
                MMIAPISET_ValidatePrivacyPwd(win_id,MMISET_PROTECT_CALENDAR_TYPE);
            }
            else
            {
                MMICALEND_OpenMainWin();
            }
            break;
            
        case ID_TOOLS_RECORD:
            MMIAPIRECORD_OpenMainWin();
            break;
            
        case ID_MAINMENU_PIM:
            MMIAPIPIM_Main(0);
            break;
            
#ifdef SEARCH_SUPPORT
        case ID_MAINMENU_SEARCH:
            MMIAPISearch_OpenMainWin();
            break;
#endif
            
        case ID_TOOLS_CALCULATOR:
            MMIAPICALC_OpenMainWin();
            break;
        case ID_TOOLS_UNIT_CONVERSION:
            MMIAPIUNITCONV_OpenMainWin();
            break;
            
        case ID_ENTERTAIMENT_FAVORITE:
#ifdef CMCC_UI_STYLE 			
            MMK_CreateWin((uint32 *)MAINMENU_ICON_MYFAVORITE_WIN_TAB,PNULL);
#else
            MMIAPIFMM_OpenExplorer();
#endif
            break;
            
        case ID_TOOLS_OTHERS:
            MMK_CreateWin((uint32 *)MAINMENU_OTHERS_WIN_TAB,PNULL);
            break;
            
        case ID_MAINMENU_SLIDE_TOOLS_OTHERS:
            MMK_CreateWin((uint32 *)MAINMENU_SLIDE_OTHERS_WIN_TAB,PNULL);
            break;

        case ID_MAINMENU_SLIDE_SETTINGS:
            MMK_CreateWin((uint32 *)MAINMENU_SLIDE_ICON_SETTINGS_WIN_TAB,PNULL);
            break;
            
        case ID_SETTINGS_CALL:
            MMISET_OpenCallSettingsWindow();
            break;
            
        case ID_SETTINGS_PHONE:
            MMISET_EnterPhoneSettingWin();
            break;
            
        case ID_SETTINGS_DISPLAY:
            MMISET_EnterDisplaySettingWin();
            break;
            
        case ID_SETTINGS_SECURITY:
            MMISET_EnterSecuritySettingWin();
            break;
            
        case ID_SETTINGS_ENVIONMENT:
            MMIENVSET_OpenMainMenuWindow();
            break;
            
        case ID_SETTINGS_LINK:
            MMIConnection_OpenMenuWin();
            break;
            
        case ID_MAINMENU_PLAYER:
            MMK_CreateWin((uint32 *)MAINMENU_ICON_PLAYER_WIN_TAB,PNULL);
            break;
            
#ifdef CMMB_SUPPORT
        case ID_ENTERTAIMENT_MTV:
            MMIAPIMTV_OpenMTVPlayer();
            break;
#endif
#ifdef ATV_SUPPORT
        case ID_ENTERTAIMENT_ATV:
            MMIAPIATV_OpenATV();
            break;
#endif

#ifdef FM_SUPPORT
        case ID_ENTERTAIMENT_FM:
            MMIAPIFM_OpenMainWin();
            break;
#endif
            
#ifdef CMCC_UI_STYLE
        case ID_MAINMENU_CMCC_MONERNET:	   	
            MMISET_EnterMonternetWin();
            break;
            
        case ID_MAINMENU_CMCC_SERVICE:
            MMK_CreateWin((uint32 *)MAINMENU_ICON_SERVICE_WIN_TAB,PNULL);	   	
            
            break;
        case ID_CUSTMER_SERVICE:
            MMIAPICS_OpenMainWin();
            break;
        case ID_MAINMENU_APPS:			
            MMK_CreateWin((uint32 *)MAINMENU_ICON_APPS_WIN_TAB,PNULL);
            break;			  
        case ID_NET_FETION:
            MMISET_EnterFetionWin();
            break;
            
        case ID_NET_MUSIC:
            MMISET_EnterMusicWin();
            break;
        case ID_ENTERTAIMENT_PIC:
#ifdef CMCC_UI_STYLE
            MMIAPIPICVIEW_OpenPicViewerExt(MMIPICVIEW_DOWNLOAD_PIC);
#else
            MMIAPIPICVIEW_OpenPicViewer();
#endif
            break;
        case ID_APPS_BT:
            MMIAPIBT_OpenMainMenuWin();	
            break;
#ifdef JAVA_SUPPORT
        case ID_JAVA_APP:
            MMIAPIJAVA_OpenMainMenu();
            break;
#endif

#ifdef CMMB_SUPPORT
        case ID_APPS_MBBMS:
            MMIAPIMTV_OpenMTVPlayer();
            break;
#endif
        case ID_CHINAMOBILE_SECURITIES:
            MMISET_EnterStockWin();
            break;
        case ID_CHINAMOBILE_MAP:
            MMISET_EnterMapWin();
            break;
            
        case ID_SETTINGS_VERSION:
            MMIAPIENG_CreateShowVersionWin();
            break;
#endif //CMCC_UI_STYLE
        case ID_MAINMENU_TOOLS:
            MMK_CreateWin((uint32 *)MAINMENU_ICON_TOOLS_WIN_TAB,PNULL);
            break;
            
        case ID_MAINMENU_PASTIME:
            MMK_CreateWin((uint32 *)MAINMENU_ICON_PASTIME_WIN_TAB,PNULL);
            break;
            
        case ID_MAINMENU_SETTINGS:
            MMK_CreateWin((uint32 *)MAINMENU_ICON_SETTINGS_WIN_TAB,PNULL);
            break;
            
#ifdef QQ_SUPPORT
        case ID_SPREADTRUM_QQ_SUPPORT:
            MMIAPIQQ_OpenMainWin();
            break;
#endif
        case ID_ENTERTAIMENT_MP3:
            MMIAPIMP3_OpenMp3Player();
            break;
            
        case ID_ENTERTAIMENT_VIDEO:
#ifdef VIDEO_PLAYER_SUPPORT
            MMIAPIVP_MainEntry();
#endif
            break;      

        case ID_ENTERTAIMENT_MOBILE_VIDEO:
#ifdef MOBILE_VIDEO_SUPPORT
            MMIAPIMV_Entry();
#endif
            break;


        case ID_MAINMENU_BT:
			MMIAPIBT_OpenMainMenuWin();			
			break;

        case ID_COUNTDOWN:
            if (MMIAPICT_IsShowIdleCoutime())
			{
				MMIAPICT_OpenCoutimeRunningWin();
			}
			else
			{
				MMIAPICT_OpenCoutimeWin();
			}
            break;
#ifdef HOME_LOCATION_INQUIRE_SUPPORT
        case ID_PHONESEARCH:
            MMIAPIPHONESEARCH_OpenWnd();
            break;
#endif

#ifdef WIFI_SUPPORT
        case ID_CONNECTION_WIFI:
            MMIAPIWIFI_OpenMainWin();
            break;
#endif
#ifdef GPRS_SUPPORT
        case ID_CONNECTION_NET_USERID:  
            MMICONNECTION_OpenSettingListWin();
            break;

        case ID_CONNECTION_GPRS:
            MMICONNECTION_OpenGprsWin();
            break;
#endif
        case ID_WORLDTIME:
            MMIAPIWCLK_OpenMainWin();
            break;
#ifdef PUSH_EMAIL_SUPPORT   //Added by yuanl  2010.5.7
        case ID_MAINMENU_PUSHMAIL:
            MMIAPIMAIL_Enter(MAIL_ENTER_MAINMENU, PNULL);
            break;
#endif /* PUSH_EMAIL_SUPPORT  */

        case ID_MAINMENU_DIANPING:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_DIANPING);
            break;
        case ID_MAINMENU_KAIXIN:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_KAIXIN);
            break;
#ifdef MAGIC_TOWER_SUPPORT
		case ID_MAINMENU_MAGIC_TOWER:
			MMIMT_Open();
			break;
#endif
        case ID_MAINMENU_CTRIP:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_CTRIP);
            break;
        case ID_MAINMENU_BAIDU:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_BAIDU);
            break;
        case ID_MAINMENU_SINA_BOLG:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_SINA_BOLG);
            break;
        case ID_MAINMENU_TAOBAO:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_TAOBAO);
            break;
        case ID_MAINMENU_YOUKU:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_YOUKU);
            break;
        case ID_MAINMENU_RENREN:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_RENREN);
            break;
        case ID_MAINMENU_QIDIAN:
            HandleBrowerUrlMenu(BROWSER_URL_TYPE_QIDIAN);
            break;

#ifdef QQ_SUPPORT
        case ID_MAINMENU_QQ:
            MMIAPIQQ_OpenMainWin();
            break;
#endif
            
#ifdef MV_SUPPORT
        case ID_MAINMENU_MAGIC_VOICE:
            MMIAPISET_OpenMagicVoiceWin();
            break;
#endif
            
        default:
            break;
        }
        break;
        
    case MSG_CTL_CANCEL:
        MMK_CloseWin(win_id);
        break;
        
    case MSG_SET_VALIDATE_PRIVACY_PWD_RETURN:
        result_info_ptr = (MMISET_VALIDATE_PRIVACY_RETURN_T *)param;
        SCI_ASSERT(PNULL != result_info_ptr);
        
        if (result_info_ptr->is_validate_sucess)
        {
            switch (result_info_ptr->protect_type)
            {
#ifdef  CAMERA_SUPPORT            
            case MMISET_PROTECT_CAMER_TYPE:
                MMIAPIDC_OpenPhotoWin();
                break;
#endif
            case MMISET_PROTECT_EBOOK_TYPE:
                MMIAPIEBOOK_ManagerWinMsg();
                break;

            case MMISET_PROTECT_CALENDAR_TYPE:
                MMICALEND_OpenMainWin();
                break;

            default:
                SCI_TRACE_LOW("HandleMainMenuWinMsg:protect type %d is error!",result_info_ptr->protect_type);
                break;
            }
        }
        break;
    default:
        result = MMI_RESULT_FALSE;
        break;
    }

    return (result);
}

/*****************************************************************************/
// 	Description : icon main second menu handle window message
//	Global resource dependence : 
//  Author:jassmine.meng
//	Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainSecondMenuWinMsg(
                                              MMI_WIN_ID_T         win_id, 
                                              MMI_MESSAGE_ID_E     msg_id, 
                                              DPARAM               param
                                              )
{
    BOOLEAN								is_menu_gray = TRUE;
    MMI_RESULT_E                        result = MMI_RESULT_TRUE;
    MMI_CTRL_ID_T                       ctrl_id = MAINMENUWIN_SECOND_MENU_CTRL_ID;
    MMI_MENU_ID_T	                    menu_id = 0;
    MMI_MENU_GROUP_ID_T	                group_id = 0;
    // MMISET_DUALSYS_TYPE_E               e_dualsys_setting = MMISET_DAULSYS_ONLY_SIM1_ON;
    MMISET_VALIDATE_PRIVACY_RETURN_T    *result_info_ptr = PNULL;
	
    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
        if (MMIAPISTK_GetStkCardNum(PNULL, 0) > 0)
        {
            is_menu_gray = FALSE;
        }
        else
        {
            is_menu_gray = TRUE;
        }

#ifdef CMCC_UI_STYLE
        GUIMENU_SetItemGrayed(MAINMENUWIN_SECOND_MENU_CTRL_ID, MENU_ICON_SERVICE,ID_COMMUNICATION_STK,is_menu_gray);
#else
        GUIMENU_SetItemGrayed(MAINMENUWIN_SECOND_MENU_CTRL_ID,MENU_ICON_TOOLS,ID_COMMUNICATION_STK,is_menu_gray);
#endif
        MMK_SetAtvCtrl(win_id,ctrl_id);
        break;

    case MSG_CTL_OK:
    case MSG_CTL_MIDSK:
    case MSG_CTL_PENOK:
        GUIMENU_GetId(ctrl_id, &group_id, &menu_id);
        switch (menu_id)
        {
#ifdef  CAMERA_SUPPORT
        case ID_ENTERTAIMENT_CAMERA:
            if (MMIAPISET_IsOpenPrivacyProtect(MMISET_PROTECT_CAMER))
			{
				//validate privacy password
				MMIAPISET_ValidatePrivacyPwd( win_id, MMISET_PROTECT_CAMER_TYPE );
			}
            else
            {
                MMIAPIDC_OpenPhotoWin();
            }
            break;
#endif
        case ID_ENTERTAIMENT_MP3:
            MMIAPIMP3_OpenMp3Player();
            break;

        case ID_ENTERTAIMENT_VIDEO:
#ifdef VIDEO_PLAYER_SUPPORT
            MMIAPIVP_MainEntry();
#endif
            break;

        case ID_ENTERTAIMENT_MOBILE_VIDEO:
#ifdef MOBILE_VIDEO_SUPPORT
            MMIAPIMV_Entry();
#endif
            break;

#ifdef SEARCH_SUPPORT
        case ID_MAINMENU_SEARCH:
             MMIAPISearch_OpenMainWin();
             break;
#endif

#ifdef FM_SUPPORT
        case ID_ENTERTAIMENT_FM:
            MMIAPIFM_OpenMainWin();
            break;
#endif

#ifdef STREAMING_SUPPORT_NEXTREAMING
        case ID_ENTERTAIMENT_ST:
            MMIAPIST_SetFromNet(FALSE);
			MMIAPIST_OpenPlayWin();
            break;
#endif

#ifdef KURO_SUPPORT
        case ID_ENTERTAIMENT_KUR:
            MMIAPIKUR_OpenKurPlayer();
            break;
#endif

#ifdef GPS_SUPPORT
        case ID_CONNECTION_GPS:
            MMIAPIGPS_OpenMainWin();
            break;
#endif

#ifdef CMMB_SUPPORT
        case ID_ENTERTAIMENT_MTV:
            MMIAPIMTV_OpenMTVPlayer();
            break;
#endif

#ifdef ATV_SUPPORT
        case ID_ENTERTAIMENT_ATV:
            MMIAPIATV_OpenATV();
            break;
#endif
            
        case ID_WORLDTIME:
            MMIAPIWCLK_OpenMainWin();
            break;

        case ID_COUNTDOWN:
            if (MMIAPICT_IsShowIdleCoutime())
			{
				MMIAPICT_OpenCoutimeRunningWin();
			}
			else
			{
				MMIAPICT_OpenCoutimeWin();
			}
            break;

#ifdef HOME_LOCATION_INQUIRE_SUPPORT
        case ID_PHONESEARCH:
            MMIAPIPHONESEARCH_OpenWnd();
            break;
#endif

#ifdef DYNAMIC_MODULE_SUPPORT
        case ID_DYNAPP:
            MMIDYNA_OpenMainListWindow();
            break;
#endif

        case ID_COMMUNICATION_CL:
            MMIAPICL_OpenMainMenuWindow();
            break;
			
#ifdef ASP_SUPPORT
        case ID_TOOLS_ASP:
	     MMIAPIASP_EnterAsp();
	     //MMIASP_StartApplet(MMIASP_START_DEFAULT);
        break;
#endif

        case ID_TOOLS_ALARM:
            MMIALM_OpenMainWin();
            break;

        case ID_TOOLS_CALENDAR:
            if(MMIAPISET_IsOpenPrivacyProtect(MMISET_PROTECT_CALENDAR))
            {
                MMIAPISET_ValidatePrivacyPwd( win_id, MMISET_PROTECT_CALENDAR_TYPE );
            }
            else
            {
                MMICALEND_OpenMainWin();
            }
            break;

        case ID_TOOLS_CALCULATOR:
            MMIAPICALC_OpenMainWin();
            break;
	case ID_TOOLS_UNIT_CONVERSION:
            MMIAPIUNITCONV_OpenMainWin();
            break;
            

       case ID_MAINMENU_PIM:
        	MMIAPIPIM_Main(0);
        break;
        
        case ID_TOOLS_RECORD:
            MMIAPIRECORD_OpenMainWin();
            break;

        case ID_COMMUNICATION_STK:
            {
                uint16 sim_sys = MN_DUAL_SYS_1;
                uint32 sim_num = 0;

                if (MMIAPISET_GetFlyMode())
                {
                    MMIPHONE_AlertSimNorOKStatus();
                    break;
                }

                sim_num = MMIAPISTK_GetStkCardNum(&sim_sys, 1);
                if (sim_num == 0)
                {
                    MMIPHONE_AlertSimNorOKStatus();
                }
                else if (sim_num == 1)
                {
                    MMIAPISTK_EnterToplevelMenu((MN_DUAL_SYS_E)sim_sys);
                }
#ifndef MMI_MULTI_SIM_SYS_SINGLE
                else
                {
                    MMK_CreateWin((uint32*)MMISTK_SELECT_SIM_WIN_TAB, PNULL);
                }
#endif
            }
            break;

        case ID_DOWNLOAD_MANAGER:
#ifdef DL_SUPPORT
            MMIAPIDL_StartDownload(MMIDL_OPEN_DOWNLOAD_MANAGER, PNULL);
#endif
            break;

        case ID_PIC_VIEWER:
            MMIAPIPICVIEW_OpenPicViewer();
            break;
#ifdef JAVA_SUPPORT
        case ID_ENTERTAIMENT_GOLDHOUSE:
            MMIAPIJAVA_OpenMainMenu();
            break;
#endif
        case ID_EBOOK:
            if( MMIAPISET_IsOpenPrivacyProtect(MMISET_PROTECT_EBOOK) )
            {
                MMIAPISET_ValidatePrivacyPwd( win_id,MMISET_PROTECT_EBOOK_TYPE );
            }
            else
            {
                MMIAPIEBOOK_ManagerWinMsg();
            }
            break;
#ifdef MMI_ENABLE_DCD            
       case ID_DCD_OPEN:	   	
            {
                MMIAPIDCD_OpenMainWin();
            }			
	     break;
#endif				

#ifdef CMCC_UI_STYLE
        case ID_EXPLORE:
			MMIAPIFMM_OpenExplorer();
			break;

        case ID_COMMUNICATION_BROWSER:
#ifdef BROWSER_SUPPORT
            {
                MMIBROWSER_ENTRY_PARAM entry_param = {0};

                entry_param.type = MMIBROWSER_ACCESS_MAINMENU;
                entry_param.dual_sys = MN_DUAL_SYS_MAX;
                entry_param.url_ptr = PNULL;
                entry_param.user_agent_ptr = PNULL;
                
                MMIBROWSER_Entry(&entry_param);
            }
#endif
            break;

        case ID_BLUETOOTH:
			MMIAPIBT_OpenMainMenuWin();			
			break;

         case ID_CUSTMER_SERVICE:
			MMIAPICS_OpenMainWin();		 	
			break;

         case ID_NET_MUSIC:
		 	MMISET_EnterMusicWin();
		 	break;
         case ID_NET_FETION:
		 	MMISET_EnterFetionWin();
		 	break;
         case  ID_CHINAMOBILE_MAP:
		 	MMISET_EnterMapWin();
		 	break;

#ifdef GAME_SUPPORT
        case ID_ENTERTAIMENT_GAME:
            MMIAPIGAME_OpenMainMenuWindow();
            break;
#endif

         case ID_JAVA_STOCK:
                   MMISET_EnterStockWin();		 	
		 	break;
#endif 
#ifdef GAME_LINK_SUPPORT
        case IDGAME_MENU_LINK_ITEM_ID:
            MMIGMLINK_OpenGameWin();
            break;
#endif

#ifdef GAME_BOXMAN_SUPPORT
        case IDGAME_MENU_BOXMAN_ITEM_ID:
            MMIGMBOXMAN_OpenGameWin();
            break;
#endif

        case ID_SETTINGS_CALL:
            MMISET_OpenCallSettingsWindow();
            break;

        case ID_SETTINGS_PHONE:
            MMISET_EnterPhoneSettingWin();
            break;

        case ID_SETTINGS_DISPLAY:
            MMISET_EnterDisplaySettingWin();
            break;

        case ID_SETTINGS_SECURITY:
            MMISET_EnterSecuritySettingWin();
            break;

        case ID_SETTINGS_ENVIONMENT:
            MMIENVSET_OpenMainMenuWindow();
            break;
            
        case ID_SETTINGS_LINK:
            MMIConnection_OpenMenuWin();
            break;
            
#ifdef  CMCC_UI_STYLE 
        case ID_SETTINGS_UPLMN:
             MMIENGTD_OpenUPLMNSettingWin();
             break;
#endif

#ifdef CMCC_UI_STYLE
#ifdef JAVA_SUPPORT
        case ID_FAVORITE_GOLDENHOUSE:
            MMIAPIJAVA_OpenMainMenu();
            break;
#endif
        case ID_FAVORITE_RING:
            MMIAPIFMM_OpenMusicFileList();
            break;
        case ID_FAVORITE_PIC:
            MMIAPIPICVIEW_OpenPicViewerExt(MMIPICVIEW_DOWNLOAD_PIC);
            break;
        case ID_FAVORITE_PHOTO:
            MMIAPIPICVIEW_OpenPicViewer();
            break;
         case ID_FAVORITE_VIDEO://xuefangjiang add 20101102
            MMIAPIFMM_OpenMovieFileList();
            break;
         case ID_SETTINGS_VERSION:
            MMIAPIENG_CreateShowVersionWin();
            break;
#endif

#ifdef QQ_SUPPORT
        case ID_SPREADTRUM_QQ_SUPPORT:
            MMIAPIQQ_OpenMainWin();
            break;
#endif

#ifdef PUSH_EMAIL_SUPPORT   //Added by yuanl  2010.5.7
        case ID_MAINMENU_PUSHMAIL:
            MMIAPIMAIL_Enter(MAIL_ENTER_MAINMENU, PNULL);
            break;
#endif /* PUSH_EMAIL_SUPPORT  */

        default:
            break;
        }
        break;

    case MSG_CTL_CANCEL:
        MMK_CloseWin(win_id);
        break;

    case MSG_SET_VALIDATE_PRIVACY_PWD_RETURN:
        result_info_ptr = (MMISET_VALIDATE_PRIVACY_RETURN_T *)param;
        SCI_ASSERT(PNULL != result_info_ptr);

        if (result_info_ptr->is_validate_sucess)
        {
            switch (result_info_ptr->protect_type)
            {
#ifdef  CAMERA_SUPPORT            
            case MMISET_PROTECT_CAMER_TYPE:
                MMIAPIDC_OpenPhotoWin();
                break;
#endif
            case MMISET_PROTECT_CALENDAR_TYPE:
                MMICALEND_OpenMainWin();
                break;

            case MMISET_PROTECT_EBOOK_TYPE:
                MMIAPIEBOOK_ManagerWinMsg();
                break;

            default:
                SCI_TRACE_LOW("HandleMainSecondMenuWinMsg:protect type %d is error!",result_info_ptr->protect_type);
                break;
            }
        }
        break;
        
    default:
        result = MMI_RESULT_FALSE;
        break;
    }

    return (result);
}

/*****************************************************************************/
//     Description : HandleMainMenuOptWinMsg
//    Global resource dependence : 
//  Author:xiaoqing.lu
//    Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E  HandleMainMenuOptWinMsg(
                                            MMI_WIN_ID_T        win_id, 
                                            MMI_MESSAGE_ID_E    msg_id, 
                                            DPARAM                param
                                            )
{
    MMI_RESULT_E recode = MMI_RESULT_TRUE;
    MMI_MENU_GROUP_ID_T group_id = 0;
    MMI_MENU_ID_T menu_id = 0;
    GUIMENU_MOVE_STATE_T move_state = GUIMENU_STATE_MOVE_NONE;

    SCI_TRACE_LOW("HandleMainMenuOptWinMsg msg_id = %d", msg_id);

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
        MMK_SetAtvCtrl(win_id, MAIN_MAINMENU_OPT_CTRL_ID);
        break;
        
    case MSG_CTL_PENOK:
    case MSG_CTL_OK:
    case MSG_APP_OK:
    case MSG_APP_WEB:
    case MSG_CTL_MIDSK:
        GUIMENU_GetId(MAIN_MAINMENU_OPT_CTRL_ID,&group_id,&menu_id);
        switch (menu_id)
        {
        case ID_MAINMENU_OPT_ARRANGE:
            move_state = GUIMENU_STATE_MOVE_SET;
            MMK_PostMsg(MAIN_MAINMENU_WIN_ID, MSG_NOTIFY_MENU_SET_STATUS, &move_state, sizeof(GUIMENU_MOVE_STATE_T));
            break;

        case ID_MAINMENU_OPT_HELP:
            {
                MMI_STRING_T    string = {0};
                MMI_CTRL_ID_T   ctrl_id = MAIN_MAINMENU_HELP_CTRL_ID;

                MMK_CreateWin((uint32*)MAINMENU_HELP_WIN_TAB, PNULL);
                MMI_GetLabelTextByLang(TXT_MAINMENU_ARRANGE_HELP, &string);
                GUITEXT_SetString(ctrl_id,string.wstr_ptr,string.wstr_len,FALSE);
            }
            break;

        default:
            SCI_PASSERT(FALSE,("HandleMainMenuOptWinMsg menu_id = %d", menu_id));
        }
        MMK_CloseWin(win_id);
        break;
        
    case MSG_CTL_CANCEL:
    case MSG_APP_CANCEL:
        MMK_CloseWin(win_id);
        break;
        
    default:
        recode = MMI_RESULT_FALSE;
        break;
    }
    return recode;
}

/*****************************************************************************/
//     Description : HandleMainMenuMoveOptWinMsg
//    Global resource dependence : 
//  Author:xiaoqing.lu
//    Note: 
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainMenuMoveOptWinMsg(
                                               MMI_WIN_ID_T        win_id, 
                                               MMI_MESSAGE_ID_E    msg_id, 
                                               DPARAM                param
                                               )
{
    MMI_RESULT_E recode = MMI_RESULT_TRUE;
    MMI_MENU_GROUP_ID_T group_id = 0;
    MMI_MENU_ID_T menu_id = 0;
    GUIMENU_MOVE_STATE_T move_state = GUIMENU_STATE_MOVE_NONE;

    SCI_TRACE_LOW("HandleMainMenuMoveOptWinMsg msg_id = %d", msg_id);
    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
        MMK_SetAtvCtrl(win_id, MAIN_MAINMENU_MOVEOPT_CTRL_ID);
        break;
        
    case MSG_CTL_PENOK:
    case MSG_CTL_OK:
    case MSG_APP_OK:
    case MSG_APP_WEB:
    case MSG_CTL_MIDSK:
        GUIMENU_GetId(MAIN_MAINMENU_MOVEOPT_CTRL_ID,&group_id,&menu_id);
        switch (menu_id)
        {
        case ID_MAINMENU_OPT_HELP:
            {
                MMI_STRING_T    string = {0};
                MMI_CTRL_ID_T   ctrl_id = MAIN_MAINMENU_HELP_CTRL_ID;

                MMK_CreateWin((uint32*)MAINMENU_HELP_WIN_TAB, PNULL);
                MMI_GetLabelTextByLang(TXT_MAINMENU_HELP, &string);
                GUITEXT_SetString(ctrl_id,string.wstr_ptr,string.wstr_len,FALSE);
            }
            break;

        case ID_MAINMENU_OPT_EXIT:
            move_state = GUIMENU_STATE_MOVE_CANCEL;
            MMK_PostMsg(MAIN_MAINMENU_WIN_ID, MSG_NOTIFY_MENU_SET_STATUS, &move_state, sizeof(GUIMENU_MOVE_STATE_T));
            // GUIMENU_CancelMoveIcon(MAIN_MAINMENU_MOVEOPT_CTRL_ID);
            break;

        default:
            SCI_PASSERT(FALSE,("HandleMainMenuMoveOptWinMsg menu_id = %d", menu_id));
        }
        MMK_CloseWin(win_id);

        break;
        
    case MSG_CTL_CANCEL:
    case MSG_APP_CANCEL:
        MMK_CloseWin(win_id);
        break;
        
    default:
        recode = MMI_RESULT_FALSE;
        break;
    }
    return recode;
}

/*****************************************************************************/
//  FUNCTION:     HandleMainMenuHelpWinMsg
//  Description :   handle help win msg
//  Global resource dependence : 
//  Author:xiaoqing.lu
//  Note:   
/*****************************************************************************/
LOCAL MMI_RESULT_E HandleMainMenuHelpWinMsg( 
                                            MMI_WIN_ID_T win_id, 
                                            MMI_MESSAGE_ID_E msg_id, 
                                            DPARAM param
                                            )
{
    MMI_RESULT_E    recode = MMI_RESULT_TRUE;
    // MMI_STRING_T    string = {0};
    MMI_CTRL_ID_T   ctrl_id = MAIN_MAINMENU_HELP_CTRL_ID;

    switch(msg_id)
    {
    case MSG_OPEN_WINDOW:
//         MMI_GetLabelTextByLang(TXT_MAINMENU_HELP, &string);
//         GUITEXT_SetString(ctrl_id,string.wstr_ptr,string.wstr_len,FALSE);
// 
        MMK_SetAtvCtrl(win_id, ctrl_id);
        break;
  
    case MSG_CTL_CANCEL:
        MMK_CloseWin(win_id);
        break;
        
    default:
        recode = MMI_RESULT_FALSE;
        break;
    }
    
    return recode;
}


/*****************************************************************************/
//  FUNCTION:     HandleBrowerUrlMenu
//  Description :   处理主菜单中通过browser 访问url的菜单项
//  Global resource dependence : 
//  Author: fen.xie
//  Note:   
/*****************************************************************************/
LOCAL void HandleBrowerUrlMenu(MAINMENU_BROWSER_URL_TYPE_E browser_url_type)
{
#ifdef BROWSER_SUPPORT
    MMIBROWSER_ENTRY_PARAM entry_param = {0};

    if (browser_url_type >= BROWSER_URL_TYPE_MAX)
    {
        return;
    }

    entry_param.type = MMIBROWSER_ACCESS_URL;
    entry_param.dual_sys = MN_DUAL_SYS_MAX;
    entry_param.user_agent_ptr = PNULL;
    
    entry_param.url_ptr = (char *)s_mainmenu_browser_url[browser_url_type];
    MMIBROWSER_Entry(&entry_param);
#endif
}

