#include <cassert>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "Capitulo4.h"

int main() {
    {
        // AAA: Arrange
        const int zero = 0;
        const int binaryBase = 2;
        const int number = 255;
        const int hexBase = 16;

        // AAA: Act
        const auto recursiveBase = ods::toBaseRecursive(zero, binaryBase);
        const auto iterativeBase = ods::toBaseIterative(number, hexBase);

        // AAA: Assert
        assert(recursiveBase == "0");
        assert(iterativeBase == "FF");
    }

    {
        // AAA: Arrange
        const std::string expr1 = "sin parentesis";
        const std::string expr2 = ")()(";
        const std::string expr3 = "{[(])}";

        // AAA: Act
        const bool result1 = ods::parenRecursive(expr1);
        const bool result2 = ods::parenRecursive(expr2);
        const bool result3 = ods::parenIterative(expr3);

        // AAA: Assert
        assert(result1);
        assert(!result2);
        assert(!result3);
    }

    {
        // AAA: Arrange
        const std::string expr1 = "3+4*2";
        const std::string expr2 = "5!+2^3";
        const std::string expr3 = "-3+5";

        // AAA: Act
        const auto eval1 = ods::evaluateExpression(expr1);
        const auto eval2 = ods::evaluateExpression(expr2);
        const auto eval3 = ods::evaluateExpression(expr3);

        // AAA: Assert
        assert(eval1.rpn == "3 4 2 * +");
        assert(std::fabs(eval1.value - 11.0) < 1e-9);

        assert(eval2.rpn == "5 ! 2 3 ^ +");
        assert(std::fabs(eval2.value - 128.0) < 1e-9);

        assert(std::fabs(eval3.value - 2.0) < 1e-9);
    }

    {
        // AAA: Arrange
        const int n = 1;

        // AAA: Act
        const auto queens = ods::placeQueens(n);

        // AAA: Assert
        assert(queens.solutions == 1);
        assert(queens.placements.size() == 1u);
        assert(queens.placements[0].size() == 1u);
        assert(queens.placements[0][0] == 0);
    }

    {
        // AAA: Arrange
        ods::Maze maze({
            "#####",
            "#.#.#",
            "###.#",
            "#...#",
            "#####"
        });

        // AAA: Act
        const auto path = ods::findPath(maze, 1, 1, 3, 3);

        // AAA: Assert
        assert(path.empty());
    }

    {
        // AAA: Arrange
        const int windows = 2;
        const int serviceTime = 8;
        const unsigned seed = 123U;

        // AAA: Act
        const auto sim = ods::simulate(windows, serviceTime, seed);

        // AAA: Assert
        assert(sim.windows == 2);
        assert(sim.serviceTime == 8);
        assert(sim.totalArrivals >= sim.totalServed);
        assert(sim.timeline.size() == 8u);
    }

    {
        // AAA: Arrange
        bool thrown = false;

        // AAA: Act
        try {
            (void)ods::toBaseIterative(10, 1);
        } catch (const std::invalid_argument&) {
            thrown = true;
        }

        // AAA: Assert
        assert(thrown);
    }

    return 0;
}