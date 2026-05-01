#include <cassert>
#include "ChainedHashTable.h"
#include "LinearHashTable.h"
#include "DoubleHashTable.h"
#include "RobinHoodHashTable.h"

int main() {
    ods::ChainedHashTable<int> c(8);
    ods::LinearHashTable<int> l(8);
    ods::DoubleHashTable<int> d(11);
    ods::RobinHoodHashTable<int> r(8);

    for (int i = 0; i < 50; ++i) {
        int x = i * 8;
        assert(c.add(x));
        assert(l.add(x));
        assert(d.add(x));
        assert(r.add(x));
    }

    assert(c.longestBucket() >= 1);
    assert(l.stats().maxProbeLength >= 1);
    assert(d.stats().maxProbeLength >= 1);
    assert(r.maxDisplacement() >= 0);
    return 0;
}
