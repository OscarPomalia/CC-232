#include "line_stats.h"

#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    const auto summary = cc232::summarize_lines(lines);
    std::cout << "total_lineas=" << summary.total_lines << '\n';
    std::cout << "lineas_no_vacias=" << summary.nonempty_lines << '\n';
    std::cout << "total_caracteres=" << summary.total_chars << '\n';
    std::cout << "longitud_linea_mas_larga=" << summary.longest_line_length << '\n';
    std::cout << "lineas_mayores_a_10=" << cc232::count_lines_longer_than(lines, 10) << '\n';
    return 0;
}