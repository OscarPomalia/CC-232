#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "HashCode.h"
#include "HashStats.h"
#include "PrimeUtils.h"
#include "RehashPolicy.h"

namespace ods {

template <class T>
class DoubleHashTable {
    enum class State { Empty, Filled, Deleted };
    struct Slot { std::optional<T> value; State state = State::Empty; };

    std::vector<Slot> table_;
    std::size_t size_ = 0;
    std::size_t occupied_ = 0;
    RehashPolicy policy_{};
    mutable HashStats stats_{};

    std::size_t h1(const T& x) const { return hashCode(x) % table_.size(); }
    std::size_t h2(const T& x) const { return 1 + (hashCode(x) % (table_.size() - 1)); }
    std::size_t index(const T& x, std::size_t step) const { return (h1(x) + step * h2(x)) % table_.size(); }

    void rehash(std::size_t requested) {
        auto old = std::move(table_);
        table_.assign(nextPrime(requested), Slot{});
        size_ = occupied_ = 0;
        ++stats_.rehashes;
        for (const auto& s : old) {
            if (s.state == State::Filled && s.value) insertWithoutStats(*s.value);
        }
    }

    void insertWithoutStats(const T& x) {
        for (std::size_t step = 0; step < table_.size(); ++step) {
            auto i = index(x, step);
            if (table_[i].state != State::Filled) {
                if (table_[i].state == State::Empty) ++occupied_;
                table_[i].value = x;
                table_[i].state = State::Filled;
                ++size_;
                return;
            }
        }
    }

public:
    explicit DoubleHashTable(std::size_t c = 11, RehashPolicy policy = {})
        : table_(nextPrime(std::max<std::size_t>(policy.minCapacity, c))), policy_(policy) {
        policy_.validate();
    }

    bool add(const T& x) {
        if (contains(x)) return false;
        if (policy_.shouldCleanOrGrow(occupied_ + 1, table_.size()) || policy_.shouldGrow(size_ + 1, table_.size())) {
            rehash(nextPrime(policy_.grownCapacity(table_.size())));
        }
        bool collided = false;
        for (std::size_t step = 0; step < table_.size(); ++step) {
            auto i = index(x, step);
            if (table_[i].state == State::Filled) {
                collided = true;
                continue;
            }
            if (table_[i].state == State::Empty) ++occupied_;
            table_[i].value = x;
            table_[i].state = State::Filled;
            ++size_;
            ++stats_.insertions;
            if (collided) ++stats_.collisions;
            stats_.recordProbe(step + 1);
            return true;
        }
        rehash(nextPrime(policy_.grownCapacity(table_.size())));
        return add(x);
    }

    bool contains(const T& x) const {
        for (std::size_t step = 0; step < table_.size(); ++step) {
            auto i = index(x, step);
            if (table_[i].state == State::Empty) {
                ++stats_.failedSearches;
                stats_.recordProbe(step + 1);
                return false;
            }
            if (table_[i].state == State::Filled && table_[i].value && *table_[i].value == x) {
                ++stats_.successfulSearches;
                stats_.recordProbe(step + 1);
                return true;
            }
        }
        ++stats_.failedSearches;
        stats_.recordProbe(table_.size());
        return false;
    }

    std::optional<T> find(const T& x) const { return contains(x) ? std::optional<T>(x) : std::nullopt; }

    bool remove(const T& x) {
        for (std::size_t step = 0; step < table_.size(); ++step) {
            auto i = index(x, step);
            if (table_[i].state == State::Empty) {
                ++stats_.failedSearches;
                stats_.recordProbe(step + 1);
                return false;
            }
            if (table_[i].state == State::Filled && table_[i].value && *table_[i].value == x) {
                table_[i].value.reset();
                table_[i].state = State::Deleted;
                --size_;
                ++stats_.removals;
                stats_.recordProbe(step + 1);
                stats_.tombstones = tombstoneCount();
                if (policy_.shouldShrink(size_, table_.size())) rehash(nextPrime(policy_.shrunkCapacity(table_.size())));
                return true;
            }
        }
        return false;
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return table_.size(); }
    std::size_t tombstoneCount() const { return occupied_ - size_; }
    double loadFactor() const { return static_cast<double>(size_) / static_cast<double>(capacity()); }
    double occupiedFactor() const { return static_cast<double>(occupied_) / static_cast<double>(capacity()); }
    HashStats stats() const { auto s = stats_; s.tombstones = tombstoneCount(); return s; }
    void resetStats() const { stats_.clearRuntimeCounters(); }
};

}  // namespace ods
