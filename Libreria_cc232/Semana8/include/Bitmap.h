#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace ods {

class Bitmap {
    std::size_t size_{};
    std::vector<std::uint64_t> bits_;

public:
    explicit Bitmap(std::size_t n = 0) {
        reset(n);
    }

    void reset(std::size_t n) {
        size_ = n;
        bits_.assign((n + 63) / 64, 0ULL);
    }

    void set(std::size_t i) {
        bits_[i / 64] |= (1ULL << (i % 64));
    }

    void clear(std::size_t i) {
        bits_[i / 64] &= ~(1ULL << (i % 64));
    }

    bool test(std::size_t i) const {
        return (bits_[i / 64] >> (i % 64)) & 1ULL;
    }

    std::size_t count() const {
        std::size_t c = 0;

        for (auto w : bits_) {
            while (w) {
                w &= w - 1;
                ++c;
            }
        }

        return c;
    }
};

}  // namespace ods
