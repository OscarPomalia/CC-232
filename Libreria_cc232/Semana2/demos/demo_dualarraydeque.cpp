#include <iostream>
#include "DualArrayDeque.h"

int main() {
    ods::DualArrayDeque<int> d;
    d.add(0, 20);
    d.add(0, 10);
    d.add(2, 40);
    d.add(2, 30);
    d.add(4, 50);

    std::cout << "size = " << d.size() << "\n";
    std::cout << "secuencia logica: ";
    for (int i = 0; i < d.size(); ++i) {
        std::cout << d.get(i) << (i + 1 < d.size() ? ' ' : '\n');
    }

    std::cout << "front.size = " << d.frontSize() << ", back.size = " << d.backSize() << "\n";
    std::cout << "remove(1) = " << d.remove(1) << "\n";
    std::cout << "despues: ";
    for (int i = 0; i < d.size(); ++i) {
        std::cout << d.get(i) << (i + 1 < d.size() ? ' ' : '\n');
    }
    return 0;
}
