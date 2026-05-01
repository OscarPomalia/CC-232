#pragma once

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "HashCode.h"
#include "HashStats.h"
#include "RehashPolicy.h"

namespace ods {

template <class T>
class RobinHoodHashTable {
    struct Slot {
        std::optional<T> value;
        bool occupied = false;
    };

    std::vector<Slot> table_;
    std::size_t size_ = 0;
    RehashPolicy policy_{};
    mutable HashStats stats_{};

    static std::size_t norm(std::size_t c) {
        std::size_t m = 8;
        while (m < c) m <<= 1;
        return m;
    }

    static std::size_t next(std::size_t i, std::size_t m) { return (i + 1) & (m - 1); }
    static std::size_t home(const T& x, std::size_t m) { return hashCode(x) & (m - 1); }

    std::size_t distanceAt(std::size_t i) const {
        return (i + table_.size() - home(*table_[i].value, table_.size())) & (table_.size() - 1);
    }

    void rehash(std::size_t requested) {
        auto old = std::move(table_);
        table_.assign(norm(std::max<std::size_t>(policy_.minCapacity, requested)), Slot{});
        size_ = 0;
        ++stats_.rehashes;
        for (const auto& s : old) {
            if (s.occupied && s.value) insertWithoutStats(*s.value);
        }
    }

    void insertWithoutStats(T x) {
        std::size_t i = home(x, table_.size());
        std::size_t dist = 0;
        while (true) {
            if (!table_[i].occupied) {
                table_[i].value = std::move(x);
                table_[i].occupied = true;
                ++size_;
                return;
            }
            std::size_t curDist = distanceAt(i);
            if (curDist < dist) {
                std::swap(x, *table_[i].value);
                dist = curDist;
            }
            i = next(i, table_.size());
            ++dist;
        }
    }

    std::optional<std::size_t> findIndex(const T& x) const {
        std::size_t i = home(x, table_.size());
        std::size_t dist = 0;
        std::size_t probes = 1;
        while (table_[i].occupied) {
            const std::size_t curDist = distanceAt(i);
            if (curDist < dist) {
                ++stats_.failedSearches;
                stats_.recordProbe(probes);
                return std::nullopt;
            }
            if (*table_[i].value == x) {
                ++stats_.successfulSearches;
                stats_.recordProbe(probes);
                return i;
            }
            i = next(i, table_.size());
            ++dist;
            ++probes;
        }
        ++stats_.failedSearches;
        stats_.recordProbe(probes);
        return std::nullopt;
    }

    void backwardShiftDelete(std::size_t hole) {
        std::size_t i = next(hole, table_.size());
        while (table_[i].occupied && distanceAt(i) > 0) {
            table_[hole].value = std::move(table_[i].value);
            table_[hole].occupied = true;
            hole = i;
            i = next(i, table_.size());
        }
        table_[hole].value.reset();
        table_[hole].occupied = false;
    }

public:
    explicit RobinHoodHashTable(std::size_t c = 8, RehashPolicy policy = {})
        : table_(norm(std::max<std::size_t>(policy.minCapacity, c))), policy_(policy) {
        policy_.maxLoad = std::min(policy_.maxLoad, 0.85);
        policy_.validate();
    }

    bool add(T x) {
        if (policy_.shouldGrow(size_ + 1, table_.size())) {
            rehash(policy_.grownCapacity(table_.size()));
        }

        std::size_t i = home(x, table_.size());
        std::size_t dist = 0;
        std::size_t probes = 1;
        bool collided = false;

        while (true) {
            if (!table_[i].occupied) {
                table_[i].value = std::move(x);
                table_[i].occupied = true;
                ++size_;
                ++stats_.insertions;
                if (collided) ++stats_.collisions;
                stats_.recordProbe(probes);
                return true;
            }
            if (*table_[i].value == x) {
                ++stats_.failedSearches;
                stats_.recordProbe(probes);
                return false;
            }
            collided = true;
            const std::size_t curDist = distanceAt(i);
            if (curDist < dist) {
                std::swap(x, *table_[i].value);
                dist = curDist;
            }
            i = next(i, table_.size());
            ++dist;
            ++probes;
        }
    }

    bool contains(const T& x) const { return findIndex(x).has_value(); }
    std::optional<T> find(const T& x) const { return contains(x) ? std::optional<T>(x) : std::nullopt; }

    bool remove(const T& x) {
        auto p = findIndex(x);
        if (!p) return false;
        backwardShiftDelete(*p);
        --size_;
        ++stats_.removals;
        if (policy_.shouldShrink(size_, table_.size())) rehash(policy_.shrunkCapacity(table_.size()));
        return true;
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return table_.size(); }
    double loadFactor() const { return static_cast<double>(size_) / static_cast<double>(capacity()); }
    std::size_t maxDisplacement() const {
        std::size_t best = 0;
        for (std::size_t i = 0; i < table_.size(); ++i) {
            if (table_[i].occupied) best = std::max(best, distanceAt(i));
        }
        return best;
    }
    HashStats stats() const { return stats_; }
    void resetStats() const { stats_.clearRuntimeCounters(); }
};

}  // namespace ods
