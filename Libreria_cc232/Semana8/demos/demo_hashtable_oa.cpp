#include <iostream>
#include "HashtableOA.h"

int main() {
    ods::HashtableOA<std::string, int> dict;
    dict.put("hash", 1);
    dict.put("tree", 2);
    dict.put("graph", 3);

    if (auto v = dict.get("hash")) std::cout << "hash -> " << *v << "\n";
    dict.remove("tree");

    std::cout << "size=" << dict.size() << " capacity=" << dict.capacity()
              << " load=" << dict.loadFactor()
              << " occupied=" << dict.occupiedFactor()
              << " tombstones=" << dict.tombstoneCount() << "\n";
    std::cout << dict.stats() << "\n";
}
