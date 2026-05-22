#pragma once

#include <algorithm>
#include <cassert>
#include <memory>

namespace ods {

template <class T>
class array {
    std::unique_ptr<T[]> a_;

public:
    int length = 0;

    array() = default;

    explicit array(int len)
        : a_(len ? std::make_unique<T[]>(len) : nullptr),
          length(len) {}

    array(int len, const T& init)
        : array(len) {
        fill(init);
    }

    array(const array& o)
        : array(o.length) {
        for (int i = 0; i < length; ++i) {
            a_[i] = o.a_[i];
        }
    }

    array& operator=(const array& o) {
        if (this == &o) {
            return *this;
        }

        array tmp(o);
        *this = std::move(tmp);
        return *this;
    }

    array(array&&) noexcept = default;

    array& operator=(array&&) noexcept = default;

    T& operator[](int i) {
        assert(i >= 0 && i < length);
        return a_[i];
    }

    const T& operator[](int i) const {
        assert(i >= 0 && i < length);
        return a_[i];
    }

    void fill(const T& x) {
        for (int i = 0; i < length; ++i) {
            a_[i] = x;
        }
    }
};

}  // namespace ods
