#include "iteration1.hh"
#include <iostream>  // Required for std::cout
using namespace std;

void printAllItems(const list<int>& lst)
{
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
}
