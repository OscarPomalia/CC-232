#include <iostream>
#include <string>
#include "sum.h"

namespace {

std::string indent(int depth) {
    return std::string(depth * 2, ' ');
}

int sumI_trace(const int A[], int n) {
    std::cout << "[sumI_trace] Invariante: antes de cada iteracion, acc = suma(A[0..i-1])\n";
    int acc = 0;
    for (int i = 0; i < n; ++i) {
        std::cout << "  i=" << i << ": acc=" << acc
                  << ", se agrega A[" << i << "]=" << A[i] << "\n";
        acc += A[i];
    }
    std::cout << "  fin: acc=" << acc << "\n";
    return acc;
}

int sum_dc_trace(const int A[], int lo, int hi, int depth = 0) {
    std::cout << indent(depth) << "sum([" << lo << ", " << hi << "))";
    if (hi <= lo) {
        std::cout << " -> intervalo vacio, retorna 0\n";
        return 0;
    }
    if (hi - lo == 1) {
        std::cout << " -> caso base, retorna A[" << lo << "]=" << A[lo] << "\n";
        return A[lo];
    }
    const int mi = lo + (hi - lo) / 2;
    std::cout << " -> se parte en [" << lo << ", " << mi << ") y [" << mi << ", " << hi << ")\n";
    const int izq = sum_dc_trace(A, lo, mi, depth + 1);
    const int der = sum_dc_trace(A, mi, hi, depth + 1);
    std::cout << indent(depth) << "combinar: " << izq << " + " << der
              << " = " << (izq + der) << "\n";
    return izq + der;
}

void print_array(const int A[], int n) {
    std::cout << "A = [";
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << (i + 1 < n ? ", " : "]\n");
    }
}

}  // namespace

int main() {
    int a[] = {1, 2, 3, 4, 5};
    const int n = static_cast<int>(sizeof(a) / sizeof(a[0]));

    print_array(a, n);

    std::cout << "\n= Version iterativa de Deng\n";
    std::cout << "sumI(a, n) = " << sumI(a, n) << "\n";
    std::cout << "\n=Trazado pedagogico de la version iterativa\n";
    std::cout << "resultado = " << sumI_trace(a, n) << "\n";

    std::cout << "\n=Version recursiva lineal de Deng\n";
    std::cout << "sum(a, n) = " << sum(a, n) << "\n";

    std::cout << "\n=Version divide y venceras de Deng\n";
    std::cout << "sum(a, 0, n) = " << sum(a, 0, n) << "\n";

    std::cout << "\n=Trazado pedagogico de divide y venceras\n";
    std::cout << "resultado = " << sum_dc_trace(a, 0, n) << "\n";

    std::cout << "\nNota: el trazado pedagogico define sum([lo, hi)) = 0 si hi <= lo.\n";
    std::cout << "La implementacion original de Deng usada por el curso asume n > 0 en el caso divide y venceras.\n";
    return 0;
}
