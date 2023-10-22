#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;

/**
 * @brief sort a given vector to a descending order
 *
 * @param v a vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortDesc(std::vector<int>& v)
{
    try 
    {
        std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; }); // Sorting the vector in descending order using a lambda function
        return EXIT_SUCCESS;
    } 
    catch(...) 
    {
        return EXIT_FAILURE;
    }
}
