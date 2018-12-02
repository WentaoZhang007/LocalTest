#ifndef  _RFID_LIST_H_
#define _RFID_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

#include "sv_common.h"
#define COUNT_RFID_LIST_NODE 5
#define BufferSize 32
    typedef unsigned int arrayposi;
    typedef struct rfid_node {
        char       rfid_num[BufferSize];
        char       rfid_num_date[BufferSize];
        SV_BOOL       rfid_num_isErrorNum;
    }Rfid_Node;

    typedef struct rfid_list {
        Rfid_Node Rfid_List[5];

        SV_VOID(*rfidlist_get_rfidNum)              (const struct rfid_list* rfid_list, arrayposi N, char outputbuffer[BufferSize]);
        SV_VOID(*rfidlist_set_rfidNum)              (struct rfid_list* rfid_list, arrayposi N, const char inputbuffer[BufferSize]);
        SV_VOID(*rfidlist_get_rfidNumDate)          (const struct rfid_list* rfid_list, arrayposi N, char outputbuffer[BufferSize]);
        SV_VOID(*rfidlist_set_rfidNumDate)          (struct rfid_list * rfid_list, arrayposi N, const char inputbuffer[BufferSize]);
        SV_VOID(*rfidlist_get_rfidNumisErrorNum)    (const struct rfid_list* rfid_list, arrayposi N, SV_BOOL* isErrorrRfidNum);
        SV_VOID(*rfidlist_set_rfidNumisErrorNum)    (struct rfid_list* rfid_list, arrayposi N, SV_BOOL* isErrorrRfidNum);
        SV_VOID(*set_rfid_entry)                    (struct rfid_list* prfid_list, arrayposi N, const char rfid_num[BufferSize], const char rfid_num_date[BufferSize], SV_BOOL*  rfid_num_isErrorNum);
        SV_VOID(*get_rfid_entry)                    (struct rfid_list* prfid_list, arrayposi N, char rfid_num[BufferSize], char rfid_num_date[BufferSize], SV_BOOL*  rfid_num_isErrorNum);
        SV_VOID(*add_rfid_entry)                    (struct rfid_list* prfid_list, const arrayposi N, const char rfid_num[BufferSize], const char rfid_num_date[BufferSize],SV_BOOL  rfid_num_isErrorNum);
        SV_S32(*delet_rfid_entry)                   (struct rfid_list* prfid_list, const char rfid_num[BufferSize]);
        SV_VOID(*delet_rfid_entry_nth)              (struct rfid_list* prfid_list, arrayposi N);
        SV_VOID(*empty_rfidlist)                    (struct rfid_list* prfid_list);
        SV_VOID(*print_rfidlist)                    (struct rfid_list* prfid_list);
        SV_S32(*count_rfidlist)                     (struct rfid_list* prfid_list);
        SV_VOID(*init_rfidlist)                     (struct rfid_list* p_rfid_list_instance);

    }Rfid_List;

    SV_VOID rfidlist_get_rfidNum(const Rfid_List* rfid_list, arrayposi N, char outputbuffer[BufferSize]);
    SV_VOID rfidlist_set_rfidNum(Rfid_List* rfid_list, arrayposi N, const char inputbuffer[BufferSize]);
    SV_VOID rfidlist_get_rfidNumDate(const Rfid_List* rfid_list, arrayposi N, char outputbuffer[BufferSize]);
    SV_VOID rfidlist_set_rfidNumDate(Rfid_List* rfid_list, arrayposi N, const char inputbuffer[BufferSize]);
    SV_VOID rfidlist_get_rfidNumisErrorNum(const Rfid_List* rfid_list, arrayposi N, SV_BOOL* isErrorrRfidNum);
    SV_VOID rfidlist_set_rfidNumisErrorNum(Rfid_List* rfid_list, arrayposi N, SV_BOOL* isErrorrRfidNum);
    SV_VOID set_rfid_entry(Rfid_List* prfid_list, arrayposi N, const char rfid_num[BufferSize], const char rfid_num_date[BufferSize], SV_BOOL*  rfid_num_isErrorNum);
    SV_VOID get_rfid_entry(Rfid_List* prfid_list, arrayposi N, char rfid_num[BufferSize], char rfid_num_date[BufferSize], SV_BOOL*  rfid_num_isErrorNum);
    SV_VOID add_rfid_entry(Rfid_List* prfid_list, const arrayposi N, const char rfid_num[BufferSize], const char rfid_num_date[BufferSize],SV_BOOL  rfid_num_isErrorNum);
    SV_S32  delet_rfid_entry(Rfid_List* prfid_list, const char rfid_num[BufferSize]);
    SV_VOID delet_rfid_entry_nth(Rfid_List* prfid_list, arrayposi N);
    SV_S32  count_rfid_entry(Rfid_List* prfid_list);
    SV_VOID empty_rfidlist(Rfid_List* prfid_list);
    SV_VOID print_rfidlist(Rfid_List* prfid_list);
    SV_VOID init_rfidlist(Rfid_List* p_rfid_list_instance);




    SV_S32 test_Rfid_recent_list_main();
    SV_S32 test_rfidlist();


#ifdef __cplusplus
}
#endif

#endif



