#include <iostream>

#include "reverse_utils.h"

namespace {
void printArray(const int A[], int n) {
    std::cout << "[";
    for (int i = 0; i < n; ++i) std::cout << A[i] << (i + 1 < n ? ", " : "");
    std::cout << "]";
  }
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6};
    int b[] = {1, 2, 3, 4, 5, 6};

    reverseRecursive(a, 6);
    std::cout << "reverseRecursive: ";
    printArray(a, 6);
    std::cout << "\n";

    shiftLeftByK(b, 6, 2);
    std::cout << "shiftLeftByK(...,2): ";
    printArray(b, 6);
    std::cout << "\n";
    return 0;
}
