// File: iteration2.cc

#include "iteration2.hh"
using namespace std;

void printEverySecond(const list<int>& lst)
{
    bool print = true;
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        if(print) {
            cout << *it << " ";
        }
        print = !print;  // toggle the print flag
    }
    cout << endl;
}
