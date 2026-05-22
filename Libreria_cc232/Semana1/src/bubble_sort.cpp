#include "bubble_sort.h"

#include <algorithm>

bool bubblePass(int A[], int n, BubbleStats& stats) {
    bool changed = false;
    stats.lastSwapIndex = 0;
    for (int i = 1; i < n; ++i) {
        ++stats.comparisons;
        if (A[i - 1] > A[i]) {
            std::swap(A[i - 1], A[i]);
            ++stats.swaps;
            stats.lastSwapIndex = i;
            changed = true;
        }
    }
    return changed;
}

BubbleStats bubbleSortBasic(int A[], int n) {
    BubbleStats stats;
    for (int end = n; end > 1; --end) {
        bubblePass(A, end, stats);
    }
    return stats;
}

BubbleStats bubbleSortOptimized(int A[], int n) {
    BubbleStats stats;
    for (int end = n; end > 1;) {
        BubbleStats passStats;
        const bool changed = bubblePass(A, end, passStats);
        stats.comparisons += passStats.comparisons;
        stats.swaps += passStats.swaps;
        stats.lastSwapIndex = passStats.lastSwapIndex;
        if (!changed) break;
        end = passStats.lastSwapIndex;
    }
    return stats;
}

bool isSortedNonDecreasing(const int A[], int n) {
    for (int i = 1; i < n; ++i) {
        if (A[i - 1] > A[i]) return false;
    }
    return true;
}

std::vector<int> inversionWitnesses(const int A[], int n) {
    std::vector<int> witnesses;
    for (int i = 1; i < n; ++i) {
        if (A[i - 1] > A[i]) witnesses.push_back(i - 1);
    }
    return witnesses;
}
