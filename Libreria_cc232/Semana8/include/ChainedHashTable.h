#pragma once

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "ArrayStack.h"
#include "HashCode.h"
#include "HashStats.h"
#include "RehashPolicy.h"
#include "array.h"

namespace ods {

template <class T>
class ChainedHashTable {
    using List = ArrayStack<T>;

    array<List> table_;
    std::size_t size_ = 0;
    RehashPolicy policy_{};
    mutable HashStats stats_{};

    std::size_t idx(const T& x) const {
        return hashCode(x) % static_cast<std::size_t>(table_.length);
    }

    void rehash(std::size_t m) {
        array<List> old = std::move(table_);
        table_ = array<List>(static_cast<int>(std::max<std::size_t>(policy_.minCapacity, m)));
        size_ = 0;
        ++stats_.rehashes;

        for (int i = 0; i < old.length; ++i) {
            for (int j = 0; j < old[i].size(); ++j) {
                insertWithoutStats(old[i].get(j));
            }
        }
    }

    void insertWithoutStats(const T& x) {
        auto& b = table_[static_cast<int>(idx(x))];
        b.add(x);
        ++size_;
    }

public:
    explicit ChainedHashTable(std::size_t buckets = 8, RehashPolicy policy = {})
        : table_(static_cast<int>(std::max<std::size_t>(policy.minCapacity, buckets))),
          policy_(policy) {
        policy_.validate();
    }

    bool add(const T& x) {
        if (policy_.shouldGrow(size_ + 1, static_cast<std::size_t>(table_.length))) {
            rehash(policy_.grownCapacity(static_cast<std::size_t>(table_.length)));
        }

        auto& b = table_[static_cast<int>(idx(x))];
        std::size_t probes = 1;
        if (b.size() > 0) {
            ++stats_.collisions;
        }

        for (int i = 0; i < b.size(); ++i, ++probes) {
            if (b.get(i) == x) {
                stats_.recordProbe(probes);
                ++stats_.failedSearches;
                return false;
            }
        }

        b.add(x);
        ++size_;
        ++stats_.insertions;
        stats_.recordProbe(probes);
        return true;
    }

    bool contains(const T& x) const {
        const auto& b = table_[static_cast<int>(idx(x))];
        std::size_t probes = 1;

        for (int i = 0; i < b.size(); ++i, ++probes) {
            if (b.get(i) == x) {
                ++stats_.successfulSearches;
                stats_.recordProbe(probes);
                return true;
            }
        }

        ++stats_.failedSearches;
        stats_.recordProbe(probes);
        return false;
    }

    std::optional<T> find(const T& x) const {
        return contains(x) ? std::optional<T>(x) : std::nullopt;
    }

    bool remove(const T& x) {
        auto& b = table_[static_cast<int>(idx(x))];
        std::size_t probes = 1;

        for (int i = 0; i < b.size(); ++i, ++probes) {
            if (b.get(i) == x) {
                b.remove(i);
                --size_;
                ++stats_.removals;
                stats_.recordProbe(probes);

                if (policy_.shouldShrink(size_, static_cast<std::size_t>(table_.length))) {
                    rehash(policy_.shrunkCapacity(static_cast<std::size_t>(table_.length)));
                }
                return true;
            }
        }

        ++stats_.failedSearches;
        stats_.recordProbe(probes);
        return false;
    }

    void clear() {
        table_ = array<List>(static_cast<int>(policy_.minCapacity));
        size_ = 0;
        stats_ = HashStats{};
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return static_cast<std::size_t>(table_.length); }

    double loadFactor() const {
        return capacity() == 0 ? 0.0 : static_cast<double>(size_) / static_cast<double>(capacity());
    }

    std::size_t longestBucket() const {
        std::size_t best = 0;
        for (int i = 0; i < table_.length; ++i) {
            best = std::max(best, static_cast<std::size_t>(table_[i].size()));
        }
        return best;
    }

    HashStats stats() const { return stats_; }
    void resetStats() const { stats_.clearRuntimeCounters(); }
};

}  // namespace ods
