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
  std::vector<int> a{9, 1, 8, 3, 7, 2, 6, 4, 5};
  printVector(a, "entrada");
  ods::heapSort(a);
  printVector(a, "salida ordenada");
  std::cout << "heapSort usa un max-heap implicito y deja el arreglo en orden ascendente.\n";
}
