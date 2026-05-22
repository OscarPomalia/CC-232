#include <iostream>

#include "max_algorithms.h"

//Ejemplo simple
int main() {
    int a[] = {-7, 3, 11, 2, 11, -4};
    const int n = static_cast<int>(sizeof(a) / sizeof(a[0]));

    std::cout << "maxI(a,n) = " << maxI(a, n) << "\n";
    std::cout << "maxRLinear(a,n) = " << maxRLinear(a, n) << "\n";
    std::cout << "maxRDivide(a,0,n) = " << maxRDivide(a, 0, n) << "\n";
    return 0;
}
