#include <iostream>
#include "Capitulo7.h"

int main() {
  ods::AVL<int> avl;
  ods::RedBlackTree1<int> rb_morin;
  ods::AVLTreeCompact<int> avl_compact;
  ods::RedBlackTreeLLRB<int> rb_llrb;
  for (int x : {16, 8, 24, 4, 12, 20, 28, 2, 6, 10, 14}) {
    avl.insert(x);
    rb_morin.add(x);
    avl_compact.insert(x);
    rb_llrb.add(x);
  }
  std::cout << "Semana 7 / silabo semana 6\n";
  std::cout << "AVL Deng        -> altura=" << avl.height() << ", valida=" << avl.isAVLValid() << '\n';
  std::cout << "RB Morin        -> tam=" << rb_morin.size() << ", valida=" << rb_morin.verifyRB() << '\n';
  std::cout << "AVL compacto    -> altura=" << avl_compact.height() << ", valida=" << avl_compact.isAVL() << '\n';
  std::cout << "RB LLRB         -> altura=" << rb_llrb.height() << ", valida=" << rb_llrb.isRedBlackTree() << '\n';
}
