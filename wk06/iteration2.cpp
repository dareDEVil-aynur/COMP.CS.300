#include "iteration2.hh"
#include <iostream>  // Required for std::cout
using namespace std;

void printEverySecond(const list<int>& lst)
{
    bool print = true;  // Variable to control when to print
    for(auto it = lst.begin(); it != lst.end(); ++it) {
        if(print) {
            cout << *it << " ";
        }
        print = !print;  // Toggle the print variable
    }
}
