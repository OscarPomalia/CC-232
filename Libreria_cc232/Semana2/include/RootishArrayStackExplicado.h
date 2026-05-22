#pragma once

#include <cassert>
#include <cmath>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace cc232::pedagogico {

template <class T>
class RootishArrayStackExplicado {
private:
    std::vector<std::unique_ptr<T[]>> blocks_;
    int n_ = 0;

    static int triangular(int r) {
        return r * (r + 1) / 2;
    }

    void grow() {
        blocks_.push_back(std::make_unique<T[]>(blocks_.size() + 1));
    }

    void shrink() {
        int r = static_cast<int>(blocks_.size());
        while (r > 0 && (r - 2) * (r - 1) / 2 >= n_) {
            blocks_.pop_back();
            --r;
        }
    }

public:
    int size() const {
        return n_;
    }

    int blocks() const {
        return static_cast<int>(blocks_.size());
    }

    int capacity_total() const {
        return triangular(blocks());
    }

    int i2b(int i) const {
        assert(0 <= i && i < n_);
        const double db = (-3.0 + std::sqrt(9.0 + 8.0 * i)) / 2.0;
        return static_cast<int>(std::ceil(db));
    }

    std::pair<int, int> locate(int i) const {
        const int b = i2b(i);
        const int j = i - b * (b + 1) / 2;
        return {b, j};
    }

    T get(int i) const {
        assert(0 <= i && i < n_);
        auto [b, j] = locate(i);
        return blocks_[b][j];
    }

    T set(int i, T x) {
        assert(0 <= i && i < n_);
        auto [b, j] = locate(i);
        const T old = blocks_[b][j];
        blocks_[b][j] = x;
        return old;
    }

    void add(int i, T x) {
        assert(0 <= i && i <= n_);
        const int r = blocks();
        if (triangular(r) < n_ + 1) {
            grow();
        }
        ++n_;
        for (int j = n_ - 1; j > i; --j) {
            set(j, get(j - 1));
        }
        auto [b, off] = locate(i);
        blocks_[b][off] = x;
    }

    void push_back(T x) {
        add(n_, x);
    }

    T remove(int i) {
        assert(0 <= i && i < n_);
        const T x = get(i);
        for (int j = i; j + 1 < n_; ++j) {
            set(j, get(j + 1));
        }
        --n_;
        const int r = blocks();
        if ((r - 2) * (r - 1) / 2 >= n_) {
            shrink();
        }
        return x;
    }

    std::string layout() const {
        std::ostringstream out;
        int global = 0;
        out << "\n";
        for (int b = 0; b < blocks(); ++b) {
            out << "  bloque " << b << " (tam=" << (b + 1) << "): [";
            for (int j = 0; j <= b; ++j) {
                if (global < n_) {
                    out << global << ':' << blocks_[b][j];
                } else {
                    out << '_';
                }
                ++global;
                if (j < b) {
                    out << " | ";
                }
            }
            out << "]\n";
        }
        return out.str();
    }

    void debug_print(std::ostream& out) const {
        out << "size=" << n_ << ", blocks=" << blocks()
            << ", capacidad total=" << capacity_total() << "\n";
        out << layout();
        out << "invariante: el bloque b tiene capacidad b+1 y guarda una porcion contigua logica de la secuencia\n";
    }
};

}  // namespace cc232::pedagogico
