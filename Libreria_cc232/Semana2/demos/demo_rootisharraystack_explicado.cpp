#include <iostream>
#include "RootishArrayStackExplicado.h"

void print_location(const cc232::pedagogico::RootishArrayStackExplicado<int>& s, int i) {
    auto [b, j] = s.locate(i);
    std::cout << "  indice logico " << i << " -> bloque " << b << ", offset " << j
              << ", valor=" << s.get(i) << "\n";
}

int main() {
    cc232::pedagogico::RootishArrayStackExplicado<int> s;

    std::cout << "RootishArrayStack explicado (Morin, capitulo 2)\n";
    for (int x : {10, 20, 30, 40, 50, 60}) {
        s.push_back(x);
    }
    s.debug_print(std::cout);

    std::cout << "\nComo se ubican algunos indices:\n";
    print_location(s, 0);
    print_location(s, 2);
    print_location(s, 5);

    std::cout << "\nOperacion: add(2, 99)\n";
    s.add(2, 99);
    s.debug_print(std::cout);

    std::cout << "\nOperacion: remove(4)\n";
    std::cout << "Valor removido = " << s.remove(4) << "\n";
    s.debug_print(std::cout);

    std::cout << "\nIdea central: se usan bloques de tamano 1, 2, 3, ...\n";
    std::cout << "Esto reduce espacio desperdiciado frente a duplicar un arreglo grande.\n";
    return 0;
}
