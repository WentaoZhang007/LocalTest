#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "rfidlist.h"
#include "sv_common.h"

#ifdef __cplusplus
extern "C" {
#endif __cplusplus

    static Rfid_List rfid_list_instance;
    SV_VOID init_rfidlist(Rfid_List* p_rfid_list_instance);
    SV_S32 test_rfidlist();



SV_S32 test_rfidlist() {



    printf("-----------test:insert new rfid then print Rfid list.--------------------\n-\n-\n");

    init_rfidlist(&rfid_list_instance);
    printf("----------------------------initi end ----------------------------------------------\n");

    printf("----------------------------adde test----------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "1111111", "2018042411305900", SV_FALSE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "2222222", "2018042512300001", SV_TRUE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "3333333", "2018042812300002", SV_FALSE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "4444444", "2018042812300003", SV_TRUE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "5555555", "2018042812300005", SV_FALSE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "66666666", "2018042812300006", SV_TRUE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");
    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "66666666", "2018042812300006", SV_FALSE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("----------------------------delete test----------------------------------------------\n");

    rfid_list_instance.delet_rfid_entry_nth(&rfid_list_instance, 0);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");
    rfid_list_instance.delet_rfid_entry_nth(&rfid_list_instance, 0);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    rfid_list_instance.delet_rfid_entry(&rfid_list_instance, "4444444");
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");
    rfid_list_instance.delet_rfid_entry(&rfid_list_instance, "11114444");
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);

    printf("----------------------------add ----------------------------------------------------\n");

    rfid_list_instance.add_rfid_entry(&rfid_list_instance, 0, "5555555", "2018042812300005", SV_FALSE);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("----------------------------empty test------------------------------------------------\n");

    rfid_list_instance.empty_rfidlist(&rfid_list_instance);
    rfid_list_instance.print_rfidlist(&rfid_list_instance);
    rfid_list_instance.count_rfidlist(&rfid_list_instance);
    printf("-------------------------------------------------------------------------------------\n");

    return 0;
}


SV_VOID init_rfidlist(Rfid_List* p_rfid_list_instance) {
    memset(p_rfid_list_instance, '\0', sizeof(*p_rfid_list_instance));
    //	printf("sizeof(*p_rfid_list_instance) %d\n", sizeof(*p_rfid_list_instance));
    //	printf("sizeof(Rfid_Node) %d\n", sizeof(Rfid_Node));
    //	printf("sizeof(Rfid_List)) %d\n", sizeof(Rfid_List));
    //	printf("sizeof point %d\n", sizeof(p_rfid_list_instance));
    p_rfid_list_instance->rfidlist_get_rfidNum = rfidlist_get_rfidNum;
    p_rfid_list_instance->rfidlist_set_rfidNum = rfidlist_set_rfidNum;
    p_rfid_list_instance->rfidlist_get_rfidNumDate = rfidlist_get_rfidNumDate;
    p_rfid_list_instance->rfidlist_set_rfidNumDate = rfidlist_set_rfidNumDate;
    p_rfid_list_instance->rfidlist_get_rfidNumisErrorNum = rfidlist_get_rfidNumisErrorNum;
    p_rfid_list_instance->rfidlist_set_rfidNumisErrorNum = rfidlist_set_rfidNumisErrorNum;
    p_rfid_list_instance->set_rfid_entry = set_rfid_entry;
    p_rfid_list_instance->get_rfid_entry = get_rfid_entry;
    p_rfid_list_instance->add_rfid_entry = add_rfid_entry;
    p_rfid_list_instance->delet_rfid_entry = delet_rfid_entry;
    p_rfid_list_instance->delet_rfid_entry_nth = delet_rfid_entry_nth;
    p_rfid_list_instance->empty_rfidlist = empty_rfidlist;
    p_rfid_list_instance->print_rfidlist = print_rfidlist;
    p_rfid_list_instance->count_rfidlist = count_rfid_entry;
    p_rfid_list_instance->init_rfidlist = init_rfidlist;
}

SV_S32 count_rfid_entry(Rfid_List* prfid_list) {
    int i = 0;
    for (i = 0; (prfid_list->Rfid_List + i)->rfid_num[0] != 0; i++) {    //注意*解引用，否则是数组地址，永远为真。
        if (i == COUNT_RFID_LIST_NODE) {
            break;
        }
    }
    printf("[There are:%d rfid Entry in rfid_list.]\n", i);
    return i;
}

SV_VOID print_rfidlist(Rfid_List* prfid_list) {
    char rfid_num[BufferSize];
    char rfid_num_date[BufferSize];
    SV_BOOL rfid_num_isErrorNum;
    printf("Rfid List Now:\n");
    for (int i = 0; i != COUNT_RFID_LIST_NODE; i++) {
        get_rfid_entry(prfid_list, i, rfid_num, rfid_num_date, &rfid_num_isErrorNum);
    }
}

SV_VOID  set_rfid_entry(Rfid_List* prfid_list, arrayposi N, const char rfid_num[BufferSize], const char rfid_num_date[BufferSize],  SV_BOOL*  rfid_num_isErrorNum) {
    rfidlist_set_rfidNum(prfid_list, N, rfid_num);
    rfidlist_set_rfidNumDate(prfid_list, N, rfid_num_date);
    rfidlist_set_rfidNumisErrorNum(prfid_list, N, rfid_num_isErrorNum);
}

SV_VOID  get_rfid_entry(Rfid_List* prfid_list, arrayposi N, char rfid_num[BufferSize], char rfid_num_date[BufferSize], SV_BOOL*  rfid_num_isErrorNum) {
    rfidlist_get_rfidNum(prfid_list, N, rfid_num);;
    rfidlist_get_rfidNumDate(prfid_list, N, rfid_num_date);
    rfidlist_get_rfidNumisErrorNum(prfid_list, N, rfid_num_isErrorNum);
    printf("Read rfidlist[%d].rfid_num:%s,rfid_num_date:%s,isErrorrRfidNum(SV_BOOL):%d.\n", N, rfid_num, rfid_num_date, *rfid_num_isErrorNum);
}

SV_VOID add_rfid_entry(Rfid_List* prfid_list, const arrayposi N, const char rfid_num[BufferSize], const char rfid_num_date[BufferSize],  SV_BOOL  rfid_num_isErrorNum) {
    for (int i = 0; i != COUNT_RFID_LIST_NODE - N - 1; i++) {
        set_rfid_entry(prfid_list, COUNT_RFID_LIST_NODE - 1 - i, (prfid_list->Rfid_List + (COUNT_RFID_LIST_NODE - 2 - i))->rfid_num, (prfid_list->Rfid_List + (COUNT_RFID_LIST_NODE - 2 - i))->rfid_num_date, &(prfid_list->Rfid_List + (COUNT_RFID_LIST_NODE - 2 - i))->rfid_num_isErrorNum);
    }
    set_rfid_entry(prfid_list, N, rfid_num, rfid_num_date, &rfid_num_isErrorNum);
}

SV_VOID delet_rfid_entry_nth(Rfid_List* prfid_list, arrayposi N) {
    for (int i = 0; i != COUNT_RFID_LIST_NODE - N - 1; i++) {
        set_rfid_entry(prfid_list, N + i, (prfid_list->Rfid_List + N + i + 1)->rfid_num, (prfid_list->Rfid_List + N + i + 1)->rfid_num_date, &(prfid_list->Rfid_List + N + i + 1)->rfid_num_isErrorNum);
    }
    memset(prfid_list->Rfid_List + COUNT_RFID_LIST_NODE - 1, 0, sizeof(Rfid_Node));
}

SV_S32 delet_rfid_entry(Rfid_List* prfid_list, const char rfid_num[BufferSize]) {     //注意添加const
    arrayposi N;
    for (N = 0; N != COUNT_RFID_LIST_NODE; N++) {
        int compareRfid(const char * p1, const  char * p2);
        printf("comparing the rfid_entry you enter(%s) in rfid_list[%d]:\"%s\"\n", rfid_num, N, (prfid_list->Rfid_List + N)->rfid_num);
        if (compareRfid((prfid_list->Rfid_List + N)->rfid_num, rfid_num) == 0) {
            printf("Found the rfid_entry willing to delete in rfid_list[%d]", N);
            break;
        }
    }
    if (N == COUNT_RFID_LIST_NODE) {
        printf("Not found the RfidNum You Enter!Delete NOT exected,check the input please!\n");
        return -1;
    }

    for (int i = 0; i != COUNT_RFID_LIST_NODE - N; i++) {
        set_rfid_entry(prfid_list, N + i, (prfid_list->Rfid_List + N + i + 1)->rfid_num, (prfid_list->Rfid_List + N + i + 1)->rfid_num_date, &(prfid_list->Rfid_List + N + i + 1)->rfid_num_isErrorNum);
    }
    memset(prfid_list->Rfid_List + COUNT_RFID_LIST_NODE - 1, 0, sizeof(Rfid_Node));
    return 0;
}

SV_VOID rfidlist_get_rfidNum(const Rfid_List* rfid_list, arrayposi N, char outputbuffer[BufferSize]) {
    memcpy(outputbuffer, (rfid_list->Rfid_List + N)->rfid_num, BufferSize);
    //	printf("Read rfidlist[%d].rfidNum:%s\n",N, outputbuffer);
}

SV_VOID rfidlist_set_rfidNum(Rfid_List* rfid_list, arrayposi N, const char inputbuffer[BufferSize]) {
    memcpy((rfid_list->Rfid_List + N)->rfid_num, inputbuffer, BufferSize);
    //	printf("Write rfidlist[%d].rfidNum:%s\n", N,(rfid_list->Rfid_List + N)->rfid_num);
}

SV_VOID rfidlist_get_rfidNumDate(const Rfid_List* rfid_list, arrayposi N, char outputbuffer[BufferSize]) {
    memcpy(outputbuffer, (rfid_list->Rfid_List + N)->rfid_num_date, BufferSize);
    //	printf("Read rfidlist[%d].rfidNumDate:%s\n", N, outputbuffer);
}

SV_VOID rfidlist_set_rfidNumDate(Rfid_List* rfid_list, arrayposi N, const char inputbuffer[BufferSize]) {
    memcpy((rfid_list->Rfid_List + N)->rfid_num_date, inputbuffer, BufferSize);
    //	printf("Write rfidlist[%d].rfidNumDate:%s\n",N,(rfid_list->Rfid_List + N)->rfid_num_date);
}

SV_VOID rfidlist_get_rfidNumisErrorNum(const Rfid_List* rfid_list, arrayposi N, SV_BOOL* isErrorrRfidNum) {
    *isErrorrRfidNum = (rfid_list->Rfid_List + N)->rfid_num_isErrorNum;
    //	printf("Read rfidlist[%d].isErrorrRfidNum:%d\n", N, *isErrorrRfidNum);
}

SV_VOID rfidlist_set_rfidNumisErrorNum(Rfid_List* rfid_list, arrayposi N, SV_BOOL* isErrorrRfidNum) {
    (rfid_list->Rfid_List + N)->rfid_num_isErrorNum = *isErrorrRfidNum;
    //	printf("Write rfidlist[%d].isErrorrRfidNum(SV_BOOL):%d\n",N, (rfid_list->Rfid_List + N)->rfid_num_isErrorNum);
}

SV_VOID empty_rfidlist(Rfid_List* p_rfid_list_instance) {
    for (int i = 0; i != COUNT_RFID_LIST_NODE; i++) {
        memset(p_rfid_list_instance->Rfid_List + i, '\0', sizeof(Rfid_Node));
    }
}

SV_S32 compareRfid(const char * p1, const char * p2) {
    char c1, c2;
    do {
        c1 = *p1++;
        c2 = *p2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}

#ifdef __cplusplus
}
#endif


