#include <iostream>

#include "NQueens.h"

int main() {
    const auto result = ods::placeQueens(4);
    std::cout << "N = " << result.n
              << ", soluciones = " << result.solutions
              << ", verificaciones = " << result.checks << "\n";

    for (const auto& placement : result.placements) {
        for (int col : placement) {
            std::cout << col << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}