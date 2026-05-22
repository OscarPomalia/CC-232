cmake_minimum_required(VERSION 3.20)
project(Semana5 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sem5_headers INTERFACE)
target_include_directories(sem5_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sem5_headers INTERFACE cxx_std_17)

function(cc232_add_sem5_target target_name source_file)
  add_executable(${target_name} "${source_file}")
  target_link_libraries(${target_name} PRIVATE sem5_headers)
endfunction()

cc232_add_sem5_target(sem5_demo_binary_tree "demos/demo_binary_tree.cpp")
cc232_add_sem5_target(sem5_demo_bst "demos/demo_bst.cpp")
cc232_add_sem5_target(sem5_demo_heap "demos/demo_heap.cpp")
cc232_add_sem5_target(sem5_demo_capitulo5_panorama "demos/demo_capitulo5_panorama.cpp")
cc232_add_sem5_target(sem5_test_public "pruebas_publicas/test_public_week5.cpp")
cc232_add_sem5_target(sem5_test_internal "pruebas_internas/test_internal_week5.cpp")

add_test(NAME semana5_public COMMAND sem5_test_public)
add_test(NAME semana5_internal COMMAND sem5_test_internal)
