#include <iostream>
#include <vector>
#include "ChainedHashTable.h"
#include "LinearHashTable.h"
#include "QuadraticHashTable.h"
#include "DoubleHashTable.h"
#include "RobinHoodHashTable.h"

int main() {
    std::vector<int> keys;
    for (int i = 0; i < 40; ++i) keys.push_back(i * 8);

    ods::ChainedHashTable<int> chained(8);
    ods::LinearHashTable<int> linear(8);
    ods::QuadraticHashTable<int> quadratic(11);
    ods::DoubleHashTable<int> dbl(11);
    ods::RobinHoodHashTable<int> robin(8);

    for (int x : keys) {
        chained.add(x);
        linear.add(x);
        quadratic.add(x);
        dbl.add(x);
        robin.add(x);
    }

    std::cout << "chained:   load=" << chained.loadFactor() << " longestBucket=" << chained.longestBucket() << " stats={" << chained.stats() << "}\n";
    std::cout << "linear:    load=" << linear.loadFactor() << " occupied=" << linear.occupiedFactor() << " stats={" << linear.stats() << "}\n";
    std::cout << "quadratic: load=" << quadratic.loadFactor() << " occupied=" << quadratic.occupiedFactor() << " stats={" << quadratic.stats() << "}\n";
    std::cout << "double:    load=" << dbl.loadFactor() << " occupied=" << dbl.occupiedFactor() << " stats={" << dbl.stats() << "}\n";
    std::cout << "robinhood: load=" << robin.loadFactor() << " maxDisp=" << robin.maxDisplacement() << " stats={" << robin.stats() << "}\n";
}
