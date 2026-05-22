#include <iostream>
#include "FastArrayStack.h"

int main() {
    ods::FastArrayStack<int> s;
    for (int i = 0; i < 6; ++i) {
        s.add(s.size(), i);
    }
    s.add(3, 99);

    std::cout << "size = " << s.size() << "\n";
    for (int i = 0; i < s.size(); ++i) {
        std::cout << s.get(i) << (i + 1 < s.size() ? ' ' : '\n');
    }
    return 0;
}
