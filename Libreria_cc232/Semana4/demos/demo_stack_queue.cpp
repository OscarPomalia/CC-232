#include <iostream>

#include "Stack.h"
#include "Queue.h"

int main() {
    ods::Stack<int> stack;
    stack.push(5);
    stack.push(7);
    stack.push(9);

    ods::Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    std::cout << "Tope de la pila = " << stack.top() << "\n";
    std::cout << "Elemento desapilado = " << stack.pop() << "\n";
    std::cout << "Frente de la cola = " << queue.front() << "\n";
    std::cout << "Elemento desencolado = " << queue.dequeue() << "\n";
    return 0;
}