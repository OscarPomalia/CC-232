#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  // PQ_ComplHeap: secuencia completa de extracciones.
  ods::PQ_ComplHeap<int> pq;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13, 14}) {
    pq.insert(x);
    assert(pq.isHeap());
  }
  std::vector<int> out;
  while (!pq.empty()) {
    out.push_back(pq.delMax());
    assert(pq.empty() || pq.isHeap());
  }
  assert((out == std::vector<int>{14, 14, 13, 10, 8, 7, 6, 4, 3, 1}));

  // Leftist heap: merge e invariantes.
  ods::PQ_LeftHeap<int> a{20, 7, 18, 3};
  ods::PQ_LeftHeap<int> b{19, 8, 4, 1, 17};
  a.merge(b);
  assert(a.isLeftistHeap());
  assert(b.empty());
  std::vector<int> leftOut;
  while (!a.empty()) {
    leftOut.push_back(a.delMax());
    assert(a.empty() || a.isLeftistHeap());
  }
  assert((leftOut == std::vector<int>{20, 19, 18, 17, 8, 7, 4, 3, 1}));

  // Huffman con heap completo y leftist heap deben tener mismo costo ponderado.
  const std::vector<ods::HuffmanSymbol> s{{'a', 45}, {'b', 13}, {'c', 12},
                                          {'d', 16}, {'e', 9},  {'f', 5}};
  const auto codes1 = ods::huffmanGenerateCodes(s);
  const auto codes2 = ods::huffmanGenerateCodesLeftHeap(s);
  assert(ods::huffmanIsPrefixFree(codes1));
  assert(ods::huffmanIsPrefixFree(codes2));
  assert(ods::huffmanWeightedPathLength(s, codes1) == 224);
  assert(ods::huffmanWeightedPathLength(s, codes2) == 224);

  // Rotaciones BST: preservan inorder aun cuando cambie la forma.
  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7, 13}) {
    bst.add(x);
  }
  auto sorted = bst.inorder();
  bst.rotateLeft(bst.root());
  assert(bst.isBST());
  assert(bst.inorder() == sorted);
  bst.rotateRight(bst.root());
  assert(bst.isBST());
  assert(bst.inorder() == sorted);

  // Treap: BST por clave + heap por prioridad.
  ods::Treap<int> treap(555);
  treap.addWithPriority(8, 80);
  treap.addWithPriority(3, 40);
  treap.addWithPriority(10, 90);
  treap.addWithPriority(1, 20);
  treap.addWithPriority(6, 70);
  treap.addWithPriority(14, 120);
  treap.addWithPriority(4, 65);
  treap.addWithPriority(7, 68);
  assert(treap.isTreap());
  assert((treap.inorderKeys() == std::vector<int>{1, 3, 4, 6, 7, 8, 10, 14}));
  assert(treap.lowerBound(5)->key == 6);
  assert(treap.upperBound(6)->key == 7);
  assert(treap.remove(3));
  assert(treap.remove(8));
  assert(treap.isTreap());
  assert((treap.inorderKeys() == std::vector<int>{1, 4, 6, 7, 10, 14}));
}
