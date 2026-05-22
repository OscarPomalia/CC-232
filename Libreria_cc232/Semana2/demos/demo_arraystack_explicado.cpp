#include <iostream>
#include "ArrayStackExplicado.h"

int main() {
    cc232::pedagogico::ArrayStackExplicado<int> s;

    std::cout << "ArrayStack explicado (Morin, capitulo 2)\n";
    std::cout << "Operacion 1: push_back(10)\n";
    s.push_back(10);
    s.debug_print(std::cout);

    std::cout << "\nOperacion 2: push_back(20)\n";
    s.push_back(20);
    s.debug_print(std::cout);

    std::cout << "\nOperacion 3: add(1, 15)\n";
    std::cout << "Se desplazan a la derecha los elementos desde i hasta n-1.\n";
    s.add(1, 15);
    s.debug_print(std::cout);

    std::cout << "\nOperacion 4: remove(0)\n";
    std::cout << "Se desplazan a la izquierda los elementos desde i+1 hasta n-1.\n";
    std::cout << "Valor removido = " << s.remove(0) << "\n";
    s.debug_print(std::cout);

    std::cout << "\nIdea central: add(i,x) y remove(i) cuestan O(n-i) por los desplazamientos.\n";
    return 0;
}
