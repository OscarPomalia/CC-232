#include <iostream>
#include <vector>

#include "Capitulo6.h"

int main() {
  const std::vector<ods::HuffmanSymbol> alphabet{{'a', 45}, {'b', 13}, {'c', 12},
                                                 {'d', 16}, {'e', 9},  {'f', 5}};
  const auto steps = ods::huffmanBuildTrace(alphabet);

  std::cout << "Fusiones durante la construccion de Huffman (PQ_ComplHeap):\n";
  for (const auto& s : steps) {
    std::cout << "  (" << s.leftLabel << ':' << s.leftFrequency << ") + (" << s.rightLabel
              << ':' << s.rightFrequency << ") -> " << s.mergedFrequency << '\n';
  }

  const auto codes = ods::huffmanGenerateCodes(alphabet);
  const auto tree = ods::huffmanGenerateTree(alphabet);
  const auto leftCodes = ods::huffmanGenerateCodesLeftHeap(alphabet);

  std::cout << "\nTabla de codigos (heap completo):\n";
  for (char c : {'a', 'b', 'c', 'd', 'e', 'f'}) {
    std::cout << "  " << c << " -> " << codes.at(c) << '\n';
  }

  std::cout << "\nTabla de codigos (leftist heap):\n";
  for (char c : {'a', 'b', 'c', 'd', 'e', 'f'}) {
    std::cout << "  " << c << " -> " << leftCodes.at(c) << '\n';
  }

  const std::string text = "face";
  const std::string bits = ods::huffmanEncode(text, codes);
  const std::string decoded = ods::huffmanDecode(bits, tree);

  std::cout << "\ntexto original = " << text << '\n';
  std::cout << "codificado     = " << bits << '\n';
  std::cout << "decodificado   = " << decoded << '\n';
  std::cout << "prefijo libre  = " << std::boolalpha << ods::huffmanIsPrefixFree(codes) << '\n';
}
