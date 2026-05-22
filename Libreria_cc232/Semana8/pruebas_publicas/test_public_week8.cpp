#include <cassert>
#include <vector>
#include "Applications.h"
#include "ChainedHashTable.h"
#include "HashtableOA.h"
#include "LinearHashTable.h"

int main() {
    ods::ChainedHashTable<int> chained;
    assert(chained.add(10));
    assert(!chained.add(10));
    assert(chained.contains(10));
    assert(chained.remove(10));
    assert(!chained.contains(10));

    ods::LinearHashTable<int> linear;
    for (int i = 0; i < 100; ++i) assert(linear.add(i));
    for (int i = 0; i < 100; ++i) assert(linear.contains(i));
    for (int i = 0; i < 50; ++i) assert(linear.remove(i));
    for (int i = 0; i < 50; ++i) assert(!linear.contains(i));
    for (int i = 50; i < 100; ++i) assert(linear.contains(i));

    ods::HashtableOA<std::string, int> dict;
    assert(dict.put("uno", 1));
    assert(dict.put("dos", 2));
    assert(!dict.put("uno", 11));
    assert(dict.get("uno") && *dict.get("uno") == 1);
    assert(dict.remove("dos"));
    assert(!dict.get("dos"));

    std::vector<int> v{1, 2, 3, 2};
    assert(ods::hasDuplicates(v));
    assert(ods::firstRepeated(v) && *ods::firstRepeated(v) == 2);
    assert(ods::twoSum({2, 7, 11, 15}, 9).has_value());

    auto f = ods::wordFrequencyFromText("Hash hash TREE tree tree");
    assert(f.get("hash") && *f.get("hash") == 2);
    assert(f.get("tree") && *f.get("tree") == 3);

    return 0;
}
