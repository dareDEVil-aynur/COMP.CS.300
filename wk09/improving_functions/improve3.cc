#include <iterator>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>


/**
 * @brief Sums up the values of the vector cumulatively, storing cumulative sum
 *        of the vector in a map, where the keys are the unique vector items,
 *        and the value is the last cumulative sum when that value was last
 *        encountered. (example: {4, 5, 4, 6} => {{4, 13}, {5, 9}, {6, 19}}).
 *
 * @param vec vector which is used for the sum operation.
 * @return std::map<int, int> sums - the sums of each cumulation stored in
 *         a map as values, vector values used as keys.
 */
std::map<int, int> cumulativeSums(const std::vector<int>& vec) {
    std::map<int, int> sums;
    int cumulative = 0; // To hold the cumulative sum
    for (int num : vec) {
        cumulative += num;
        sums[num] = cumulative;
    }
    return sums;
}
