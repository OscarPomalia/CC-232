#pragma once

namespace ods {

struct Queen {
    int x;
    int y;

    // Construye una reina en la posición (x, y)
    Queen(int xx = 0, int yy = 0) : x(xx), y(yy) {}

    // Dos reinas entran en conflicto si comparten fila, columna o diagonal
    bool operator==(const Queen& other) const {
        return x == other.x || y == other.y || x + y == other.x + other.y || x - y == other.x - other.y;
    }

    // Retorna true si no hay conflicto
    bool operator!=(const Queen& other) const {
        return !(*this == other);
    }
};

} // namespace ods