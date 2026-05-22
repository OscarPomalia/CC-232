#include <iostream>
#include "RootishArrayStack.h"

int main() {
    ods::RootishArrayStack<int> s;
    for (int i = 0; i < 8; ++i) {
        s.add(i, i * 10);
    }

    std::cout << "size = " << s.size() << "\n";
    for (int i = 0; i < s.size(); ++i) {
        std::cout << s.get(i) << (i + 1 < s.size() ? ' ' : '\n');
    }
    std::cout << "remove(3) = " << s.remove(3) << "\n";
    return 0;
}
