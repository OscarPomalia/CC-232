#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

namespace cc232::pedagogico {

template <class T>
class ArrayStackExplicado {
private:
    std::unique_ptr<T[]> data_;
    int capacity_;
    int n_;

    void check_invariant() const {
        assert(capacity_ >= 1);
        assert(0 <= n_ && n_ <= capacity_);
    }

    void resize() {
        const int new_capacity = std::max(2 * n_, 1);
        std::unique_ptr<T[]> next(new T[new_capacity]);
        for (int i = 0; i < n_; ++i) {
            next[i] = data_[i];
        }
        data_ = std::move(next);
        capacity_ = new_capacity;
        check_invariant();
    }

public:
    ArrayStackExplicado() : data_(std::make_unique<T[]>(1)), capacity_(1), n_(0) {
        check_invariant();
    }

    int size() const {
        return n_;
    }

    int capacity() const {
        return capacity_;
    }

    T get(int i) const {
        assert(0 <= i && i < n_);
        return data_[i];
    }

    T set(int i, T x) {
        assert(0 <= i && i < n_);
        const T old = data_[i];
        data_[i] = x;
        return old;
    }

    void add(int i, T x) {
        assert(0 <= i && i <= n_);
        if (n_ + 1 > capacity_) {
            resize();
        }
        for (int j = n_; j > i; --j) {
            data_[j] = data_[j - 1];
        }
        data_[i] = x;
        ++n_;
        check_invariant();
    }

    void push_back(T x) {
        add(n_, x);
    }

    T remove(int i) {
        assert(0 <= i && i < n_);
        const T x = data_[i];
        for (int j = i; j + 1 < n_; ++j) {
            data_[j] = data_[j + 1];
        }
        --n_;
        if (capacity_ >= 3 * n_) {
            resize();
        }
        check_invariant();
        return x;
    }

    std::string layout() const {
        std::ostringstream out;
        out << "[";
        for (int i = 0; i < capacity_; ++i) {
            if (i < n_) {
                out << data_[i];
            } else {
                out << "_";
            }
            if (i + 1 < capacity_) {
                out << " | ";
            }
        }
        out << "]";
        return out.str();
    }

    void debug_print(std::ostream& out) const {
        out << "size=" << n_ << ", capacity=" << capacity_ << "\n";
        out << "layout=" << layout() << "\n";
        out << "invariante: 0 <= n <= capacity y los elementos validos viven en [0, n)\n";
    }
};

}  // namespace cc232::pedagogico
