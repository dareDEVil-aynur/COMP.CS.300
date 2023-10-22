#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    try 
    {
        std::stable_sort(v.begin(), v.end(), [](int a, int b) {
            // First sort by modulo 3
            if (a % 3 != b % 3) return a % 3 < b % 3;
            
            // Then sort by value within each modulo 3 category
            return a < b;
        });

        return EXIT_SUCCESS;
    } 
    catch(...) 
    {
        return EXIT_FAILURE;
    }
}
