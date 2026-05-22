#pragma once

#include <algorithm>
#include <cstddef>
#include <ostream>

namespace ods {

struct HashStats {
    std::size_t insertions = 0;
    std::size_t successfulSearches = 0;
    std::size_t failedSearches = 0;
    std::size_t removals = 0;
    std::size_t collisions = 0;
    std::size_t totalProbes = 0;
    std::size_t maxProbeLength = 0;
    std::size_t rehashes = 0;
    std::size_t tombstones = 0;

    void recordProbe(std::size_t probes) {
        totalProbes += probes;
        maxProbeLength = std::max(maxProbeLength, probes);
    }

    double averageProbeLength() const {
        const std::size_t ops = insertions + successfulSearches + failedSearches + removals;
        return ops == 0 ? 0.0 : static_cast<double>(totalProbes) / static_cast<double>(ops);
    }

    void clearRuntimeCounters() {
        insertions = successfulSearches = failedSearches = removals = 0;
        collisions = totalProbes = maxProbeLength = 0;
    }
};

inline std::ostream& operator<<(std::ostream& os, const HashStats& s) {
    os << "insertions=" << s.insertions
       << ", successfulSearches=" << s.successfulSearches
       << ", failedSearches=" << s.failedSearches
       << ", removals=" << s.removals
       << ", collisions=" << s.collisions
       << ", totalProbes=" << s.totalProbes
       << ", maxProbeLength=" << s.maxProbeLength
       << ", averageProbeLength=" << s.averageProbeLength()
       << ", rehashes=" << s.rehashes
       << ", tombstones=" << s.tombstones;
    return os;
}

}  // namespace ods
