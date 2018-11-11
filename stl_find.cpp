/**************************************************************************
* 函数功能: 搜索算法示例。
* 输入参数:
***************************************************************************/
#include<iostream>
#include<algorithm>
#include<functional>
#include<string>
#include<vector>
#include <map>
#include<cstdio>

using namespace std;

class Student
{
public:
    Student() {}
    Student(string iname, float iscore) :name(iname), score(iscore) {}
    ~Student() {}
    string name;
    float score;
};


/*********************************************************************
unary_function  一元函数对象基类。explicit 用于禁止单参数默认类转化。
**********************************************************************/

class StudentAdapter :public unary_function<Student, bool>
{
private:
    string name;

public:
    explicit StudentAdapter(string iname) :name(iname) {}
    bool operator()(const Student& student)
    {
        return (student.name == name);
    }
};


int Vector_findif_main()
{
    vector<Student> admin;
    vector<Student>::iterator pos;

    Student stu1("lanzhihui", 89.1);
    Student stu2("wangdan", 89.2);
    Student stu3("wangqian", 89.3);

    admin.push_back(stu1);
    admin.push_back(stu2);
    admin.push_back(stu3);

    //实验find_if
    pos = find_if(admin.begin(), admin.end(), StudentAdapter("lanzhihui"));

    if (pos != admin.end())
    {
        cout << pos->name << " " << pos->score << endl;
    }

    //以下实验find
    vector<int> coll;
    vector<int>::iterator pos1;
    for (int i = 0; i<10; i++)
    {
        coll.push_back(i);
    }

    pos1 = find(coll.begin(), coll.end(), 5);

    if (pos1 != coll.end())
    {
        cout << *pos1 << " is find" << endl;
    }

    return 0;
}

/**************************************************************************
* 函数功能: 搜索算法示例。
* 输入参数:
***************************************************************************/
class  map_finder
{
public:
    map_finder(const std::string &cmp_string) :m_s_cmp_string(cmp_string) {}
    bool operator ()(const std::map<int, std::string>::value_type &pair)
    {
        return pair.second == m_s_cmp_string;
    }
private:
    const std::string &m_s_cmp_string;
};


int mapfind_main()
{
    std::map<int, std::string> my_map;
    my_map.insert(std::make_pair(10, "china"));
    my_map.insert(std::make_pair(20, "usa"));
    my_map.insert(std::make_pair(30, "english"));
    my_map.insert(std::make_pair(40, "hongkong"));

    std::map<int, std::string>::iterator it = my_map.end();
    it = std::find_if(my_map.begin(), my_map.end(), map_finder("english"));
    if (it == my_map.end())
        printf("not found\n");
    else
        printf("found key:%d value:%s\n", it->first, it->second.c_str());
    
    return 0;
}


