#include <cmath>
#include <iostream>
#include "FastSqrt.h"

int main() {
    ods::FastSqrt::init();

    for (int x : {0, 1, 2, 3, 4, 8, 9, 15, 16, 17, 63, 64, 65, 999, 1024}) {
        const int fast = ods::FastSqrt::sqrt(x);
        const int exact = static_cast<int>(std::floor(std::sqrt(static_cast<double>(x))));
        std::cout << "x=" << x << " fast=" << fast << " exact=" << exact << "\n";
    }
    return 0;
}
