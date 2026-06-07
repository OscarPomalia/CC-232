#pragma once

#include <algorithm>
#include <functional>
#include <vector>

#include "PQ_ComplHeap_heapifyFloyd.h"
#include "PQ_ComplHeap_percolateDown.h"

namespace ods {

template <class T, class Compare = std::less<T>>
void heapSort(std::vector<T>& a, Compare comp = Compare{}) {
    if (a.size() < 2) {
        return;
    }
    complHeapHeapifyFloyd(a, comp);
    for (std::size_t n = a.size(); n > 1; --n) {
        std::swap(a[0], a[n - 1]);
        complHeapPercolateDown(a, n - 1, 0, comp);
    }
}

// MOD-A6-B7: heapSort direccional in situ (nueva sobrecarga)
template <class T, class Compare>
void heapSort(std::vector<T>& a, Compare comp, bool ascending) {
    if (a.size() < 2) {
        return;
    }
    complHeapHeapifyFloyd(a, comp);
    for (std::size_t n = a.size(); n > 1; --n) {
        std::swap(a[0], a[n - 1]);
        complHeapPercolateDown(a, n - 1, 0, comp);
    }
    
    // Si piden descendente, invertimos el arreglo resultante in situ
    if (!ascending) {
        std::reverse(a.begin(), a.end());
    }
}

template <class T, class Compare = std::less<T>>
std::vector<T> heapSorted(std::vector<T> a, Compare comp = Compare{}) {
    heapSort(a, comp);
    return a;
}

} // namespace ods