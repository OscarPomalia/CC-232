#pragma once

#include <string>

#include "Stack.h"

namespace ods {

// Recorta extremos sin paréntesis
inline void trimParentheses(const std::string& expr, int& lo, int& hi) {
    while (lo <= hi && expr[lo] != '(' && expr[lo] != ')') {
        ++lo;
    }
    while (lo <= hi && expr[hi] != '(' && expr[hi] != ')') {
        --hi;
    }
}

// Busca el punto de división del bloque
inline int divideParentheses(const std::string& expr, int lo, int hi) {
    int mi = lo;
    int crc = 1;

    while (crc > 0 && ++mi < hi) {
        if (expr[mi] == '(') {
            ++crc;
        } else if (expr[mi] == ')') {
            --crc;
        }
    }
    return mi;
}

// Verifica paréntesis de forma recursiva
inline bool parenRecursive(const std::string& expr, int lo, int hi) {
    trimParentheses(expr, lo, hi);

    if (lo > hi) {
        return true;
    }
    if (expr[lo] != '(' || expr[hi] != ')') {
        return false;
    }

    const int mi = divideParentheses(expr, lo, hi);
    if (mi > hi) {
        return false;
    }

    return parenRecursive(expr, lo + 1, mi - 1) && parenRecursive(expr, mi + 1, hi);
}

// Versión recursiva para toda la cadena
inline bool parenRecursive(const std::string& expr) {
    if (expr.empty()) {
        return true;
    }
    return parenRecursive(expr, 0, static_cast<int>(expr.size()) - 1);
}

// Verifica paréntesis con pila
inline bool parenIterative(const std::string& expr) {
    Stack<char> stack;

    for (char ch : expr) {
        switch (ch) {
            case '(':
            case '[':
            case '{':
                stack.push(ch);
                break;

            case ')':
                if (stack.empty() || stack.pop() != '(') {
                    return false;
                }
                break;

            case ']':
                if (stack.empty() || stack.pop() != '[') {
                    return false;
                }
                break;

            case '}':
                if (stack.empty() || stack.pop() != '{') {
                    return false;
                }
                break;

            default:
                break;
        }
    }

    return stack.empty();
}

} // namespace ods