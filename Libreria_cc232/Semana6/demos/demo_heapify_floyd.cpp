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
  std::vector<int> a{17, 3, 11, 9, 6, 14, 1, 8, 5, 2};
  printVector(a, "antes de heapify");
  ods::complHeapHeapifyFloyd(a, std::less<int>{});
  printVector(a, "despues de heapify");
  std::cout << "Interpretacion: el mayor elemento sube a la raiz y cada padre domina a sus hijos.\n";
}
