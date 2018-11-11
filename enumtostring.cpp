#include <iostream>
#include <list>
#include <string.h>

using namespace std;

enum ProgLang
{
	e_cpp,
	e_java,
	e_csharp
};

int main(int argc, char const *argv[])
{
    ProgLang e_test = static_cast<ProgLang>(1);
    std::cout<<"over!"<<std::endl;
    return 0;
}
