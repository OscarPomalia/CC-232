#pragma once

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

namespace ods {

inline std::uint64_t mix64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

inline std::size_t hashCode(int x) {
    return static_cast<std::size_t>(mix64(static_cast<std::uint32_t>(x)));
}

inline std::size_t hashCode(long long x) {
    return static_cast<std::size_t>(mix64(static_cast<std::uint64_t>(x)));
}

inline std::size_t hashCode(std::size_t x) {
    return static_cast<std::size_t>(mix64(static_cast<std::uint64_t>(x)));
}

inline std::size_t hashCode(const std::string& s) {
    // Variante polinomial rotada, suficiente para laboratorio y portable.
    std::size_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return static_cast<std::size_t>(mix64(static_cast<std::uint64_t>(h)));
}


inline std::size_t hashCode(const char* s) {
    return hashCode(std::string(s ? s : ""));
}

template <typename T>
inline std::size_t hashCode(const T& x) {
    return static_cast<std::size_t>(mix64(static_cast<std::uint64_t>(std::hash<T>{}(x))));
}

template <typename T>
inline void hashCombine(std::size_t& seed, const T& value) {
    seed ^= hashCode(value) + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

inline std::string normalizeToken(std::string s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s) {
        if (std::isalnum(c)) {
            out.push_back(static_cast<char>(std::tolower(c)));
        }
    }
    return out;
}

}  // namespace ods
