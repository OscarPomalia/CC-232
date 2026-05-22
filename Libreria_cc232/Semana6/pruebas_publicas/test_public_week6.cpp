#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include "Capitulo5.h"
#include "Capitulo6.h"

int main() {
  ods::PQ_ComplHeap<int> h{4, 10, 7, 1, 3, 9};
  assert(h.isHeap());
  assert(h.getMax() == 10);
  h.insert(12);
  assert(h.isHeap());
  assert(h.delMax() == 12);
  assert(h.isHeap());

  std::vector<int> xs{5, 1, 8, 3, 2};
  ods::heapSort(xs);
  assert((xs == std::vector<int>{1, 2, 3, 5, 8}));

  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3};
  ods::leftHeapMerge(a, b);
  assert(b.empty());
  assert(a.size() == 6);
  assert(a.isLeftistHeap());
  assert(a.getMax() == 9);

  const std::vector<ods::HuffmanSymbol> s{{'a', 45}, {'b', 13}, {'c', 12},
                                          {'d', 16}, {'e', 9},  {'f', 5}};
  const auto codes = ods::huffmanGenerateCodes(s);
  const auto tree = ods::huffmanGenerateTree(s);
  const std::string msg = "face";
  const std::string bits = ods::huffmanEncode(msg, codes);
  assert(ods::huffmanDecode(bits, tree) == msg);
  assert(ods::huffmanIsPrefixFree(codes));

  ods::BinarySearchTree<int> bst;
  for (int x : {8, 3, 10, 1, 6, 14, 4, 7}) {
    bst.add(x);
  }
  const auto before = bst.inorder();
  bst.rotateRight(bst.root());
  bst.rotateLeft(bst.root());
  const auto after = bst.inorder();
  assert(before == after);
  assert(bst.isBST());

  ods::Treap<int> treap(123);
  assert(treap.addWithPriority(8, 80));
  assert(treap.addWithPriority(3, 60));
  assert(treap.addWithPriority(10, 90));
  assert(treap.addWithPriority(1, 50));
  assert(treap.addWithPriority(6, 70));
  assert(treap.isTreap());
  assert(!treap.addWithPriority(6, 71));
  assert(treap.contains(3));
  assert(treap.remove(3));
  assert(!treap.contains(3));
  assert(treap.isTreap());
}
