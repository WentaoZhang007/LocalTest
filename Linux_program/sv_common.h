#pragma once
#ifndef _SV_COMMON_H_
#define _SV_COMMON_H_

#ifdef __cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

extern "C" {
#endif

#define PRINT_ERROR printf
#define PRINT_INFO printf
#define COMMON_NAME_LEN 256
#define COMMON_CMD_LEN 256

#define SV_MAX(a, b) ((a) > (b) ?(a):(b))
#define SV_MIN(a, b) ((a) < (b) ?(a):(b))

	typedef unsigned char           SV_U8;
	typedef unsigned short          SV_U16;
	typedef unsigned int            SV_U32;
	typedef signed char             SV_S8;
	typedef short                   SV_S16;
	typedef int                     SV_S32;
	typedef unsigned long long      SV_U64;
	typedef long long               SV_S64;
	typedef char                    SV_CHAR;
	typedef char*                   SV_PCHAR;
	typedef float                   SV_FLOAT;
	typedef double                  SV_DOUBLE;
	typedef void                    SV_VOID;
	typedef unsigned long           SV_SIZE_T;
	//typedef unsigned long         SV_LENGTH_T;

	typedef enum
	{
		SV_FALSE = 0,
		SV_TRUE = 1
	}SV_BOOL;

#define SV_NULL          0L
#define SV_NULL_PTR      0L
#define SV_SUCCESS       0
#define SV_FAILURE       (-1)

#define ERROR_CODE_DEVICE 2
#define ERROR_CODE_LEVEL  0

	typedef enum
	{
		ERROR_CODE_MEDIA,
		ERROR_CODE_STORAGE,
		ERROR_CODE_NETWORK,
		ERROR_CODE_RFID,
		ERROR_CODE_MCU,
		ERROR_CODE_MAINCONTROL,
	}ERRORCODE_MODULE_E;

	typedef enum
	{
		RFID_AUTH_ERROR,
	}ERRORCODE_RFID_E;

	// levle 0~9 module 0~99 code 0~999
#define SV_CREATE_ERRORCODE(LEVEL, MODULE, CODE){\
	 (SV_U32)(ERROR_CODE_DEVICE * 1000000 + MODULE * 100000 + LEVEL * 1000 + CODE)\
}

#define SV_CHECK(expr) \
do{ \
    if (!(expr)) { \
        printf("\nCHECK failed at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
                __FILE__,__FUNCTION__, __LINE__, #expr); \
        return (-1); \
    } \
}while(0)

#define SV_FUN_CHECK(express,name)\
		do{\
			if (SV_SUCCESS != express)\
			{\
				printf("%s failed at %s: LINE: %d !\n", name, __FUNCTION__, __LINE__);\
				return SV_FAILURE;\
			}\
		}while(0)

#ifdef __cplusplus
}
#endif

/*****������ؽṹ��******/

#define UID_PATH "/etc/DeviceUid"
#define SV_DVR_CHN_NUM 8
#define SV_DVR_CONFIG_FILE "/etc/sv_xml.xml"

#define SV_DVR_LICENSE_DISABLE_P		".:?&|*/%_<>"


typedef enum
{
	JPG_INTERVAL_5S,
	JPG_INTERVAL_3S,
	JPG_INTERVAL_1S,
	JPG_INTERVAL_MIN

}SV_DVR_JPG_INTERVAL_E;

typedef struct
{
	SV_U32 u32BitRate;
	SV_U32 u32FrameRate;
	SV_U32 u32PicSize;
	SV_U32 u32SubBitRate;
	SV_U32 u32SubFrameRate;
	SV_U32 u32SubPicSize;
	SV_U8  u8JpgInterval;
	SV_BOOL bAudio;
}SV_DVR_VIDEOQUALITY_S;

typedef struct
{
	SV_U8 u8RecChn;
}SV_DVR_RECORDCHN_S;

typedef struct
{
	SV_BOOL bPowerOnRec;
	SV_BOOL bCyclicRec;
	SV_BOOL bAlarmRec;
	SV_BOOL bALarmRecLock;
	SV_U32  u32PreRecTime;
	SV_U32  u32FileTime;
	SV_U8 u8MotionSensitivity;
	SV_U8 u8GsensorSensitivity;
	SV_U8 u8FileType;
}SV_DVR_RECORD_INFO_S;

typedef struct
{
	SV_U8 u8Brightness;
	SV_U8 u8Contrast;
	SV_U8 u8Saturation;
	SV_U8 u8Hue;
}SV_DVR_CAMERA_S;

typedef struct
{
	SV_DVR_CAMERA_S sChnParm[SV_DVR_CHN_NUM];
}SV_DVR_CAMERA_PARAM_S;

typedef struct
{
	SV_U8 u8AudioOutChn;
	SV_U8 u8Volume;
}SV_DVR_AUDIOOUT_CHN_S;

typedef struct
{
	SV_U8 u8MenuOn;
}SV_DVR_MenuOn_Time_S;

typedef struct
{
	SV_U8 u8SysFormat;
	SV_U8 u8GuiDisplay;
	SV_U8 u8SDFormat;
}SV_DVR_SYSFORMAT_S;

typedef struct
{
	SV_CHAR szCamerName[SV_DVR_CHN_NUM][64];
}SV_DVR_CAMERANAME_S;

typedef enum
{
	ALARM_CHN_1,
	ALARM_CHN_2,
	ALARM_CHN_3,
	ALARM_CHN_4,
	ALARM_CHN_REVERSE, //Alarm 5
	ALARM_CHN_BRAKE,   //Alarm 6
	ALARM_CHN_LEFT,    //Alarm 7
	ALARM_CHN_RIGHT,   //Alarm 8
	ALARM_CHN_COUNT
}ALARM_CHN_E;

typedef struct
{
	SV_BOOL bTime;
	SV_BOOL bVideoLoss;
	SV_BOOL bChannelName;
	SV_BOOL bAlarmStatus;
	SV_BOOL bLicenseNo;
}SV_DVR_OSDSTATUS_S;

typedef struct
{
	SV_U8 u8SpeedSrc;
	SV_U8 u8SpeedUnit;
	SV_U16 u16OverSpeed;
}SV_DVR_SPEED_S;

typedef struct {
	SV_CHAR szUserName[32];
	SV_CHAR szPwd[32];
	SV_CHAR szGuestName[32];
	SV_CHAR szGuestPwd[32];
	SV_BOOL bLock;
}SV_DVR_USERSETUP_S;

typedef struct {
	SV_CHAR szLicenseNo[128];
	SV_CHAR szDeviceID[128];
	SV_CHAR szPathNo[128];
}SV_DVR_DEVICE_S;

typedef struct {
	SV_S8 s8TimeZone; //ʱ��
	SV_U8 u8Format;
	SV_BOOL bFormatAble;
	SV_BOOL bGpsSync;
	SV_BOOL bNtpSync;
	SV_CHAR szNtpServer[128];
}SV_DVR_TIMEZONE_S;

typedef struct {
	SV_U16 u16ShutVol;
	SV_U16 u16AccDelay;
}SV_DVR_ACC_S;

typedef struct {
	SV_U8 u8AlarmOut1;
	SV_U8 u8AlarmOut2;
}SV_DVR_ALARMOUT_S;

typedef struct {
	SV_BOOL bOutBuzz;
	SV_BOOL bOutVol1;
	SV_BOOL bOutVol2;
	SV_U16  u16DispChn;
}SV_DVR_ALARNIN_S;

typedef struct {
	SV_U16  u16TrigLevel;
	SV_U16  u16Delay;
	SV_U8	U8Priority;
	SV_BOOL bRec;
}SV_DVR_ALARMSETUP_S;

typedef struct {
	SV_DVR_ALARNIN_S stAlarm[SV_DVR_CHN_NUM];
}SV_DVR_ALARMARRY_S;

typedef struct {
	SV_DVR_ALARMSETUP_S stAlarmSetup[SV_DVR_CHN_NUM];
}SV_DVR_ALARMSETUPARRY_S;


typedef struct tag_timing {
	SV_BOOL bTimerEnable;
	SV_BOOL bDayFlag[7];
	SV_U32 u32TimingRecStartTime;
	SV_U32 u32TimingRecEndTime;
}SV_DVR_TIMINGRECINFO_S;

typedef struct tag_timerinfo {
	SV_DVR_TIMINGRECINFO_S stTimingRecInfo[4];
}SV_DVR_TIMERINFO_S;

typedef struct {
	SV_BOOL bDhcp;
	SV_CHAR szIpAddr[19];
	SV_CHAR szMaskAddr[19];
	SV_CHAR szGateWayAddr[19];
	SV_CHAR szMacAddr[19];
}SV_DVR_LANSETUPINFO_S;

typedef struct
{
	SV_BOOL bWifi;
	SV_BOOL bDhcp;
	SV_CHAR szIpAddr[19];
	SV_CHAR szMaskAddr[19];
	SV_CHAR szGateWayAddr[19];
	SV_CHAR szSSId[64];
	SV_CHAR szPassWd[64];
	SV_S32  s32AuthMode;
	SV_S32  s32NetworkType;
	SV_S32  s32EncrypType;
	SV_S32  s32DefaultKeyID;
	SV_BOOL bHiddenSsid;
	//Ap setup
	SV_BOOL	bApEnable;
	SV_BOOL bAccessInternet;
	SV_CHAR szApSSID[64];
	SV_CHAR szApWPAPSK[64];
	SV_U8	u8ApFrequency;
}SV_DVR_WIFISETUP_S;

typedef struct
{
	SV_BOOL bCellular;
	SV_CHAR szApn[64];
	SV_CHAR szAccNumber[64];
	SV_CHAR szUserName[64];
	SV_CHAR szPassWd[64];
}SV_DVR_CELLULARSETUP_S;

typedef struct {
	SV_CHAR szServerIP[32];
	SV_U16  u16Port;
	SV_CHAR szServerName1[128];
	SV_BOOL bEnableName1;
	SV_CHAR szServerName2[128];
	SV_BOOL bEnableName2;
	SV_CHAR szServerName3[128];
	SV_BOOL bEnableName3;
}SV_DVR_SERVERSETUP_S;

typedef enum 
{
	SERVER_LAN = 0,
	SERVER_WIFI,
	SERVER_CELLULAR,
	SERVER_BUTT,
} NETWORK ;

typedef struct tag_SERVERSETUP {
	SV_DVR_SERVERSETUP_S stSetupArry[SERVER_BUTT];
}SV_DVR_SERVERSETUPArry_S;

typedef struct {
	SV_CHAR szServerIP[32];
	SV_CHAR szUserName[32];
	SV_CHAR szPassword[32];
	SV_U16  u16Port;
	SV_BOOL bEnableFTP;
	SV_BOOL bUploadNormalFile;
	SV_BOOL bCellar;
}SV_DVR_FTPSETUP_S;

typedef struct
{
	SV_U8 u8MirrChn;
}SV_DVR_MIRRCHN_S;

typedef struct
{
	SV_BOOL bSitch;
	SV_U16 u16Interval;
}SV_DVR_BUZZERSETUP_S;

typedef struct
{
	SV_U16 u8Language;
}SV_DVR_LANGUAGE_S;

typedef struct
{
	SV_U8 u8Year;
	SV_U8 u8Month;
	SV_U8 u8WeekNum;
	SV_U8 u8WeekDay;
	SV_U8 u8Hour;
	SV_U8 u8Minute;
	SV_U8 u8Second;
}SV_DVR_DSTWEEKTIME_S;

typedef struct
{
	SV_U8 u8Year;
	SV_U8 u8Month;
	SV_U8 u8Day;
	SV_U8 u8Hour;
	SV_U8 u8Minute;
	SV_U8 u8Second;
}SV_DVR_DATETIME_S;

typedef struct
{
	SV_BOOL bEnable;
	SV_U8 	u8Offest;
	SV_U8 	u8Mode;
	SV_DVR_DSTWEEKTIME_S stWeekTimeStart;
	SV_DVR_DSTWEEKTIME_S stWeekTimeEnd;
	SV_DVR_DATETIME_S stDateTimeStart;
	SV_DVR_DATETIME_S stDateTimeEnd;
}SV_DVR_DST_S;

#if 0

typedef struct
{
	SV_DVR_POINT_S stAccThreshold;
	SV_DVR_POINT_S stGyroThreshold;
	SV_S32 s32CompassThreshold;
}SV_DVR_GFORCE_S;
#endif

typedef struct
{
	SV_S32 s32x;
	SV_S32 s32y;
	SV_S32 s32z;
}SV_DVR_POINT_S;

typedef enum
{
	DIRCTION_FORWARD_X = 1,
	DIRCTION_FORWARD_Y,
	DIRCTION_FORWARD_Z,
	DIRCTION_REVERSE_X,
	DIRCTION_REVERSE_Y,
	DIRCTION_REVERSE_Z,
	DIRCTION_BUTT
}SV_DVR_DIRCTION_TYPE;

typedef struct
{
	SV_S32 s32Threshold;  //mg  DPS
	SV_S32 s32Duration;   //ms  MS
	SV_S32 s32Offset;	  //mg  DPS
}SV_DVR_AXIS_SETTING;

typedef struct
{
	SV_DVR_POINT_S stAccOffset;
	SV_DVR_AXIS_SETTING stAcceleration;
	SV_DVR_AXIS_SETTING stDeceleration;
	SV_DVR_AXIS_SETTING stTurnAcc;
	SV_DVR_AXIS_SETTING stTurnGyro;
	SV_DVR_AXIS_SETTING stImpact;
	SV_U8 u8ImpactFilter;
	SV_U8 u8Forward;               //dvrǰ������ȡֵSV_DVR_DIRCTION_TYPE
	SV_U8 u8Left;				   //dvr��װ������ȡֵSV_DVR_DIRCTION_TYPE
}SV_DVR_GFORCE_S;

typedef struct event_Gsensor_data{
    SV_FLOAT fACCX;
    SV_FLOAT fACCY;
    SV_FLOAT fACCZ;
    SV_FLOAT fGgrX;
    SV_FLOAT fGgrY;
    SV_FLOAT fGgrZ;
    SV_FLOAT fpitch;
    SV_FLOAT froll;
    SV_FLOAT fyawZ;
}Event_Gsensor_data;


#define PRINT_INFO printf

/*****end******/


#endif
