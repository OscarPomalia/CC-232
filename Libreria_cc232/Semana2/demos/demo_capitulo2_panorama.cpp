#include <iostream>
#include "Capitulo2.h"

namespace {
void increaseByOne(int& x) {
    ++x;
}
}

int main() {
    ods::FastSqrt::init();

    ods::ArrayStack<int> stack;
    stack.add(0, 10);
    stack.add(1, 20);
    stack.add(1, 15);

    ods::FastArrayStack<int> fast_stack;
    for (int i = 0; i < 4; ++i) fast_stack.add(i, i + 1);

    ods::ArrayQueue<int> queue;
    queue.add(7);
    queue.add(8);
    queue.add(9);

    ods::ArrayDeque<int> deque;
    deque.add(0, 100);
    deque.add(1, 300);
    deque.add(1, 200);

    ods::DualArrayDeque<int> dual;
    dual.add(0, 1);
    dual.add(1, 3);
    dual.add(1, 2);

    ods::RootishArrayStack<int> rootish;
    for (int i = 0; i < 6; ++i) rootish.add(i, i * 10);

    ods::DengVector<int> deng;
    for (int i = 0; i < 5; ++i) deng.insert(deng.size(), (i + 1) * 11);
    deng.insert(2, 99);
    deng.remove(4);
    deng.traverse(increaseByOne);

    std::cout << "ArrayStack: ";
    for (int i = 0; i < stack.size(); ++i) std::cout << stack.get(i) << (i + 1 < stack.size() ? ' ' : '\n');

    std::cout << "FastArrayStack: ";
    for (int i = 0; i < fast_stack.size(); ++i) std::cout << fast_stack.get(i) << (i + 1 < fast_stack.size() ? ' ' : '\n');

    std::cout << "ArrayQueue remove = " << queue.remove() << "\n";

    std::cout << "ArrayDeque: ";
    for (int i = 0; i < deque.size(); ++i) std::cout << deque.get(i) << (i + 1 < deque.size() ? ' ' : '\n');

    std::cout << "DualArrayDeque: ";
    for (int i = 0; i < dual.size(); ++i) std::cout << dual.get(i) << (i + 1 < dual.size() ? ' ' : '\n');

    std::cout << "RootishArrayStack: ";
    for (int i = 0; i < rootish.size(); ++i) std::cout << rootish.get(i) << (i + 1 < rootish.size() ? ' ' : '\n');

    std::cout << "DengVector: ";
    for (int i = 0; i < deng.size(); ++i) std::cout << deng[i] << (i + 1 < deng.size() ? ' ' : '\n');
    std::cout << "DengVector size=" << deng.size() << ", capacity=" << deng.capacity() << "\n";

    std::cout << "FastSqrt(999) = " << ods::FastSqrt::sqrt(999) << "\n";
    return 0;
}
