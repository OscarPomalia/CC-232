#include <chrono>
#include <iostream>
#include "LinearHashTable.h"
#include "RehashPolicy.h"

int main() {
    for (double maxLoad : {0.45, 0.65, 0.85}) {
        ods::RehashPolicy p;
        p.maxLoad = maxLoad;
        p.maxOccupiedLoad = std::min(0.95, maxLoad + 0.10);
        ods::LinearHashTable<int> t(8, p);

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 5000; ++i) t.add(i * 37);
        for (int i = 0; i < 5000; ++i) t.contains(i * 37);
        auto stop = std::chrono::high_resolution_clock::now();

        auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        std::cout << "maxLoad=" << maxLoad
                  << " capacity=" << t.capacity()
                  << " load=" << t.loadFactor()
                  << " maxProbe=" << t.stats().maxProbeLength
                  << " avgProbe=" << t.stats().averageProbeLength()
                  << " time_us=" << us << "\n";
    }
}
