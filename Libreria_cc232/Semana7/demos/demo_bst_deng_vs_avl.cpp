#include <iostream>
#include "Capitulo7.h"

int main() {
  ods::BST<int> bst;
  ods::AVL<int> avl;
  for (int x : {1, 2, 3, 4, 5, 6, 7}) {
    bst.insert(x);
    avl.insert(x);
  }
  std::cout << "Altura BST: " << bst.height() << '\n';
  std::cout << "Altura AVL: " << avl.height() << '\n';
  std::cout << "AVL valido: " << (avl.isAVLValid() ? "si" : "no") << '\n';
}
