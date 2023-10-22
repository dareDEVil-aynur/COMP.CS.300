#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;

/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    if (v.empty())
    {
        return NOT_FOUND;
    }

    std::sort(v.begin(), v.end());

    size_t size = v.size();

    // If even number of elements, return average of the two middle numbers
    if (size % 2 == 0)
    {
        return (v[size / 2 - 1] + v[size / 2]) / 2; // Integer division rounds down
    }
    // If odd number of elements, return the middle number
    else
    {
        return v[size / 2];
    }
}
