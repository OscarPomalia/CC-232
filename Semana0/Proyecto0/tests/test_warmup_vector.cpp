#include "mini_test.h"
#include "warmup_vector.h"

#include <vector>

namespace {

void test_sum_readonly() {
    const std::vector<int> values{1, 2, 3, 4};
    cc232::test::expect(cc232::sum_readonly(values) == 10, "sum_readonly debe devolver 10");
}

void test_append_in_place_changes_original() {
    std::vector<int> values{10, 20};
    cc232::append_in_place(values, 30);
    cc232::test::expect(values.size() == 3, "append_in_place debe cambiar el tamaño original");
    cc232::test::expect(values.back() == 30, "append_in_place debe agregar 30 al final");
}

void test_appended_copy_preserves_original() {
    std::vector<int> values{10, 20};
    const std::vector<int> copied = cc232::appended_copy(values, 30);

    cc232::test::expect(values.size() == 2, "el vector original debe permanecer sin cambios");
    cc232::test::expect(copied.size() == 3, "el vector copiado debe tener tamaño 3");
    cc232::test::expect(copied.back() == 30, "el vector copiado debe agregar 30 al final");
}

void test_count_greater_than() {
    const std::vector<int> values{2, 5, 8, 1, 9};
    cc232::test::expect(cc232::count_greater_than(values, 4) == 3, "tres valores deben ser mayores que 4");
}

void test_is_strictly_increasing() {
    cc232::test::expect(cc232::is_strictly_increasing({1, 2, 3, 9}), "un vector creciente debe devolver true");
    cc232::test::expect(!cc232::is_strictly_increasing({1, 2, 2, 9}), "valores duplicados deben devolver false");
    cc232::test::expect(!cc232::is_strictly_increasing({4, 3, 2, 1}), "un vector descendente debe devolver false");
}

}  // namespace

int main() {
    test_sum_readonly();
    test_append_in_place_changes_original();
    test_appended_copy_preserves_original();
    test_count_greater_than();
    test_is_strictly_increasing();
    cc232::test::pass();
    return 0;
}