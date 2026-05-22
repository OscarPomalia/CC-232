#include <iostream>

#include "Capitulo4.h"

int main() {
    ods::Stack<int> st;
    st.push(1);
    st.push(2);

    ods::Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);

    const auto eval = ods::evaluateExpression("(0!+1)*2^(3!+4)-(5!-67-(8+9))");
    const auto queens = ods::placeQueens(4);

    ods::Maze maze({
        "#####",
        "#...#",
        "#.#.#",
        "#...#",
        "#####"
    });
    const auto path = ods::findPath(maze, 1, 1, 3, 3);

    const auto bank = ods::simulate(2, 6, 2024U);

    std::cout << "Semana 4 cargada correctamente\n";
    std::cout << "Tope de la pila = " << st.top() << "\n";
    std::cout << "Frente de la cola = " << q.front() << "\n";
    std::cout << "12345 en base 8 = " << ods::toBaseIterative(12345, 8) << "\n";
    std::cout << "Parentesis balanceados = " << std::boolalpha << ods::parenIterative("a+(b*[c])") << "\n";
    std::cout << "Expresion en RPN = " << eval.rpn << "\n";
    std::cout << "Valor = " << eval.value << "\n";
    std::cout << "Soluciones de N-Reinas(4) = " << queens.solutions << "\n";
    std::cout << "Longitud del camino en el laberinto = " << path.size() << "\n";
    std::cout << "Llegadas al banco = " << bank.totalArrivals
              << ", atendidos = " << bank.totalServed << "\n";
    return 0;
}