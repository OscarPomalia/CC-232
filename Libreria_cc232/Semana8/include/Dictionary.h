#pragma once
#include <cstddef>
#include <optional>
namespace ods {
template <typename K, typename V>
struct Dictionary {
    virtual ~Dictionary() = default;
    virtual std::size_t size() const = 0;
    virtual bool put(const K& key, const V& value) = 0;
    virtual std::optional<V> get(const K& key) const = 0;
    virtual bool remove(const K& key) = 0;
};
}
