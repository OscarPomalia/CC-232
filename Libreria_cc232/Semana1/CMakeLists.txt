cmake_minimum_required(VERSION 3.20)

add_library(sem1_algorithms STATIC
  "src/sum.cpp"
  "src/power.cpp"
  "src/fibonacci.cpp"
  "src/count_ones.cpp"
  "src/max_algorithms.cpp"
  "src/bubble_sort.cpp"
  "src/reverse_utils.cpp"
  "src/gcd.cpp"
  "src/hanoi.cpp"
)

target_include_directories(sem1_algorithms PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(sem1_demo_sum "demos/demo_sum.cpp")
target_link_libraries(sem1_demo_sum PRIVATE sem1_algorithms)

add_executable(sem1_demo_power "demos/demo_power.cpp")
target_link_libraries(sem1_demo_power PRIVATE sem1_algorithms)

add_executable(sem1_demo_fibonacci "demos/demo_fibonacci.cpp")
target_link_libraries(sem1_demo_fibonacci PRIVATE sem1_algorithms)

add_executable(sem1_demo_sum_explicado "demos/demo_sum_explicado.cpp")
target_link_libraries(sem1_demo_sum_explicado PRIVATE sem1_algorithms)

add_executable(sem1_demo_adt_secuencia "demos/demo_adt_secuencia.cpp")

add_executable(sem1_demo_bubblesort "demos/demo_bubblesort.cpp")
target_link_libraries(sem1_demo_bubblesort PRIVATE sem1_algorithms)

add_executable(sem1_demo_maximos "demos/demo_maximos.cpp")
target_link_libraries(sem1_demo_maximos PRIVATE sem1_algorithms)

add_executable(sem1_demo_countones "demos/demo_countones.cpp")
target_link_libraries(sem1_demo_countones PRIVATE sem1_algorithms)

add_executable(sem1_demo_reverse_shift "demos/demo_reverse_shift.cpp")
target_link_libraries(sem1_demo_reverse_shift PRIVATE sem1_algorithms)

add_executable(sem1_demo_gcd "demos/demo_gcd.cpp")
target_link_libraries(sem1_demo_gcd PRIVATE sem1_algorithms)

add_executable(sem1_demo_hanoi "demos/demo_hanoi.cpp")
target_link_libraries(sem1_demo_hanoi PRIVATE sem1_algorithms)

add_executable(sem1_test_public "pruebas_publicas/test_public_week1.cpp")
target_link_libraries(sem1_test_public PRIVATE sem1_algorithms)

add_executable(sem1_test_public_extra "pruebas_publicas/test_public_week1_extra.cpp")
target_link_libraries(sem1_test_public_extra PRIVATE sem1_algorithms)

add_executable(sem1_test_internal "pruebas_internas/test_internal_week1.cpp")
target_link_libraries(sem1_test_internal PRIVATE sem1_algorithms)

add_executable(sem1_test_internal_extra "pruebas_internas/test_internal_week1_extra.cpp")
target_link_libraries(sem1_test_internal_extra PRIVATE sem1_algorithms)

add_executable(sem1_edge_cases "pruebas_internas/edge_cases_week1.cpp")
target_link_libraries(sem1_edge_cases PRIVATE sem1_algorithms)

add_test(NAME semana1_public COMMAND sem1_test_public)
add_test(NAME semana1_public_extra COMMAND sem1_test_public_extra)
add_test(NAME semana1_internal COMMAND sem1_test_internal)
add_test(NAME semana1_internal_extra COMMAND sem1_test_internal_extra)
add_test(NAME semana1_edge_cases COMMAND sem1_edge_cases)
