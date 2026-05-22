#include <iostream>
#include "Capitulo7.h"

int main() {
  ods::RedBlackTree1<int> rb;
  for (int x : {7, 3, 18, 10, 22, 8, 11, 26, 2, 6, 13}) rb.add(x);
  std::cout << "RB inorder: ";
  for (int x : rb.inorder()) std::cout << x << ' ';
  std::cout << "\nValido RedBlack: " << (rb.verifyRB() ? "si" : "no") << '\n';
  rb.remove(18);
  rb.remove(11);
  std::cout << "Tras borrar 18 y 11: ";
  for (int x : rb.inorder()) std::cout << x << ' ';
  std::cout << "\nValido RedBlack: " << (rb.verifyRB() ? "si" : "no") << '\n';
}
