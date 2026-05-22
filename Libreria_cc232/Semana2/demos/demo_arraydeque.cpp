#include <iostream>
#include "ArrayDeque.h"

int main() {
    ods::ArrayDeque<int> d;
    d.add(0, 10);
    d.add(1, 30);
    d.add(1, 20);
    d.add(3, 40);
    d.add(0, 5);

    std::cout << "size = " << d.size() << "\n";
    std::cout << "secuencia: ";
    for (int i = 0; i < d.size(); ++i) {
        std::cout << d.get(i) << (i + 1 < d.size() ? ' ' : '\n');
    }

    std::cout << "remove(2) = " << d.remove(2) << "\n";
    std::cout << "despues: ";
    for (int i = 0; i < d.size(); ++i) {
        std::cout << d.get(i) << (i + 1 < d.size() ? ' ' : '\n');
    }
    return 0;
}
