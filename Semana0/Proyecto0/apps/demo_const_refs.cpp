#include "warmup_vector.h"

#include <cstddef>
#include <iostream>
#include <vector>

namespace {

void print_vector(const std::vector<int>& values) {
    std::cout << '{';
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 != values.size()) {
            std::cout << ", ";
        }
    }
    std::cout << '}';
}

}  // namespace

int main() {
    std::vector<int> original{1, 2, 3};

    std::cout << "original = ";
    print_vector(original);
    std::cout << '\n';

    const auto total = cc232::sum_readonly(original);
    std::cout << "suma_lectura(original) = " << total << '\n';

    cc232::append_in_place(original, 4);
    std::cout << "despues de append_in_place(original, 4): ";
    print_vector(original);
    std::cout << '\n';

    const std::vector<int> copied = cc232::appended_copy(original, 99);
    std::cout << "despues de appended_copy(original, 99), original = ";
    print_vector(original);
    std::cout << '\n';

    std::cout << "copia = ";
    print_vector(copied);
    std::cout << '\n';
    return 0;

}