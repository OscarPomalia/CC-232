#pragma once

#include <cstddef>
#include <cstdint>
#include <random>
#include <stdexcept>

#include "HashCode.h"
#include "PrimeUtils.h"

namespace ods {

// Familia universal estilo MAD: h(x) = ((a * code(x) + b) mod p) mod m.
// Se usa para discutir hashing con datos adversariales y para comparar con hashCode fijo.
class UniversalHash {
    std::uint64_t a_ = 1;
    std::uint64_t b_ = 0;
    std::uint64_t p_ = 4294967311ULL;  // primo mayor que 2^32

public:
    UniversalHash() = default;

    explicit UniversalHash(std::uint64_t seed, std::uint64_t prime = 4294967311ULL)
        : p_(prime) {
        if (p_ < 3 || !isPrime(static_cast<std::size_t>(p_))) {
            throw std::invalid_argument("UniversalHash: p debe ser primo");
        }
        std::mt19937_64 rng(seed);
        std::uniform_int_distribution<std::uint64_t> distA(1, p_ - 1);
        std::uniform_int_distribution<std::uint64_t> distB(0, p_ - 1);
        a_ = distA(rng);
        b_ = distB(rng);
    }

    template <typename T>
    std::size_t operator()(const T& key, std::size_t m) const {
        if (m == 0) {
            throw std::invalid_argument("UniversalHash: capacidad cero");
        }
        const std::uint64_t x = static_cast<std::uint64_t>(hashCode(key)) % p_;
        return static_cast<std::size_t>(((a_ * x + b_) % p_) % m);
    }

    std::uint64_t a() const { return a_; }
    std::uint64_t b() const { return b_; }
    std::uint64_t p() const { return p_; }
};

}  // namespace ods
