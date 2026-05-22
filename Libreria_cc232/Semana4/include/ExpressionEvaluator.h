#pragma once

#include <cctype>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

#include "OperatorPriority.h"
#include "Stack.h"

namespace ods {

struct EvaluationResult {
    double value{};
    std::string rpn;
};

// Elimina espacios de la expresión
inline std::string removeSpaces(std::string expr) {
    std::string out;
    out.reserve(expr.size());
    for (char ch : expr) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            out.push_back(ch);
        }
    }
    return out;
}

// Verifica si un carácter es operador
inline bool isOperatorChar(char ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '!':
        case '(':
        case ')':
        case '\0':
            return true;
        default:
            return false;
    }
}

// Detecta si '-' es signo unario
inline bool isUnaryMinus(const std::string& expr, std::size_t i) {
    if (expr[i] != '-') {
        return false;
    }
    if (i + 1 >= expr.size()) {
        return false;
    }
    if (!(std::isdigit(static_cast<unsigned char>(expr[i + 1])) || expr[i + 1] == '.')) {
        return false;
    }
    if (i == 0) {
        return true;
    }
    const char prev = expr[i - 1];
    return prev == '(' || prev == '+' || prev == '-' || prev == '*' || prev == '/' || prev == '^';
}

// Calcula factorial entero
inline long long factorialInt(int n) {
    if (n < 0) {
        throw std::runtime_error("el factorial no se define para enteros negativos");
    }
    long long ans = 1;
    for (int i = 2; i <= n; ++i) {
        ans *= i;
    }
    return ans;
}

// Aplica operador binario
inline double calcu(double a, char op, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0.0) {
                throw std::runtime_error("division entre cero");
            }
            return a / b;
        case '^': return std::pow(a, b);
        default: throw std::runtime_error("operador binario no soportado");
    }
}

// Aplica operador unario
inline double calcu(char op, double b) {
    switch (op) {
        case '!': {
            const double rounded = std::round(b);
            if (std::fabs(b - rounded) > 1e-9) {
                throw std::runtime_error("el factorial requiere un operando entero");
            }
            return static_cast<double>(factorialInt(static_cast<int>(rounded)));
        }
        default:
            throw std::runtime_error("operador unario no soportado");
    }
}

// Convierte un número a texto
inline std::string formatNumber(double value) {
    const double rounded = std::round(value);
    if (std::fabs(value - rounded) < 1e-9) {
        return std::to_string(static_cast<long long>(rounded));
    }
    std::ostringstream out;
    out << std::setprecision(12) << value;
    return out.str();
}

// Agrega un operando a la RPN
inline void appendRpn(std::string& rpn, double operand) {
    if (!rpn.empty()) {
        rpn.push_back(' ');
    }
    rpn += formatNumber(operand);
}

// Agrega un operador a la RPN
inline void appendRpn(std::string& rpn, char op) {
    if (!rpn.empty()) {
        rpn.push_back(' ');
    }
    rpn.push_back(op);
}

// Lee un número y lo apila
inline void readNumber(const std::string& expr, std::size_t& i, Stack<double>& operands) {
    std::size_t start = i;
    if (expr[i] == '-') {
        ++i;
    }
    while (i < expr.size() && std::isdigit(static_cast<unsigned char>(expr[i]))) {
        ++i;
    }
    if (i < expr.size() && expr[i] == '.') {
        ++i;
        while (i < expr.size() && std::isdigit(static_cast<unsigned char>(expr[i]))) {
            ++i;
        }
    }
    operands.push(std::stod(expr.substr(start, i - start)));
}

// Evalúa la expresión y genera su RPN
inline EvaluationResult evaluateExpression(const std::string& rawExpr) {
    std::string expr = removeSpaces(rawExpr);
    expr.push_back('\0');

    Stack<double> operands;
    Stack<char> operators;
    operators.push('\0');

    std::size_t i = 0;
    std::string rpn;

    while (!operators.empty()) {
        if (i >= expr.size()) {
            throw std::runtime_error("fin inesperado de la expresion");
        }

        const char current = expr[i];
        if (std::isdigit(static_cast<unsigned char>(current)) || current == '.' || isUnaryMinus(expr, i)) {
            readNumber(expr, i, operands);
            appendRpn(rpn, operands.top());
            continue;
        }

        const char relation = orderBetween(operators.top(), current);
        switch (relation) {
            case '<':
                operators.push(current);
                ++i;
                break;
            case '=':
                operators.pop();
                ++i;
                break;
            case '>': {
                const char op = operators.pop();
                appendRpn(rpn, op);
                if (op == '!') {
                    if (operands.empty()) {
                        throw std::runtime_error("falta operando para factorial");
                    }
                    operands.push(calcu(op, operands.pop()));
                } else {
                    if (operands.size() < 2) {
                        throw std::runtime_error("faltan operandos para el operador binario");
                    }
                    const double right = operands.pop();
                    const double left = operands.pop();
                    operands.push(calcu(left, op, right));
                }
                break;
            }
            default:
                throw std::runtime_error("orden de operadores invalido");
        }
    }

    if (operands.size() != 1) {
        throw std::runtime_error("la expresion no se redujo a un unico valor");
    }

    return EvaluationResult{operands.pop(), rpn};
}

// Retorna solo la RPN
inline std::string toRPN(const std::string& expr) {
    return evaluateExpression(expr).rpn;
}

// Retorna solo el valor
inline double evaluateOnly(const std::string& expr) {
    return evaluateExpression(expr).value;
}

} // namespace ods