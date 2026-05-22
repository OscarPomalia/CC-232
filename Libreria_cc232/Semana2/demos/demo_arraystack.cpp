#include <iostream>
#include "ArrayStack.h"

int main() {
    ods::ArrayStack<int> s;
    s.add(10);
    s.add(20);
    s.add(1, 15);

    std::cout << "size = " << s.size() << "\n";
    for (int i = 0; i < s.size(); ++i) {
        std::cout << s.get(i) << (i + 1 < s.size() ? ' ' : '\n');
    }
    std::cout << "remove(1) = " << s.remove(1) << "\n";
    return 0;
}
