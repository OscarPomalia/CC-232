#include <cassert>
#include "ArrayStack.h"
#include "FastArrayStack.h"
#include "RootishArrayStack.h"
#include "DengVector.h"

int main() {
    {
        ods::ArrayStack<int> s;
        for (int i = 0; i < 200; ++i) s.add(s.size(), i);
        for (int i = 199; i >= 100; --i) assert(s.remove(i) == i);
        assert(s.size() == 100);
    }

    {
        ods::FastArrayStack<int> s;
        for (int i = 0; i < 200; ++i) s.add(s.size(), i);
        for (int i = 0; i < 50; ++i) assert(s.remove(0) == i);
        assert(s.size() == 150);
    }

    {
        ods::RootishArrayStack<int> s;
        for (int i = 0; i < 120; ++i) s.add(i, i);
        for (int i = 119; i >= 60; --i) assert(s.remove(i) == i);
        assert(s.size() == 60);
    }

    {
        ods::DengVector<int> v;
        for (int i = 0; i < 1000; ++i) v.insert(v.size(), i);
        assert(v.size() == 1000);
        for (int i = 0; i < 700; ++i) assert(v.remove(0) == i);
        assert(v.size() == 300);
        for (int i = 700; i < 1000; ++i) assert(v[i - 700] == i);
        for (int i = 1000; i < 1300; ++i) v.insert(v.size(), i);
        assert(v.size() == 600);
        for (int i = 0; i < 300; ++i) assert(v[i] == i + 700);
        for (int i = 300; i < 600; ++i) assert(v[i] == i + 700);
    }

    return 0;
}
