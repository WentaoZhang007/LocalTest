// Call list Func

SV_S32   TELIT910C1_GetRevPhoneList( SV_S32 index , CALL_INFO *Phoneentry )
{
    if(index >= SMSPHONELISTSIZE  )
    {
        PRINT_ERROR("SMS index:[%d] execed maxSize[%d]!\n",index,SMSPHONELISTSIZE);
        return SV_FAILURE;
    }
    SV_COMMON_ScopedLock  lock( TELIT910C1_CallList_Mutex );
    *Phoneentry = st_TELIT910C1_SMSPhoneList.CallList[index];
    return SV_SUCCESS;  
}

SV_S32   TELIT910C1_GetRevSMSList( SV_S32   index, SMS_INFO *SMSentry )
{
    if(index >= SMSPHONELISTSIZE  )
    {
        PRINT_ERROR("SMS index:[%d] execed maxSize[%d]\n",index,SMSPHONELISTSIZE);
        return SV_FAILURE;
    }
    SV_COMMON_ScopedLock  lock( TELIT910C1_SMSList_Mutex );  
    *SMSentry = st_TELIT910C1_SMSPhoneList.SMSList[index];
    return SV_SUCCESS;    
}

SV_S32   TELIT910C1_getCallListSize(CALL_INFO CallList[SMSPHONELISTSIZE])
{
    SV_S32 s32Callsize = 0;
    for (SV_S32 CallIndex = 0; CallIndex != SMSPHONELISTSIZE ; CallIndex++)
    {
        if (0 != CallList[CallIndex].c16Phone[0])
        {
            s32Callsize++;
        }
        else
        {
            break;
        }
    }
    return s32Callsize;
}

SV_S32   TELIT910C1_addNewCalltoList(CALL_INFO *p_newCallInfo, CALL_INFO CallList[SMSPHONELISTSIZE])
{
    SV_S32  s32SMSsixe = 0;
    
    SV_COMMON_ScopedLock  lock( TELIT910C1_CallList_Mutex );
    s32SMSsixe = TELIT910C1_getCallListSize(CallList);
    
    for ( SV_S32 listindex = s32SMSsixe - 1; listindex != -1 ; listindex-- )
    {
        if (listindex == SMSPHONELISTSIZE - 1)
        {
            continue;
        }
        CallList[listindex + 1 ] = CallList[listindex];
    }
    CallList[0] = *p_newCallInfo;
    return SV_SUCCESS;
}

SV_S32 TELIT910C1_printCallList( CALL_INFO CallList[SMSPHONELISTSIZE] )
{
    SV_S32  s32SMSsixe = 0;

    SV_COMMON_ScopedLock  lock( TELIT910C1_CallList_Mutex );
    s32SMSsixe = TELIT910C1_getCallListSize(CallList);   
    
    for (SV_S32 CallListindex = 0; CallListindex != s32SMSsixe ; CallListindex++) 
    {
        PRINT_INFO("Call[%d]:date[%s],phone[%s].\n", CallListindex, CallList[CallListindex].c32Date, CallList[CallListindex].c16Phone );
    }  
    PRINT_INFO("--total size:%d.\n",s32SMSsixe);
    return SV_SUCCESS;
}


// SMS
SV_S32   TELIT910C1_getSMSListSize(SMS_INFO SMSList[SMSPHONELISTSIZE])
{
    SV_S32 s32SMSsize = 0;
    for (SV_S32 SMSIndex = 0; SMSIndex != SMSPHONELISTSIZE ; SMSIndex++)
    {
        if (0 != SMSList[SMSIndex].c32Date[0])
        {
            s32SMSsize++;
        }
        else
        {
            break;
        }
    }
    return s32SMSsize;
}

SV_S32   TELIT910C1_addNewSMStoList(SMS_INFO *p_newSMSInfo, SMS_INFO SMSList[SMSPHONELISTSIZE])
{
    SV_S32  s32SMSsixe = 0;
    
    SV_COMMON_ScopedLock  lock( TELIT910C1_SMSList_Mutex );
    s32SMSsixe = TELIT910C1_getSMSListSize(SMSList);
    
    for ( SV_S32 listindex = s32SMSsixe - 1; listindex != -1 ; listindex-- )
    {
        if (listindex == SMSPHONELISTSIZE - 1)
        {
            continue;
        }
        SMSList[listindex + 1 ] = SMSList[listindex];
    }
    SMSList[0] = *p_newSMSInfo;
    return SV_SUCCESS;
}

SV_S32 TELIT910C1_printSMSList( SMS_INFO SMSList[SMSPHONELISTSIZE] )
{
    SV_S32  s32SMSsixe = 0;

    SV_COMMON_ScopedLock  lock( TELIT910C1_SMSList_Mutex );
    s32SMSsixe = TELIT910C1_getSMSListSize(SMSList);   
    
    for (SV_S32 SMSListindex = 0; SMSListindex != s32SMSsixe ; SMSListindex++) 
    {
        PRINT_INFO("SMS[%d]:date[%s],phone[%s],content[%s].\n", SMSListindex, SMSList[SMSListindex].c32Date, SMSList[SMSListindex].c16Phone, SMSList[SMSListindex].c140cont );
    }  
    PRINT_INFO("--total size:%d.\n",s32SMSsixe);
    return SV_SUCCESS;
}

