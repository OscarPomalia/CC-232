#include <iostream>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  const std::vector<int> xs{8, 3, 10, 1, 6, 14, 4, 7, 13};

  ods::PQ_ComplHeap<int> pq;
  ods::BinaryHeap<int> minHeap;
  ods::BinarySearchTree<int> bst;

  for (int x : xs) {
    pq.insert(x);
    minHeap.add(x);
    bst.add(x);
  }

  std::cout << "PQ_ComplHeap::getMax() = " << pq.getMax() << "\n";
  std::cout << "BinaryHeap::top()     = " << minHeap.top() << "\n";
  std::cout << "BST inorder           = ";
  for (int x : bst.inorder()) {
    std::cout << x << ' ';
  }
  std::cout << "\n\n";

  std::cout << "Interpretacion:\n";
  std::cout << "- PQ_ComplHeap responde a la prioridad maxima.\n";
  std::cout << "- BinaryHeap de Semana5 era un min-heap implicito.\n";
  std::cout << "- BinarySearchTree conserva orden para busqueda, no para extraer maximos repetidamente como PQ.\n";
}
