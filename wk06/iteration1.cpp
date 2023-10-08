// File: iteration1.cc

#include "iteration1.hh"
using namespace std;

void printAllItems(const list<int>& lst)
{
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}
