#include "sum.h"

int sumI(const int A[], int n) {
    int acc = 0;
    for (int i = 0; i < n; ++i) acc += A[i];
    return acc;
}

int sum(const int A[], int n) {
    if (n <= 0) return 0;
    return sum(A, n - 1) + A[n - 1];
}

int sum(const int A[], int lo, int hi) {
    if (hi <= lo) return 0;
    if (hi - lo == 1) return A[lo];
    const int mi = lo + (hi - lo) / 2;
    return sum(A, lo, mi) + sum(A, mi, hi);
}
