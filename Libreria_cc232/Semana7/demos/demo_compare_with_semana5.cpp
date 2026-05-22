#include <iostream>
#include "Capitulo7.h"

int main() {
  ods::BinarySearchTree1<int> bst_morin;
  ods::AVL<int> avl_deng;
  for (int x : {50, 30, 70, 20, 40, 60, 80}) {
    bst_morin.add(x);
    avl_deng.insert(x);
  }
  std::cout << "Semana5 -> BinarySearchTree inorder: ";
  for (int x : bst_morin.inorder()) std::cout << x << ' ';
  std::cout << "\nSemana7 -> AVL inorder: ";
  for (int x : avl_deng.inorder()) std::cout << x << ' ';
  std::cout << '\n';
}
