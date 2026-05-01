#pragma once

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "Bitmap.h"
#include "Dictionary.h"
#include "Entry.h"
#include "HashCode.h"
#include "HashStats.h"
#include "PrimeUtils.h"
#include "RehashPolicy.h"

namespace ods {

template <typename K, typename V>
class HashtableOA : public Dictionary<K, V> {
    std::vector<std::optional<Entry<K, V>>> table_;
    Bitmap removed_;
    std::size_t size_ = 0;
    RehashPolicy policy_{};
    mutable HashStats stats_{};

    struct Probe { std::size_t index{}; bool found{}; std::size_t probes{}; };

    Probe probe4Hit(const K& k) const {
        std::size_t start = hashCode(k) % table_.size();
        std::size_t probes = 1;

        for (std::size_t step = 0; step < table_.size(); ++step, ++probes) {
            std::size_t i = (start + step) % table_.size();
            if (table_[i] && table_[i]->key == k) return {i, true, probes};
            if (!table_[i] && !removed_.test(i)) return {i, false, probes};
        }
        return {start, false, probes};
    }

    std::size_t probe4Free(const K& k, std::size_t& probes, bool& collided) const {
        std::size_t start = hashCode(k) % table_.size();
        for (std::size_t step = 0; step < table_.size(); ++step) {
            std::size_t i = (start + step) % table_.size();
            probes = step + 1;
            if (!table_[i]) return i;
            collided = true;
        }
        return start;
    }

    void rehash(std::size_t requestedCapacity = 0) {
        auto old = std::move(table_);
        std::size_t target = requestedCapacity == 0
            ? policy_.grownCapacity(old.size())
            : requestedCapacity;
        target = nextPrime(std::max<std::size_t>(policy_.minCapacity, target));

        table_.assign(target, std::nullopt);
        removed_.reset(target);
        size_ = 0;
        ++stats_.rehashes;

        for (const auto& slot : old) {
            if (slot) insertWithoutStats(slot->key, slot->value);
        }
    }

    void insertWithoutStats(const K& k, const V& v) {
        std::size_t probes = 0;
        bool collided = false;
        const std::size_t i = probe4Free(k, probes, collided);
        table_[i] = Entry<K, V>{k, v};
        removed_.clear(i);
        ++size_;
    }

public:
    explicit HashtableOA(std::size_t c = 11, RehashPolicy policy = {})
        : table_(nextPrime(std::max<std::size_t>(policy.minCapacity, c))),
          removed_(table_.size()),
          policy_(policy) {
        policy_.validate();
    }

    std::size_t size() const override { return size_; }
    std::size_t capacity() const { return table_.size(); }
    std::size_t tombstoneCount() const { return removed_.count(); }

    bool put(const K& k, const V& v) override {
        auto hit = probe4Hit(k);
        stats_.recordProbe(hit.probes);
        if (hit.found) {
            ++stats_.failedSearches;
            return false;
        }

        if (policy_.shouldCleanOrGrow(size_ + removed_.count() + 1, table_.size()) ||
            policy_.shouldGrow(size_ + 1, table_.size())) {
            rehash(policy_.grownCapacity(table_.size()));
        }

        std::size_t probes = 0;
        bool collided = false;
        const std::size_t i = probe4Free(k, probes, collided);
        if (collided) ++stats_.collisions;

        table_[i] = Entry<K, V>{k, v};
        removed_.clear(i);
        ++size_;
        ++stats_.insertions;
        stats_.recordProbe(probes);
        return true;
    }

    std::optional<V> get(const K& k) const override {
        auto hit = probe4Hit(k);
        stats_.recordProbe(hit.probes);
        if (hit.found) {
            ++stats_.successfulSearches;
            return table_[hit.index]->value;
        }
        ++stats_.failedSearches;
        return std::nullopt;
    }

    bool remove(const K& k) override {
        auto hit = probe4Hit(k);
        stats_.recordProbe(hit.probes);
        if (!hit.found) {
            ++stats_.failedSearches;
            return false;
        }

        table_[hit.index].reset();
        removed_.set(hit.index);
        --size_;
        ++stats_.removals;
        stats_.tombstones = removed_.count();

        if (policy_.shouldShrink(size_, table_.size())) {
            rehash(policy_.shrunkCapacity(table_.size()));
        } else if (policy_.shouldCleanOrGrow(size_ + removed_.count(), table_.size())) {
            rehash(table_.size());
        }
        return true;
    }

    double loadFactor() const {
        return capacity() == 0 ? 0.0 : static_cast<double>(size_) / static_cast<double>(capacity());
    }

    double occupiedFactor() const {
        return capacity() == 0 ? 0.0 : static_cast<double>(size_ + removed_.count()) / static_cast<double>(capacity());
    }

    HashStats stats() const {
        auto s = stats_;
        s.tombstones = removed_.count();
        return s;
    }
    void resetStats() const { stats_.clearRuntimeCounters(); }
};

}  // namespace ods
