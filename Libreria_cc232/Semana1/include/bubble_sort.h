#pragma once

#include <vector>

struct BubbleStats {
    int comparisons = 0;
    int swaps = 0;
    int lastSwapIndex = 0;
};

bool bubblePass(int A[], int n, BubbleStats& stats);
BubbleStats bubbleSortBasic(int A[], int n);
BubbleStats bubbleSortOptimized(int A[], int n);
bool isSortedNonDecreasing(const int A[], int n);
std::vector<int> inversionWitnesses(const int A[], int n);
