#pragma once

#include <utility>
#include <vector>

using HanoiMove = std::pair<char, char>;

void solveHanoi(int n, char from, char aux, char to, std::vector<HanoiMove>& moves);
long long hanoiMoveCount(int n);
