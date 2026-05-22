#include "gcd.h"

#include <cstdlib>

long long gcdCN(long long a, long long b) {
    a = std::llabs(a);
    b = std::llabs(b);
    if (a == 0) return b;
    if (b == 0) return a;

    int r = 0;
    while (((a & 1LL) == 0) && ((b & 1LL) == 0)) {
        a >>= 1;
        b >>= 1;
        ++r;
    }
    while (true) {
        while ((a & 1LL) == 0) a >>= 1;
        while ((b & 1LL) == 0) b >>= 1;
        if (a > b) {
            a -= b;
            if (a == 0) return b << r;
        } else {
            b -= a;
            if (b == 0) return a << r;
        }
    }
}
