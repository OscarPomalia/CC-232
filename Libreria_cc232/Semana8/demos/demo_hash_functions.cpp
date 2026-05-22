#include <iostream>
#include "HashCode.h"
#include "UniversalHash.h"

int main() {
    constexpr std::size_t m = 17;
    ods::UniversalHash h1(12345);
    ods::UniversalHash h2(98765);

    for (int x : {10, 20, 30, 40, 50}) {
        std::cout << "x=" << x
                  << " hashCode%m=" << ods::hashCode(x) % m
                  << " universal1=" << h1(x, m)
                  << " universal2=" << h2(x, m) << "\n";
    }
}
