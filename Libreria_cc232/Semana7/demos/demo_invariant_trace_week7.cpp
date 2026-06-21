#include <iostream>
#include <vector>

#include "Capitulo7.h"

namespace {

template <typename T>
void printVector(const std::vector<T>& values) {
  for (const auto& value : values) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
}

}  // namespace

int main() {
  ods::AVL<int> avl;
  ods::RedBlackTree1<int> rb;

  for (int value : {30, 20, 40, 10, 25, 35, 50, 5, 15}) {
    avl.insert(value);
    rb.add(value);
  }

  std::cout << "Estado inicial\n";
  std::cout << "AVL inorder: ";
  printVector(avl.inorder());
  std::cout << "AVL height=" << avl.height() << ", valid=" << avl.isAVLValid() << '\n';
  std::cout << "RB inorder: ";
  printVector(rb.inorder());
  std::cout << "RB height=" << rb.height() << ", valid=" << rb.verifyRB() << '\n';

  for (int value : {20, 40}) {
    avl.remove(value);
    rb.remove(value);
  }

  std::cout << "Despues de borrar 20 y 40\n";
  std::cout << "AVL inorder: ";
  printVector(avl.inorder());
  std::cout << "AVL height=" << avl.height() << ", valid=" << avl.isAVLValid() << '\n';
  std::cout << "RB inorder: ";
  printVector(rb.inorder());
  std::cout << "RB height=" << rb.height() << ", valid=" << rb.verifyRB() << '\n';
}