#include <iostream>
#include "ChainedHashTable.h"

int main() {
    ods::ChainedHashTable<int> t(8);
    for (int x : {10, 18, 26, 34, 42, 50}) t.add(x);

    std::cout << "ChainedHashTable\n";
    std::cout << "size=" << t.size() << " capacity=" << t.capacity()
              << " load=" << t.loadFactor() << " longestBucket=" << t.longestBucket() << "\n";
    std::cout << "contains(26)=" << t.contains(26) << " contains(99)=" << t.contains(99) << "\n";
    std::cout << t.stats() << "\n";
}
