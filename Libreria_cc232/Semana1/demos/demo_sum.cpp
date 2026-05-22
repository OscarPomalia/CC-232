#include <iostream>
#include "sum.h"

// Ejemplo simple
int main() {
    int a[] = {1, 2, 3, 4, 5};
    const int n = static_cast<int>(sizeof(a) / sizeof(a[0]));

    std::cout << "sumI(a, n)   = " << sumI(a, n) << "\n";
    std::cout << "sum(a, n)    = " << sum(a, n) << "\n";
    std::cout << "sum(a,0,n)   = " << sum(a, 0, n) << "\n";
    return 0;
}
