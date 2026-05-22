#include <iostream>
#include <vector>

#include "Capitulo6.h"


namespace {

template <typename T>
void printVector(const std::vector<T>& xs, const char* label) {
  std::cout << label << ": [";
  for (std::size_t i = 0; i < xs.size(); ++i) {
    if (i != 0) std::cout << ", ";
    std::cout << xs[i];
  }
  std::cout << "]\n";
}

}  // namespace


int main() {
  ods::PQ_LeftHeap<int> a{7, 2, 9};
  ods::PQ_LeftHeap<int> b{1, 8, 3, 11};

  printVector(a.levelOrder(), "heap A antes del merge");
  printVector(b.levelOrder(), "heap B antes del merge");

  a.merge(b);
  printVector(a.levelOrder(), "heap A despues del merge");
  std::cout << "B queda vacio: " << std::boolalpha << b.empty() << "\n";

  a.insert(10);
  printVector(a.levelOrder(), "A despues de insert(10)");

  std::cout << "Secuencia de prioridad: ";
  while (!a.empty()) {
    std::cout << a.delMax() << ' ';
  }
  std::cout << '\n';
}
