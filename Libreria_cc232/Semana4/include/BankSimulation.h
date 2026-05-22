#pragma once

#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Queue.h"

namespace ods {

// Cliente atendido en una ventanilla
struct Customer {
    int window = -1;          // Ventanilla asignada
    unsigned int time = 0;    // Tiempo restante de atención
};

// Retorna el indice de la cola mas corta
inline int bestWindow(const std::vector<Queue<Customer>>& windows) {
    if (windows.empty()) {
        throw std::invalid_argument("windows must not be empty");
    }

    int minSize = windows[0].size();
    int opt = 0;

    for (int i = 1; i < static_cast<int>(windows.size()); ++i) {
        if (windows[i].size() < minSize) {
            minSize = windows[i].size();
            opt = i;
        }
    }
    return opt;
}

// Estado de la simulacion en un instante
struct BankSimulationStep {
    int now = 0;
    std::vector<std::vector<unsigned int>> queues;
};

// Resultado completo de la simulacion
struct BankSimulationResult {
    int windows = 0;
    int serviceTime = 0;
    int totalArrivals = 0;
    int totalServed = 0;
    std::vector<BankSimulationStep> timeline;
};

// Simula el servicio bancario durante servTime instantes
inline BankSimulationResult simulate(int nWin, int servTime, unsigned int seed = 20260406U) {
    if (nWin <= 0 || servTime < 0) {
        throw std::invalid_argument("invalid simulation parameters");
    }

    // Una cola por ventanilla
    std::vector<Queue<Customer>> windows(static_cast<std::size_t>(nWin));

    // Generador aleatorio
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> arrival(0, nWin);
    std::uniform_int_distribution<int> service(1, 98);

    BankSimulationResult result;
    result.windows = nWin;
    result.serviceTime = servTime;
    result.timeline.reserve(static_cast<std::size_t>(servTime));

    for (int now = 0; now < servTime; ++now) {
        // Llega un nuevo cliente
        if (arrival(rng) != 0) {
            Customer c;
            c.time = static_cast<unsigned int>(service(rng));
            c.window = bestWindow(windows);

            windows[static_cast<std::size_t>(c.window)].enqueue(c);
            ++result.totalArrivals;
        }

        // Atiende una unidad de tiempo en cada ventanilla
        for (int i = 0; i < nWin; ++i) {
            if (!windows[static_cast<std::size_t>(i)].empty()) {
                Customer& front = windows[static_cast<std::size_t>(i)].front();
                if (--front.time == 0) {
                    windows[static_cast<std::size_t>(i)].dequeue();
                    ++result.totalServed;
                }
            }
        }

        // Guardar el estado actual
        BankSimulationStep step;
        step.now = now;
        step.queues.resize(static_cast<std::size_t>(nWin));

        for (int i = 0; i < nWin; ++i) {
            for (const Customer& c : windows[static_cast<std::size_t>(i)].data()) {
                step.queues[static_cast<std::size_t>(i)].push_back(c.time);
            }
        }

        result.timeline.push_back(std::move(step));
    }

    return result;
}

} // namespace ods
