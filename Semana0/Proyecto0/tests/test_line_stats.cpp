#include "line_stats.h"
#include "mini_test.h"

#include <string>
#include <vector>

namespace {

void test_summary_basic() {
    const std::vector<std::string> lines{"hola", "", "algoritmos", "C++17"};
    const auto summary = cc232::summarize_lines(lines);

    cc232::test::expect(summary.total_lines == 4, "total_lines debe ser 4");
    cc232::test::expect(summary.nonempty_lines == 3, "nonempty_lines debe ser 3");
    cc232::test::expect(summary.total_chars == 19, "total_chars debe ser 19");
    cc232::test::expect(summary.longest_line_length == 10, "la línea mas larga debe tener longitud 10");
}

void test_count_lines_longer_than() {
    const std::vector<std::string> lines{"a", "abcd", "abcdef", ""};
    cc232::test::expect(cc232::count_lines_longer_than(lines, 3) == 2, "dos lineas deben ser mas largas que 3");
    cc232::test::expect(cc232::count_lines_longer_than(lines, 10) == 0, "ninguna linea debe ser mas larga que 10");
}

void test_empty_input() {
    const std::vector<std::string> lines{};
    const auto summary = cc232::summarize_lines(lines);
    cc232::test::expect(summary.total_lines == 0, "la entrada vacia debe tener cero lineas");
    cc232::test::expect(summary.nonempty_lines == 0, "la entrada vacia debe tener cero lineas no vacias");
    cc232::test::expect(summary.total_chars == 0, "la entrada vacia debe tener cero caracteres");
    cc232::test::expect(summary.longest_line_length == 0, "la entrada vacia debe tener longitud maxima cero");
}

}  // namespace

int main() {
    test_summary_basic();
    test_count_lines_longer_than();
    test_empty_input();
    cc232::test::pass();
    return 0;
}
