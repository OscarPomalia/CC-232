#include <iostream>
#include <vector>

#include "../include/Capitulo5.h"

namespace {

template <typename T>
void printVector(const std::string& label, const std::vector<T>& values) {
  std::cout << label << ": ";
  for (std::size_t i = 0; i < values.size(); ++i) {
    if (i > 0) {
      std::cout << ' ';
    }
    std::cout << values[i];
  }
  std::cout << '\n';
}

}  // namespace

int main() {
  ods::BinarySearchTree<int> bst;
  for (int x : {7, 3, 10, 1, 5, 8, 12, 4, 6}) {
    bst.add(x);
  }

  std::cout << "BST:\n" << bst;
  printVector("BST inorden", bst.inorder());

  if (auto* exact = bst.findEQ(5); exact != nullptr) {
    std::cout << "findEQ(5): " << exact->data << '\n';
  }
  if (auto* lb = bst.lowerBound(9); lb != nullptr) {
    std::cout << "lowerBound(9): " << lb->data << '\n';
  }
  if (auto* ub = bst.upperBound(8); ub != nullptr) {
    std::cout << "upperBound(8): " << ub->data << '\n';
  }
  if (auto* parent = bst.findLast(9); parent != nullptr) {
    std::cout << "findLast(9): " << parent->data << '\n';
  }

  bst.remove(3);
  printVector("Tras remove(3)", bst.inorder());

  if (auto* r = bst.root(); r != nullptr && r->right != nullptr) {
    bst.rotateLeft(r);
    std::cout << "Tras rotateLeft(root):\n" << bst;
    bst.rotateRight(bst.root());
  }

  auto balanced = ods::BinarySearchTree<int>::buildBalancedFromSorted(
      std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
  std::cout << "BST balanceado desde vector ordenado:\n" << balanced;
  std::cout << "isBST: " << (balanced.isBST() ? "si" : "no") << '\n';
  return 0;
}
