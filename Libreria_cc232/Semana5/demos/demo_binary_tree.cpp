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
  ods::BinaryTree<int> tree;
  auto* root = tree.insertAsRoot(7);
  auto* n3 = tree.insertAsLC(root, 3);
  auto* n10 = tree.insertAsRC(root, 10);
  tree.insertAsLC(n3, 1);
  auto* n5 = tree.insertAsRC(n3, 5);
  tree.insertAsLC(n10, 8);
  tree.insertAsRC(n10, 12);
  tree.insertAsLC(n5, 4);
  tree.insertAsRC(n5, 6);

  std::cout << "Arbol:\n" << tree;
  printVector("Preorden recursivo", tree.preorder());
  printVector("Preorden iterativo", tree.preorderIterative());
  printVector("Inorden recursivo", tree.inorder());
  printVector("Inorden iterativo #1", tree.inorder(ods::InorderStrategy::Iterative1));
  printVector("Inorden iterativo #2", tree.inorder(ods::InorderStrategy::Iterative2));
  printVector("Inorden iterativo #3", tree.inorder(ods::InorderStrategy::Iterative3));
  printVector("Postorden recursivo", tree.postorder());
  printVector("Postorden iterativo", tree.postorderIterative());
  printVector("Niveles", tree.levelOrder());
  printVector("Iteracion por sucesor", tree.iterateBySuccessor());

  if (auto* succ = n5->succ(); succ != nullptr) {
    std::cout << "Sucesor de 5: " << succ->data << '\n';
  }
  if (auto* pred = n5->pred(); pred != nullptr) {
    std::cout << "Predecesor de 5: " << pred->data << '\n';
  }

  std::cout << "Primer nodo inorden: " << tree.firstNode()->data << '\n';
  std::cout << "Ultimo nodo inorden: " << tree.lastNode()->data << '\n';
  std::cout << "Altura estructural: " << tree.height() << '\n';
  std::cout << "Profundidad de 5: " << tree.depth(n5) << '\n';
  std::cout << "Parent links OK: " << (tree.checkParentLinks() ? "si" : "no") << '\n';
  return 0;
}
