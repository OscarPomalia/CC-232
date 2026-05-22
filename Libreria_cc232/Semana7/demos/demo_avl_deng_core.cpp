#include <iostream>
#include "Capitulo7.h"

int main() {
  ods::AVL<int> avl;
  for (int x : {30, 20, 10, 25, 40, 50, 22, 27}) avl.insert(x);

  std::cout << "AVL inorder: ";
  for (int x : avl.inorder()) std::cout << x << ' ';
  std::cout << "\nAVL level-order: ";
  for (int x : avl.levelOrder()) std::cout << x << ' ';
  std::cout << "\nValido AVL: " << (avl.isAVLValid() ? "si" : "no") << '\n';

  avl.remove(20);
  avl.remove(40);
  std::cout << "Tras borrar 20 y 40: ";
  for (int x : avl.inorder()) std::cout << x << ' ';
  std::cout << "\nValido AVL: " << (avl.isAVLValid() ? "si" : "no") << '\n';
}
