#pragma once

#include <cstddef>

namespace ods {

inline bool isPrime(std::size_t n) {
    if (n < 2) {
        return false;
    }

    if (n % 2 == 0) {
        return n == 2;
    }

    for (std::size_t d = 3; d * d <= n; d += 2) {
        if (n % d == 0) {
            return false;
        }
    }

    return true;
}

inline std::size_t nextPrime(std::size_t n) {
    if (n <= 2) {
        return 2;
    }

    if (n % 2 == 0) {
        ++n;
    }

    while (!isPrime(n)) {
        n += 2;
    }

    return n;
}

}  // namespace ods
