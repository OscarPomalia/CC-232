#include <cassert>
#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "RootishArrayStack.h"

int main() {
    {
        ods::ArrayStack<int> s;
        s.add(1);
        s.add(2);
        s.add(1, 99);
        assert(s.size() == 3);
        assert(s.get(0) == 1);
        assert(s.get(1) == 99);
        assert(s.get(2) == 2);
        assert(s.remove(1) == 99);
        assert(s.size() == 2);
    }

    {
        ods::FastArrayStack<int> s;
        s.add(s.size(), 5);
        s.add(s.size(), 6);
        s.add(1, 7);
        assert(s.size() == 3);
        assert(s.get(1) == 7);
        assert(s.remove(0) == 5);
        assert(s.get(0) == 7);
    }

    {
        ods::RootishArrayStack<int> s;
        for (int i = 0; i < 6; ++i) s.add(i, i);
        assert(s.size() == 6);
        assert(s.get(4) == 4);
        assert(s.set(4, 40) == 4);
        assert(s.get(4) == 40);
        assert(s.remove(2) == 2);
        assert(s.size() == 5);
    }

    return 0;
}
