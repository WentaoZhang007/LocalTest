#include <iostream>
#include <list>
#include <string>
#include "sv_common.h"
using namespace std;

class rfid_entry {
public:
	string   rfid_num;
	string   rfid_date;
	SV_BOOL  isErrorNum;
	rfid_entry(const string& string_rfid_num,const string& string_rfid_date, SV_BOOL bool_isErrorNum);
};

class rfid_recent_list_ {
public:
    explicit  rfid_recent_list_();
    explicit  rfid_recent_list_(SV_U32 max_size);
    SV_VOID   add_rfid_Entry(string string_rfid_num, string string_rfid_date, SV_BOOL bool_isErrorNum);
    SV_VOID   empty_rfid_entry();
    SV_VOID   printlist();
    SV_U32    _size;
    SV_VOID   get_latest_RfidList_N(const SV_U32 N, string& rfidNum, string& rfidData, string& ErrorOrMatched);
    list<rfid_entry> RfidList;
    SV_U32    MAXSIZE;
};

rfid_entry::rfid_entry(const string& string_rfid_num, const string& string_rfid_date, SV_BOOL bool_isErrorNum) {
    this->rfid_num = string_rfid_num;
    this->rfid_date = string_rfid_date;
    this->isErrorNum = bool_isErrorNum;
}

rfid_recent_list_::rfid_recent_list_(SV_U32 maxsize=5) {
	this->MAXSIZE = maxsize;
	_size = 0;
}

rfid_recent_list_::rfid_recent_list_() {
    this->MAXSIZE = 5;
    _size = 0;
}

SV_VOID rfid_recent_list_::add_rfid_Entry(const string string_rfid_num, const string string_rfid_date, SV_BOOL bool_isErrorNum) {
	if (this->_size != this->MAXSIZE) {
		RfidList.push_front(rfid_entry(string_rfid_num, string_rfid_date, bool_isErrorNum));
		_size++;	
	}
	else {
		RfidList.push_front(rfid_entry(string_rfid_num, string_rfid_date, bool_isErrorNum));
		RfidList.pop_back();
		this->_size = this->MAXSIZE;
	}
}

SV_VOID rfid_recent_list_::empty_rfid_entry() {
	for (SV_S32 i = 0; i != this->_size;i++) {
		RfidList.pop_front();
	}
	this->_size = 0;
}

SV_VOID rfid_recent_list_::printlist() {    
    if (this->_size != 0) {
        list<rfid_entry>::iterator it;
        string strisError ;
        for (it = RfidList.begin();it!= RfidList.end(); it++) {
            strisError = (*it).isErrorNum == 0 ? "Error." : "Matched.";
            cout << "DriverID: "<<" Num:" << (*it).rfid_num<< ",  Date:" <<(*it).rfid_date<< "  "<<strisError<<endl;
        }
    }
    else {
        cout << "rfid_recent_list is Empty!" << endl;
    }
}

SV_VOID rfid_recent_list_::get_latest_RfidList_N(const  SV_U32 N, string& rfidNum, string& rfidData, string& ErrorOrMatched) {
    if (N>=this->MAXSIZE) 
    {
        cout<<"input:"<< N << " is exceeding MAXSIZEsettnig" << endl;
        return;            
    }    
    else if (this->_size != 0) 
    {
        list<rfid_entry>::iterator it;
        string strisError;
        int i = 0;
        for (it = RfidList.begin(); it != RfidList.end(); it++) 
        {            
            if (i == N) 
            {
                strisError = (*it).isErrorNum == 0 ? "Error." : "Matched.";
                rfidNum = (*it).rfid_num;
                rfidData = (*it).rfid_date;
                ErrorOrMatched = strisError;
                cout <<"get Latest"<< N <<"Rfid" << endl ;
                cout << "DriverID: " << " Num:"  << rfidNum << ",  Date:" << rfidData << "  " << ErrorOrMatched << endl;
                break;            
            }
            i++;
        }
    }
    else 
    {
        rfidNum = "\0";
        rfidData = "\0";
        ErrorOrMatched = "\0";
    }
}


int test_Rfid_recent_list_main() {
    rfid_recent_list_ rfidlist(5);
    cout << "Latest 5 RFID ---------------------------------------------"<<endl;
    rfidlist.add_rfid_Entry("1111111", "20180405 08:30", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("2222222", "20180405 09:00", SV_FALSE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("2222222", "20180405 09:01", SV_FALSE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("3333333", "20180405 09:05", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("2222222", "20180405 09:20", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("444444",  "20180405 09:30", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("555555",  "20180405 09:50", SV_FALSE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("666666",  "20180405 10:00", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("77777777", "20180405 10:10", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("888888888", "20180405 10:20", SV_FALSE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("*",        "20180405 10:30", SV_TRUE);
    rfidlist.printlist();
    cout << "Latest 5 rfid ---------------------------------------------" << endl;
    rfidlist.add_rfid_Entry("9999999", "20180405 12:00", SV_FALSE);
    rfidlist.printlist();
    cout << "Latest N rfid ---------------------------------------------" << endl;
    string srfidNum; 
    string &ref_srfidNum = srfidNum;
    string srfidData; 
    string &ref_srfidData = srfidData;
    string ErrorOrMatched; 
    string &ref_ErrorOrMatched = ErrorOrMatched;
    cout << "Latest N=0 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(0, srfidNum, srfidData, ErrorOrMatched);   
    cout << "Latest N=1 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(1, srfidNum, srfidData, ErrorOrMatched);
    cout << "Latest N=2 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(2, srfidNum, srfidData, ErrorOrMatched);
    cout << "Latest N=3 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(3, srfidNum, srfidData, ErrorOrMatched);
    cout << "Latest N=4 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(4, srfidNum, srfidData, ErrorOrMatched);
    cout << "Latest N=5 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(5, srfidNum, srfidData, ErrorOrMatched);
    cout << "Latest N=6 test ---------------------------------------------" << endl;
    rfidlist.get_latest_RfidList_N(6, srfidNum, srfidData, ErrorOrMatched);
    cout << "empty test ---------------------------------------------" << endl;
    rfidlist.empty_rfid_entry();
    rfidlist.printlist();
    cout << "end test -----------------------------------" << endl;

	return 0;
}