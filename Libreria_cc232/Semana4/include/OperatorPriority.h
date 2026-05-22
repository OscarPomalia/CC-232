#pragma once

#include <array>
#include <stdexcept>

namespace ods {

constexpr int N_OPTR = 9;

enum Operator {
    ADD,
    SUB,
    MUL,
    DIV,
    POW,
    FAC,
    L_P,
    R_P,
    EOE
};

// Tabla de precedencias entre operadores
inline constexpr std::array<std::array<char, N_OPTR>, N_OPTR> pri{{
    std::array<char, N_OPTR>{'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    std::array<char, N_OPTR>{'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    std::array<char, N_OPTR>{'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    std::array<char, N_OPTR>{'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    std::array<char, N_OPTR>{'>', '>', '>', '>', '>', '<', '<', '>', '>'},
    std::array<char, N_OPTR>{'>', '>', '>', '>', '>', '>', ' ', '>', '>'},
    std::array<char, N_OPTR>{'<', '<', '<', '<', '<', '<', '<', '=', ' '},
    std::array<char, N_OPTR>{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    std::array<char, N_OPTR>{'<', '<', '<', '<', '<', '<', '<', ' ', '='}
}};

// Convierte un símbolo en su tipo de operador
inline Operator optr2rank(char op) {
    switch (op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '^': return POW;
        case '!': return FAC;
        case '(': return L_P;
        case ')': return R_P;
        case '\0': return EOE;
        default: throw std::runtime_error("operador desconocido");
    }
}

// Retorna la relación de precedencia entre dos operadores
inline char orderBetween(char op1, char op2) {
    return pri[static_cast<int>(optr2rank(op1))][static_cast<int>(optr2rank(op2))];
}

} // namespace ods