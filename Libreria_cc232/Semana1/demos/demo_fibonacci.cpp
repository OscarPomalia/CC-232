#include <iostream>
#include "Fib.h"

int main() {
    const int n = 10;
    long long prev = 0;

    std::cout << "fibI(" << n << ")      = " << fibI(n) << "\n";
    std::cout << "fib(" << n << ")       = " << fib(n) << "\n";
    std::cout << "fib(" << n << ", prev) = " << fib(n, prev) << ", prev = " << prev << "\n";

    Fib seq(0);
    std::cout << "Primeros 8 Fibonacci desde la clase Fib: ";
    for (int i = 0; i < 8; ++i) {
        std::cout << seq.get() << (i + 1 < 8 ? ' ' : '\n');
        seq.next();
    }
    return 0;
}
