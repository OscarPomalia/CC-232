#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Capitulo5.h"

namespace {

void expect(bool condition, const std::string& message) {
  if (!condition) {
    std::cerr << "[FALLO] " << message << '\n';
    std::exit(1);
  }
}

template <typename T>
std::vector<T> sorted(const std::vector<T>& values) {
  std::vector<T> out = values;
  std::sort(out.begin(), out.end());
  return out;
}

}  // namespace

int main() {
  {
    ods::BinarySearchTree<int> bst;
    for (int x : {7, 3, 10, 1, 5, 8, 12, 4, 6}) {
      expect(bst.add(x), "Insercion BST debe aceptar claves nuevas");
    }
    expect(!bst.add(5), "BST no debe aceptar duplicados");
    expect((bst.inorder() == std::vector<int>{1, 3, 4, 5, 6, 7, 8, 10, 12}),
           "El inorden recursivo del BST debe quedar ordenado");
    expect((bst.inorder(ods::InorderStrategy::Iterative1) ==
            std::vector<int>{1, 3, 4, 5, 6, 7, 8, 10, 12}),
           "El inorden iterativo #1 debe coincidir");
    expect((bst.inorder(ods::InorderStrategy::Iterative2) ==
            std::vector<int>{1, 3, 4, 5, 6, 7, 8, 10, 12}),
           "El inorden iterativo #2 debe coincidir");
    expect((bst.inorder(ods::InorderStrategy::Iterative3) ==
            std::vector<int>{1, 3, 4, 5, 6, 7, 8, 10, 12}),
           "El inorden iterativo #3 debe coincidir");
    expect(bst.findEQ(8) != nullptr && bst.findEQ(8)->data == 8,
           "findEQ debe ubicar una clave exacta");
    expect(bst.find(9) != nullptr && bst.find(9)->data == 10,
           "find debe actuar como lowerBound");
    expect(bst.lowerBound(9) != nullptr && bst.lowerBound(9)->data == 10,
           "lowerBound debe devolver 10 para 9");
    expect(bst.upperBound(8) != nullptr && bst.upperBound(8)->data == 10,
           "upperBound debe devolver el primer valor estrictamente mayor");
    expect(bst.minNode()->data == 1 && bst.maxNode()->data == 12,
           "minNode y maxNode deben ubicar extremos");
    expect(bst.isBST(), "La estructura debe validar propiedad BST");
  }

  {
    ods::BinarySearchTree<int> bst;
    for (int x : {7, 3, 10, 1, 5, 8, 12, 4, 6}) {
      bst.add(x);
    }
    expect(bst.remove(3), "remove debe borrar una clave existente");
    expect((bst.inorder() == std::vector<int>{1, 4, 5, 6, 7, 8, 10, 12}),
           "Tras borrar 3, el BST debe seguir ordenado");
    expect(!bst.contains(3), "La clave eliminada no debe permanecer en el BST");
    expect(bst.checkParentLinks(), "Los parent links deben mantenerse tras borrar");
  }

  {
    ods::BinaryHeap<int> heap(std::vector<int>{7, 3, 10, 1, 5, 8, 2});
    expect(heap.isHeap(), "heapify debe dejar una estructura valida");
    std::vector<int> extracted;
    while (!heap.empty()) {
      extracted.push_back(heap.remove());
    }
    expect((extracted == std::vector<int>{1, 2, 3, 5, 7, 8, 10}),
           "Las extracciones del min-heap deben salir ordenadas");
    expect(ods::BinaryHeap<int>::isHeapArray(std::vector<int>{1, 3, 2, 7, 5, 8, 10}),
           "isHeapArray debe reconocer un heap valido");
  }

  {
    ods::BinaryTree<int> tree;
    auto* root = tree.insertAsRoot(7);
    auto* l = tree.insertAsLC(root, 3);
    auto* r = tree.insertAsRC(root, 10);
    tree.insertAsLC(l, 1);
    auto* five = tree.insertAsRC(l, 5);
    tree.insertAsLC(r, 8);
    tree.insertAsRC(r, 12);
    tree.insertAsLC(five, 4);
    tree.insertAsRC(five, 6);

    expect((tree.preorder() == std::vector<int>{7, 3, 1, 5, 4, 6, 10, 8, 12}),
           "Preorden recursivo debe coincidir con la forma del arbol");
    expect((tree.preorderIterative() == std::vector<int>{7, 3, 1, 5, 4, 6, 10, 8, 12}),
           "Preorden iterativo debe coincidir");
    expect((tree.postorder() == std::vector<int>{1, 4, 6, 5, 3, 8, 12, 10, 7}),
           "Postorden recursivo debe coincidir");
    expect((tree.postorderIterative() == std::vector<int>{1, 4, 6, 5, 3, 8, 12, 10, 7}),
           "Postorden iterativo debe coincidir");
    expect((tree.levelOrder() == std::vector<int>{7, 3, 10, 1, 5, 8, 12, 4, 6}),
           "Recorrido por niveles debe visitar por capas");
    expect(five->succ() != nullptr && five->succ()->data == 6,
           "El sucesor inorden de 5 debe ser 6");
    expect(five->pred() != nullptr && five->pred()->data == 4,
           "El predecesor inorden de 5 debe ser 4");
    expect(tree.checkParentLinks(), "Los parent links del arbol base deben ser consistentes");
    expect(tree.asciiArt().find("7") != std::string::npos,
           "asciiArt debe producir una representacion textual");
  }

  {
    auto balanced = ods::BinarySearchTree<int>::buildBalancedFromSorted(
        std::vector<int>{1, 2, 3, 4, 5, 6, 7});
    expect(balanced.isBST(), "El BST balanceado desde ordenado debe ser valido");
    expect(balanced.height() == 2, "El BST balanceado de 7 nodos debe tener altura 2");
    std::vector<int> iterated;
    for (int x : balanced) {
      iterated.push_back(x);
    }
    expect((iterated == std::vector<int>{1, 2, 3, 4, 5, 6, 7}),
           "El iterador inorder debe soportar range-for");
  }

  {
    ods::BinTree<int> host;
    auto* root = host.insertAsRoot(10);
    ods::BinTree<int> extra;
    auto* eroot = extra.insertAsRoot(20);
    extra.insertAsLC(eroot, 15);
    extra.insertAsRC(eroot, 30);
    host.attachAsRC(root, extra);
    expect(host.size() == 4, "attachAsRC debe sumar nodos del subarbol");
    expect(extra.empty(), "El subarbol adjunto debe quedar vacio");
    auto detached = host.secede(root->right);
    expect(host.size() == 1, "secede debe descontar el subarbol desprendido");
    expect(detached.size() == 3, "El arbol desprendido debe preservar su tamano");
    expect(detached.checkParentLinks(), "El subarbol separado debe conservar parent links validos");
    expect(host.removeSubtree(host.root()) == 1, "removeSubtree debe eliminar el nodo restante");
    expect(host.empty(), "El arbol debe quedar vacio tras removeSubtree");
  }

  std::cout << "OK test_public_week5_final\n";
  return 0;
}
