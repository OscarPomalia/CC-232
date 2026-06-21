#include <cassert>
#include <vector>

#include "Capitulo7.h"

int main() {
  {
    ods::AVL<int> avl;
    for (int value : {1, 2, 3, 4, 5, 6, 7}) {
      avl.insert(value);
    }

    assert((avl.inorder() == std::vector<int>{1, 2, 3, 4, 5, 6, 7}));
    assert(avl.isAVLValid());
    assert(avl.height() <= 2);
  }

  {
    ods::RedBlackTree1<int> rb;
    for (int value : {40, 20, 60, 10, 30, 50, 70, 25, 35}) {
      assert(rb.add(value));
    }

    assert(rb.verifyRB());
    assert(rb.contains(25));
    assert(rb.contains(70));
    assert(!rb.contains(99));
    assert((rb.inorder() == std::vector<int>{10, 20, 25, 30, 35, 40, 50, 60, 70}));
  }
}