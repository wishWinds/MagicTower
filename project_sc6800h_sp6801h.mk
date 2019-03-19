# *************************************************************************
# Feature Options (For User)
# !!!!!!!! The customer value can be modified in this option part.!!!!!!!!!
# !!!!!!!! If modification is in need,please find support from SPRD CPM or FAE.!!!!!!!!!
# !!!!!!!! 此部分Options 的值客户一般可以修改.!!!!!!!!!
# !!!!!!!! 此部分修改，最好与展讯客户经理(CPM)或技术支持工程师(FAE)沟通寻求支持.!!!!!!!!! 
# *************************************************************************
BAIJIAXING_SUPPORT = TRUE		# BAIJIAXING_SUPPORT
									# Option1:TRUE
									# Option2:FALSE

MAGIC_TOWER_SUPPORT = TRUE				### MAGIC TOWER Support
								#Option1:TRUE
								#Option2:FALSE
								
GPRS_SUPPORT =   TRUE         ### GRPS Support:客户不能修改该宏，如需修改需联系展讯技术支持人员
                                        # Option1:TRUE
                                        # Option2:FALSE  
CUSTOM_CFLAG    = -g             # CUSTOM CFLAG
                                        # Option1:-g
                                        # Option2: 

RELEASE_INFO    = FALSE          ### RELEASE version
                                        # Option1:TRUE
                                        # Option2:FALSE

ASSERT_TYPE_SUPPORT   = ASSERT   ### ASSERT TYPE SUPPORT
                                        # Option1:ASSERT
                                        # Option2:WARNING

TRACE_INFO_SUPPORT = TRUE        ### TRACE INFO SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

NOR_SINGLEBANK_SUPPORT= FALSE    ### Support Single Bank Type Norflash:
                                        # Option1:FALSE
                                        # Option1:TRUE

MULTI_BIN_SUPPORT   = FALSE      ### Multi Output Image Support(Please Refer To Project Scatter File)
                                        # Option1:TRUE
                                        # Option2:FALSE

FONT_TYPE_SUPPORT   = VECTOR       ### font type support:
                                        # Option1:NONE   #define FONT_TYPE_SUPPORT_NONE
                                        # Option2:GRAY   #define FONT_TYPE_SUPPORT_GRAY
                                        # Option3:VECTOR #define FONT_TYPE_SUPPORT_VECTOR

MMI_MULTI_GREEN_KEY = DUAL         ### MMI_MULTI_GREEN_KEY Support for Dial Key
                                        # Option1:SINGLE    #define MMI_MULTI_GREEN_KEY_SINGLE
                                        # Option2:DUAL       #define MMI_MULTI_GREEN_KEY_DUAL
                                        # Option3:TRI          #define MMI_MULTI_GREEN_KEY_TRI
                                        # OPtion4:QUAD       #define MMI_MULTI_GREEN_KEY_QUAD

MMI_MULTI_SIM_SYS = DUAL        ### Platform Support Multi Sim Card Number:
                                        # Option1:SINGLE    #define MMI_MULTI_SIM_SYS_SINGLE
                                        # Option2:DUAL       #define MMI_MULTI_SIM_SYS_DUAL
                                        # Option3:TRI          #define MMI_MULTI_SIM_SYS_TRI
                                        # OPtion4:QUAD       #define MMI_MULTI_SIM_SYS_QUAD
                                        
MULTI_SIM_SYS_QUAD_TO_DUAL_WITHOUT6302 = TRUE  ### if Platform not use 6402 to expand to TRI or QUAD sim,use TRUE,or USE FALSE
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
KEYPAD_TYPE  = TYPICAL_KEYPAD    ### KEYPAD TYPE
                                        # Option1:TYPICAL_KEYPAD   #define KEYPAD_TYPE_TYPICAL_KEYPAD
                                        # Option2:QWERTY_KEYPAD    #define KEYPAD_TYPE_QWERTY_KEYPAD 
                                        # Option3:COMPACT_KEYPAD   #define KEYPAD_TYPE_COMPACT_KEYPAD 

TOUCHPANEL_TYPE	= HW            ### Touch panel type
                                        # Option1 SW      #define TOUCHPANEL_TYPE_SW
                                        # Option2 HW      #define TOUCHPANEL_TYPE_HW
                                        # Option3 NONE    #define TOUCHPANEL_TYPE_NONE

TOUCH_PANEL_HWICON_SUPPORT    =  NONE   ### touch panel hw support: 
                                             # Option1:DIAL_PB_SMS_MAINMENU    #define TOUCH_PANEL_HWICON_SUPPORT_DIAL_PB_SMS_MAINMENU
                                             # Option2:MAINMENU_PB_SMS_CAMERA_MP4  #define TOUCH_PANEL_HWICON_SUPPORT_MAINMENU_PB_SMS_CAMERA_MP4
                                             # Option3:MAINMENU_SMS_PB_DIAL_MP3    #define TOUCH_PANEL_HWICON_SUPPORT_MAINMENU_SMS_PB_DIAL_MP3
                                             # Option4:NONE

BB_DRAM_TYPE    = 32MB_16BIT            ### DRAM Type:
                                        # Option1:NONE     #define BB_DRAM_TYPE_NONE
                                        # Option1:32MB_16BIT     #define BB_DRAM_TYPE_32MB_16BIT
                                        # Option2:32MB_32BIT_13R #define BB_DRAM_TYPE_32MB_32BIT_13R
                                        # Option3:32MB_32BIT_12R #define BB_DRAM_TYPE_32MB_32BIT_12R
                                        # Option4:64MB_16BIT     #define BB_DRAM_TYPE_64MB_16BIT
                                        # Option5:64MB_32BIT     #define BB_DRAM_TYPE_64MB_32BIT

LCD_FMARK_SUPPORT = FALSE        ### if support lcd fmark:
                                        # Option1:TRUE
                                        # Option2:FALSE  
				                                         
MMI_RES_DIR    = mmi_res_240x320 # resource directory
                                        # Option1:mmi_res_176x220
                                        # Option2:mmi_res_240x320
                                        # Option3:mmi_res_240x400
                                        # Option4:mmi_res_320x480
                                        
MMI_RES_ORIENT = BOTH            ### screen orientation
                                        # Option1:PORTRAIT     #define MMI_RES_ORIENT_PORTRAIT
                                        # Option2:LANDSCAPE    #define MMI_RES_ORIENT_LANDSCAPE
                                        # Option3:BOTH         #define MMI_RES_ORIENT_BOTH

MAINLCD_DEV_SIZE    = 240X320    ### Resolution Of Main LCD Device,  MAINLCD_SIZE is the size of MMI
                                 # Option1:176X220    #define MAINLCD_DEV_SIZE_176X220
                                 # Option2:220X176    #define MAINLCD_DEV_SIZE_220X176
                                 # Option3:240X320    #define MAINLCD_DEV_SIZE_240X320
                                 # Option4:320X240    #define MAINLCD_DEV_SIZE_320X240
                                 # Option5:240X400    #define MAINLCD_DEV_SIZE_240X400                                    
                                 # Option6:400X240    #define MAINLCD_DEV_SIZE_400X240
                                 # Option7:320X480    #define MAINLCD_DEV_SIZE_320X480
                                 # Option8:480X320    #define MAINLCD_DEV_SIZE_480X320

MAINLCD_SIZE    = 240X320        ### Resolution Of Main LCD: 
                                        # Option1:320X480    #define MAINLCD_SIZE_320X480
                                        # Option2:240X400    #define MAINLCD_SIZE_240X400                                        
                                        # Option3:240X320    #define MAINLCD_SIZE_240X320
                                        # Option4:176X220    #define MAINLCD_SIZE_176X220

MAINLCD_LOGIC_ANGLE = 0          ### Mainlcd logic angle
                                 # Option1:0	    #define MAINLCD_LOGIC_ANGLE_0
                                 # Option2:90	    #define MAINLCD_LOGIC_ANGLE_90
                                 # Option3:180	    #define MAINLCD_LOGIC_ANGLE_180
                                 # Option4:270	    #define MAINLCD_LOGIC_ANGLE_270

SUBLCD_DEV_SIZE  = NONE          ### Resolution Of Main LCD(None To Disable Related Opeartions Of SUBLCD):
                                 # Option1:NONE       #define SUBLCD_DEV_SIZE_NONE
                                 # Option2:96X64      #define SUBLCD_DEV_SIZE_96X64
                                 # Option3:96X96      #define SUBLCD_DEV_SIZE_96X96                                         

SUBLCD_LOGIC_ANGLE = 0           ### Sublcd logic angle
                                 # Option1:0	    #define SUBLCD_LOGIC_ANGLE_0
                                 # Option2:90	    #define SUBLCD_LOGIC_ANGLE_90
                                 # Option3:180	    #define SUBLCD_LOGIC_ANGLE_180
                                 # Option4:270	    #define SUBLCD_LOGIC_ANGLE_270

SUBLCD_SIZE     = NONE           ### Resolution Of Main LCD(None To Disable Related Opeartions Of SUBLCD):
                                        # Option1:NONE       #define SUBLCD_SIZE_NONE
                                        # Option2:96X64      #define SUBLCD_SIZE_96X64
                                        # Option3:96X96      #define SUBLCD_SIZE_96X96

SUBLCD_LOGIC_ANGLE = 0           ### Sublcd logic angle
                                        # Option1:0	    #define SUBLCD_LOGIC_ANGLE_0
                                        # Option2:90	    #define SUBLCD_LOGIC_ANGLE_90
                                        # Option3:180	    #define SUBLCD_LOGIC_ANGLE_180
                                        # Option4:270	    #define SUBLCD_LOGIC_ANGLE_270
MAIN_LCD_DISPLAY_LAYER_NUM = 1   ### Support display layer num of main lcd
				 																 # Option1:1		#define MAIN_LCD_DISPLAY_LAYER_NUM_1
																				 # Option2:2		#define MAIN_LCD_DISPLAY_LAYER_NUM_2 
																				 # Option3:3		#define MAIN_LCD_DISPLAY_LAYER_NUM_3  
																				
SUB_LCD_DISPLAY_LAYER_NUM = 0   ### Support display layer num of sub lcd
																			# Option1:0		#define SUB_LCD_DISPLAY_LAYER_NUM_0  
																			# Option2:1		#define SUB_LCD_DISPLAY_LAYER_NUM_1
										
DISPLAY_PIXELDEPTH_MAX = 32      ### depth of display pixel on lcd
																				# Option1:16    #define DISPLAY_PIXELDEPTH_MAX_16
																				# Option2:32    #define DISPLAY_PIXELDEPTH_MAX_32

SPECIAL_EFFECT_ICON_SIZE = 48X48 ### Wide x Height of special effect icon
                                        # Option1:48X48      if MAINLCD_SIZE = 240X320  or 240X400
                                        # Option2:45X40      if MAINLCD_SIZE = 176X220 
                                        # Option3:48X48      if MAINLCD_SIZE = 320X480

LOW_MEMORY_SUPPORT  = FALSE      ### Low Memory Size Requirement:
                                        # Option1:FALSE
                                        # Option2:TRUE

UI_P3D_SUPPORT     = TRUE        ### UI P3D Effect Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

MMIWIDGET_SUPPORT = TRUE         ### Widget support
                                        # Option1:TRUE  
                                        # Option2:FALSE

FM_SUPPORT      = CL6012X         ### FM Function Support:
                                        # Option0:NONE     #define FM_SUPPORT_NONE
                                        # Option1:CL6012X   #define FM_SUPPORT_CL6012X

TTS_SUPPORT    =    IFLYTEK      ### TTS Support
                                        # Option1:NONE     #define TTS_SUPPORT_NONE
                                        # Option2:IFLYTEK  #define TTS_SUPPORT_IFLYTEK

MV_SUPPORT    = 	   IFLYTEK      ### Magic voice Support
                                        # Option1:NONE     #define MV_SUPPORT_NONE
                                        # Option2:IFLYTEK  #define MV_SUPPORT_IFLYTEK

ASP_SUPPORT    = TRUE            ### ASP Support:
                                        # Option1:TRUE
                                        # Option2:FALSE                                        
                                                                                                                  
KURO_SUPPORT     = FALSE         ### KURO Player Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                       
MULTI_THEME_SUPPORT   = TRUE     ### theme Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

PB_SEARCH_SURPPORT = NUMBER          ### Phonebook Surpported search algorithm:
                                        # Option1:NONE	    #define PB_SEARCH_SURPPORT_NONE    no algorithm surpported
                                        # Option2:NUMBER    #define PB_SEARCH_SURPPORT_NUMBER  rush search surpported
                                        # Option3:CHAR      #define PB_SEARCH_SURPPORT_CHAR 

HOME_LOCATION_INQUIRE_SUPPORT = TRUE     ### HOME_LOCATION_INQUIRE_SUPPORT Support:
                                        	# Option1:TRUE
                                        	# Option2:FALSE	

ATV_SUPPORT     = TRUE           ### ATV_SUPPORT Player And Driver Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
ATV_TYPE  = TLG1120               ### Analog TV Type:
                                        # Option1:TLG1120     #define ATV_TYPE_TLG1120
                                        # Option2:QN8610      #define ATV_TYPE_QN8610

CMMB_SUPPORT     = FALSE         ### CMMB Player And Driver Support:
                                        # Option1:FALSE

ifeq ($(strip $(GPRS_SUPPORT)), TRUE)
MBBMS_SUPPORT    = FALSE         ### MBBMS Player And Driver Support:
                                        # Option1:FALSE

endif

CMMB_DAC_TYPE    = HYBRID        ### support 3 dac mode
                                        # Option1:AP        #define CMMB_DAC_TYPE_AP
                                        # Option2:V         #define CMMB_DAC_TYPE_V
                                        # Option3:HYBRID    #define CMMB_DAC_TYPE_HYBRID

STREAMING_SUPPORT = TRUE    ### Switch Streaming Support:
                                        # Option1:TRUE
                                        # Option2:FALSE                                         

VIDEO_PLAYER_SUPPORT    = TRUE    ### video player:
																		# Option1:TRUE
																		# Option2:FALSE
					
TYPE_3GP_SUPPORT = MP4         ### 3GP type format Support:
                                        # Option1:NONE       #define TYPE_3GP_SUPPORT_NONE
                                        # Option2:MP4        #define TYPE_3GP_SUPPORT_MP4
                                        # Option3:MJPEG      #define TYPE_3GP_SUPPORT_MJPEG

PIC_EDITOR_SUPPORT   = TRUE      ### Picture Editor Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
PIC_GLIDE_SUPPORT = TRUE         ### Picture glide preview support
                                        # Option1:TRUE  
                                        # Option2:FALSE
                                        
PIC_ZOOM_SUPPORT = TRUE          ### Picture zoom
                                        # Option1:TRUE  
                                        # Option2:FALSE

WIFI_SUPPORT   =   NONE              ### wifi Support
                                        # Option1:NONE           #define WIFI_SUPPORT_NONE
                                        # Option2:AR6102         #define WIFI_SUPPORT_AR6102
                                        # Option3:AR6302         #define WIFI_SUPPORT_AR6302
                                        # Option4:CSR6026        #define WIFI_SUPPORT_CSR6026

ifeq ($(strip $(GPRS_SUPPORT)), TRUE)
MMI_AUTO_UPDATE_TIME_SUPPORT = TRUE     ### MMI_AUTO_UPDATE_TIME_SUPPORT
                                        	# Option1:TRUE
                                        	# Option2:FALSE

DCD_SUPPORT    = FALSE            ### dcd support:
                                        # Option1:TRUE
                                        # Option2:FALSE

BROWSER_SUPPORT = DORADO         ### Browser SW Supplier:
                                        # Option1:NONE     #define BROWSER_SUPPORT_NONE
                                        # Option2:DORADO    #define BROWSER_SUPPORT_DORADO
                                        # Option3:NETFRONT    #define BROWSER_SUPPORT_NETFRONT

ifeq ($(strip $(BROWSER_SUPPORT)), NETFRONT)
NETFRONT_SUPPORT = VER40         ### Browser SW Supplier:
                                        # Option1:VER35     #define NETFRONT_SUPPORT_VER35
                                        # Option2:VER40     #define NETFRONT_SUPPORT_VER40
endif

MMS_SUPPORT = DORADO             ### MMS SW Supplier:
                                        # Option1:NONE     #define MMS_SUPPORT_NONE
                                        # Option2:DORADO    #define MMS_SUPPORT_DORADO

DEV_MANAGE_SUPPORT = FALSE        ### device manage support:
                                        # Option1:TRUE
                                        # Option2:FALSE

PIM_SUPPORT     = FALSE           ### PIM(personal Information Manage) Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

JAVA_SUPPORT     = NONE            ### JAVA SW Supplier:
                                        # Option1:IA          #define JAVA_SUPPORT_IA
                                        # Option2:NONE        #define JAVA_SUPPORT_NONE

QQ_SUPPORT = NONE             ### QQ Support
                                        # Option1:2009     #define QQ_SUPPORT_2009 
                                        # Option2:NONE        #define QQ_SUPPORT_NONE 
endif
                                        
PCLINK_SUPPORT    = TRUE         ### PCLink function
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        # work for TCPIP_SUPPORT = TRUE  

USB_WEBCAMERA_SUPPORT = TRUE     ### USB Web Camera Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                     
SCREENSAVER_SUPPORT = TRUE       ### screensaver support:
                                        # Option1:TRUE
                                        # Option2:FALSE


PRODUCT_CONFIG = sc6800h_sp6801h    # MS_Customize/source/product/config;scf file;nv;resource
                                        # default: project name 

PRODUCT_BASELIB_DIR = $(PROJECT) # Dir name for base lib in MS_Code\lib\
                                        # default: project name 

MOTION_SENSOR_TYPE  = ST_LIS35DE   ### MOTION SENSOR SUPPORT:
                                        # Option1:NONE
                                        # Option2:ST_LIS35DE
                                        # Option3:MEMS_DTOS
                                        
BLUETOOTH_SUPPORT = NONE    ### Bluetooth Chip Type: 
                                        # Option0:NONE      #define BLUETOOTH_SUPPORT_NONE
                                        # Option1:CSR_BC6   #define BLUETOOTH_SUPPORT_CSR_BC6
                                        # Option2:CSR_BC4_6 #define BLUETOOTH_SUPPORT_CRS_BC4_6
                                        # Option3:ATHR_AR3002
EXSTERN_WIFI_CO_EXIST			= FALSE  ###Co-exist atheros with csr

BT_SHARE_XTL_SUPPORT    = FALSE  ### Switch Of BT Share Crystal Support
                                        # Option1:TRUE
                                        # Option2:FALSE

USB_SUPPORT      = TRUE          ### USB TXer Type: 
                                        # Option1:TRUE
                                        # Option2:FALSE

SHELL_DEBUG_SUPPORT   = TRUE     ### SHELL_DEBUG_SUPPOR
                                        # Option1:TRUE
                                        # Option2:FALSE

EMAIL_SUPPORT     = FALSE        ### EMAIL Client:
                                        # Option1:FALSE    
              
GPS_SUPPORT      = FALSE         ### Switch Of GPS Module Support
                                        # Option1:FALSE

MULTI_SIM_GSM_CTA_SUPPORT = FALSE               ### MULTI SIM GSM CTA Support
                                        # Option1:TRUE
                                        # Option2:FALSE

GPIO_SIMULATE_SPI_SUPPORT = FALSE       ### To simulate SPI by GPIO
                                        # Option1:TRUE
                                        # Option2:FALSE  

GPIO_SPI_SUPPORT = NONE     ### Quadsim SPI by GPIO mode:
                                        # Option1:NONE                 #define GPIO_SPI_SUPPORT_NONE
                                        # Option2:SINGLE               #define GPIO_SPI_SUPPORT_SINGLE
                                        # Option3:DUAL                 #define GPIO_SPI_SUPPORT_DUAL
                                        # Option4:DUAL_SAMEGPIO_CLKDO  #define GPIO_SPI_SUPPORT_DUAL_SAMEGPIO_CLKDO
                                        # Option5:DUAL_REALSPI_CLKDO   #define GPIO_SPI_SUPPORT_DUAL_REALSPI_CLKDO

IM_ENGINE   	  = CSTAR      ### Im Engine Support:
                                        # Option1:CSTAR    #define IM_ENGINE_CSTAR

IM_HANDWRITING    = HANWANG      ### Handwriting SW Supplier(None to Disable):
                                        # Option1:HANWANG   #define IM_HANDWRITING_HANWANG
                                        # Option2:NONE      #define IM_HANDWRITING_NONE


IM_SIMP_CHINESE_SUPPORT	= TRUE	### SIMPLE CHINESE SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
IM_TRAD_CHINESE_SUPPORT = FALSE	  ### TRAD CHINESE SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
IM_ARABIC_SUPPORT    = TRUE      ### ARABIC SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_THAI_SUPPORT    = TRUE       ### THAI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_VIETNAMESE_SUPPORT  = TRUE   ### VIETNAMESE SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_PORTUGUESE_SUPPORT = TRUE    ### PORTUGUESE SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_RUSSIAN_SUPPORT    = TRUE     ### RUSSIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_HINDI_SUPPORT    = TRUE       ### HINDI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_INDONESIAN_SUPPORT  = TRUE   ### INDONESIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_GREEK_SUPPORT    = TRUE      ### GREEK SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_PERSIAN_SUPPORT    = TRUE   ### PERSIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_MALAY_SUPPORT    = TRUE      ### MALAY SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_FRENCH_SUPPORT    = TRUE    ### FRENCH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_TAGALOG_SUPPORT    = FALSE    ### TAGALOG SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_URDU_SUPPORT    = TRUE       ### URDU SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_HUNGARIAN_SUPPORT    = TRUE  ### HUNGARIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ITALIAN_SUPPORT    = TRUE    ### ITALIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_TURKISH_SUPPORT    = TRUE   ### TURKISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_SPANISH_SUPPORT    = TRUE    ### SPANISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_GERMAN_SUPPORT    = TRUE     ### GERMAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ROMANIAN_SUPPORT    = TRUE    ### ROMANIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_SLOVENIAN_SUPPORT    = TRUE     ### SLOVENIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_HEBREW_SUPPORT    = TRUE     ### HEBREW SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_BENGALI_SUPPORT    = TRUE    ### BENGALI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_CZECH_SUPPORT    = TRUE     	### CZECH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_DUTCH_SUPPORT    = TRUE     	### DUTCH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_TELUGU_SUPPORT    = FALSE     ### TELUGU SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_MARATHI_SUPPORT    = FALSE    ### MARATHI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_TAMIL_SUPPORT    = FALSE      ### TAMIL SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_GUJARATI_SUPPORT   = FALSE    ### GUJARATI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_KANNADA_SUPPORT    = FALSE    ### KANNADA SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_MALAYALAM_SUPPORT  = FALSE   	### MALAYALAM SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ORIYA_SUPPORT      = FALSE    ### ORIYA SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_PUNJABI_SUPPORT   = FALSE   	### PUNJABI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_AFRIKAANS_SUPPORT   = FALSE   	### AFRIKAANS SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ALBANIAN_SUPPORT   = FALSE   	### ALBANIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ARMENIAN_SUPPORT   = FALSE   	### ARMENIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_AZERBAIJANI_SUPPORT   = FALSE   	### AZERBAIJANI SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_BASQUE_SUPPORT   = FALSE   	### BASQUE SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_BULGARIAN_SUPPORT   = TRUE   	### BULGARIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_CATALAN_SUPPORT   = FALSE   	### CATALAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_CROATIAN_SUPPORT   = FALSE   	### CROATIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_DANISH_SUPPORT   = TRUE   	### DANISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ESTONIAN_SUPPORT   = FALSE   	### ESTONIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_FILIPINO_SUPPORT   = FALSE   	### FILIPINO SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_FINNISH_SUPPORT   = FALSE   	### FINNISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_GALICIAN_SUPPORT   = FALSE   	### GALICIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_GEORGIAN_SUPPORT   = FALSE   	### GEORGIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_HAUSA_SUPPORT   = FALSE   	### HAUSA SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_ICELANDIC_SUPPORT   = FALSE   ### ICELANDIC SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_IGBO_SUPPORT   = FALSE        ### IGBO SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_IRISH_SUPPORT   = FALSE   	### IRISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_KAZAKH_SUPPORT   = FALSE   	### KAZAKH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_LATVIAN_SUPPORT   = FALSE   	### LATVIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_LITHUANIAN_SUPPORT   = FALSE  ### LITHUANIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_MACEDONIAN_SUPPORT   = FALSE  ### MACEDONIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_MOLDOVAN_SUPPORT   = FALSE   	### MOLDOVAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_NORWEGIAN_SUPPORT   = TRUE   ### NORWEGIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_POLISH_SUPPORT   = TRUE   	### POLISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_SERBIAN_SUPPORT   = FALSE   	### SERBIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_SESOTHO_SUPPORT   = FALSE   	### SESOTHO SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_SLOVAK_SUPPORT   = FALSE   	### SLOVAK SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_SWEDISH_SUPPORT   = TRUE   	### SWEDISH SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_UKRAINIAN_SUPPORT   = FALSE   ### UKRAINIAN SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

IM_YORUBA_SUPPORT   = FALSE   	### YORUBA SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

#****************************************************************************************#
#  Segment: SPRD MACRO
#  Description: Get all sprd macro list 
#****************************************************************************************#
SPRD_MACRO_LIST_START := $(call GET_SPRD_MACRO_START)


# *************************************************************************
# Feature Options FOR SPRD
# !!!!!!!! Attention:please don't modify the customer value of this option part. !!!!!!!!!
# !!!!!!!! If modification is in need, the new version should be released by SPRD. !!!!!!!!!
# !!!!!!!! 注意: 此部分Options 的取值客户请勿修改!!!!!!!!!
# !!!!!!!! 若需要修改，需展讯重新发布版本!!!!!!!!!
# *************************************************************************

SPRD_CUSTOMER   = TRUE          # SPRD Customer 
                                        # Option1:TRUE
                                        # Option2:FALSE

PLATFORM        = SC6800H        ### Chip Platform Definition:
                                        # Option1:SC6600R    #define PLATFORM_SC6600R
                                        # Option2:SC6600L    #define PLATFORM_SC6600L
                                        # Option3:SC6800H    #define PLATFORM_SC6800H

CHIP_VER        = 6800H1         ### Chip version:
                                        # Option1:6600L1    #define CHIP_VER_6600L1
                                        # Option2:6600L2    #define CHIP_VER_6600L2
                                        # Option3:6600W2     #define CHIP_VER_6600W2
                                        # Option4:6600H3     #define CHIP_VER_6600H3

CHIP_MARK       = NONE           ### Chip Mark Number:
                                        # Option1:NONE       #define CHIP_MARK_NONE

CHIP_ENDIAN     = BIG            ### Chip endianess:
                                        # Option1: BIG
                                        # Option2: LITTLE
                                        
NANDBOOT_SUPPORT   = TRUE       ### Boot From Nandflash Support: 
                                        # Option1:TRUE
                                        # Option2:FALSE			 

POWER_OFF_PROTECT_SUPPORT = TRUE ### Switch power off protect support:
                                 # Option1:TRUE
                                 # Option2:FALSE  
                                                                             
RF_TYPE         = SR528      ### RF Chip Type:
                                        # Option1:QUORUM      #define RF_TYPE_QUORUM
                                        # Option2:QUORUM518	#define RF_TYPE_QUORUM518
                                        # Option2:SR528	        #define RF_TYPE_SR528

SBC_DSP_SUPPORT  = VERSION1      ### dsp support sbc or mp3-sbc. VERSION1:sbc,VERSION2:sbc-mp3
                                        # Option1:VERSION1      #define SBC_DSP_SUPPORT_VERSION1
                                        # Option2:VERSION2	#define SBC_DSP_SUPPORT_VERSION2

SBC_OVERLAY        =   FALSE     ### implement sbc with memory overlay  HR L = false, M = TRUE, default = FALSE
                                        # Option1:TRUE
                                        # Option2:FALSE

DOLPHIN_SUPPORT    = TRUE        ### Switch Of dolphin device Support
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
EXPRESS_PROCESS_IN_DSP    = TRUE        ### Switch Of express process(transamplerate and sbc encode) in dsp 
                                        # Option1:TRUE
                                        # Option2:FALSE 

HALFRATE_SUPPORT	  = TRUE       ### halfrate support feature
                                        # Option1:TRUE
                                        # Option2:FALSE

ATC_SUPPORT	  = FULL       ### ATC support feature
                                       # Option1:FULL
                                       # Option2:COMPACT


PRODUCT_DM       = FALSE         ### TD/GSM DualModule product
                                        # Option1:TRUE
                                        # Option2:FALSE

GPRSMPDP_SUPPORT       = TRUE   ### GPRS Multi PDP support
                                        # Option1:TRUE
                                        # Option2:FALSE
										
VM_SUPPORT    = TRUE             ### VM support:
                                        # Option1:TRUE
                                        # Option2:FALSE  
					
FDN_SUPPORT =   FALSE            ### FDN Support:
                                        # Option1:TRUE
                                        # Option2:FALSE 

UI_MULTILAYER_SUPPORT = TRUE       ### ui layer support:
                                        # Option1:TRUE
                                        # Option2:FALSE

MSDC_CARD_SUPPORT = TRUE         ### SD Card Support:
                                        # Option1:TRUE
                                        # Option2:FALSE 
                   
USB_VCOM_SUPPORT   = TRUE        ### USB Virtual COM Support:
                                        # Option1:TRUE
                                        # Option2:FALSE  

TCPIP_SUPPORT     = TRUE         ### TCPIP Profile Support:
                                        # Option1:TRUE

SSL_SUPPORT      = TRUE         ### SSL Profile Support:
                                        # Option1:TRUE

HTTP_SUPPORT     = TRUE         ### HTTP Profile Support:
                                        # Option1:TRUE
                                        
RTP_SUPPORT     = TRUE          ### RTP Support:
                                        # Option1:FALSE
                                        # Option2:TRUE                                        
 
RTSP_SUPPORT     = TRUE          ### RTSP Support:
                                        # Option1:FALSE
                                        # Option2:TRUE

WSP_SUPPORT     = TRUE          ### WSP Profile Support:
                                        # Option1:TRUE
                                        
XML_SUPPORT      = TRUE          ### EXPAT XML Support:
                                        # Option1:TRUE

OMADL_SUPPORT    = FALSE         ### OMA download Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        # work for XML_SUPPORT = TRUE && HTTP_SUPPORT = TRUE

DRM_SUPPORT      = FALSE         ### DRM Support:
                                        # Option1:FALSE

STACK_CHECK_SUPPORT = FALSE       ### STACK CHECK SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE

CARD_LOG = TRUE                  ### CARD SAVE LOG SUPPORT:
                                        # Option1:TRUE
                                        # Option2:FALSE 

MULTI_SIM_SYS = QUAD        ### Platform Support Multi Sim Card Number:
                                        # Option1:SINGLE    #define MULTI_SIM_SYS_SINGLE
                                        # Option2:DUAL      #define MULTI_SIM_SYS_DUAL
                                        # Option3:TRI       #define MULTI_SIM_SYS_TRI
                                        # Option4:QUAD      #define MULTI_SIM_SYS_QUAD

JTAG_SUPPORT    = FALSE          ### JTAG Debug Version:
                                        # Option1: TRUE
                                        # Option2: FALSE

SOUNDBANK_VER     = ARM_2MB      ### Soundbank Talbe Type
                                        # Option1:ARM_512KB #define SOUNDBANK_VER_ARM_512KB
                                        # Option2:ARM_2MB   #define SOUNDBANK_VER_ARM_2MB
                                        # Option3:ARM_256KB #define SOUNDBANK_VER_ARM_256KB
                                        # Option4:ARM_700KB #define SOUNDBANK_VER_ARM_700KB
                                        # Option5:ARM_300KB #define SOUNDBANK_VER_ARM_300KB
                                        # Option6/7/8  for midi_opt
                                        # Option6:ARM_300KB #define SOUNDBANK_VER_1MB_HALFSAMPL_16BITS
                                        # Option7:ARM_300KB #define SOUNDBANK_VER_1MB_ORISAMPL_8BITS
                                        # Option8:ARM_300KB #define SOUNDBANK_VER_700KB_HALFSAMPL_8BITS
                                                      
BT_OPP_SUPPORT    = TRUE         ### Switch Of OPP Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE

BT_FTP_SERVER_SUPPORT = TRUE     ### Switch Of FTP Server Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE

BT_FTP_CLIENT_SUPPORT = FALSE    ### Switch Of FTP Client Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE

BT_DUN_SUPPORT    = FALSE        ### Switch Of DUN Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE

BT_SPP_SUPPORT    = FALSE        ### Switch Of SPP Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE

BT_A2DP_SUPPORT    = TRUE        ### Switch Of A2DP Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE

BT_A2DP_SAMPLERATE_RECONFIG_SUPPORT    = TRUE       ### a2dp sample rate reconfig Support
       	                                                   # Option1:TRUE, Only 6600L chip
	                                                   # Option2:FALSE

BT_AVRCP_SUPPORT   = TRUE        ### Switch Of AVRCP Profile Support
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
MP3_A2DP_SUPPORT   = TRUE        ### MP3 Support Bluetooth Stereo:
                                        # Option1:TRUE
                                        # Option2:FALSE

WAV_A2DP_SUPPORT   = TRUE       ### WAV Support Bluetooth Stereo:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
AMR_A2DP_SUPPORT   = TRUE       ### AMR_DSP Support Bluetooth Stereo:
                                        # Option1:TRUE
                                        # Option2:FALSE

MIDI_A2DP_SUPPORT   = TRUE       ### MIDI Support Bluetooth Stereo:
                                        # Option1:TRUE
                                        # Option2:FALSE

AAC_A2DP_SUPPORT   = TRUE        ### AAC Support Bluetooth Stereo:
                                        # Option1:TRUE
                                        # Option2:FALSE

WMA_A2DP_SUPPORT   = FALSE       ### WMA Support Bluetooth Stereo:
                                        # Option1:FALSE

MP3_SUPPORT    = TRUE            ### MP3 Decoder Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

AAC_SUPPORT    = TRUE            ### AAC Decoder Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

WMA_SUPPORT    = FALSE           ### WMA Decoder Support:
                                        # Option1:FALSE

AMR_SUPPORT    = TRUE            ### AMR Decoder Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

MIDI_SUPPORT    = TRUE           ### MIDI Decoder Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                                                               
MIDI_DECODER_OPTIMIZED   = FALSE  ### MIDI Decoder Optimized:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
H264_DEC_SUPPORT    = TRUE          ### H264 Decoder Support:
                                        # Option1:TRUE
                                        # Option2:FALSE                                        

WAV_SUPPORT    = TRUE            ### WAV Decoder Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                       
MP3_BACKGROUND_SUPPORT =   TRUE  ###  MP3 BACKGROUND SUPPORT
                                        # Option1:TRUE
                                        # Option2:FALSE

WMA_BACKGROUND_SUPPORT = FALSE   ###  WMA BACKGROUND SUPPORT
                                        # Option1:FALSE
  
AAC_BACKGROUND_SUPPORT =   TRUE  ### AAC BACKGROUND SUPPORT
                                        # Option1:TRUE
                                        # Option2:FALSE

AMR_BACKGROUND_SUPPORT =   TRUE ### AMR BACKGROUND SUPPORT
                                        # Option1:TRUE
                                        # Option2:FALSE

MIDI_BACKGROUND_SUPPORT = TRUE  ### MIDI BACKGROUND SUPPORT
                                        # Option1:TRUE
                                        # Option2:FALSE

WAV_BACKGROUND_SUPPORT =  TRUE  ### WAV BACKGROUND SUPPORT
                                        # Option1:TRUE
                                        # Option2:FALSE

MP3_EQ_SUPPORT    = TRUE         ### MP3 EQ Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
EQ_EXE_ON_CHIP    = TRUE         ###  EQ Type:
                                        # Option1:TRUE
                                        # Option2:FALSE 
                     
MP3_SEEK_SUPPORT   = TRUE        ### MP3 Seek Function Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

AAC_SEEK_SUPPORT   = TRUE        ### AAC Seek Function Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

WMA_SEEK_SUPPORT   = FALSE       ### WMA Seek Function Support:
                                        # Option1:FALSE

AMR_SEEK_SUPPORT   = TRUE       ### AMR Seek Function Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

MIDI_SEEK_SUPPORT   = FALSE      ### MIDI Seek Function Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

WAV_SEEK_SUPPORT   = TRUE       ### WAV Seek Function Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                    
GIF_DEC_SUPPORT  = GIF_SW        ### GIF Decoder Lib Type:
                                        # Option0:NONE     #define GIF_DEC_SUPPORT_NONE
                                        # Option1:GIF_SW   #define GIF_DEC_SUPPORT_GIF_SW
                                        # Option2:GIF_HW   #define GIF_DEC_SUPPORT_GIF_HW

PNG_DEC_SUPPORT    = PNG_SW      ### PNG Decoder Lib Type:
                                        # Option0:NONE     #define PNG_DEC_SUPPORT_NONE
                                        # Option1:PNG_SW   #define PNG_DEC_SUPPORT_PNG_SW

BMP_DEC_SUPPORT    = BMP_SW      ### BMP Decoder Lib Type:
                                        # Option0:NONE     #define BMP_DEC_SUPPORT_NONE
                                        # Option1:BMP_SW   #define BMP_DEC_SUPPORT_BMP_SW

JPG_DEC_SUPPORT    = JPG_HW      ### JPG Decoder Lib Type:
                                        # Option0:NONE     #define JPG_DEC_SUPPORT_NONE
                                        # Option1:JPG_SW   #define JPG_DEC_SUPPORT_JPG_SW
                                        # Option2:JPG_HW   #define JPG_DEC_SUPPORT_JPG_HW
                                        
JPG_DEC_TYPE_SUPPORT  = BASELINE_PROGRESSIVE		### decode type support:
                                        # Option0:BASELINE
                                        # Option1:BASELINE_PROGRESSIVE  
                                        

JPG_ENC_SUPPORT    = JPG_HW      ### JPG Encoder Lib Type:
                                        # Option0:NONE     #define JPG_ENC_SUPPORT_NONE
                                        # Option1:JPG_SW   #define JPG_ENC_SUPPORT_JPG_SW
                                        # Option2:JPG_HW   #define JPG_ENC_SUPPORT_JPG_HW 
                                        
WMA_DEC_SUPPORT    = FALSE       ### WMA Decoder Lib Support:
                                        # Option1:FALSE

AVI_DEC_SUPPORT    = TRUE        ### AVI Decoder Lib Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
FLV_DEC_SUPPORT    = TRUE        ### FLV Decoder Lib Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
 
AVI_ENC_SUPPORT    = TRUE        ### AVI Encoder Lib Support:
                                        # Option1:TRUE
                                        # Option2:FALSE

GZIP_DEC_SUPPORT    = GZIP_SW       ### GZIP Decoder Lib Type:
                                        # Option0:NONE     #define GZIP_DEC_SUPPORT_NONE
                                        # Option1:GZIP_SW  #define GZIP_DEC_SUPPORT_GZIP_SW      

NULL_CODEC_SUPPORT    = TRUE            ### NULL_CODEC  Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
ARM_AD_ADP_SUPPORT    = TRUE            ### ARM_AD_ADP CODEC Support:
                                        # Option1:TRUE
                                        # Option2:FALSE
                                        
AD_OUTPUT_ADP_SUPPORT    = TRUE            ### AD_OUTPUT_ADP CODEC Support:
                                        # Option1:TRUE
                                        # Option2:FALSE  

DYNAMIC_MODULE_SUPPORT   = FALSE  ### caf Support:
                                        # Option1:TRUE
                                        # Option2:FALSE	
                                       
AUDIO_PARAM_ARM = TRUE     #### move audio param from dsp audio nv to arm audio nv

LCD_UPDATE_ASYNC_SUPPORT = BLEND_INVALIDATE        ### if support lcd task: need more 1x or 3x screen buffer
                                        # Option1:NONE                  #define LCD_UPDATE_ASYNC_SUPPORT_NONE
                                        # Option2:INVALIDATE            #define LCD_UPDATE_ASYNC_SUPPORT_INVALIDATE
                                        # Option3:BLEND_INVALIDATE      #define LCD_UPDATE_ASYNC_SUPPORT_BLEND_INVALIDATE




