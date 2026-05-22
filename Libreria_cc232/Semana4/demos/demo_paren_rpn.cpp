#include <iostream>

#include "ExpressionEvaluator.h"
#include "Parentheses.h"

int main() {
    const std::string expr = "(0!+1)*2^(3!+4)-(5!-67-(8+9))";
    const auto evaluated = ods::evaluateExpression(expr);

    std::cout << "Parentesis balanceados (iterativo) = "
              << std::boolalpha << ods::parenIterative(expr) << "\n";
    std::cout << "Expresion en RPN = " << evaluated.rpn << "\n";
    std::cout << "Valor de la expresion = " << evaluated.value << "\n";
    return 0;
}