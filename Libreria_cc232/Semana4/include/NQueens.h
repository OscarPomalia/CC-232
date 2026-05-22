#pragma once

#include <vector>

#include "Queen.h"
#include "Stack.h"

namespace ods {

struct NQueensResult {
    int n = 0;
    int solutions = 0;
    long long checks = 0;
    std::vector<std::vector<int>> placements;
};

// Verifica si una reina entra en conflicto con alguna ya colocada
inline bool conflictsWithAny(const Stack<Queen>& placed, const Queen& candidate, long long& checks) {
    const auto& data = placed.data();
    for (const Queen& q : data) {
        ++checks;
        if (candidate == q) {
            return true;
        }
    }
    return false;
}

// Resuelve el problema de las N reinas
inline NQueensResult placeQueens(int n, bool collectPlacements = true) {
    NQueensResult result;
    result.n = n;

    if (n <= 0) {
        return result;
    }

    Stack<Queen> solution;
    Queen q(0, 0);

    do {
        // Si ya no se puede avanzar, retroceder
        if (solution.size() >= n || q.y >= n) {
            if (solution.empty()) {
                break;
            }
            q = solution.pop();
            ++q.y;
        } else {
            // Busca una columna válida en la fila actual
            while (q.y < n && conflictsWithAny(solution, q, result.checks)) {
                ++q.y;
            }

            if (q.y < n) {
                solution.push(q);

                // Si se completó una solución, guardarla
                if (solution.size() >= n) {
                    ++result.solutions;

                    if (collectPlacements) {
                        std::vector<int> placement;
                        placement.reserve(n);

                        for (const Queen& queen : solution.data()) {
                            placement.push_back(queen.y);
                        }
                        result.placements.push_back(std::move(placement));
                    }
                }

                // Pasa a la siguiente fila
                ++q.x;
                q.y = 0;
            }
        }
    } while (q.x > 0 || q.y < n);

    return result;
}

} // namespace ods
