#include <cassert>
#include <vector>
#include "Capitulo7.h"
int main() {
  { ods::AVL<int> avl; for (int x : {30,20,10}) avl.insert(x); assert((avl.inorder() == std::vector<int>{10,20,30})); assert(avl.isAVLValid()); assert(avl.height() == 1); }
  { ods::AVL<int> avl; for (int x : {40,20,60,10,30,50,70,25}) avl.insert(x); assert(avl.remove(20)); assert(avl.isAVLValid()); assert((avl.inorder() == std::vector<int>{10,25,30,40,50,60,70})); }
  { ods::RedBlackTree1<int> rb; for (int x : {7,3,18,10,22,8,11,26}) assert(rb.add(x)); assert(rb.verifyRB()); assert(!rb.add(22)); assert(rb.remove(18)); assert(rb.verifyRB()); }
  { ods::AVLTreeCompact<int> avl; for (int x : {30,10,20}) avl.insert(x); assert(avl.root() && avl.root()->data == 20); assert(avl.isAVL()); }
  { ods::RedBlackTreeLLRB<int> rb; for (int x : {30,20,40,10,25,35,50,5,15}) assert(rb.add(x)); assert(rb.isRedBlackTree()); assert(rb.remove(20)); assert((rb.inorder() == std::vector<int>{5,10,15,25,30,35,40,50})); }
}
