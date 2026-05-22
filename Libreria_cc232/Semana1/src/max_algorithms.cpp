#include "max_algorithms.h"

#include <algorithm>
#include <cassert>
#include <limits>

int maxI(const int A[], int n) {
    assert(n > 0);
    int m = std::numeric_limits<int>::min();
    for (int i = 0; i < n; ++i) {
        m = std::max(m, A[i]);
    }
    return m;
}

int maxRLinear(const int A[], int n) {
    assert(n > 0);
    if (n < 2) return A[n - 1];
    return std::max(maxRLinear(A, n - 1), A[n - 1]);
}

int maxRDivide(const int A[], int lo, int hi) {
    assert(lo < hi);
    if (lo + 1 == hi) return A[lo];
    const int mi = lo + (hi - lo) / 2;
    return std::max(maxRDivide(A, lo, mi), maxRDivide(A, mi, hi));
}
