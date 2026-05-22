#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "HashCode.h"
#include "HashStats.h"
#include "RehashPolicy.h"

namespace ods {

template <class T>
class LinearHashTable {
    enum class State { Empty, Filled, Deleted };

    struct Slot {
        std::optional<T> value;
        State state = State::Empty;
    };

    std::size_t size_ = 0;      // elementos activos
    std::size_t occupied_ = 0;  // activos + Deleted
    std::vector<Slot> table_;
    RehashPolicy policy_{};
    mutable HashStats stats_{};

    static std::size_t norm(std::size_t c) {
        std::size_t m = 8;
        while (m < c) m <<= 1;
        return m;
    }

    static std::size_t next(std::size_t i, std::size_t m) { return (i + 1) & (m - 1); }
    static std::size_t idx(const T& x, std::size_t m) { return hashCode(x) & (m - 1); }

    std::optional<std::size_t> findIndex(const T& x) const {
        std::size_t i = idx(x, table_.size());
        std::size_t probes = 1;

        while (table_[i].state != State::Empty && probes <= table_.size()) {
            if (table_[i].state == State::Filled && table_[i].value && *table_[i].value == x) {
                ++stats_.successfulSearches;
                stats_.recordProbe(probes);
                return i;
            }
            i = next(i, table_.size());
            ++probes;
        }

        ++stats_.failedSearches;
        stats_.recordProbe(probes);
        return std::nullopt;
    }

    void rehash(std::size_t m) {
        auto old = std::move(table_);
        table_.assign(norm(std::max<std::size_t>(policy_.minCapacity, m)), Slot{});
        size_ = 0;
        occupied_ = 0;
        ++stats_.rehashes;

        for (const auto& s : old) {
            if (s.state == State::Filled && s.value) {
                insertWithoutStats(*s.value);
            }
        }
    }

    void insertWithoutStats(const T& x) {
        std::size_t i = idx(x, table_.size());
        while (table_[i].state == State::Filled) {
            i = next(i, table_.size());
        }
        if (table_[i].state == State::Empty) ++occupied_;
        table_[i].value = x;
        table_[i].state = State::Filled;
        ++size_;
    }

public:
    explicit LinearHashTable(std::size_t c = 8, RehashPolicy policy = {})
        : table_(norm(std::max<std::size_t>(policy.minCapacity, c))), policy_(policy) {
        policy_.validate();
    }

    bool add(const T& x) {
        if (contains(x)) return false;

        if (policy_.shouldCleanOrGrow(occupied_ + 1, table_.size()) ||
            policy_.shouldGrow(size_ + 1, table_.size())) {
            rehash(policy_.grownCapacity(table_.size()));
        }

        std::size_t i = idx(x, table_.size());
        std::size_t probes = 1;
        bool collided = false;

        while (table_[i].state == State::Filled) {
            collided = true;
            i = next(i, table_.size());
            ++probes;
        }

        if (collided) ++stats_.collisions;
        if (table_[i].state == State::Empty) ++occupied_;

        table_[i].value = x;
        table_[i].state = State::Filled;
        ++size_;
        ++stats_.insertions;
        stats_.recordProbe(probes);
        return true;
    }

    bool contains(const T& x) const { return findIndex(x).has_value(); }

    std::optional<T> find(const T& x) const {
        auto p = findIndex(x);
        return p ? table_[*p].value : std::nullopt;
    }

    bool remove(const T& x) {
        auto p = findIndex(x);
        if (!p) return false;

        table_[*p].value.reset();
        table_[*p].state = State::Deleted;
        --size_;
        ++stats_.removals;
        stats_.tombstones = tombstoneCount();

        if (policy_.shouldShrink(size_, table_.size())) {
            rehash(policy_.shrunkCapacity(table_.size()));
        } else if (policy_.shouldCleanOrGrow(occupied_, table_.size())) {
            rehash(table_.size());  // limpieza de marcas Deleted sin crecer
        }
        return true;
    }

    void clear() {
        table_.assign(norm(policy_.minCapacity), Slot{});
        size_ = occupied_ = 0;
        stats_ = HashStats{};
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return table_.size(); }
    std::size_t occupied() const { return occupied_; }
    std::size_t tombstoneCount() const { return occupied_ - size_; }

    double loadFactor() const {
        return capacity() == 0 ? 0.0 : static_cast<double>(size_) / static_cast<double>(capacity());
    }

    double occupiedFactor() const {
        return capacity() == 0 ? 0.0 : static_cast<double>(occupied_) / static_cast<double>(capacity());
    }

    HashStats stats() const {
        auto s = stats_;
        s.tombstones = tombstoneCount();
        return s;
    }
    void resetStats() const { stats_.clearRuntimeCounters(); }
};

}  // namespace ods
