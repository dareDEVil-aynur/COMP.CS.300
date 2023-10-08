// File: iteration4.cc

#include "iteration4.hh"
using namespace std;

void printReverse(const list<int>& lst)
{
    for(auto it = lst.rbegin(); it != lst.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
