#include "Fib.h"

long long fibI(int n) {
    long long f = 1;
    long long g = 0;
    while (n-- > 0) {
        g += f;
        f = g - f;
    }
    return g;
}

long long fib(int n) {
    return (n < 2) ? static_cast<long long>(n) : fib(n - 1) + fib(n - 2);
}

long long fib(int n, long long& prev) {
    if (n == 0) {
        prev = 1;
        return 0;
    }
    long long prev_prev = 0;
    prev = fib(n - 1, prev_prev);
    return prev_prev + prev;
}
