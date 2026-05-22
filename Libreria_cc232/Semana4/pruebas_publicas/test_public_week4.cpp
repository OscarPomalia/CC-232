#include <cassert>
#include <cmath>
#include <vector>

#include "Capitulo4.h"

int main() {
    {
        // AAA: Arrange
        ods::Stack<int> st;

        // AAA: Act
        const bool initiallyEmpty = st.empty();
        st.push(5);
        st.push(9);
        const int topValue = st.top();
        const int firstPop = st.pop();
        const int secondPop = st.pop();
        const bool finallyEmpty = st.empty();

        // AAA: Assert
        assert(initiallyEmpty);
        assert(topValue == 9);
        assert(firstPop == 9);
        assert(secondPop == 5);
        assert(finallyEmpty);
    }

    {
        // AAA: Arrange
        ods::Queue<int> q;

        // AAA: Act
        const bool initiallyEmpty = q.empty();
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        const int frontValue = q.front();
        const int firstDequeue = q.dequeue();
        const int secondDequeue = q.dequeue();
        const int thirdDequeue = q.dequeue();
        const bool finallyEmpty = q.empty();

        // AAA: Assert
        assert(initiallyEmpty);
        assert(frontValue == 1);
        assert(firstDequeue == 1);
        assert(secondDequeue == 2);
        assert(thirdDequeue == 3);
        assert(finallyEmpty);
    }

    {
        // AAA: Arrange
        const int number = 12345;
        const int base = 8;

        // AAA: Act
        const auto recursiveBase = ods::toBaseRecursive(number, base);
        const auto iterativeBase = ods::toBaseIterative(number, base);

        // AAA: Assert
        assert(recursiveBase == "30071");
        assert(iterativeBase == "30071");
    }

    {
        // AAA: Arrange
        const std::string expr1 = "a+(b*(c+d))";
        const std::string expr2 = "a+(b*[c-{d/e}])";
        const std::string expr3 = "([)]";

        // AAA: Act
        const bool result1 = ods::parenRecursive(expr1);
        const bool result2 = ods::parenIterative(expr2);
        const bool result3 = ods::parenIterative(expr3);

        // AAA: Assert
        assert(result1);
        assert(result2);
        assert(!result3);
    }

    {
        // AAA: Arrange
        const std::string expr = "(0!+1)*2^(3!+4)-(5!-67-(8+9))";

        // AAA: Act
        const auto eval = ods::evaluateExpression(expr);

        // AAA: Assert
        assert(eval.rpn == "0 ! 1 + 2 3 ! 4 + ^ * 5 ! 67 - 8 9 + - -");
        assert(std::fabs(eval.value - 2012.0) < 1e-9);
    }

    {
        // AAA: Arrange
        const int n = 4;

        // AAA: Act
        const auto queens = ods::placeQueens(n);

        // AAA: Assert
        assert(queens.solutions == 2);
        assert(queens.placements.size() == 2u);
    }

    {
        // AAA: Arrange
        ods::Maze maze({
            "#####",
            "#...#",
            "#.#.#",
            "#...#",
            "#####"
        });

        // AAA: Act
        const auto path = ods::findPath(maze, 1, 1, 3, 3);

        // AAA: Assert
        assert(!path.empty());
        assert(path.front() == std::make_pair(1, 1));
        assert(path.back() == std::make_pair(3, 3));
    }

    {
        // AAA: Arrange
        std::vector<ods::Queue<ods::Customer>> windows(3);
        windows[0].enqueue({0, 10});
        windows[0].enqueue({0, 20});
        windows[1].enqueue({1, 7});

        // AAA: Act
        const int selectedWindow = ods::bestWindow(windows);

        // AAA: Assert
        assert(selectedWindow == 2);
    }

    return 0;
}