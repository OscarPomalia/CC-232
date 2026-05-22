#include <cassert>
#include "sum.h"
#include "power.h"
#include "Fib.h"


int main() {
    int a[] = {-2, 5, -3, 8, 1};
    assert(sumI(a, 5) == 9);
    assert(sum(a, 5) == 9);
    assert(sum(a, 0, 5) == 9);

    assert(power(3, 0) == 1);
    assert(power(3, 4) == 81);
    assert(fibI(0) == 0);
    assert(fibI(1) == 1);
    assert(fibI(7) == 13);
    return 0;
}
