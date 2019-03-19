

MCFLAG_OPT      = -DJBED_ARM -DUSB_LOG -DUSB_VUART
                  
MCFLAG_OPT		+=  -DMUSIC_PLAYER_SUPPORT

#浏览器支持GZIP
ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DBROWSER_GZIP_SUPPORT
endif

ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DCALCULATOR_SUPPORT
		#计算器
endif

ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DEBOOK_SUPPORT
		#电子书	
endif

ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else		
MCFLAG_OPT		+=  -DGAME_SUPPORT
		#游戏
endif

ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DGAME_BOXMAN_SUPPORT
		#推箱子
endif

MCFLAG_OPT		+=  -DKEY_RING_THROUGH_RECEIVER
		#键盘音播放从receiver发声

MCFLAG_OPT		+=  -DTP_RING_THROUGH_RECEIVER
		#触屏音播放从receiver发声

#MCFLAG_OPT		+=  -DCMCC_IDLE_DISPLAY    
        #移动定制规范的待机界面显示
ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DMMI_AUDIO_PLAYER_SUPPORT
#		#MP3
endif

		
MCFLAG_OPT		+=  -DCALL_TIMES_SUPPORT
		#通话记录次数

MCFLAG_OPT      +=  -DMMI_BT_MID_QUALITY ### A2DP  Quality Option:
                                         # Option1:MMI_BT_HIGH_QUALITY
                                                   #select this option, the Bluetooth A2DP 
                                                   #default sample rate will be set 48K
                                          # Option2:MMI_BT_MID_QUALITY
                                                    #select this option, the Bluetooth A2DP 
                                                    #default sample rate will be set 36K
                                          # Option3:MMI_BT_LOW_QUALITY
                                                    #select this option, the Bluetooth A2DP 
                                                    #default sample rate will be set 16K

ifeq ($(strip $(TTS_SUPPORT)), IFLYTEK)
MCFLAG_OPT  	+=  -DMMI_TTS_ENABLE -DTTS_FILE_RES
endif

#CAMERA
MCFLAG_OPT += -DCAMERA_SUPPORT
#export CAMERA_SUPPORT    = TRUE         ### Camera support:
                                        # Option1:TRUE
                                        # Option2:FALSE

#本地搜索
MCFLAG_OPT += -DSEARCH_SUPPORT

#R8
MCFLAG_OPT += -DMMI_R8_SUPPORT


#不是低memory平台
ifeq ($(strip $(LOW_MEMORY_SUPPORT)), FALSE)
   ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
   else
		    MCFLAG_OPT		+=  -DCOUNTEDTIME_SUPPORT
				#倒计时
	 endif
	 ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
   else
				MCFLAG_OPT		+=  -DWORLD_CLOCK_SUPPORT
						#世界时间
	 endif
	
	 ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
   else
				MCFLAG_OPT		+=  -DGAME_LINK_SUPPORT
						#连连看
	 endif
	 
				MCFLAG_OPT		+=  -DENG_SUPPORT
						#工程模式
				MCFLAG_OPT		+=  -DMMI_UNITCONVERSION_SUPPORT
					#工程模式				
endif

#是否为低memory平台
ifeq ($(strip $(LOW_MEMORY_SUPPORT)), TRUE)
ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DPB_SUPPORT_LOW_MEMORY
                #PB(500条/单条内容3个)
endif

ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
#MCFLAG_OPT		+=  -DSMS_SUPPORT_LOW_MEMORY
                #SMS(200条)
endif

MCFLAG_OPT		+=  -DCALENDAR_SUPPORT_LOW_MEMORY
                #日程（50个缩减）
                
ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
else
MCFLAG_OPT		+=  -DMAIN_MENU_SUPPORT_LOW_MEMORY
                #主菜单设为九宫格
endif

#MCFLAG_OPT		+=  -DPHOTO_FRAME_SUPPORT_LOW_MEMORY
                #拍照不支持像框											             
MCFLAG_OPT		+=  -DKEYBOARD_SUPPORT_LOW_MEMORY
		        		#触笔输入不支持软键盘及触笔拼音
MCFLAG_OPT		+=  -DPINYIN_SUPPORT_LOW_MEMORY                
		        		#不支持单词输入只支持单字输入，不支持联想输入
		        		
ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
MCFLAG_OPT		+=  -DENG_SUPPORT
		#工程模式
MCFLAG_OPT		+=  -DMMI_UNITCONVERSION_SUPPORT
		#工程模式		        
endif
		
endif

ifeq ($(strip $(CARD_LOG)), TRUE)
MCFLAG_OPT      += -DCARD_LOG
endif

# Auto Testing Support
ifeq ($(strip $(ATEST_SUPPORT)), TRUE)
MCFLAG_OPT  	+=  -D_ATEST_
endif

#GSM/TD双模, 暂时保留
ifeq ($(strip $(APP_DUALMODE_ENABLE)), TRUE)
MCFLAG_OPT		+=  -DMMI_DUALMODE_ENABLE
endif

ifeq ($(strip $(DEV_MANAGE_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DDM_SUPPORT
else
ifeq ($(strip $(DM_ONLY_SELFREG_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DDM_ONLY_SELFREG_SUPPORT
endif
endif

ifeq ($(strip $(ASP_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DMMI_ENABLE_ASP
endif

ifeq ($(strip $(DCD_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DMMI_ENABLE_DCD
endif

#TD/GSM DualModule product
ifeq ($(strip $(MAINLCD_SIZE)), 128X64)
  MCFLAG_OPT              += -DENGTD_SUPPORT
else
	ifeq ($(strip $(LOW_MEMORY_SUPPORT)), FALSE)
		ifeq ($(strip $(APP_PRODUCT_DM)), TRUE)
		MCFLAG_OPT		+=  -DPRODUCT_DM
		MCFLAG_OPT		+=  -DENGTD_SUPPORT
		endif
	endif
endif
#TD工程模式设置

MCFLAG_OPT		+=  -DIM_ENGLISH_SUPPORT

ifneq ($(strip $(TOUCHPANEL_TYPE)), NONE)
MCFLAG_OPT		+=  -DTOUCH_PANEL_SUPPORT
endif


MCFLAG_OPT		+=  -DBLUETOOTH_HFG_PLAY_MUSIC_SUPPORT


ifeq ($(strip $(PLATFORM)), SC6600L)
MCFLAG_OPT		+=  -DP3D_AUDIO_EQ_CONFLICT
endif

#6600L and 8800H support p3d when mp3bg
ifeq ($(strip $(PLATFORM)), SC6600L)
MCFLAG_OPT		+=  -DP3D_WHEN_MP3BG_SUPPORT
endif
ifeq ($(strip $(PLATFORM)), SC8800H)
MCFLAG_OPT		+=  -DP3D_WHEN_MP3BG_SUPPORT
endif

ifeq ($(strip $(PRODUCT_CONFIG)), sc6800h_sp6801h_nor)
MCFLAG_OPT      += -DJAVA_NOR_FLASH
endif

ifeq ($(strip $(JAVA_SUPPORT)), IA)
MCFLAG_OPT		+=  -DJAVA_OTA_SUPPORT -DMMI_JAVA_PIM
endif
ifeq ($(strip $(PLATFORM)), SC6800H)
MCFLAG_OPT		+= -DP3D_WHEN_MP3BG_SUPPORT -DFPGA_6800H_POWER_ON -DPLATFORM_SC6800H -DAUDIO_SC6800H  -DDC_SC6800H \
                           -DMV_EFFECT_SUPPORT	
endif


ifeq ($(strip $(PIM_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DPIM_SUPPORT
endif

ifeq ($(strip $(ASSERT_TYPE_SUPPORT)), ASSERT)
MCFLAG_OPT		+=  -DMMI_ASSERT_MODE
endif

#支持Mocor示例代码
ifeq ($(strip $(MMI_MOCOR_SAMPLE)), TRUE)
MCFLAG_OPT		+=  -DMMI_MOCOR_SAMPLE
endif

ifeq ($(strip $(LOW_MEMORY_SUPPORT)), FALSE)
MCFLAG_OPT		+=  -DMMI_AUTOTEST_SUPPORT
endif

ifeq ($(strip $(UI_SPRITE_ENABLE)), TRUE)
MCFLAG_OPT		+=  -DMMI_SPRITE_ENABLE
endif

#支持streaming
ifeq ($(strip $(VIDEO_PLAYER_SUPPORT)), TRUE)
ifeq ($(strip $(STREAMING_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DMMI_STREAMING_PLAYER_SUPPORT
endif
endif


ifeq ($(strip $(UMEM_SUPPORT)),	TRUE)
MCFLAG_OPT += -DMMI_UDISK_MEM_ENABLE
endif

ifeq ($(strip $(DV_UDISK_SUPPORT)),TRUE)
MCFLAG_OPT += -DMMI_DV_UDISK_ENABLE
endif

#camera module
export CAMERA_SENSOR_ANGLE = 0    ### camera sensor direction
                                  # Option1:0	    #define CAMERA_SENSOR_ANGLE_0
                                  # Option2:90   	#define CAMERA_SENSOR_ANGLE_90
                                        
export BURST_VOICE = EVERY        ### camera sensor direction
                                  # Option1:ONCE	    #define BURST_VOICE_ONCE
                                  # Option2:EVERY   	#define BURST_VOICE_EVERY        
                                  
                                  
# camera sensor direction 
#screen mode CAMERA_SCREEN_PORTRAIT and CAMERA_SCREEN_LANDSCAPE
#if define macro CAMERA_SENSOR_ANGLE_90 
#then define macro CAMERA_SCREEN_LANDSCAPE                                                        
ifeq ($(strip $(CAMERA_SENSOR_ANGLE)), 90)
    MCFLAG_OPT += -DCAMERA_SENSOR_ANGLE_90
    MCFLAG_OPT += -DCAMERA_SCREEN_LANDSCAPE
else
    MCFLAG_OPT += -DCAMERA_SENSOR_ANGLE_0
    
    ifeq ($(strip $(MAINLCD_LOGIC_ANGLE)), 0)
        MCFLAG_OPT += -DCAMERA_SCREEN_PORTRAIT
    endif

    ifeq ($(strip $(MAINLCD_LOGIC_ANGLE)), 90)
        MCFLAG_OPT += -DCAMERA_SCREEN_LANDSCAPE
    endif
endif

#burst voice 
ifeq ($(strip $(BURST_VOICE)), ONCE)
    MCFLAG_OPT += -DBURST_VOICE_ONCE
else
    MCFLAG_OPT += -DBURST_VOICE_EVERY
endif

#end camera module

ifeq ($(strip $(MULTI_LAN_SUPPORT)),CSTAR)
#另外一种阿拉伯或者波斯语的丝印
#MCFLAG_OPT              +=  -DMMI_SPECIAL_ARABIC_PERSIAN
#另外一种泰语的丝印
#MCFLAG_OPT              +=  -DMMI_SPECIAL_THAI
#另外一种印地语的丝印
#MCFLAG_OPT              +=  -DMMI_SPECIAL_HINDI
endif

#dorado浏览器是否显示toolbar(显示toolbar时,不显示softkey);触摸情况下,该开关默认打开
ifneq ($(strip $(TOUCHPANEL_TYPE)), NONE)
MCFLAG_OPT		+=  -DBROWSER_TOOLBAR
endif

#GBK support
ifeq ($(strip $(IM_SIMP_CHINESE_SUPPORT)), TRUE)
ifneq ($(strip $(FONT_HAN_SIMP_ONLY)), TRUE)
MCFLAG_OPT		+=  -DGBK_SUPPORT
endif
endif

#endif
#BIG5 support
ifeq ($(strip $(IM_TRAD_CHINESE_SUPPORT)), TRUE)
MCFLAG_OPT		+=  -DBIG5_SUPPORT
endif

ifneq ($(strip $(PRODUCT_CONFIG)), sc6800h_sp6801h_nor)
ifeq ($(strip $(PIC_EDITOR_SUPPORT)), TRUE)
MCFLAG_OPT      += -DPIC_EDIT_FRAME_SUPPORT
endif
endif

ifneq ($(strip $(PRODUCT_CONFIG)), sc6800h_sp6801h_nor)
MCFLAG_OPT      += -DCAMERA_FRAME_SUPPORT
endif


MINCPATH = MS_MMI/source/mmi_app/app/accessory/h
MINCPATH += MS_MMI/source/mmi_app/app/audio/h 
MINCPATH += MS_MMI/source/mmi_app/app/bt/h 
MINCPATH += MS_MMI/source/mmi_app/app/camera/h 
MINCPATH += MS_MMI/source/mmi_app/app/cc/h 
MINCPATH += MS_MMI/source/mmi_app/app/cl/h 
MINCPATH += MS_MMI/source/mmi_app/app/connection/h 
MINCPATH += MS_MMI/source/mmi_app/app/cs/h 
MINCPATH += MS_MMI/source/mmi_app/app/dcd/h 
MINCPATH += MS_MMI/source/mmi_app/app/dl/h 
MINCPATH += MS_MMI/source/mmi_app/app/dm/h 
MINCPATH += MS_MMI/source/mmi_app/app/dynamic/h 
MINCPATH += MS_MMI/source/mmi_app/app/ebook/h 
MINCPATH += MS_MMI/source/mmi_app/app/eng/h 
MINCPATH += MS_MMI/source/mmi_app/app/engtd/h 
MINCPATH += MS_MMI/source/mmi_app/app/envset/h 
MINCPATH += MS_MMI/source/mmi_app/app/fdn/h
MINCPATH += MS_MMI/source/mmi_app/app/fm/h 
MINCPATH += MS_MMI/source/mmi_app/app/fmm/h 
MINCPATH += MS_MMI/source/mmi_app/app/game/game_boxman/h 
MINCPATH += MS_MMI/source/mmi_app/app/game/game_link/h 
MINCPATH += MS_MMI/source/mmi_app/app/game/game_manager/h 
MINCPATH += MS_MMI/source/mmi_app/app/idle/h 
MINCPATH += MS_MMI/source/mmi_app/app/im/h 
MINCPATH += MS_MMI/source/mmi_app/app/menu/h 
MINCPATH += MS_MMI/source/mmi_app/app/mmi3d/h 
MINCPATH += MS_MMI/source/mmi_app/app/mms/h 
MINCPATH += MS_MMI/source/mmi_app/app/mobiletv/h
MINCPATH += MS_MMI/source/mmi_app/app/atv/h 
MINCPATH += MS_MMI/source/mmi_app/app/mp3/h 
MINCPATH += MS_MMI/source/mmi_app/app/msd/h 
MINCPATH += MS_MMI/source/mmi_app/app/multim/h 
MINCPATH += MS_MMI/source/mmi_app/app/ocr/h 
MINCPATH += MS_MMI/source/mmi_app/app/otapush/h  
MINCPATH += MS_MMI/source/mmi_app/app/pb/h 
MINCPATH += MS_MMI/source/mmi_app/app/pdp/h 
MINCPATH += MS_MMI/source/mmi_app/app/phone/h 
MINCPATH += MS_MMI/source/mmi_app/app/pic/h 
MINCPATH += MS_MMI/source/mmi_app/app/pic_viewer/h 
MINCPATH += MS_MMI/source/mmi_app/app/pim/h
MINCPATH += MS_MMI/source/mmi_app/app/record/h 
MINCPATH += MS_MMI/source/mmi_app/app/setting/h 
MINCPATH += MS_MMI/source/mmi_app/app/sms/h 
MINCPATH += MS_MMI/source/mmi_app/app/ss/h 
MINCPATH += MS_MMI/source/mmi_app/app/stk/h 
#MINCPATH += MS_MMI/source/mmi_app/app/streaming/h 
MINCPATH += MS_MMI/source/mmi_app/app/theme/h 
MINCPATH += MS_MMI/source/mmi_app/app/tp/h 
MINCPATH += MS_MMI/source/mmi_app/app/udisk/h 
MINCPATH += MS_MMI/source/mmi_app/app/vcard/h 
MINCPATH += MS_MMI/source/mmi_app/app/vt/h 
MINCPATH += MS_MMI/source/mmi_app/app/clipbrd/h 
MINCPATH += MS_MMI/source/mmi_app/app/search/h
MINCPATH += MS_MMI/source/mmi_app/common/h 
MINCPATH += MS_MMI/source/mmi_app/custom/h 
MINCPATH += MS_MMI/source/mmi_app/kernel/h 
MINCPATH += MS_MMI/source/mmi_gui/include 
MINCPATH += MS_MMI/source/mmi_kernel/include 
MINCPATH += MS_MMI/source/mmi_spml/include
MINCPATH += MS_MMI/source/mmi_utility/h 
MINCPATH += MS_MMI/source/spim/include
MINCPATH += MS_MMI/source/pim/h
MINCPATH += MS_MMI/source/resource
MINCPATH += chip_drv/export/inc/outdated 
MINCPATH += CAF/Interface/source/resource 
MINCPATH += CAF/Template/include 
MINCPATH += DAPS/source/wbxml_parser/inc 
MINCPATH += DAPS/source/wsp_header_decoder/inc
MINCPATH += DAPS/source/xml_expat/inc 
MINCPATH += l4/export/inc 
MINCPATH += PARSER/export/inc 
MINCPATH += sim/export/inc 
MINCPATH += Third-party/cstar/include 
MINCPATH += Third-party/S9/include 

#API文件
#MINCPATH += CMMB/source/mbbms/inc
MINCPATH += MS_MMI/source/mmi_app/app/kuro/h 

ifeq ($(strip $(MMIWIDGET_SUPPORT)), TRUE)
MINCPATH += MS_MMI/source/mmi_app/app/widget/h 
endif

ifeq ($(strip $(CMMB_SUPPORT)), TRUE)
MINCPATH += CMMB/export/inc 
endif

ifeq ($(strip $(TTS_SUPPORT)), IFLYTEK)
MINCPATH += Third-party/InterSound4/h
MINCPATH += Third-party/InterSound4/Lib
MINCPATH += MS_MMI/source/mmi_app/app/tts/h
endif

ifeq ($(strip $(CARD_LOG)), TRUE)
MINCPATH += logsave/export/inc
endif

ifeq ($(strip $(DEV_MANAGE_SUPPORT)), TRUE)
ifeq ($(strip $(SPRD_CUSTOMER)), FALSE)    
MINCPATH += Third-party/formal/Dm/import 
MINCPATH += Third-party/formal/Dm/include 
else
MINCPATH += Third-party/Dm/import 
MINCPATH += Third-party/Dm/include 
endif
endif

ifeq ($(strip $(BROWSER_SUPPORT)), NETFRONT)
    ifeq ($(strip $(NETFRONT_SUPPORT)), VER35)
        ifeq ($(strip $(SPRD_CUSTOMER)), FALSE)    
            MINCPATH += Third-party/formal/netfront/Netfront3.5/include 
            MINCPATH += Third-party/formal/netfront/Netfront3.5/include/config
        else
            MINCPATH += Third-party/netfront/Netfront3.5/include 
            MINCPATH += Third-party/netfront/Netfront3.5/include/config
        endif
    else
        ifeq ($(strip $(SPRD_CUSTOMER)), FALSE)    
            MINCPATH += Third-party/formal/netfront/Netfront4.0/include 
            MINCPATH += Third-party/formal/netfront/Netfront4.0/include/config
        else
            MINCPATH += Third-party/netfront/Netfront4.0/include 
            MINCPATH += Third-party/netfront/Netfront4.0/include/config
        endif
    endif
endif

ifeq ($(strip $(VT_SUPPORT)), TRUE)
ifeq ($(strip $(SPRD_CUSTOMER)), FALSE)    
MINCPATH += Third-party/formal/Mplapi/include 
MINCPATH += Third-party/formal/Mplapi/Arm_lib/normal
else
MINCPATH += Third-party/Mplapi/include 
MINCPATH += Third-party/Mplapi/Arm_lib/normal
endif
endif


#sun java api              
ifeq ($(strip $(JAVA_SUPPORT)), SUN)
MINCPATH        +=      MS_MMI/source/mmi_app/app/java/h\
			MS_MMI/source/sun_java/h \
                        MS_MMI/source/sun_java/h/javacall/midp \
                        MS_MMI/source/sun_java/h/javacall/common \
                        MS_MMI/source/sun_java/h/javacall \
                        MS_MMI/source/sun_java/h/javacall/jsr135_mmapi \
                        MS_MMI/source/sun_java/h/javacall/jsr120_wma \
                        MS_MMI/source/sun_java/h/platform \
                        MS_MMI/source/sun_java/h/javacall/jsr75_pim_fc\
                        MS_MMI/source/sun_java/c/javacall/midp
endif

ifeq ($(strip $(JAVA_SUPPORT)), IA)
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/jblend
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/jblend/gui/common
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/jblend/gui/inner
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/jblend/gui/user
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/extlib
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/ajsc
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/port
MINCPATH += MS_MMI/source/mmi_app/app/ia_java/h/jas
endif
ifeq ($(strip $(SPRD_CUSTOMER)), FALSE)
    ifeq ($(strip $(PLATFORM)), SC8800H)
	MINCPATH += Third-party/formal/hw/include
    else
    ifeq ($(strip $(PLATFORM)), SC8800G)
    MINCPATH += Third-party/formal/hw/include
    else
	MINCPATH += Third-party/hw/include 
	endif
    endif
else
	MINCPATH += Third-party/hw/include 
endif
				
ifeq ($(strip $(BROWSER_SUPPORT)), NETFRONT)
 MINCPATH += MS_MMI/source/mmi_app/app/www/h
endif

ifeq ($(strip $(VT_SUPPORT)), TRUE)
 MINCPATH += MS_MMI/source/mmi_app/app/vt/h
endif


ifeq ($(strip $(BROWSER_SUPPORT)), DORADO)
 MINCPATH += MS_MMI/source/mmi_app/app/browser/h
 MINCPATH += MS_MMI/source/mmi_app/app/browser/control/inc
endif

ifeq ($(strip $(MMI_MOCOR_SAMPLE)), TRUE)
 MINCPATH		+=  MS_MMI/source/mmi_app/app/sample/h
endif

#ifeq ($(strip $(STREAMING_SUPPORT)), TRUE)
# MINCPATH +=    MS_MMI/source/mmi_app/app/streaming/h/nex_inc \
#                MS_MMI/source/mmi_app/app/streaming/h/nex_inc/nxsys
#endif

ifeq ($(strip $(OCR_SUPPORT)), TRUE)
 MINCPATH += Third-party/ocr/include
endif

ifeq ($(strip $(GPS_SUPPORT)), TRUE)
 MINCPATH += MS_MMI/source/mmi_app/app/gps/h
endif

ifeq ($(strip $(VIDEO_PLAYER_SUPPORT)), TRUE)
MINCPATH += MS_MMI/source/mmi_app/app/video_player/h
endif

ifeq ($(strip $(STREAMING_SUPPORT)), TRUE)
ifeq ($(strip $(MOBILE_VIDEO_SUPPORT)), TRUE)
MINCPATH += MS_MMI/source/mmi_app/app/mobile_video/h \
            MS_MMI/source/mmi_app/app/mobile_video/h/include \
            MS_MMI/source/mmi_app/app/mobile_video/h/mv
endif
endif

ifeq ($(strip $(ASP_SUPPORT)), TRUE)
 MINCPATH += MS_MMI/source/mmi_app/app/asp/h
endif

ifeq ($(strip $(PUSH_EMAIL_SUPPORT)), TRUE)
MINCPATH  +=  MS_MMI/source/mmi_app/app/push_mail/h
MINCPATH  +=  MS_MMI/source/push_mail/comm/h
MINCPATH  +=  MS_MMI/source/push_mail/push_mail/h
endif



MINCPATH += $(PS_INCPATH) $(L1_INCPATH) $(ATC_INCPATH)						
             
MSRCPATH = MS_MMI/source/mmi_app 
MSRCPATH += MS_MMI/source/mmi_app/kernel/c 
MSRCPATH += MS_MMI/source/mmi_app/common/c 
MSRCPATH += MS_MMI/source/mmi_app/app/theme/c 
MSRCPATH += MS_MMI/source/mmi_app/app/accessory/c 
MSRCPATH += MS_MMI/source/mmi_app/app/audio/c 
MSRCPATH += MS_MMI/source/mmi_app/app/cc/c 
MSRCPATH += MS_MMI/source/mmi_app/app/cl/c 
MSRCPATH += MS_MMI/source/mmi_app/app/connection/c 
MSRCPATH += MS_MMI/source/mmi_app/app/ebook/c 
MSRCPATH += MS_MMI/source/mmi_app/app/eng/c 
MSRCPATH += MS_MMI/source/mmi_app/app/envset/c 
MSRCPATH += MS_MMI/source/mmi_app/app/fm/c 
MSRCPATH += MS_MMI/source/mmi_app/app/fmm/c 
MSRCPATH += MS_MMI/source/mmi_app/app/game/game_boxman/c 
MSRCPATH += MS_MMI/source/mmi_app/app/game/game_link/c 
MSRCPATH += MS_MMI/source/mmi_app/app/game/game_manager/c 
MSRCPATH += MS_MMI/source/mmi_app/app/idle/c 
MSRCPATH += MS_MMI/source/mmi_app/app/menu/c 
MSRCPATH += MS_MMI/source/mmi_app/app/mms/c  
MSRCPATH += MS_MMI/source/mmi_app/app/otapush/c 
MSRCPATH += MS_MMI/source/mmi_app/app/msd/c 
MSRCPATH += MS_MMI/source/mmi_app/app/pb/c 
MSRCPATH += MS_MMI/source/mmi_app/app/fdn/c
MSRCPATH += MS_MMI/source/mmi_app/app/phone/c 
MSRCPATH += MS_MMI/source/mmi_app/app/pic/c 
MSRCPATH += MS_MMI/source/mmi_app/app/pic_viewer/c
MSRCPATH += MS_MMI/source/mmi_app/app/record/c 
MSRCPATH += MS_MMI/source/mmi_app/app/setting/c 
MSRCPATH += MS_MMI/source/mmi_app/app/sms/c 
MSRCPATH += MS_MMI/source/mmi_app/app/stk/c 
MSRCPATH += MS_MMI/source/mmi_app/app/udisk/c 
MSRCPATH += MS_MMI/source/mmi_app/app/vcard/c 
MSRCPATH += MS_MMI/source/mmi_app/app/vt/c 
MSRCPATH += MS_MMI/source/mmi_app/app/engtd/c 
MSRCPATH += MS_MMI/source/mmi_app/app/mp3/c 
#MSRCPATH += MS_MMI/source/mmi_app/app/streaming/c 
MSRCPATH += MS_MMI/source/mmi_app/app/tp/c 
MSRCPATH += MS_MMI/source/mmi_app/app/bt/c 
MSRCPATH += MS_MMI/source/mmi_app/app/pdp/c 
MSRCPATH += MS_MMI/source/mmi_app/app/dcd/c 
MSRCPATH += MS_MMI/source/mmi_app/app/cs/c 
MSRCPATH += MS_MMI/source/mmi_app/app/mmi3d/c 
MSRCPATH += MS_MMI/source/mmi_app/app/ocr/c 
MSRCPATH += MS_MMI/source/mmi_app/app/dynamic/c 
MSRCPATH += MS_MMI/source/mmi_app/app/im/c 
MSRCPATH += MS_MMI/source/mmi_app/app/dm/c 
MSRCPATH += MS_MMI/source/mmi_app/app/camera/c 
MSRCPATH += MS_MMI/source/mmi_app/app/mobiletv/c
MSRCPATH += MS_MMI/source/mmi_app/app/atv/c 
MSRCPATH += MS_MMI/source/mmi_app/app/www/c 
MSRCPATH += MS_MMI/source/mmi_app/app/dl/c 
ifeq ($(strip $(JAVA_SUPPORT)), SUN)
MSRCPATH += MS_MMI/source/mmi_app/app/java/c
endif
MSRCPATH += MS_MMI/source/mmi_app/app/pim/c
MSRCPATH += MS_MMI/source/mmi_app/app/browser/c 
MSRCPATH += MS_MMI/source/mmi_app/app/browser/control/src
MSRCPATH += MS_MMI/source/mmi_app/app/clipbrd/c 
MSRCPATH += MS_MMI/source/mmi_app/app/search/c 

ifeq ($(strip $(JAVA_SUPPORT)), IA)
MSRCPATH += MS_MMI/source/mmi_app/app/ia_java/c/port
MSRCPATH += MS_MMI/source/mmi_app/app/ia_java/c/port/ksc
MSRCPATH += MS_MMI/source/mmi_app/app/ia_java/c/port/jsc
MSRCPATH += MS_MMI/source/mmi_app/app/ia_java/c/jas
endif

#API文件
MSRCPATH += MS_MMI/source/mmi_app/app/kuro/c 

ifeq ($(strip $(GPS_SUPPORT)), TRUE)
MSRCPATH		+=  MS_MMI/source/mmi_app/app/gps/c 
endif

ifeq ($(strip $(ASP_SUPPORT)), TRUE)
MSRCPATH		+=  MS_MMI/source/mmi_app/app/asp/c 
endif

ifeq ($(strip $(MMI_MOCOR_SAMPLE)), TRUE)
MSRCPATH		+=  MS_MMI/source/mmi_app/app/sample/c
endif

ifeq ($(strip $(TTS_SUPPORT)), IFLYTEK)
MSRCPATH += MS_MMI/source/mmi_app/app/tts/c
endif

ifeq ($(strip $(VIDEO_PLAYER_SUPPORT)), TRUE)
 MSRCPATH += MS_MMI/source/mmi_app/app/video_player/c
endif

ifeq ($(strip $(STREAMING_SUPPORT)), TRUE)
ifeq ($(strip $(MOBILE_VIDEO_SUPPORT)), TRUE)
MSRCPATH += MS_MMI/source/mmi_app/app/mobile_video/c \
            MS_MMI/source/mmi_app/app/mobile_video/c/mv
endif
endif

ifeq ($(strip $(MMIWIDGET_SUPPORT)), TRUE)
MSRCPATH += MS_MMI/source/mmi_app/app/widget/c
endif

ifeq ($(strip $(PUSH_EMAIL_SUPPORT)), TRUE)
MSRCPATH  +=  MS_MMI/source/mmi_app/app/push_mail/c
endif

MINCPATH +=  build/$(PROJECT)_builddir/tmp  

SOURCES	        = app_tasks.c block_mem.c mmi_atc.c mmi_atc_wintab.c mmi_common.c mmi_filetask.c mmi_modu_main.c mmi_osbridge.c mmi_port.c \
                mmi_rglexpr.c mmimain.c mmi_nv.c mmi_default.c mmi_menutable.c \
                mmi_parse.c mmidisplay_data.c mmi_applet_table.c\
                mmi_solarlunar.c mmiacc_winmain.c mmicalc_main.c mmiwclk_main.c mmialarm.c mmialarm_service.c mmicalendar_main.c mmiacc_menutable.c \
                mmialarm_menutable.c mmischedule.c mmiacc_nv.c mmialarm_nv.c  mmischedule_atc.c \
                mmiaudio.c mmiaudio_ctrl.c mmiaudio_vibrate.c mmicc_app.c mmicc_audio.c mmicc_nv.c mmicc_speeddial_wintab.c mmiussd.c mmicc_menutable.c mmicc_speeddial.c mmicc_wintab.c \
                mmicl.c mmicl_costs_wintab.c mmicl_wintab.c mmi_keylock.c mainapp.c mmiidle_hw_icon.c mmi_subwintab.c window_parse.c mmi_applet_manager.c\
                mmiconn_manager_wintab.c mmiconnection_menutable.c mmiconnection.c mmitv_out.c \
                mmiebook_file.c mmiebook_nv.c mmiebook_wintab.c mmiebook_menutable.c mmiebook_task.c \
                mmieng_main.c mmieng_nv.c mmieng_win.c mmieng_menutable.c mmieng_uitestwin.c mmieng_base.c\
                mmieng_dynamic_main.c \
                mmienvset.c mmienvset_wintab.c \
                mmifmm.c mmifmm_menutable.c mmifmm_wintab.c mmifilearray.c mmifmm_id.c mmifmm_interface.c mmivirtualarray.c mmifmm_nv.c mmifmm_pic.c \
                mmigame_boxman_func.c mmigame_boxman_nv.c mmigame_boxman_menutable.c mmigame_boxman_wintab.c \
                mmigame_link_func.c mmigame_link_nv.c mmigame_link_menutable.c mmigame_link_wintab.c \
                mmigame.c mmigame_menutable.c mmigame_wintab.c \
                mainmenu_win.c mmimenu_optionpage.c mmimenu_data.c mmimenu_second.c mmimenu_popup.c mmimenu_slide_page.c mmimenu_cube.c \
                mmiota_file.c mmiota_id.c mmiota_main.c mmiota_menutable.c mmiota_wintable.c \
                mmimp3.c mmimp3_sort.c mmimp3_lyric.c mmimp3_music.c mmimp3_wintab.c mmimp3_bt.c mmimp3_menutable.c mmimp3_nv.c \
                mmimsd.c mmimsd_wintab.c mmi_filemgr.c \
                mmipb_menutable.c mmipb_signal_api.c mmipb_atc.c mmipb_mnapi.c  mmipb_wintab.c \
                mmipb_isdn_adn.c mmipb_nv.c mmipb_search.c mmifdn.c\
                mmiphone.c mmiphone_wintab.c \
		mmipicview.c mmipicview_id.c mmipicview_menutable.c mmipicview_nv.c mmipicview_list.c mmipicview_preview.c mmipicview_wintab.c  mmipicview_zoom.c \
                mmi_pubwin.c mmi_pubeditwin.c mmi_pubmenuwin.c mmi_pubtextwin.c mmi_pubrichtextwin.c mmi_publistwin.c \
                mmi_setlist_win.c \
                mmirecord.c mmirecord_menutable.c mmirecord_nv.c mmirecord_wintab.c \
                mmiset_call.c mmiset_func.c mmiset_nv.c mmiset_security.c mmiset_display.c mmiset_menutable.c mmiset_ring.c mmiset_wintab.c \
				mmiset_shortcut.c \
                mmisms_api.c mmisms_nv.c mmismsapp_order.c mmismscb_api.c mmisms_menutable.c mmismsapp_main.c mmismsapp_wintab.c mmismscb_wintab.c \
                mmisms_delete.c mmisms_edit.c mmisms_read.c mmisms_receive.c mmisms_save.c mmisms_send.c mmisms_set.c mmisms_vociemail.c mmisms_file.c\
                mmistk_app.c mmistk_win.c mmitheme_anim.c mmitheme_iconlist.c mmitheme_menu.c mmitheme_prgbox.c mmitheme_pubwin.c mmi_theme.c mmitheme_tab.c mmitheme_label.c \
		mmitheme_statusbar.c mmitheme_tips.c mmitheme_dropdownlist.c mmitheme_edit.c mmitheme_im.c mmitheme_text.c mmitheme_setlist.c mmitheme_form.c mmitheme_button.c \
		mmitheme_block.c mmitheme_pos.c mmitheme_update.c mmitheme_toolbar.c\
                mmi_sd.c mmi_sd_plug.c mmiudisk.c mmiudisk_wintab.c \
                mmivcard.c vf_create_object.c vf_modified.c vf_strings.c vf_access.c vf_delete.c vf_parser.c vf_writer.c \
                vf_access_calendar.c vf_malloc.c vf_search.c vf_access_wrappers.c vf_malloc_stdlib.c vf_string_arrays.c \
                mmipdp_api.c mmipdp_list.c mmipdp_ps_adap.c \
                coordinate_wintab.c tp_func.c tp_nv.c \
                mmibt_a2dp.c mmibt_menutable.c mmibt_nv.c mmibt_wintab.c  mmibt_app.c \
                mmi_id.c mmiacc_id.c mmibt_id.c mmicc_id.c mmiconnection_id.c mmieng_id.c mmigame_boxman_id.c mmigame_link_id.c \
                mmimp3_id.c mmipb_id.c mmirecord_id.c mmiset_id.c mmisms_id.c mmistk_id.c tp_id.c mmialarm_id.c mmiebook_id.c mmigame_id.c\
                mmimenu_icon.c mmi_wallpaper.c mmimp_location.c mmiphonesearch_wintab.c \
                mmiset_dualsim.c mmicountedtime_main.c \
                mmicom_panel.c mmicom_data.c mmicom_string.c mmicom_time.c \
                mmitheme_special.c mmitheme_special_func.c \
                mmiidle_screensaver.c mmiidle_shortcut.c mmiidle_dial.c\
                mmiidle_screensaver_seed.c mmiidle_screensaver_snake.c mmiidle_screensaver_special.c mmiidle_screensaver_star.c \
                mmidyna_win.c mmidyna_id.c mmidyna_menutable.c mmi_resource.c mmiidle_display.c mmi3d.c mmicamera_manager.c mmidv_manager.c \
                mmi_event_api.c mmi_event_manager.c \
                mmiunitconversion.c mmi_autotest.c \
                mmitheme_clipbrd.c mmiclipbrd.c mmiclipbrd_id.c mmiclipbrd_menutable.c mmiclipbrd_wintab.c mmisearch_wintab.c mmisearch_main.c mmisearch_id.c mmisearch_menutable.c\
                string_anim.c

#API文件

SOURCES	 +=     mmikur.c mmipim_export.c mmiocr_export.c \
                mmidm_export.c mmiengtd_export.c mmifm_export.c mmidcd_export.c mmimms_export.c mmipb_export.c mmipic_edit_export.c \
                mmiudisk_export.c tp_export.c mmibt_export.c mmimtv_export.c mmiatv_export.c                               

SOURCES	 +=   mmiim_im_switching.c mmiim_tp_cstar_keyboard_cfg.c mmiim_tp_ui.c \
							mmiim_base.c mmiim.c mmiim_wintab.c mmiim_id.c mmiim_nv.c mmiim_menutable.c mmiim_multitap.c \
						  mmiim_sp_basic.c mmiim_sp_tp_basic.c mmiim_sp_hw.c mmiim_sp_symbol.c mmiim_sp_symbol_data.c \
						  mmiim_sp_multitap.c mmiim_sp_ml_data.c mmiim_sp_ml9key_data.c mmiim_sp_ml26key_data.c \
						  mmiim_tp_multitap_26key.c mmiim_tp_multitap_9key.c
ifeq ($(strip $(IM_ENGINE)), S9)
SOURCES	 +=     mmiim_sp_stroke.c mmiim_sp_py9key.c mmiim_sp_en9key.c mmiim_tp_sp.c mmiim_sp_py26key.c mmiim_sp_en26key.c  
#SOURCES	 +=     mmiim_sp_tp_common.c mmiim_sp_tp_en26key.c mmiim_sp_tp_abc26key.c mmiim_sp_tp_digital.c \
#                mmiim_sp_tp_py26key.c mmiim_sp_tp_stroke.c mmiim_sp_tp_en9key.c mmiim_sp_tp_abc9key.c
else
SOURCES	 +=     mmiim_cstar.c  mmiim_tp_cstar.c 
endif

ifeq ($(strip $(MAGIC_TOWER_SUPPORT)),TRUE)
MINCPATH	+= MS_MMI/source/mmi_app/app/magic_tower/h
MSRCPATH	+= MS_MMI/source/mmi_app/app/magic_tower/c
SOURCES		+= magic_tower.c
endif


ifeq ($(strip $(MMI_AUTO_UPDATE_TIME_SUPPORT)),TRUE)
MINCPATH += MS_MMI/source/mmi_app/app/aut/h
MSRCPATH += MS_MMI/source/mmi_app/app/aut/c
SOURCES	 += mmiaut_net_fun.c mmiaut_socket.c mmiaut_net_wintab.c mmiaut_api.c
endif

ifeq ($(strip $(CMCC_UI_STYLE)), TRUE)
SOURCES	 +=     mmics_export.c mmics_id.c mmics_main.c mmics_menutable.c mmics_nv.c mmics_wintab.c               
endif 
  				
  
ifeq ($(strip $(APP_PRODUCT_DM)), TRUE)   
SOURCES	 +=     mmiengtd_menutable.c mmiengtd_win.c mmiengtd_nv.c mmiengtd_main.c mmiengtd_id.c               
endif 

ifeq ($(strip $(TTS_SUPPORT)), IFLYTEK)
SOURCES	 +=     TTS_api.c TTS_audio.c 
endif 
  
ifneq ($(strip $(FM_SUPPORT)), NONE)
SOURCES	 +=     mmifm_app.c mmifm_nv.c mmifm_wintab.c mmifm_id.c               
endif 
     
ifeq ($(strip $(PIC_EDITOR_SUPPORT)), TRUE)
SOURCES	 +=     mmipic_edit.c mmipic_edit_wintab.c mmipic_id.c mmipic_menutable.c
endif 
            
ifeq ($(strip $(CMMB_SUPPORT)), TRUE)
SOURCES	 +=     mmimtv_data.c mmimtv_main.c mmimtv_nv.c mmimtv_osd_display.c mmimtv_wintab.c mbbms_api_dummy.c mmimbbms_main.c mmimbbms_wintab.c mmimtv_simu.c mmimtv_menutable.c
endif

ifeq ($(strip $(ATV_SUPPORT)), TRUE)
SOURCES	 +=     mmiatv_data.c mmiatv_main.c mmiatv_wintab.c mmiatv_nv.c mmiatv_menutable.c mmiatv_simu.c
endif                                 

ifeq ($(strip $(KURO_SUPPORT)), TRUE)
SOURCES	 +=     kdbparser.c mmikur_bt.c mmikur_lyric.c mmikur_menutable.c mmikur_musicstyle.c mmikur_nv.c mmikur_wintab.c kuro_depends.c
endif   

ifeq ($(strip $(UI_SPRITE_ENABLE)), TRUE)
SOURCES	 +=     mmiidle_sprite.c
endif   

#ifeq ($(strip $(STREAMING_SUPPORT)), TRUE)
#SOURCES	 +=     mmist_id.c tester_cal_ral.c mmist.c mmist_nv.c app_common_event_handlers.c mmist_wintab.c nexsal.c \
#                app_reg_sys2sal.c nexcr_bbamr.c app_streaming_event_handlers.c mmist_menutable.c nexcr_mv8602.c
#endif   
                
                
ifeq ($(strip $(OCR_SUPPORT)), TRUE)
SOURCES	 +=     mmiocr_id.c mmiocr.c mmiocr_lib.c mmiocr_wintab.c
endif                                

#ifeq ($(strip $(VT_SUPPORT)), TRUE)
SOURCES	 +=    mmivt_kernel_324Adapter.c mmivt_kernel_process.c mmivt_kernel_refAdapter.c mmivt_main.c \
                mmivt_ui.c mmivt_id.c mmivt_nv.c
#endif


ifneq ($(strip $(QQ_SUPPORT)), NONE)
ifeq ($(strip $(QQ_SUPPORT)),2009)
MCFLAG_OPT	+= -DQQ_SUPPORT_2009
endif
MSRCPATH 	+= MS_MMI/source/mmi_app/app/qq/c
MINCPATH 	+= MS_MMI/source/mmi_app/app/qq/h
SOURCES	+= mmiqq_ui.c  mmiqq_file.c mmiqq_input.c mmiqq_main.c mmiqq_socket.c mmiqq_system.c 
endif


ifeq ($(strip $(GPS_SUPPORT)), TRUE)
SOURCES	 +=     mmigps_wintab.c mmigps_nv.c mmigps.c mmgps_menutable.c mmigps_simu.c mmigps_osapi.c
endif

ifeq ($(strip $(BROWSER_SUPPORT)), NETFRONT)
SOURCES	 +=    mmiwww.c mmiwww_func.c mmiwww_menutab.c mmiwww_netfront.c mmiwww_netfront_cmd.c mmiwww_nv.c \
                mmiwww_slim_peer_alt.c mmiwww_slim_peer_debug.c mmiwww_slim_peer_file.c mmiwww_slim_peer_net.c \
                mmiwww_slim_peer_system.c mmiwww_slim_peer_time.c mmiwww_slim_peer_wave.c mmiwww_wintab.c mmiwww_bookmark.c
MCFLAG_OPT		+=-DDL_SUPPORT
SOURCES	 +=    mmidl.c mmidl_file.c mmidl_func.c mmidl_menutab.c mmidl_nv.c mmidl_wintab.c mmiwww_id.c
endif

ifeq ($(strip $(MMI_MOCOR_SAMPLE)), TRUE)
SOURCES		+=  sample_anim_ctrl.c sample_dropdownlist_ctrl.c sample_editbox_ctrl.c sample_form_ctrl.c \
					sample_iconlist_ctrl.c sample_id.c sample_im.c sample_main.c sample_menutable.c sample_nv.c \
					sample_richtext_ctrl.c sample_tab_ctrl.c sample_test_ctrl.c
endif

ifeq ($(strip $(PIM_SUPPORT)), TRUE)
SOURCES		+=  mmipim_id.c mmipim_menutable.c mmipim_nv.c mmipim_wintab.c mmipim.c mmipim_pb.c Vcalendar_parse.c Vcard_parse.c 
endif

ifeq ($(strip $(BROWSER_SUPPORT)), DORADO)
SOURCES	 +=    brw_wtai.c brw_temp.c brw_core_adapter.c \
               brw_gwt.c brw_dlinterface.c brw_history.c brw_control.c brw_httpinterface.c brw_snapshot.c brw_plinterface.c brw_utility.c \
               mmibrowser_api.c mmibrowser_memutable.c mmibrowser_bookmark.c mmibrowser_wintable_history.c mmibrowser_wintable_snapshot.c \
               mmibrowser_setting.c mmibrowser_wintable.c mmibrowser_nv.c mmibrowser_wintable_bookmark.c mmibrowser_wintable_setting.c \
               mmibrowser_dummy.c mmibrowser_wintable_flowrate.c
endif   

ifeq ($(strip $(MMS_SUPPORT)), DORADO)
SOURCES	 += mmimms_control_main.c mmimms_edit.c mmimms_editwin.c  mmimms_file.c mmimms_menutable_new.c mmimms_net.c mmimms_id.c\
                    mmimms_previewwin.c mmimms_push.c mmimms_setting.c mmimms_settingwin.c mmimms_main_new.c mmimms_waitingwin.c
endif 

ifeq ($(strip $(ASP_SUPPORT)), TRUE)
SOURCES	 += mmiasp_api.c mmiasp_cortrol_layer.c mmiasp_id.c mmiasp_menutable.c mmiasp_nv.c mmiasp_wintab.c
endif  

ifeq ($(strip $(DCD_SUPPORT)), TRUE)
SOURCES	 += mmidcd_file.c mmidcd_http.c mmidcd_id.c mmidcd_main.c mmidcd_menutable.c mmidcd_nv.c mmidcd_wintab.c mmidcd_xml_parse.c mmidcd_setting.c
endif  


ifeq ($(strip $(DEV_MANAGE_SUPPORT)), TRUE)
SOURCES	 += mmdm_id.c mmidm_app.c mmidm_menutable.c mmidm_nv.c mmidm_wintab.c mmidm_task.c mmidm_internal.c \
            mmidm_pl_mmi.c mmidm_pl_os.c mmidm_pl_comm.c mmidm_pl_string.c 
else
ifeq ($(strip $(DM_ONLY_SELFREG_SUPPORT)), TRUE)
SOURCES  += mmdm_id.c mmidm_app.c mmidm_wintab.c mmidm_menutable.c mmidm_nv.c 
endif
endif  

#ifeq ($(strip $(CAMERA_SUPPORT)), TRUE)
SOURCES  += mmidc_full_osd_display.c mmidc_flow.c mmidc_gui.c \
            mmidc_save.c mmidc_setting.c mmidc_main_wintab.c \
            mmidc_window_option.c mmidc_setting_nv.c mmidc_osd_option.c
#else
SOURCES  += mmidc_export.c
#endif

ifeq ($(strip $(JAVA_SUPPORT)), IA)               
SOURCES	       += mmijava_func.c mmijava_nv.c mmijava_wintab.c java_menutable.c mmijava_id.c \
		  AJEvent.c jblend_logFiler.c jwe.c jwe_eime.c jwe_log.c jwe_log_chk.c \
		  jwe_thread_com.c jwe_thread_kve.c \
		  jas_gfx_font.c AudioClient.c \
		  mediaControl.c media_midiControl.c media_toneControl.c media_mp3Control.c media_waveControl.c media_amrControl.c media_aacControl.c media_fileStream.c \
		  JgurToolKit.c JkMediaControl.c JkMediaCustomProtocol.c \
		  JkMediaMIDIDrv.c JkMediaStream.c JkMediaTone.c JkSoftkey.c JkUDP.c UDPResource.c \
		  UDPTaskBase.c UDPTaskProcess.c \
		  kjava_adv_fs.c kjava_sys.c kjava_sys_core.c kjava_sys_data_content.c \
		  kjava_sys_device.c kjava_sys_ext.c kjava_sys_ext_cert.c kjava_sys_fs.c kjava_sys_gfx.c \
		  kjava_sys_gfx_font_intra.c kjava_sys_http.c kjava_sys_log_out.c kjava_sys_pe.c \
		  kjava_sys_push.c kjava_sys_serial.c kjava_sys_sock.c kjava_sys_wma.c kjava_dev_fs.c JkPIM.c pim_contact.c pim_common.c JkVmBackground.c \
		  JkVmTimer.c JkCpuCache.c JkCommConnection.c
endif

ifeq ($(strip $(JAVA_SUPPORT)), SUN)
SOURCES	 += preload00_gen.c mmijava_main.c  mmijava_export.c mmijava_id.c mmijava_nv.c
endif 
 
ifeq ($(strip $(UI_P3D_SUPPORT)), TRUE)
MSRCPATH +=  build/$(PROJECT)_builddir/tmp  
SOURCES	 +=  $(PROJECT)_ui_special_effect_table.c
endif       

    
ifeq ($(strip $(VIDEO_PLAYER_SUPPORT)), TRUE)
 SOURCES	 += mmivp_api.c mmivp_bookmarklist.c mmivp_fsm.c mmivp_historylist.c mmivp_locallist.c \
			mmivp_nv.c mmivp_setting.c mmivp_wintable.c mmivp_id.c mmivp_menutable.c
ifneq ($(strip $(STREAMING_SUPPORT)), TRUE)
 SOURCES	 +=mmivp_dummy.c
endif
endif


ifeq ($(strip $(STREAMING_SUPPORT)), TRUE)
ifeq ($(strip $(MOBILE_VIDEO_SUPPORT)), TRUE)
SOURCES	      += mv_fs_api.c  mv_mm_api.c  mv_net_api.c  mv_sms_api.c mv_base_api.c  \
                 mv_contact_api.c mv_date_api.c mv_output_api.c mv_player_api.c mv_string_api.c mv_ui_api.c mv_timer_api.c \
                 mv_path_transfer.c mmimv_wintab.c mmimv_id.c mmimv.c mmimv_export.c
endif
endif


  
ifeq ($(strip $(PLATFORM)), SC8800H)
SOURCES		+=   dummy_mneng_api.c    
endif  
ifeq ($(strip $(PLATFORM)), SC8800G)
SOURCES		+=   dummy_mneng_api.c    
endif             
ifeq ($(strip $(PLATFORM)), SC6600L)
MCFLAG_OPT += -DSC6600L_ARM7
endif    

ifeq ($(strip $(PLATFORM)), SC6800H)
SOURCES		+=   dummy_mneng_api.c    
endif

ifneq ($(strip $(WIFI_SUPPORT)), NONE)
ifeq ($(strip $(WLAN_SUPPORT)), TRUE)
MINCPATH += MS_MMI/source/mmi_app/app/wlan/h \
            MS_MMI/source/mmi_app/app/wifi/wifi_supplicant/inc  
MSRCPATH += MS_MMI/source/mmi_app/app/wlan/c \
            MS_MMI/source/mmi_app/app/wifi/wifi_supplicant/src \
            MS_MMI/source/mmi_app/app/wifi/wifi_test 
else
MINCPATH += MS_MMI/source/mmi_app/app/wifi/h \
            MS_MMI/source/mmi_app/app/wifi/wifi_supplicant/inc  
MSRCPATH += MS_MMI/source/mmi_app/app/wifi/c \
            MS_MMI/source/mmi_app/app/wifi/wifi_supplicant/src \
            MS_MMI/source/mmi_app/app/wifi/wifi_test 
endif
ifeq ($(strip $(WLAN_SUPPORT)), TRUE)
SOURCES	 += mmiwlan_id.c mmiwlan_manager.c mmiwlan_menutable.c mmiwlan_nv.c mmiwlan_profile.c mmiwlan_win.c \
            wifisupp_api.c wifisupp_main.c wifisupp_adap_none.c  wifi_test.c  wifisupp_eut.c
else
SOURCES	 += mmiwifi_id.c mmiwifi_manager.c mmiwifi_menutable.c mmiwifi_nv.c mmiwifi_profile.c mmiwifi_win.c \
            wifisupp_api.c wifisupp_main.c wifisupp_adap_none.c  wifi_test.c  wifisupp_eut.c
endif
  ifeq ($(strip $(WIFI_SUPPORT)), AR6102)
  MINCPATH += MS_Customize/source/product/driver/wifi/ar6102
  SOURCES	 += wifisupp_adap_atheros.c wifisupp_eut_ar6102.c
  endif
  ifeq ($(strip $(WIFI_SUPPORT)), AR6302)
  MINCPATH += MS_Customize/source/product/driver/wifi/ar6302
  SOURCES	 += wifisupp_adap_atheros.c wifisupp_eut_ar6302.c
  endif
  ifeq ($(strip $(WIFI_SUPPORT)), CSR6026)
  MINCPATH +=  Third-party/wifi_csr/fw/include
  MINCPATH +=  Third-party/wifi_csr/wifi/include
  MCFLAG_OPT +=  -DCSR_WIFI_NME_ENABLE

#ifeq ($(strip $(CSR_LOG)), TRUE)  
#  MCFLAG_OPT +=  -DCSR_LOG_ENABLE -DCSR_LOG_INCLUDE_FILE_NAME_AND_LINE_NUMBER
#endif
  SOURCES	 += wifisupp_adap_csr.c wifisupp_adap_csr_sef.c wifisupp_eut_csr6026.c wifisupp_adap_csr_mib_openphone_v1_0.c
  endif  
endif

ifeq ($(strip $(MMIWIDGET_SUPPORT)), TRUE)
SOURCES		+=   mmiwidget.c mmiwidget_clock.c mmiwidget_display.c mmiwidget_mp3.c \
                mmiwidget_nv.c mmiwidget_pb.c mmiwidget_id.c mmitheme_widget.c mmiwidget_memo.c mmiwidget_shortcut_menu.c \
                mmiwidget_calendar.c  mmiwidget_network_name.c  mmiwidget_custom_word.c  mmiwidget_NewSms.c \
                mmiwidget_calllog.c   mmiwidget_fm.c mmiwidget_menutable.c mmiwidget_alarm.c mmiwidget_shortcut_set.c \
                mmiwidget_Aclock.c mmiwidget_elve.c mmiwidget_Search.c mmiwidget_dcd.c mmiwidget_dual_clock.c mmiwidget_dual_aclock.c \
                mmiwidget_autoanswer_log.c
endif

ifeq ($(strip $(PUSH_EMAIL_SUPPORT)), TRUE)
SOURCES += mail_file.c mail_util.c mail_setting.c mail_main.c mail_welcom.c mmimail_wintab.c mmimail_edit.c \
           mmimail_read.c mmimail_menutable.c mmimail_id.c mail_export.c 
endif
# Auto Testing Support
ifeq ($(strip $(ATEST_SUPPORT)), TRUE)
MSRCPATH +=  MS_MMI/source/mmi_app/app/atest/c
MINCPATH +=  MS_MMI/source/mmi_app/app/atest/h
SOURCES	 +=  atest_main.c atest_key_step.c atest_location.c atest_pb.c atest_r8.c atest_ota.c
endif

#存在复杂文本,需要严格的计算字符串的宽高
#需要临时变量做或判断
#arabic, thai, hindi, hebrew, tibet等语言为复杂文本
ifeq ($(strip $(IM_ARABIC_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

ifeq ($(strip $(IM_PERSIAN_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

ifeq ($(strip $(IM_URDU_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

ifeq ($(strip $(IM_THAI_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

ifeq ($(strip $(IM_HINDI_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

ifeq ($(strip $(IM_HEBREW_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

ifeq ($(strip $(IM_BENGALI_SUPPORT)), TRUE)
MCFLAG_OPT_COMPLEX_TEMP		?=  -DCOMPLEX_TEXT_SCRIPT
endif

MCFLAG_OPT += $(MCFLAG_OPT_COMPLEX_TEMP)
#存在复杂文本,需要严格的计算字符串的宽高

ifeq ($(strip $(BAIJIAXING_SUPPORT)), TRUE)
SOURCES += mmi_baijiaxing.c
endif

