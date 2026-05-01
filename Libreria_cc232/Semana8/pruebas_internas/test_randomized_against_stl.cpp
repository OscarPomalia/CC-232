#include <cassert>
#include <random>
#include <unordered_set>
#include "LinearHashTable.h"
#include "RobinHoodHashTable.h"

int main() {
    ods::LinearHashTable<int> linear;
    ods::RobinHoodHashTable<int> robin;
    std::unordered_set<int> ref;
    std::mt19937 rng(808);
    std::uniform_int_distribution<int> dist(0, 2000);

    for (int i = 0; i < 3000; ++i) {
        int x = dist(rng);
        if (i % 3 == 0) {
            bool expected = ref.erase(x) > 0;
            assert(linear.remove(x) == expected);
            assert(robin.remove(x) == expected);
        } else {
            bool expected = ref.insert(x).second;
            assert(linear.add(x) == expected);
            assert(robin.add(x) == expected);
        }
    }

    for (int x = 0; x <= 2000; ++x) {
        bool expected = ref.count(x) > 0;
        assert(linear.contains(x) == expected);
        assert(robin.contains(x) == expected);
    }
    return 0;
}
