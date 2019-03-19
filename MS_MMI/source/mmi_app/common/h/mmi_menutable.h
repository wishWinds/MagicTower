
#ifndef MENUTABLE_H
#define MENUTABLE_H

#include "mmi_common.h"
#include "guimenu.h"
#include "mmi_text.h"
#include "mmi_image.h"

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
    extern   "C"
    {
#endif
#define TIP_NULL 0
/*-------------------------------------------------------------------------*/
/*                         TYPES/CONSTANTS                                 */
/*-------------------------------------------------------------------------*/
//菜单ID
typedef enum
{
    ID_MAINMENU_COMMUNICATION,
    ID_MAINMENU_SETTINGS,
    ID_MAINMENU_TOOLS,
    ID_MAINMENU_PASTIME,
	ID_MAINMENU_PLAYER,
    ID_COMMUNICATION_DIAL,
    ID_COMMUNICATION_MESSAGE,
    ID_COMMUNICATION_BROWSER,
    ID_COMMUNICATION_PB,

    // 滑动菜单
    ID_MAINMENU_SLIDE_PAGE1,
    ID_MAINMENU_SLIDE_PAGE2,
    ID_MAINMENU_SLIDE_PAGE3,
    ID_MAINMENU_SLIDE_PAGE4,
    ID_MAINMENU_SLIDE_PAGE5,
    ID_MAINMENU_SLIDE_PAGE6,

    ID_MAINMENU_SLIDE_TOOLS_OTHERS,
    ID_MAINMENU_SLIDE_SETTINGS,

#ifdef CMCC_UI_STYLE
   ID_MAINMENU_CMCC_MONERNET,
   ID_MAINMENU_CMCC_SERVICE,
   ID_MAINMENU_APPS,
   ID_BLUETOOTH,
       ID_EXPLORE,
       ID_CUSTMER_SERVICE,
//   ID_MAINMENU_MY_FAVORITE,
#endif 

    ID_MAINMENU_BT,
    ID_MAINMENU_CONNECT_MNG,
    ID_COMMUNICATION_CL,
    ID_COMMUNICATION_STK,
    ID_DOWNLOAD_MANAGER,
    ID_SETTINGS_ENVIONMENT,
    ID_SETTINGS_DISPLAY,
    ID_SETTINGS_PHONE,
    ID_SETTINGS_CALL,
    ID_SETTINGS_LINK,
    ID_SETTINGS_UPLMN,
    ID_SETTINGS_SECURITY,
    ID_TOOLS_ALARM,
    
#ifdef ASP_SUPPORT
  ID_TOOLS_ASP,
#endif
#ifdef DCD_SUPPORT
    ID_TOOLS_DCD,
#endif
    ID_TOOLS_CALCULATOR,
    ID_TOOLS_CALENDAR,
    ID_TOOLS_PAINT,
	ID_TOOLS_RECORD,
	ID_TOOLS_GPS,
	ID_TOOLS_OTHERS,
    ID_ENTERTAIMENT_PLAYER,
#ifdef  CAMERA_SUPPORT
    ID_ENTERTAIMENT_CAMERA,
#endif    
    ID_ENTERTAIMENT_FAVORITE,
	ID_ENTERTAIMENT_PIC,
    ID_ENTERTAIMENT_GAME,
    ID_ENTERTAIMENT_GOLDHOUSE,
	ID_ENTERTAIMENT_MP3,
	ID_ENTERTAIMENT_VIDEO,
    ID_ENTERTAIMENT_FM,
    ID_ENTERTAIMENT_ST,
    ID_ENTERTAIMENT_KUR,
    ID_ENTERTAIMENT_MTV,
    ID_ENTERTAIMENT_ATV,
    ID_ENTERTAIMENT_MOBILE_VIDEO,
	
    ID_MESSAGE,
    ID_DC,
    ID_PB,
    ID_ACCESSORY,
    ID_SETTING,
    ID_MULTIMEDIA,
    ID_BROWSER,
    ID_STK,
    ID_ENJOY_WORLD,
    ID_DV,  
    ID_PB_MAIN,
	ID_LENOVO_SPACE,
	ID_MYDOC,
	ID_PLAYER,
	ID_TOOLS,
    ID_GOLD_HOUSE,//@maggie add for ebook

	//MSD begin
	ID_MSD_SETUP,
	ID_MSD_CLOSE,
	ID_MSD_MODIFY_PSW,
	ID_MSD_MODIFY_INFO_TEL,

	//MSD END
	//idle phone number operation
    ID_DIAL_SEND_MESSAGE,
    ID_DIAL_SEND,
	ID_DIAL_SEND_SMS,
    ID_DIAL_SEND_MMS,
    ID_DAIL_CALL_LOG,
    ID_DIAL_ADD_PB_OPT,
    ID_DIAL_OPT,
	ID_DIAL_ADD_PB,
	ID_DIAL_ADD_EXISTNUM,//@zhaohui add
    ID_DIAL_INSERT_P_W, //insert p, w ,n

    //ID_SIM1_DIAL_CALL,
    //ID_SIM2_DIAL_CALL,
    ID_DIAL_CALL,
    ID_DIAL_IPCALL,
    ID_DIAL_CALL_AUDIO,
    ID_DIAL_CALL_VIDEO,

    ID_DIAL_INSERT_P,
    ID_DIAL_INSERT_W,
    ID_DIAL_INSERT_N,

	//begin message
    ID_MESSAGE_SHORTMESSAGE_ID,
    ID_MESSAGE_MMS_ID,
    ID_MESSAGE_BROADCAST_ID,             //小区广播菜单项ID号
    ID_MESSAGE_VOICEMAIL,                //语音信箱

	ID_MESSAGE_WRITE_MMS,
    ID_MESSAGE_SETTING_ID,

	ID_GAME,
    ID_PIC_VIEWER,
	ID_EBOOK,
#ifdef MMI_ENABLE_DCD
	ID_DCD_OPEN,
#endif 
	ID_JAVA_APP,
    ID_WORLDTIME,
	ID_PHONESEARCH,
	ID_COUNTDOWN,
	ID_STOPWATCH,
    ID_DYNAPP,
    ID_MAINMENU_PIM,
#ifdef SEARCH_SUPPORT
    ID_MAINMENU_SEARCH,
#endif
    ID_MAINMENU_OPT_ARRANGE,
    ID_MAINMENU_OPT_HELP,
    ID_MAINMENU_OPT_EXIT,
#ifdef CMCC_UI_STYLE
    ID_MAINMENU_CMCC,
    ID_MAINMENU_NET,
    ID_NET_FETION,
    ID_NET_MUSIC,
    ID_MAINMENU_APP,
    ID_APPS_BT,
    ID_APPS_MBBMS,
    //ID_CHINAMOBILE_DREAM,
    //ID_CHINAMOBILE_SERVICE,
    ID_CHINAMOBILE_SECURITIES,
    ID_CHINAMOBILE_MAP,
    ID_JAVA_STOCK,
    ID_FAVORITE_GOLDENHOUSE,
    ID_FAVORITE_RING,
    ID_FAVORITE_PIC,
    ID_FAVORITE_PHOTO,
    ID_FAVORITE_VIDEO,
    ID_SETTINGS_VERSION,
#endif
#ifdef QQ_SUPPORT
    ID_SPREADTRUM_QQ_SUPPORT,
#endif
	ID_TOOLS_UNIT_CONVERSION,
    // new
    ID_MAINMENU_HEALTH_MNG, // 健康管理
    ID_MAINMENU_MAGIC_VOICE, // 魔音
    ID_MAINMENU_FLASH, // Flash 播放

    // QQ	Ucweb	大智慧	大众点评
    ID_MAINMENU_QQ,
    ID_MAINMENU_UCWEB,
    ID_MAINMENU_GURAN,
    ID_MAINMENU_DIANPING,
    
    // 手机地图	开心农场	MSN	携程
    ID_MAINMENU_PHONE_MAP,
    ID_MAINMENU_KAIXIN,
    ID_MAINMENU_MSN,
    ID_MAINMENU_CTRIP,

    // 百度	新浪微博	淘宝网	优酷
    ID_MAINMENU_BAIDU,
    ID_MAINMENU_SINA_BOLG,
    ID_MAINMENU_TAOBAO,
    ID_MAINMENU_YOUKU,

    // 人人网	起点中文
    ID_MAINMENU_RENREN,
    ID_MAINMENU_QIDIAN,

#ifdef PUSH_EMAIL_SUPPORT 
    ID_MAINMENU_PUSHMAIL,
#endif /* PUSH_EMAIL_SUPPORT  */

#ifdef MAGIC_TOWER_SUPPORT
	ID_MAINMENU_MAGIC_TOWER,
#endif
    // end new
	ID_TOTAL
}MMI_MENU_ID_E;

#define MENU_DEF(_TABLEID, _ITEMPTR, _STYLE, _TITLESTR, _TITLE_ICON, _TITLE_NUMICON, _TITLE_BACKGROUND, \
	_ITEMCOUNT) \
     _TABLEID,

typedef enum
{
	MENU_NULL,
	MENU_DYNA,
	#include "mmi_menutable.def"
	MENUTABLE_MAX
} MenuLabelE;

#undef MENU_DEF

/*-------------------------------------------------------------------------*/
/*                         FUNCTIONS                                       */
/*-------------------------------------------------------------------------*/
extern const GUIMENU_GROUP_T* MMI_GetMenuTable(void);

/*-------------------------------------------------------------------------*/
/*                         VARIABLES                                       */
/*-------------------------------------------------------------------------*/
extern const GUIMENU_GROUP_T menu_table[];

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
    }
#endif
/*-------------------------------------------------------------------------*/

#endif /* MENUTABLE_H */
