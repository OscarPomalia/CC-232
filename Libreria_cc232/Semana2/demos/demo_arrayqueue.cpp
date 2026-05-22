#include <iostream>
#include "ArrayQueue.h"

int main() {
    ods::ArrayQueue<int> q;
    for (int x : {10, 20, 30, 40}) {
        q.add(x);
    }

    std::cout << "size = " << q.size() << "\n";
    std::cout << "peek = " << q.peek() << "\n";
    std::cout << "remove = " << q.remove() << "\n";
    q.add(50);
    q.add(60);

    std::cout << "cola en orden FIFO: ";
    while (q.size() > 0) {
        std::cout << q.remove() << (q.size() > 0 ? ' ' : '\n');
    }
    return 0;
}
