#pragma once

#include <algorithm>
#include <cstddef>
#include <vector>

#include "PQ_ComplHeap_macro.h"

namespace ods {

template <class T, class Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
    while (pqHasLeftChild(i, n)) {
        std::size_t c = pqLeftChild(i);
        const std::size_t r = pqRightChild(i);
        if (pqHasRightChild(i, n) && comp(a[c], a[r])) {
            c = r;
        }
        if (!comp(a[i], a[c])) {
            break;
        }
        std::swap(a[i], a[c]);
        i = c;
    }
    return i;
}

// MOD-A6-B4: Conteo en percolateDown
template <class T, class Compare>
std::size_t complHeapPercolateDownCount(std::vector<T>& a, std::size_t n, std::size_t i, Compare comp) {
    std::size_t swaps = 0;
    while (pqHasLeftChild(i, n)) {
        std::size_t c = pqLeftChild(i);
        const std::size_t r = pqRightChild(i);
        if (pqHasRightChild(i, n) && comp(a[c], a[r])) {
            c = r;
        }
        if (!comp(a[i], a[c])) {
            break;
        }
        std::swap(a[i], a[c]);
        swaps++;
        i = c;
    }
    return swaps;
}

} // namespace ods