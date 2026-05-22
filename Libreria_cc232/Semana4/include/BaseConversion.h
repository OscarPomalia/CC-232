#pragma once

#include <stdexcept>
#include <string>

#include "Stack.h"

namespace ods {

// Verifica que la base esté en el rango permitido
inline void validateBase(int base) {
    if (base < 2 || base > 16) {
        throw std::invalid_argument("la base debe estar entre 2 y 16");
    }
}

// Convierte usando la versión recursiva
inline void convertRecursive(Stack<char>& stack, unsigned long long n, int base) {
    validateBase(base);
    static const char digit[] = "0123456789ABCDEF";

    if (n > 0) {
        stack.push(digit[n % static_cast<unsigned long long>(base)]); // Apila el dígito actual
        convertRecursive(stack, n / static_cast<unsigned long long>(base), base); // Continúa con el cociente
    }
}

// Convierte usando la versión iterativa
inline void convertIterative(Stack<char>& stack, unsigned long long n, int base) {
    validateBase(base);
    static const char digit[] = "0123456789ABCDEF";

    while (n > 0) {
        stack.push(digit[n % static_cast<unsigned long long>(base)]); // Apila el residuo
        n /= static_cast<unsigned long long>(base); // Avanza al siguiente dígito
    }
}

// Extrae todos los elementos de la pila y forma la cadena final
inline std::string popAll(Stack<char>& stack) {
    std::string out;
    while (!stack.empty()) {
        out.push_back(stack.pop());
    }
    return out;
}

// Convierte un número a una base dada usando recursión
inline std::string toBaseRecursive(unsigned long long n, int base) {
    validateBase(base);

    if (n == 0) {
        return "0";
    }

    Stack<char> stack;
    convertRecursive(stack, n, base);
    return popAll(stack);
}

// Convierte un número a una base dada usando iteración
inline std::string toBaseIterative(unsigned long long n, int base) {
    validateBase(base);

    if (n == 0) {
        return "0";
    }

    Stack<char> stack;
    convertIterative(stack, n, base);
    return popAll(stack);
}

} // namespace ods