#include <iostream>
#include "Capitulo7.h"

int main() {
  ods::RedBlackTreeLLRB<int> rb;
  for (int x : {40, 20, 60, 10, 30, 50, 70, 5, 15, 25, 35}) rb.add(x);
  std::cout << "RB-LLRB inorder: ";
  for (int x : rb.inorder()) std::cout << x << ' ';
  std::cout << "\nheight = " << rb.height() << "\nvalido = " << std::boolalpha << rb.isRedBlackTree() << '\n';
  rb.remove(20);
  rb.remove(60);
  std::cout << "Tras borrar 20 y 60, valido = " << rb.isRedBlackTree() << '\n';
}
