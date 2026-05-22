#include <iostream>
#include <string>
#include <vector>

#include "Maze.h"

int main() {
    ods::Maze maze({
        "#####",
        "#...#",
        "#.#.#",
        "#...#",
        "#####"
    });

    const auto path = ods::findPath(maze, 1, 1, 3, 3);
    std::cout << "Medida del camino = " << path.size() << "\n";
    for (const auto& [x, y] : path) {
        std::cout << '(' << x << ',' << y << ") ";
    }
    std::cout << '\n';
    return 0;
}