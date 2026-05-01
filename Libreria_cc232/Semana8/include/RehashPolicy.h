#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace ods {

struct RehashPolicy {
    double maxLoad = 0.70;          // elementos activos / capacidad
    double minLoad = 0.125;         // umbral de contracción
    double maxOccupiedLoad = 0.82;  // activos + borrados perezosos / capacidad
    std::size_t minCapacity = 8;
    double growthFactor = 2.0;
    double shrinkFactor = 0.5;

    void validate() const {
        if (!(0.0 < minLoad && minLoad < maxLoad && maxLoad < 1.0)) {
            throw std::invalid_argument("RehashPolicy: se requiere 0 < minLoad < maxLoad < 1");
        }
        if (!(maxLoad <= maxOccupiedLoad && maxOccupiedLoad < 1.0)) {
            throw std::invalid_argument("RehashPolicy: se requiere maxLoad <= maxOccupiedLoad < 1");
        }
        if (minCapacity < 2 || growthFactor <= 1.0 || !(0.0 < shrinkFactor && shrinkFactor < 1.0)) {
            throw std::invalid_argument("RehashPolicy: capacidad o factores invalidos");
        }
    }

    bool shouldGrow(std::size_t active, std::size_t capacity) const {
        return capacity == 0 || static_cast<double>(active) / capacity > maxLoad;
    }

    bool shouldCleanOrGrow(std::size_t occupied, std::size_t capacity) const {
        return capacity == 0 || static_cast<double>(occupied) / capacity > maxOccupiedLoad;
    }

    bool shouldShrink(std::size_t active, std::size_t capacity) const {
        return capacity > minCapacity && static_cast<double>(active) / capacity < minLoad;
    }

    std::size_t grownCapacity(std::size_t capacity) const {
        return std::max<std::size_t>(minCapacity, static_cast<std::size_t>(capacity * growthFactor) + 1);
    }

    std::size_t shrunkCapacity(std::size_t capacity) const {
        return std::max<std::size_t>(minCapacity, static_cast<std::size_t>(capacity * shrinkFactor));
    }
};

}  // namespace ods
