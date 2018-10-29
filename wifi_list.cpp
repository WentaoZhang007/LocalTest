#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#include<fstream>
#include<string>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<algorithm>
#include <list>
#include <string>
#define SV_U16       unsigned short
#define SV_S32       int
#define SV_CHAR      char
#define SV_TRUE      1
#define SV_FALSE     0
#define SV_FAILURE   -1
#define SV_SUCCESS   0
#define SV_BOOL      int
using namespace std;


typedef enum _NDIS_802_11_AUTHENTICATION_MODE {
    Ndis802_11AuthModeOpen,
    Ndis802_11AuthModeShared,
    Ndis802_11AuthModeAutoSwitch,
    Ndis802_11AuthModeWPA,
    Ndis802_11AuthModeWPAPSK,
    Ndis802_11AuthModeWPANone,
    Ndis802_11AuthModeWPA2,
    Ndis802_11AuthModeWPA2PSK,
    Ndis802_11AuthModeWPA1WPA2,
    Ndis802_11AuthModeWPA1PSKWPA2PSK,
#ifdef WAPI_SUPPORT
    Ndis802_11AuthModeWAICERT,	/* WAI certificate authentication */
    Ndis802_11AuthModeWAIPSK,	/* WAI pre-shared key */
#endif		             		/* WAPI_SUPPORT */
    Ndis802_11AuthModeMax	    /* Not a real mode, defined as upper bound */
} NDIS_802_11_AUTHENTICATION_MODE;

typedef enum _APSTORAGETYPE
{
    E_STORUNKNOWN,
    E_STORPRESET,
    E_STORUSERSET,
    E_STORNOAUTH
}STORAGETYPE;

typedef enum _AP_SIGNAL_LEVL
{
    E_SIGNUNKNOWN,
    E_SIGNNOSIGNAL,
    E_SIGNWEAK,
    E_SIGNSTRONG
}AP_SIGNAL_LEVL;

int thread = 6;

typedef struct tag_WifiApInfo_S
{
    char           szSSID[64];
    //char         szBSSID[22];
    SV_U16         u16Signal;
    STORAGETYPE    E_storType;
    AP_SIGNAL_LEVL E_sigLev;
    //NDIS_802_11_AUTHENTICATION_MODE enAuthMode;
    //NDIS_802_11_WEP_STATUS          enEncryType;
} Wifi_AP_INFO_S;


struct APdescendbySignal
{
    bool operator()(const Wifi_AP_INFO_S& t1, const Wifi_AP_INFO_S& t2)
    {
        return t1.u16Signal > t2.u16Signal;
    }
};

SV_S32 Wifi_XMLlist_creat(std::list<Wifi_AP_INFO_S > & XMLlist)
{
    XMLlist.clear();

    Wifi_AP_INFO_S XML1 = { "SSID_F", 0 ,E_STORPRESET, E_SIGNSTRONG };
    Wifi_AP_INFO_S XML2 = { "SSID_G", 0 ,E_STORPRESET ,E_SIGNSTRONG };
    Wifi_AP_INFO_S XML3 = { "SSID_H", 0 ,E_STORPRESET ,E_SIGNSTRONG };
    Wifi_AP_INFO_S XML4 = { "SSID_Z", 0 ,E_STORPRESET, E_SIGNSTRONG };
    Wifi_AP_INFO_S XML5 = { "SSID_A", 0 ,E_STORUSERSET,E_SIGNSTRONG };
    Wifi_AP_INFO_S XML6 = { "SSID_B", 0 ,E_STORUSERSET,E_SIGNSTRONG };

    XMLlist.push_back(XML1);
    XMLlist.push_back(XML2);
    XMLlist.push_back(XML3);
    XMLlist.push_back(XML4);
    XMLlist.push_back(XML5);
    XMLlist.push_back(XML6);

    return 0;
}

SV_S32 Wifi_APlist_creat(std::list<Wifi_AP_INFO_S > & APlist)
{
    APlist.clear();

    Wifi_AP_INFO_S AP1 = { "SSID_A", 12 ,E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP2 = { "SSID_B", 10 ,E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP3 = { "SSID_C", 9 , E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP4 = { "SSID_D", 8 , E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP5 = { "SSID_E", 6 , E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP6 = { "SSID_F", 1 , E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP7 = { "SSID_G", 0 , E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP8 = { "SSID_H", 13 ,E_STORUNKNOWN ,E_SIGNSTRONG };
    Wifi_AP_INFO_S AP9 = { "SSID_I", 0 , E_STORUNKNOWN ,E_SIGNSTRONG };

    APlist.push_back(AP1);
    APlist.push_back(AP2);
    APlist.push_back(AP3);
    APlist.push_back(AP4);
    APlist.push_back(AP5);
    APlist.push_back(AP6);
    APlist.push_back(AP7);
    APlist.push_back(AP8);
    APlist.push_back(AP9);

    return 0;
}

SV_S32 Wifi_APlist_print(const std::list<Wifi_AP_INFO_S> & AP_list)
{
    printf("Wifi_APlist_print.\n");
    std::list<Wifi_AP_INFO_S>::const_iterator it;
    for (it = AP_list.cbegin(); it != AP_list.cend(); it++)
    {
        printf("Wifi_AP_INFO_S :SSIS[%s],signal[%u],storeType[%d],signLev[%d].\n",
            (*it).szSSID, (*it).u16Signal, (*it).E_storType, (*it).E_sigLev);
    }
    return SV_SUCCESS;
}

SV_S32 Wifi_cachGet()
{
    std::cout << "cachGet." << std::endl;
    return SV_SUCCESS;

}

SV_S32 Wifi_XML_insert()
{
    std::cout << "Cach update." << std::endl;
    return SV_SUCCESS;
}

SV_S32 Wifi_XML_storge()
{
    std::cout << "Cach storage." << std::endl;
    return SV_SUCCESS;
}

SV_S32 Wifi_APlist_update_signnLev(std::list<Wifi_AP_INFO_S> & APlist, const SV_S32 s32Thres)
{
    std::list<Wifi_AP_INFO_S>::iterator it;
    for (it = APlist.begin(); it != APlist.end(); it++)
    {
        if ((*it).u16Signal <= 0)
            (*it).E_sigLev = E_SIGNNOSIGNAL;
        else if ((*it).u16Signal < s32Thres)
            (*it).E_sigLev = E_SIGNWEAK;
        else
            (*it).E_sigLev = E_SIGNSTRONG;
    }
    return SV_SUCCESS;
}


SV_S32 Wifi_APlist_sync(std::list<Wifi_AP_INFO_S> & APlist, std::list<Wifi_AP_INFO_S> &XMLAPlist)
{
    std::list<Wifi_AP_INFO_S>::iterator itAP;
    std::list<Wifi_AP_INFO_S>::iterator itXML;
    int s32XMLnum_Signal = 0;
    int s32XMLnum_NOSigna = 0;

    for (itXML = XMLAPlist.begin(); itXML != XMLAPlist.end(); itXML++)
    {
        for (itAP = APlist.begin(); itAP != APlist.end(); itAP++)
        {
            if (strcmp((*itXML).szSSID, (*itAP).szSSID) == 0 && strlen((*itXML).szSSID) != 0 && strlen((*itAP).szSSID) != 0)
            {
                (*itAP).E_storType = (*itXML).E_storType;
                (*itXML).E_sigLev = (*itAP).E_sigLev;
                (*itXML).u16Signal = (*itAP).u16Signal;
                s32XMLnum_Signal++;
                break;
            }
        }
        if (itAP == APlist.end())
        {
            printf("found no XMLAP[SSID:%s] in APlist.", (*itXML).szSSID);
            if ((*itXML).E_storType == E_STORPRESET)
            {
                (*itXML).E_sigLev = E_SIGNNOSIGNAL;
                //(*itAP).E_sigLev = E_SIGNNOSIGNAL;
                APlist.push_back(*itXML);
                s32XMLnum_NOSigna++;
            }
        }
    }
    printf("AP num :XMLnum_hasSignal [%d],XMLnum_NOSigna[%d]\n", s32XMLnum_Signal, s32XMLnum_NOSigna);

    return 0;
}

SV_S32 Wifi_APlist_sort(std::list<Wifi_AP_INFO_S> & APlist, const std::list<Wifi_AP_INFO_S> &XMLAPlist)
{
    std::list<Wifi_AP_INFO_S>::const_iterator  itXML;
    std::list<Wifi_AP_INFO_S>::reverse_iterator  itAP;
    int n = 0;
    

    for (itXML = XMLAPlist.cbegin(); itXML != XMLAPlist.cend(); itXML++)
    {
        //for (itAP = APlist.end(); itAP != APlist.begin(); )  
        for (itAP = APlist.rbegin(); itAP != APlist.rend(); )  
        {
            if (strcmp((*itAP).szSSID,(*itXML).szSSID)== 0 && (*itAP).E_sigLev == E_SIGNSTRONG)
            {
                printf("find AP in XML :%s.\n", (*itAP).szSSID);
                APlist.push_front(*itAP);
                *itAP;
                std::list<Wifi_AP_INFO_S>::reverse_iterator itAPtemp = ++itAP;
                APlist.erase((itAP).base());                
                n++;     
                break;
            }
            else 
            {
                itAP++;
            }
        }
    }    
    return SV_SUCCESS;
}



/*
如果预设ifi可用，选择预设Wifi；
如果设ifi不可用（<=weak），选择信号最强的自定义Wifi
如果自定义Wifi不可用，则提示弹窗。
*/
SV_S32 Wifi_select( Wifi_AP_INFO_S & CurrentWifi, const std::list<Wifi_AP_INFO_S> & XML_list, const std::list<Wifi_AP_INFO_S> & AP_list)
{
    int res = -1;
    std::list<Wifi_AP_INFO_S>::const_iterator itXML, itAP;

    if (CurrentWifi.E_sigLev == E_SIGNSTRONG)
    {
        printf("Aviable Wifi AP NO changed!\n");
        return 0;
    }
    for ( itXML = XML_list.cbegin();itXML != XML_list.cend(); itXML++)
    {
        for ( itAP = AP_list.cbegin(); itAP != AP_list.cend(); itAP++) 
        {
            if (strcmp((*itXML).szSSID, (*itAP).szSSID) == 0) 
            {    
                CurrentWifi = (*itAP);
                printf("Aviable Wifi AP changed!\n");
                res = 1;
            }
        }       
    }
    if (itXML == XML_list.cend()) 
    {
        printf("Found No Aviable Wifi.\n");
        res = -1;
    }

    return res;
}

SV_BOOL Wifi_judge()
{
    return SV_FALSE;
}




int main()
{
    std::list<Wifi_AP_INFO_S> APlist;
    std::list<Wifi_AP_INFO_S> XMLlist;

    Wifi_APlist_creat(APlist);
    Wifi_XMLlist_creat(XMLlist);
    Wifi_APlist_print(APlist);
    Wifi_APlist_print(XMLlist);

    Wifi_APlist_update_signnLev(APlist, 8);
    Wifi_APlist_sync(APlist, XMLlist);
    cout << "synced..." << endl;
    Wifi_APlist_print(APlist);
    Wifi_APlist_print(XMLlist);

    APlist.sort(APdescendbySignal());
    XMLlist.sort(APdescendbySignal());
    XMLlist.reverse();

    Wifi_APlist_print(APlist);
    Wifi_APlist_print(XMLlist);
    
    cout << "sort..."<<endl;
    Wifi_APlist_sort(APlist, XMLlist);

    Wifi_APlist_print(APlist);

    cout <<"select..."<<endl;
    Wifi_select(APlist.front(), XMLlist,APlist);

    Wifi_APlist_print(APlist);
    //Wifi_APlist_print(XMLlist);

    return 0;
}













