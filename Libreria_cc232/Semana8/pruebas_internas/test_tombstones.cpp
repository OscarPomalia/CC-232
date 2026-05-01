#include <cassert>
#include "HashtableOA.h"
#include "LinearHashTable.h"

int main() {
    ods::LinearHashTable<int> t(32);
    for (int i = 0; i < 20; ++i) assert(t.add(i));
    for (int i = 0; i < 10; ++i) assert(t.remove(i));
    assert(t.tombstoneCount() > 0);
    for (int i = 10; i < 20; ++i) assert(t.contains(i));
    for (int i = 100; i < 110; ++i) assert(t.add(i));

    ods::HashtableOA<int, int> m(31);
    for (int i = 0; i < 20; ++i) assert(m.put(i, i));
    for (int i = 0; i < 10; ++i) assert(m.remove(i));
    assert(m.tombstoneCount() > 0);
    for (int i = 10; i < 20; ++i) assert(m.get(i) && *m.get(i) == i);
    return 0;
}
