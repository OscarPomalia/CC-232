#include <iostream>
#include "LinearHashTable.h"

int main() {
    ods::LinearHashTable<int> t(8);
    for (int x : {7, 15, 23, 31, 39}) t.add(x);
    t.remove(23);
    t.add(47);

    std::cout << "LinearHashTable\n";
    std::cout << "size=" << t.size() << " capacity=" << t.capacity()
              << " activeLoad=" << t.loadFactor()
              << " occupiedLoad=" << t.occupiedFactor()
              << " tombstones=" << t.tombstoneCount() << "\n";
    std::cout << t.stats() << "\n";
}
