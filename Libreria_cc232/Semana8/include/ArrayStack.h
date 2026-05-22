#pragma once

#include <stdexcept>

#include "array.h"

namespace ods {

template <class T>
class ArrayStack {
    array<T> a_{1};
    int n_ = 0;

    void resize(int m) {
        array<T> b(m);

        for (int i = 0; i < n_; ++i) {
            b[i] = a_[i];
        }

        a_ = std::move(b);
    }

public:
    int size() const {
        return n_;
    }

    bool empty() const {
        return n_ == 0;
    }

    const T& get(int i) const {
        if (i < 0 || i >= n_) {
            throw std::out_of_range("get");
        }

        return a_[i];
    }

    void add(const T& x) {
        add(n_, x);
    }

    void add(int i, const T& x) {
        if (i < 0 || i > n_) {
            throw std::out_of_range("add");
        }

        if (n_ + 1 > a_.length) {
            resize((n_ + 1) <= 1 ? 1 : 2 * (n_ + 1));
        }

        for (int j = n_; j > i; --j) {
            a_[j] = a_[j - 1];
        }

        a_[i] = x;
        ++n_;
    }

    T remove(int i) {
        if (i < 0 || i >= n_) {
            throw std::out_of_range("remove");
        }

        T x = a_[i];

        for (int j = i; j < n_ - 1; ++j) {
            a_[j] = a_[j + 1];
        }

        --n_;

        if (a_.length >= 3 * (n_ + 1)) {
            resize((n_ <= 1) ? 1 : 2 * n_);
        }

        return x;
    }

    void clear() {
        a_ = array<T>(1);
        n_ = 0;
    }
};

}  // namespace ods
