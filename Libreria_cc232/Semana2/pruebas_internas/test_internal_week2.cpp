#include <cassert>
#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "RootishArrayStack.h"

int main() {
    ods::ArrayStack<int> a;
    for (int i = 0; i < 20; ++i) a.add(i);
    assert(a.size() == 20);
    for (int i = 0; i < 20; ++i) assert(a.get(i) == i);

    ods::FastArrayStack<int> f;
    for (int i = 0; i < 20; ++i) f.add(f.size(), i);
    for (int i = 19; i >= 10; --i) assert(f.remove(i) == i);
    assert(f.size() == 10);

    ods::RootishArrayStack<int> r;
    for (int i = 0; i < 15; ++i) r.add(i, i * 2);
    for (int i = 0; i < 15; ++i) assert(r.get(i) == i * 2);
    return 0;
}
