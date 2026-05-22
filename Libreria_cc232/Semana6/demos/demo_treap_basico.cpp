#include <iostream>
#include <vector>

#include "Capitulo6.h"

int main() {
  ods::Treap<int> t(232);

  std::cout << "Inserciones con prioridades fijas para ver bubbleUp:\n";
  t.addWithPriority(8, 80);
  t.addWithPriority(3, 60);
  t.addWithPriority(10, 90);
  t.addWithPriority(1, 50);
  t.addWithPriority(6, 70);
  t.addWithPriority(4, 65);
  t.addWithPriority(7, 68);

  std::cout << t << '\n';
  std::cout << "inorder: ";
  for (int x : t.inorderKeys()) {
    std::cout << x << ' ';
  }
  std::cout << "\n";
  std::cout << "es treap valido: " << std::boolalpha << t.isTreap() << "\n\n";

  std::cout << "Eliminar 3 y 8 (trickleDown + splice):\n";
  t.remove(3);
  t.remove(8);
  std::cout << t << '\n';
  std::cout << "inorder final: ";
  for (int x : t.inorderKeys()) {
    std::cout << x << ' ';
  }
  std::cout << "\n";
  std::cout << "es treap valido: " << std::boolalpha << t.isTreap() << '\n';
}
