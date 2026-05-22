#include <cassert>
#include <vector>

#include "bubble_sort.h"
#include "count_ones.h"
#include "gcd.h"
#include "hanoi.h"
#include "max_algorithms.h"
#include "reverse_utils.h"

int main() {
    int sorted[] = {1, 2, 3, 4, 5};
    auto statsSorted = bubbleSortOptimized(sorted, 5);
    assert(isSortedNonDecreasing(sorted, 5));
    assert(statsSorted.swaps == 0);

    int dup[] = {3, 3, 2, 2, 1, 1};
    bubbleSortBasic(dup, 6);
    assert(isSortedNonDecreasing(dup, 6));

    for (unsigned int x : {0u, 1u, 7u, 31u, 255u, 256u, 1023u}) {
        assert(countOnes1(x) == countOnes2(x));
    }

    int a[] = {42};
    assert(maxI(a, 1) == 42);
    assert(maxRLinear(a, 1) == 42);
    assert(maxRDivide(a, 0, 1) == 42);

    int r[] = {1, 2, 3, 4, 5, 6};
    shiftLeftByK(r, 6, 8);
    int expected[] = {3, 4, 5, 6, 1, 2};
    for (int i = 0; i < 6; ++i) assert(r[i] == expected[i]);

    assert(gcdCN(-270, 192) == 6);
    assert(gcdCN(0, 5) == 5);

    std::vector<HanoiMove> moves;
    solveHanoi(1, 'A', 'B', 'C', moves);
    assert(moves.size() == 1u);
    assert(moves[0].first == 'A' && moves[0].second == 'C');
    return 0;
}
