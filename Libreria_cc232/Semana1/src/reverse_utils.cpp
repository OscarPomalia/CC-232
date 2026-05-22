#include "reverse_utils.h"

#include <algorithm>

void reverseIterative(int A[], int n) {
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        std::swap(A[i], A[j]);
    }
}

void reverseRecursive(int A[], int n) {
    if (n < 2) return;
    std::swap(A[0], A[n - 1]);
    reverseRecursive(A + 1, n - 2);
}

void shiftLeftByK(int A[], int n, int k) {
    if (n <= 0) return;
    k %= n;
    if (k < 0) k += n;
    if (k == 0) return;
    reverseIterative(A, k);
    reverseIterative(A + k, n - k);
    reverseIterative(A, n);
}
