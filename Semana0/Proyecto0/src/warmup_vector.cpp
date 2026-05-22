#include "warmup_vector.h"

namespace cc232 {

int sum_readonly(const std::vector<int>& values) {
    int total = 0;
    for (const int value : values) {
        total += value;
    }
    return total;
}

void append_in_place(std::vector<int>& values, int x) {
    values.push_back(x);
}

std::vector<int> appended_copy(std::vector<int> values, int x) {
    values.push_back(x);
    return values;
}

std::size_t count_greater_than(const std::vector<int>& values, int limit) {
    std::size_t count = 0;
    for (const int value : values) {
        if (value > limit) {
            ++count;
        }
    }
    return count;
}

bool is_strictly_increasing(const std::vector<int>& values) {
    if (values.empty()) {
        return true;
    }

    for (std::size_t i = 1; i < values.size(); ++i) {
        if (!(values[i - 1] < values[i])) {
            return false;
        }
    }
    return true;
}

}  // namespace cc232
