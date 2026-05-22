#include <iomanip>
#include <iostream>
#include <vector>
#include "Capitulo7.h"

int main() {
  const std::vector<int> datos{1,2,3,4,5,6,7,8,9,10,11,12};
  ods::AVL<int> avl;
  ods::RedBlackTree1<int> rb_morin;
  ods::AVLTreeCompact<int> avl_compact;
  ods::RedBlackTreeLLRB<int> rb_llrb;
  for (int x : datos) {
    avl.insert(x);
    rb_morin.add(x);
    avl_compact.insert(x);
    rb_llrb.add(x);
  }
  std::cout << "Insercion ordenada 1..12\n";
  std::cout << std::left << std::setw(20) << "estructura"
            << std::setw(8) << "size" << std::setw(8) << "height" << "valida\n";
  std::cout << std::setw(20) << "AVL (Deng)" << std::setw(8) << avl.size()
            << std::setw(8) << avl.height() << avl.isAVLValid() << '\n';
  std::cout << std::setw(20) << "RedBlack (Morin)" << std::setw(8) << rb_morin.size()
            << std::setw(8) << rb_morin.height() << rb_morin.verifyRB() << '\n';
  std::cout << std::setw(20) << "AVL compacto" << std::setw(8) << avl_compact.size()
            << std::setw(8) << avl_compact.height() << avl_compact.isAVL() << '\n';
  std::cout << std::setw(20) << "RedBlack LLRB" << std::setw(8) << rb_llrb.size()
            << std::setw(8) << rb_llrb.height() << rb_llrb.isRedBlackTree() << '\n';
}
