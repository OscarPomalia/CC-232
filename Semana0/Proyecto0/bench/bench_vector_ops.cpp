#include "mini_bench.h"

#include <cstddef>
#include <numeric>
#include <vector>

namespace {

void bench_push_back_end(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i));
    }
    volatile long long checksum = std::accumulate(values.begin(), values.end(), 0LL);
    (void)checksum;
}

void bench_insert_begin(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.insert(values.begin(), static_cast<int>(i));
    }
    volatile long long checksum = std::accumulate(values.begin(), values.end(), 0LL);
    (void)checksum;
}

void bench_insert_middle(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        const auto middle = values.begin() + static_cast<std::ptrdiff_t>(values.size() / 2);
        values.insert(middle, static_cast<int>(i));
    }
    volatile long long checksum = std::accumulate(values.begin(), values.end(), 0LL);
    (void)checksum;
}

}  // namespace

int main() {
    constexpr std::size_t n = 20000;
    constexpr int trials = 5;

    const double avg_push_back = cc232::bench::average_us(trials, [=] { bench_push_back_end(n); });
    const double avg_insert_begin = cc232::bench::average_us(trials, [=] { bench_insert_begin(n); });
    const double avg_insert_middle = cc232::bench::average_us(trials, [=] { bench_insert_middle(n); });

    cc232::bench::print_header("Benchmark inicial: vector push_back vs insert", n, trials);
    cc232::bench::print_result("push_back al final", avg_push_back);
    cc232::bench::print_result("insert en begin()", avg_insert_begin);
    cc232::bench::print_result("insert en el medio", avg_insert_middle);
    return 0;
}