#include "count_ones.h"

namespace {
constexpr unsigned int POW(unsigned int c) { return 1u << c; }
constexpr unsigned int MASK(unsigned int c) {
    return static_cast<unsigned int>(~0u) / (POW(POW(c)) + 1u);
}
constexpr unsigned int ROUND(unsigned int n, unsigned int c) {
    return (n & MASK(c)) + ((n >> POW(c)) & MASK(c));
}
}

int countOnes1(unsigned int n) {
    int ones = 0;
    while (n > 0) {
        ++ones;
        n &= (n - 1);
    }
    return ones;
}

int countOnes2(unsigned int n) {
    n = ROUND(n, 0);
    n = ROUND(n, 1);
    n = ROUND(n, 2);
    n = ROUND(n, 3);
    n = ROUND(n, 4);
    return static_cast<int>(n);
}
