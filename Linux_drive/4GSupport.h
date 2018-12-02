#include <stdbool.h>
#ifdef __cplusplus 

extern "C" { 
#endif

#define TTYUSB "/dev/ttyUSB2"
#define MODEUSB "/dev/ttyUSB3"

#define _4GDEVICE "/proc/dvrperipheral/pwr_3G"
#define UTRAN  0
#define GSM    1
#define _4G     2
#define SUCCEED  0
#define FAILED  -1

#define OFF_POWER 0
#define CONNECTING_4G 1
#define INITING_4GSYSTEM 2
#define CONNECTED_4G  3

typedef struct tag_OperationParam_t
{
	char Apn[50];
	char Dial[50];
	char user[50];
	char password[50];
}OperationParam_t;

typedef enum 
{
	DEVICE_INITING,
	DEVICE_INITED,
	NETCONNECTING,
	NETCONNECTED,
	NETCONNECTFAIL,
	POWEROFF,
}DATA_STATUS;

typedef enum
{
	SUCCESS_INIT,
	NOT_SIM_CARD, 
	HARDWAREERR,
	NOT_SIGNAL,
	CEREG_FAIL,	
	SIM_UNUSUAL,
}ERR_STATUS;

typedef enum
{
	REGISTER_UNKNOW =-1,
	REGISTER_2G, 
	REGISTER_3G, 
	REGISTER_4G,
}REGISTER_NET;


void setDeviceInfo(char **pProductor, char **pDevName, int iProCount, int iDevCount);

int Init(int print);

int Connect(const OperationParam_t *stParam, char *dev);

int getRiss(int *iSigalStrength);

int GetStatus(int *iStatus);

int GetErrStatus(int *iErrStatus);

int RegisterNet(int *net);

int ResetDevice(bool isAuto);

int GetPPPStatus();

int GetDevInfo(char *iProductor, char *iDeviceName);

int CloseDev();

int GetErrString(char *pBuf);

int getQLogProc();

#ifdef __cplusplus 
} 
#endif 

