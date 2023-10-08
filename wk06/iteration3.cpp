#include "iteration3.hh"
#include <iostream>  // Required for std::cout
using namespace std;

void printHalf(const list<int>& lst)
{
    auto mid = lst.size() / 2;  // Calculate the midpoint
    auto it = lst.begin();
    for(size_t i = 0; i < mid; ++i, ++it) {
        cout << *it << " ";
    }
}
