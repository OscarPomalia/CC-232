#ifndef CC232_MINI_BENCH_H
#define CC232_MINI_BENCH_H

#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

namespace cc232::bench {

using Clock = std::chrono::steady_clock;

template <typename Fn>
long long measure_us(Fn&& fn) {
    const auto start = Clock::now();
    std::forward<Fn>(fn)();
    const auto end = Clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template <typename Fn>
double average_us(int trials, Fn&& fn) {
    long long total = 0;
    for (int t = 0; t < trials; ++t) {
        total += measure_us(fn);
    }
    return static_cast<double>(total) / static_cast<double>(trials);
}

inline void print_header(const std::string& title, std::size_t n, int trials) {
    std::cout << title << '\n';
    std::cout << "n = " << n << ", repeticiones = " << trials << '\n';
    std::cout << std::fixed << std::setprecision(2);
}

inline void print_result(const std::string& label, double avg_us) {
    std::cout << std::left << std::setw(30) << label << ": " << avg_us << " us\n";
}

}  // namespace cc232::bench

#endif
