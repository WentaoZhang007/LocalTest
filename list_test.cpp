

#define  _SCL_SECURE_NO_WARNINGS

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
#include <iostream>
#include <algorithm>
#include <list>



using namespace std;



struct Node {

    int a;
    char c;	//如果c是0的化，控制台显示不了（ASCII 0 ）

    Node(int b, char e) 
    {
        a = b;
        c = e;
    }
};



void fun(Node &d) {

    cout << d.a << " " << (int)d.c << "\n";	//"\n"比endl效率更高	

}



void fun1(Node &d) {

    cout << d.a << " " << d.c << "\n";	//"\n"比endl效率更高	

}



int main() {

    list<Node> ls;

    ls.push_back(Node(11, 'a'));
    ls.push_back(Node(12, 'b'));
    ls.push_back(Node(13, 'c'));
    ls.push_back(Node(14, 'd'));
    ls.push_back(Node(15, 'e'));

    for_each(ls.begin(), ls.end(), fun1);
    cout << endl;


    ls.pop_back();
    for_each(ls.begin(), ls.end(), fun1);
    cout << endl;

    ls.pop_front();
    for_each(ls.begin(), ls.end(), fun1);
    cout << endl;

    list<Node>::iterator ite = ls.begin();

    ite++;

    ls.erase(ite);

    for_each(ls.begin(), ls.end(), fun1);
    cout << endl;

    ls.erase(--ls.end());

    for_each(ls.begin(), ls.end(), fun1);
    cout << endl;
    

    //ls.assign(3, Node(1, 'z'));	//不够就自动增加
    //for_each(ls.begin(), ls.end(), fun1);
   // cout << endl;

    system("pause");
    return 0;

}
