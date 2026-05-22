#include <iostream>
#include <vector>

#include "hanoi.h"

int main() {
    std::vector<HanoiMove> moves;
    solveHanoi(3, 'A', 'B', 'C', moves);

    std::cout << "Movimientos para Hanoi con 3 discos (ejemplo):\n";
    for (const auto& [from, to] : moves) {
        std::cout << from << " -> " << to << "\n";
    }
    std::cout << "Total esperado = " << hanoiMoveCount(3) << "\n";
    return 0;
}
