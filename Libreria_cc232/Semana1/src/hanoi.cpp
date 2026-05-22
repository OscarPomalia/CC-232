#include "hanoi.h"

void solveHanoi(int n, char from, char aux, char to, std::vector<HanoiMove>& moves) {
    if (n <= 0) return;
    solveHanoi(n - 1, from, to, aux, moves);
    moves.push_back({from, to});
    solveHanoi(n - 1, aux, from, to, moves);
}

long long hanoiMoveCount(int n) {
    if (n <= 0) return 0;
    return 2LL * hanoiMoveCount(n - 1) + 1LL;
}
