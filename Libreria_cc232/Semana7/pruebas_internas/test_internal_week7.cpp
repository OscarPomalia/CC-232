#include <algorithm>
#include <cassert>
#include <random>
#include <set>
#include <vector>
#include "Capitulo7.h"
int main() {
  { ods::BST<int> bst; for (int x : {5,3,7,2,4,6,8}) bst.insert(x); assert(bst.isBSTValid()); assert(bst.remove(5)); assert((bst.inorder() == std::vector<int>{2,3,4,6,7,8})); assert(bst.isBSTValid()); }
  { ods::BinarySearchTree1<int> bst; for (int x : {50,20,70,10,30,60,80}) bst.add(x); assert(bst.contains(30)); assert(bst.lowerBound(25).value() == 30); assert(bst.upperBound(30).value() == 50); assert(bst.isBSTValid()); }
  std::mt19937 rng(20260429); std::uniform_int_distribution<int> dist(1,500);
  ods::AVL<int> avl; ods::RedBlackTree1<int> rb_morin; ods::AVLTreeCompact<int> avl_compact; ods::RedBlackTreeLLRB<int> rb_llrb; std::set<int> oracle;
  for (int i = 0; i < 250; ++i) { int x = dist(rng); avl.insert(x); rb_morin.add(x); avl_compact.insert(x); rb_llrb.add(x); oracle.insert(x); }
  std::vector<int> sorted(oracle.begin(), oracle.end());
  assert(avl.isAVLValid()); assert(rb_morin.verifyRB()); assert(avl_compact.isAVL()); assert(rb_llrb.isRedBlackTree());
  assert(avl.inorder() == sorted); assert(rb_morin.inorder() == sorted); assert(avl_compact.inorder() == sorted); assert(rb_llrb.inorder() == sorted);
  std::shuffle(sorted.begin(), sorted.end(), rng);
  for (int i = 0; i < 120; ++i) { int x = sorted[i]; assert(avl.remove(x)); assert(rb_morin.remove(x)); assert(avl_compact.remove(x)); assert(rb_llrb.remove(x)); oracle.erase(x); assert(avl.isAVLValid()); assert(rb_morin.verifyRB()); assert(avl_compact.isAVL()); assert(rb_llrb.isRedBlackTree()); }
  const std::vector<int> remain(oracle.begin(), oracle.end());
  assert(avl.inorder() == remain); assert(rb_morin.inorder() == remain); assert(avl_compact.inorder() == remain); assert(rb_llrb.inorder() == remain);
}
