typedef struct {
    SV_S32     s32Index;
    SV_CHAR    c16Phone[32];
    SV_CHAR    c32Date[32];
    SV_CHAR    c140cont[140];
}SMS_INFO;

typedef struct {
    SV_U32     s32Index;
    SV_CHAR    c16Phone[32];
    SV_CHAR    c32Date[32];
}CALL_INFO;

#define SMSPHONELISTSIZE 5


SV_S32   TELIT910C1_addNewCalltoList(CALL_INFO *p_newCallInfo, CALL_INFO TELIT910C1_CallList[SMSPHONELISTSIZE]);
SV_S32   TELIT910C1_printCallList( CALL_INFO TELIT910C1_CallList[SMSPHONELISTSIZE] );
SV_S32   TELIT910C1_addNewSMStoList(SMS_INFO *p_newSMSInfo, SMS_INFO TELIT910C1_SMSList[SMSPHONELISTSIZE]);
SV_S32   TELIT910C1_printSMSList( SMS_INFO TELIT910C1_SMSList[SMSPHONELISTSIZE] );