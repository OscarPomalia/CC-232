#include <cassert>
#include "sum.h"
#include "power.h"
#include "Fib.h"


int main() {
    int vacio[] = {0};
    assert(sumI(vacio, 0) == 0);
    assert(sum(vacio, 0) == 0);
    assert(sum(vacio, 0, 0) == 0);

    int solo[] = {42};
    assert(sumI(solo, 1) == 42);
    assert(sum(solo, 1) == 42);
    assert(sum(solo, 0, 1) == 42);

    assert(powerBF(-2, 3) == -8);
    assert(power2(0) == 1);
    assert(fib(0) == 0);
    assert(fib(1) == 1);
    return 0;
}
