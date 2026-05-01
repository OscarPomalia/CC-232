#include <iostream>
#include "HashtableOA.h"
#include "LinearHashTable.h"

int main() {
    ods::LinearHashTable<int> linear(16);
    for (int i = 0; i < 12; ++i) linear.add(i);
    for (int i = 0; i < 8; i += 2) linear.remove(i);

    std::cout << "Linear tombstones=" << linear.tombstoneCount()
              << " activeLoad=" << linear.loadFactor()
              << " occupiedLoad=" << linear.occupiedFactor() << "\n";

    ods::HashtableOA<int, int> map(17);
    for (int i = 0; i < 12; ++i) map.put(i, i * i);
    for (int i = 0; i < 8; i += 2) map.remove(i);

    std::cout << "HashtableOA tombstones=" << map.tombstoneCount()
              << " activeLoad=" << map.loadFactor()
              << " occupiedLoad=" << map.occupiedFactor() << "\n";
}
