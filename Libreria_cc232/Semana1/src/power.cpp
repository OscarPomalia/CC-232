#include "power.h"

namespace {
inline long long sqr(long long a) { return a * a; }
}

long long powerBF(long long a, int n) {
    long long pow = 1;
    while (n > 0) {
        pow *= a;
        --n;
    }
    return pow;
}

long long power(long long a, int n) {
    long long pow = 1;
    long long p = a;
    while (n > 0) {
        if (n & 1) pow *= p;
        n >>= 1;
        p *= p;
    }
    return pow;
}

long long power2BF_I(int n) {
    long long pow = 1;
    while (n-- > 0) pow <<= 1;
    return pow;
}

long long power2_I(int n) {
    long long pow = 1;
    long long p = 2;
    while (n > 0) {
        if (n & 1) pow *= p;
        n >>= 1;
        p *= p;
    }
    return pow;
}

long long power2BF(int n) {
    return (n <= 0) ? 1LL : (power2BF(n - 1) << 1);
}

long long power2(int n) {
    if (n == 0) return 1;
    const long long half = power2(n >> 1);
    return (n & 1) ? (sqr(half) << 1) : sqr(half);
}
