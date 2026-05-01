cmake_minimum_required(VERSION 3.20)
project(Semana8 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sem8_headers INTERFACE)
target_include_directories(sem8_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sem8_headers INTERFACE cxx_std_17)

function(cc232_add_sem8_target target_name source_file)
  add_executable(${target_name} "${source_file}")
  target_link_libraries(${target_name} PRIVATE sem8_headers)
endfunction()

# Demos basicos
cc232_add_sem8_target(sem8_demo_chained "demos/demo_chained.cpp")
cc232_add_sem8_target(sem8_demo_linear "demos/demo_linear.cpp")
cc232_add_sem8_target(sem8_demo_hashtable_oa "demos/demo_hashtable_oa.cpp")
cc232_add_sem8_target(sem8_demo_aplicaciones "demos/demo_aplicaciones.cpp")

# Demos avanzados
cc232_add_sem8_target(sem8_demo_collision_strategies "demos/demo_collision_strategies.cpp")
cc232_add_sem8_target(sem8_demo_hash_functions "demos/demo_hash_functions.cpp")
cc232_add_sem8_target(sem8_demo_tombstones "demos/demo_tombstones.cpp")
cc232_add_sem8_target(sem8_demo_benchmark_load_factor "demos/demo_benchmark_load_factor.cpp")

# Pruebas
cc232_add_sem8_target(sem8_test_public "pruebas_publicas/test_public_week8.cpp")
cc232_add_sem8_target(sem8_test_internal "pruebas_internas/test_internal_week8.cpp")
cc232_add_sem8_target(sem8_test_tombstones "pruebas_internas/test_tombstones.cpp")
cc232_add_sem8_target(sem8_test_collision_patterns "pruebas_internas/test_collision_patterns.cpp")
cc232_add_sem8_target(sem8_test_rehashing "pruebas_internas/test_rehashing.cpp")
cc232_add_sem8_target(sem8_test_randomized_against_stl "pruebas_internas/test_randomized_against_stl.cpp")

add_test(NAME semana8_public COMMAND sem8_test_public)
add_test(NAME semana8_internal COMMAND sem8_test_internal)
add_test(NAME semana8_tombstones COMMAND sem8_test_tombstones)
add_test(NAME semana8_collision_patterns COMMAND sem8_test_collision_patterns)
add_test(NAME semana8_rehashing COMMAND sem8_test_rehashing)
add_test(NAME semana8_randomized_against_stl COMMAND sem8_test_randomized_against_stl)
