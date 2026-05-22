#include <iostream>

#include "BankSimulation.h"

int main() {
    const auto result = ods::simulate(3, 10, 12345U);
    std::cout << "Llegadas = " << result.totalArrivals
              << ", atendidos = " << result.totalServed << "\n";

    for (const auto& step : result.timeline) {
        std::cout << "t=" << step.now << ':';
        for (const auto& q : step.queues) {
            std::cout << " [";
            for (std::size_t i = 0; i < q.size(); ++i) {
                if (i) std::cout << ',';
                std::cout << q[i];
            }
            std::cout << ']';
        }
        std::cout << '\n';
    }
    return 0;
}