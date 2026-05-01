#include <cassert>
#include "ChainedHashTable.h"
#include "LinearHashTable.h"
#include "HashtableOA.h"

int main() {
    ods::ChainedHashTable<int> c(8);
    ods::LinearHashTable<int> l(8);
    ods::HashtableOA<int, int> m(11);

    auto c0 = c.capacity();
    auto l0 = l.capacity();
    auto m0 = m.capacity();

    for (int i = 0; i < 1000; ++i) {
        c.add(i);
        l.add(i);
        m.put(i, i * i);
    }

    assert(c.capacity() > c0);
    assert(l.capacity() > l0);
    assert(m.capacity() > m0);
    assert(c.stats().rehashes > 0);
    assert(l.stats().rehashes > 0);
    assert(m.stats().rehashes > 0);
    return 0;
}
