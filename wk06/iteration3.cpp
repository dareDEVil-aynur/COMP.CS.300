// File: iteration3.cc

#include "iteration3.hh"
using namespace std;

void printHalf(const list<int>& lst)
{
    auto it = lst.begin();
    size_t halfSize = lst.size() / 2;
    for(size_t i = 0; i < halfSize; ++i, ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
