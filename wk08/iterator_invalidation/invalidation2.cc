#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    auto it = vec.begin();
    while (it != vec.end()) {
        ++it;  // skip the current element
        if (it != vec.end()) {
            it = vec.erase(it);  // erase the next element and return the iterator to the subsequent element
        }
    }
}

