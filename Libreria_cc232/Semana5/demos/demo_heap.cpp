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
  ods::BinaryHeap<int> heap(std::vector<int>{7, 3, 10, 1, 5, 8, 2});
  printVector("Heapify", heap.data());
  std::cout << "isHeap: " << (heap.isHeap() ? "si" : "no") << '\n';

  heap.add(0);
  printVector("Tras add(0)", heap.data());

  std::cout << "remove() -> " << heap.remove() << '\n';
  printVector("Tras remove()", heap.data());

  std::cout << "Secuencia ordenada por extraccion: ";
  bool first = true;
  while (!heap.empty()) {
    if (!first) {
      std::cout << ' ';
    }
    first = false;
    std::cout << heap.remove();
  }
  std::cout << '\n';
  return 0;
}
