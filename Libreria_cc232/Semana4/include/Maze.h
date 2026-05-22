#pragma once

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Stack.h"

namespace ods {

enum Status {
    AVAILABLE,
    ROUTE,
    BACKTRACKED,
    WALL
};

enum ESWN {
    UNKNOWN,
    EAST,
    SOUTH,
    WEST,
    NORTH,
    NO_WAY
};

// Avanza a la siguiente dirección
inline ESWN nextESWN(ESWN eswn) {
    return static_cast<ESWN>(static_cast<int>(eswn) + 1);
}

struct Cell {
    int x = 0;
    int y = 0;
    Status status = AVAILABLE;
    ESWN incoming = UNKNOWN;
    ESWN outgoing = UNKNOWN;
};

class Maze {
private:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<std::vector<Cell>> cells_;

public:
    Maze() = default;

    // Construye el laberinto desde una grilla de texto
    explicit Maze(const std::vector<std::string>& layout) {
        if (layout.empty()) {
            return;
        }
        rows_ = static_cast<int>(layout.size());
        cols_ = static_cast<int>(layout.front().size());
        cells_.assign(rows_, std::vector<Cell>(cols_));

        for (int i = 0; i < rows_; ++i) {
            if (static_cast<int>(layout[i].size()) != cols_) {
                throw std::invalid_argument("todas las filas del laberinto deben tener el mismo ancho");
            }
            for (int j = 0; j < cols_; ++j) {
                cells_[i][j].x = i;
                cells_[i][j].y = j;
                cells_[i][j].status = (layout[i][j] == '#') ? WALL : AVAILABLE;
                cells_[i][j].incoming = UNKNOWN;
                cells_[i][j].outgoing = UNKNOWN;
            }
        }
    }

    int rows() const { return rows_; }
    int cols() const { return cols_; }

    // Retorna la celda si está dentro del rango
    Cell* at(int x, int y) {
        if (x < 0 || x >= rows_ || y < 0 || y >= cols_) {
            return nullptr;
        }
        return &cells_[x][y];
    }

    // Versión constante de acceso
    const Cell* at(int x, int y) const {
        if (x < 0 || x >= rows_ || y < 0 || y >= cols_) {
            return nullptr;
        }
        return &cells_[x][y];
    }

    // Reinicia el estado de búsqueda
    void resetSearchState() {
        for (auto& row : cells_) {
            for (auto& cell : row) {
                if (cell.status != WALL) {
                    cell.status = AVAILABLE;
                }
                cell.incoming = UNKNOWN;
                cell.outgoing = UNKNOWN;
            }
        }
    }
};

// Retorna la celda vecina según la dirección de salida
inline Cell* neighbor(Maze& maze, Cell* cell) {
    switch (cell->outgoing) {
        case EAST:  return maze.at(cell->x, cell->y + 1);
        case SOUTH: return maze.at(cell->x + 1, cell->y);
        case WEST:  return maze.at(cell->x, cell->y - 1);
        case NORTH: return maze.at(cell->x - 1, cell->y);
        default:    return nullptr;
    }
}

// Avanza a la celda vecina y marca la dirección de entrada
inline Cell* advance(Maze& maze, Cell* cell) {
    Cell* next = neighbor(maze, cell);
    if (next == nullptr) {
        return nullptr;
    }

    switch (cell->outgoing) {
        case EAST:  next->incoming = WEST;  break;
        case SOUTH: next->incoming = NORTH; break;
        case WEST:  next->incoming = EAST;  break;
        case NORTH: next->incoming = SOUTH; break;
        default:    return nullptr;
    }
    return next;
}

// Busca si existe camino entre inicio y destino
inline bool labyrinth(Maze& maze, Cell* start, Cell* target) {
    if (start == nullptr || target == nullptr) {
        return false;
    }
    if (start->status != AVAILABLE || target->status != AVAILABLE) {
        return false;
    }

    Stack<Cell*> path;
    start->incoming = UNKNOWN;
    start->outgoing = UNKNOWN;
    start->status = ROUTE;
    path.push(start);

    do {
        Cell* current = path.top();

        if (current == target) {
            return true;
        }

        // Prueba direcciones hasta hallar una celda libre
        while ((current->outgoing = nextESWN(current->outgoing)) < NO_WAY) {
            Cell* next = neighbor(maze, current);
            if (next != nullptr && next->status == AVAILABLE) {
                break;
            }
        }

        // Si no hay salida, retrocede
        if (current->outgoing >= NO_WAY) {
            current->status = BACKTRACKED;
            path.pop();
        } else {
            Cell* next = advance(maze, current);
            if (next == nullptr) {
                current->status = BACKTRACKED;
                path.pop();
            } else {
                next->outgoing = UNKNOWN;
                next->status = ROUTE;
                path.push(next);
            }
        }
    } while (!path.empty());

    return false;
}

// Retorna el camino encontrado como coordenadas
inline std::vector<std::pair<int, int>> findPath(Maze& maze, int sx, int sy, int tx, int ty) {
    maze.resetSearchState();

    Cell* start = maze.at(sx, sy);
    Cell* target = maze.at(tx, ty);

    if (start == nullptr || target == nullptr) {
        return {};
    }
    if (start->status != AVAILABLE || target->status != AVAILABLE) {
        return {};
    }

    Stack<Cell*> path;
    start->incoming = UNKNOWN;
    start->outgoing = UNKNOWN;
    start->status = ROUTE;
    path.push(start);

    do {
        Cell* current = path.top();

        if (current == target) {
            std::vector<std::pair<int, int>> coords;
            coords.reserve(path.size());

            for (Cell* cell : path.data()) {
                coords.emplace_back(cell->x, cell->y);
            }
            return coords;
        }

        // Prueba direcciones hasta hallar una celda libre
        while ((current->outgoing = nextESWN(current->outgoing)) < NO_WAY) {
            Cell* next = neighbor(maze, current);
            if (next != nullptr && next->status == AVAILABLE) {
                break;
            }
        }

        // Si no hay salida, retrocede
        if (current->outgoing >= NO_WAY) {
            current->status = BACKTRACKED;
            path.pop();
        } else {
            Cell* next = advance(maze, current);
            if (next == nullptr) {
                current->status = BACKTRACKED;
                path.pop();
            } else {
                next->outgoing = UNKNOWN;
                next->status = ROUTE;
                path.push(next);
            }
        }
    } while (!path.empty());

    return {};
}

} // namespace ods
