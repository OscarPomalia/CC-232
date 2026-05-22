#include <iostream>
#include <vector>

#include "../include/Capitulo5.h"

int main() {
  std::cout << "Semana 5 final: BinaryTree, BST, heap, recorridos iterativos y utilidades\n";

  ods::BinaryHeap<int> heap(std::vector<int>{9, 4, 7, 1, 3});
  std::cout << "Heap minimo actual: " << heap.top() << '\n';

  ods::BinarySearchTree<int> bst;
  for (int x : {9, 4, 12, 2, 7, 10, 15}) {
    bst.add(x);
  }
  std::cout << "Raiz BST: " << bst.root()->data << '\n';
  std::cout << "Altura BST: " << bst.height() << '\n';
  std::cout << "Arbol BST:\n" << bst;
  std::cout << "Recorrido STL-like: ";
  for (int x : bst) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
  return 0;
}
