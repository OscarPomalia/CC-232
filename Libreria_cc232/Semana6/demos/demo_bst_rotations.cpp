#include <iostream>
#include <vector>

#include "Capitulo5.h"

int main() {
  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7}) {
    bst.add(x);
  }

  std::cout << "BST original:\n" << bst << '\n';
  const auto before = bst.inorder();

  auto* root = bst.root();
  bst.rotateRight(root);
  std::cout << "Despues de rotateRight(root):\n" << bst << '\n';

  bst.rotateLeft(bst.root());
  std::cout << "Despues de rotateLeft(root actual):\n" << bst << '\n';

  const auto after = bst.inorder();
  std::cout << "El inorder se conserva: " << std::boolalpha << (before == after) << '\n';
}
