
#include <iostream>       // std::cout  
#include <string>         // std::string  

int test_stringFindmain()
{
    std::string str("There are two needles in this haystack with needles.");
    std::string str2("needle");

    std::cout << str << std::endl;
    // different member versions of find in the same order as above:  
    std::size_t found = str.find(str2);
    if (found != std::string::npos)
        std::cout << "first 'needle' found at: " << found << '\n';

    found = str.find("needles are small", found + 1, 6);
    //在str中的第(found+1)位开始搜索，搜索"needles are small"字符串中的前6位，找到索引位置。
    if (found != std::string::npos)
        std::cout << "second 'needle' found at: " << found << '\n';

    found = str.find("haystack");
    if (found != std::string::npos)
        std::cout << "'haystack' also found at: " << found << '\n';

    found = str.find('.');
    if (found != std::string::npos)
        std::cout << "Period found at: " << found << '\n';

    // let's replace the first needle:  
    str.replace(str.find(str2), str2.length(), "preposition");  //replace 用法  
    std::cout << str << '\n';

    return 0;
}

int main()
{
    test_stringFindmain();
    return 0;
}