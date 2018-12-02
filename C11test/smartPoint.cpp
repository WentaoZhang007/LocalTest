#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

int test_smartcpp_main(void)
{
    // two shared pointers representing two persons by their name
    shared_ptr<string> pNico(new string("nico"));
    shared_ptr<string> pJutta(new string("jutta"),
        // deleter (a lambda function) 
        [](string *p)
    {
        cout << "delete " << *p << endl;
        delete p;
    }
    );

    // capitalize person names
    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "J");

    // put them multiple times in a container
    vector<shared_ptr<string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutta);
    whoMadeCoffee.push_back(pNico);

    // print all elements
    for (auto ptr : whoMadeCoffee)
        cout << *ptr << " ";
    cout << endl;

    // overwrite a name again
    *pNico = "Nicolai";

    // print all elements
    for (auto ptr : whoMadeCoffee)
        cout << *ptr << " ";
    cout << endl;

    // print some internal data
    cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;

    return 0;
}