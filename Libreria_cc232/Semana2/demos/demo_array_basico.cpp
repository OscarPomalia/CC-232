#include <iostream>
#include "array.h"

int main() {
    ods::array<int> a(5);
    for (int i = 0; i < a.length; ++i) {
        a[i] = (i + 1) * 10;
    }

    std::cout << "array.length = " << a.length << "\n";
    std::cout << "contenido: ";
    for (int i = 0; i < a.length; ++i) {
        std::cout << a[i] << (i + 1 < a.length ? ' ' : '\n');
    }

    ods::array<int> b(3);
    b[0] = -1;
    b[1] = -2;
    b[2] = -3;
    std::cout << "antes de la asignacion, b[0] = " << b[0] << "\n";

    b = a;  // en esta implementacion la asignacion transfiere el arreglo a b
    std::cout << "despues de b = a, b.length = " << b.length << "\n";
    std::cout << "b: ";
    for (int i = 0; i < b.length; ++i) {
        std::cout << b[i] << (i + 1 < b.length ? ' ' : '\n');
    }
    std::cout << "nota: esta version de array usa una asignacion por transferencia de ownership.\n";
    return 0;
}
