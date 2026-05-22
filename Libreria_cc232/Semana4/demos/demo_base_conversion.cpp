#include <iostream>

#include "BaseConversion.h"

int main() {
    const unsigned long long n = 12345;
    std::cout << "12345 en base 8 (recursivo) = " << ods::toBaseRecursive(n, 8) << "\n";
    std::cout << "12345 en base 8 (iterativo) = " << ods::toBaseIterative(n, 8) << "\n";
    return 0;
}
