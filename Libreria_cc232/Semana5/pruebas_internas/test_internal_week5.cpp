#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/Capitulo5.h"

namespace {

void expect(bool condition, const std::string& message) {
  if (!condition) {
    std::cerr << "[FALLO] " << message << '\n';
    std::exit(1);
  }
}

}  // namespace

int main() {
  {
    ods::BinarySearchTree<int> bst;
    for (int x : {3, 2, 1}) {
      bst.add(x);
    }
    expect(bst.root()->data == 3, "La raiz inicial debe ser 3");
    bst.rotateRight(bst.root());
    expect(bst.root()->data == 2, "rotateRight debe subir al hijo izquierdo");
    expect((bst.inorder() == std::vector<int>{1, 2, 3}),
           "La rotacion no debe romper el orden del BST");
    bst.rotateLeft(bst.root());
    expect(bst.root()->data == 3, "rotateLeft debe restaurar la raiz anterior en este caso");
    expect(bst.isBST(), "Las rotaciones deben preservar la propiedad BST");
  }

  {
    ods::BinaryHeap<int> heap;
    for (int x : {5, 4, 3, 2, 1}) {
      heap.add(x);
    }
    expect(heap.top() == 1, "bubbleUp debe llevar el minimo a la raiz");
    expect(heap.remove() == 1, "remove debe extraer el minimo actual");
    expect(heap.top() == 2, "Tras una extraccion, el nuevo minimo debe quedar arriba");
    expect(heap.isHeap(), "El heap debe seguir valido tras remove");
  }

  {
    ods::BinTree<int> tree;
    auto* root = tree.insertAsRoot(10);
    auto* left = tree.insertAsLC(root, 5);
    auto* right = tree.insertAsRC(root, 20);
    tree.insertAsLC(left, 3);
    tree.insertAsRC(left, 7);
    tree.insertAsLC(right, 15);
    expect(root->height == 2, "updateHeightAbove debe mantener la altura de la raiz");
    expect(tree.size() == 6, "El tamano del BinTree debe contar todos los nodos insertados");
  }

  {
    ods::BinaryTree<int> tree;
    auto* root = tree.insertAsRoot(10);
    auto* left = tree.insertAsLC(root, 5);
    auto* right = tree.insertAsRC(root, 20);
    tree.insertAsLC(left, 3);
    tree.insertAsRC(left, 7);
    tree.insertAsLC(right, 15);

    expect(tree.depth(left) == 1, "BinaryTree::depth debe contar ancestros desde la raiz");
    expect(tree.height() == 2, "BinaryTree::height debe calcular la altura estructural");
    expect(tree.subtreeSize(root) == 6, "BinaryTree::subtreeSize debe contar todos los nodos del subarbol");
    expect(tree.firstNode() != nullptr && tree.firstNode()->data == 3,
           "BinaryTree::firstNode debe ubicar el minimo inorden");
    expect(tree.lastNode() != nullptr && tree.lastNode()->data == 20,
           "BinaryTree::lastNode debe ubicar el maximo inorden");
    expect((tree.iterateBySuccessor() == std::vector<int>{3, 5, 7, 10, 15, 20}),
           "Iterar por sucesor debe recorrer en inorden sin recursion");
    expect((tree.iterateByPredecessor() == std::vector<int>{20, 15, 10, 7, 5, 3}),
           "Iterar por predecesor debe recorrer en orden inverso");
  }

  {
    auto bst = ods::BinarySearchTree<int>::buildBalancedFromSorted(
        std::vector<int>{2, 4, 6, 8, 10, 12});
    expect(bst.root() != nullptr, "buildBalancedFromSorted debe construir una raiz");
    expect(bst.checkParentLinks(), "El arbol construido desde ordenado debe conectar parents");
    expect(bst.lowerBound(5) != nullptr && bst.lowerBound(5)->data == 6,
           "lowerBound debe ubicar el primer mayor o igual");
    expect(bst.upperBound(8) != nullptr && bst.upperBound(8)->data == 10,
           "upperBound debe ubicar el primer estrictamente mayor");
  }

  std::cout << "OK test_internal_week5_final\n";
  return 0;
}
