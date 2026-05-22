#include <cassert>
#include "sum.h"
#include "power.h"
#include "Fib.h"

int main() {
    int vacio[] = {0};
    assert(sumI(vacio, 0) == 0);
    assert(sum(vacio, 0) == 0);
    assert(sum(vacio, 0, 0) == 0);

    int a[] = {1, 2, 3, 4};
    assert(sumI(a, 4) == 10);
    assert(sum(a, 4) == 10);
    assert(sum(a, 0, 4) == 10);

    assert(powerBF(2, 10) == 1024);
    assert(power(2, 10) == 1024);
    assert(power2BF_I(10) == 1024);
    assert(power2_I(10) == 1024);
    assert(power2BF(10) == 1024);
    assert(power2(10) == 1024);

    long long prev = -1;
    assert(fibI(10) == 55);
    assert(fib(10) == 55);
    assert(fib(10, prev) == 55);
    assert(prev == 34);

    Fib seq(5);
    assert(seq.get() >= 5u);
    return 0;
}
