#include <cassert>
#include <random>
#include <unordered_set>
#include "ChainedHashTable.h"
#include "DoubleHashTable.h"
#include "LinearHashTable.h"
#include "QuadraticHashTable.h"
#include "RobinHoodHashTable.h"
#include "UniversalHash.h"

int main() {
    std::mt19937 rng(232);
    std::uniform_int_distribution<int> dist(-5000, 5000);

    ods::ChainedHashTable<int> chained;
    ods::LinearHashTable<int> linear;
    ods::QuadraticHashTable<int> quadratic;
    ods::DoubleHashTable<int> dbl;
    ods::RobinHoodHashTable<int> robin;
    std::unordered_set<int> ref;

    for (int i = 0; i < 1000; ++i) {
        int x = dist(rng);
        bool expected = ref.insert(x).second;
        assert(chained.add(x) == expected);
        assert(linear.add(x) == expected);
        assert(quadratic.add(x) == expected);
        assert(dbl.add(x) == expected);
        assert(robin.add(x) == expected);
    }

    for (int x : ref) {
        assert(chained.contains(x));
        assert(linear.contains(x));
        assert(quadratic.contains(x));
        assert(dbl.contains(x));
        assert(robin.contains(x));
    }

    ods::UniversalHash uh(123);
    assert(uh(42, 17) < 17);
    assert(uh("hashing", 31) < 31);

    return 0;
}
