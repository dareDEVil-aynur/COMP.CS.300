#include "iteration4.hh"
#include <iostream>  // Required for std::cout
using namespace std;

void printReverse(const list<int>& lst)
{
    for(auto rit = lst.rbegin(); rit != lst.rend(); ++rit) {
        cout << *rit << " ";
    }
}
