#include <iostream>
#include <vector>
#include "Capitulo7.h"

static void printVector(const std::vector<int>& xs, const char* label) {
  std::cout << label << ": ";
  for (int x : xs) std::cout << x << ' ';
  std::cout << '\n';
}

int main() {
  ods::AVLTreeCompact<int> avl;
  for (int x : {30, 20, 10, 25, 28, 27}) {
    avl.insert(x);
    std::cout << "insert(" << x << ") -> root=" << (avl.root() ? avl.root()->data : -1)
              << ", height=" << avl.height() << '\n';
  }
  printVector(avl.inorder(), "inorder");
  printVector(avl.levelOrder(), "level");
  std::cout << avl.summary() << '\n';
  std::cout << "isAVL = " << std::boolalpha << avl.isAVL() << '\n';
}
