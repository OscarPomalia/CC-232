#include <cassert>
#include <vector>

#include "bubble_sort.h"
#include "count_ones.h"
#include "gcd.h"
#include "hanoi.h"
#include "max_algorithms.h"
#include "reverse_utils.h"

//Pruebas adicionales
int main() {
    int a[] = {5, 1, 4, 2, 8};
    const BubbleStats stats = bubbleSortOptimized(a, 5);
    assert(isSortedNonDecreasing(a, 5));
    assert(stats.comparisons > 0);

    assert(countOnes1(0u) == 0);
    assert(countOnes1(0b11110000u) == 4);
    assert(countOnes2(0b11110000u) == 4);

    int b[] = {-5, 10, 3, 7};
    assert(maxI(b, 4) == 10);
    assert(maxRLinear(b, 4) == 10);
    assert(maxRDivide(b, 0, 4) == 10);

    int c[] = {1, 2, 3, 4, 5};
    reverseRecursive(c, 5);
    assert(c[0] == 5 && c[4] == 1);
    shiftLeftByK(c, 5, 2);
    int expected[] = {3, 2, 1, 5, 4};
    for (int i = 0; i < 5; ++i) assert(c[i] == expected[i]);

    assert(gcdCN(48, 18) == 6);

    std::vector<HanoiMove> moves;
    solveHanoi(3, 'A', 'B', 'C', moves);
    assert(static_cast<long long>(moves.size()) == hanoiMoveCount(3));
    return 0;
}
