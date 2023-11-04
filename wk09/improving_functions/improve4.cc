#include <iterator>
#include <vector>
#include <algorithm>
#include <random>


//---- Some utilities
using iter = std::vector<int>::iterator;
using RNG = std::default_random_engine;

/**
 * @brief Sorts a given vector using a 3 part randomized quicksort algorithm.
 *        Randomization is used to avoid worst case (where the pivot value is
 *        chosen poorly).
 *
 * HINT: The way randomization is implemented can be changed. Shuffle may not
 *       be the only or the best way to implement randomization.
 *
 * @param begin an iterator that points to the beginning part of the sequence where the quicksort is performed.
 * @param end an iterator that points to the end part of the sequence where the quicksort is performed
 * @param rng the random number generator that can be used
 */
void threeWayPartition(iter begin, iter end, iter& i, iter& j, RNG& rng) {
    std::uniform_int_distribution<> dis(0, std::distance(begin, end) - 1);
    std::iter_swap(begin, begin + dis(rng));
    auto pivot = *begin;
    i = begin;
    j = end;

    iter it = begin + 1;
    while (it < j) {
        if (*it < pivot) {
            std::iter_swap(i++, it++);
        } else if (*it > pivot) {
            std::iter_swap(--j, it);
        } else {
            ++it;
        }
    }
}

void randomizedThreePartQuicksort(iter begin, iter end, RNG& rng) {
    if (begin >= end) return;

    iter i, j;
    threeWayPartition(begin, end, i, j, rng);

    randomizedThreePartQuicksort(begin, i, rng);
    randomizedThreePartQuicksort(j, end, rng);
}