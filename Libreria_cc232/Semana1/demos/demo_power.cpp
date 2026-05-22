#include <iostream>
#include "power.h"

// Ejemplo simple
int main() {
    const long long base = 3;
    const int exp = 5;

    std::cout << "powerBF(" << base << ", " << exp << ") = " << powerBF(base, exp) << "\n";
    std::cout << "power(" << base << ", " << exp << ")   = " << power(base, exp) << "\n";
    std::cout << "power2BF_I(" << exp << ") = " << power2BF_I(exp) << "\n";
    std::cout << "power2_I(" << exp << ")   = " << power2_I(exp) << "\n";
    std::cout << "power2BF(" << exp << ")   = " << power2BF(exp) << "\n";
    std::cout << "power2(" << exp << ")     = " << power2(exp) << "\n";
    return 0;
}
