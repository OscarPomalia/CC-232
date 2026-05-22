cmake_minimum_required(VERSION 3.20)
project(Semana6 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sem6_headers INTERFACE)

target_include_directories(sem6_headers
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Semana5/include"
)

target_compile_features(sem6_headers INTERFACE cxx_std_17)

function(cc232_add_sem6_target target_name source_file)
  add_executable(${target_name} "${source_file}")
  target_link_libraries(${target_name} PRIVATE sem6_headers)
endfunction()

cc232_add_sem6_target(sem6_demo_pq_complheap_basico "demos/demo_pq_complheap_basico.cpp")
cc232_add_sem6_target(sem6_demo_heapify_floyd "demos/demo_heapify_floyd.cpp")
cc232_add_sem6_target(sem6_demo_heapsort "demos/demo_heapsort.cpp")
cc232_add_sem6_target(sem6_demo_left_heap_merge "demos/demo_left_heap_merge.cpp")
cc232_add_sem6_target(sem6_demo_huffman "demos/demo_huffman.cpp")
cc232_add_sem6_target(sem6_demo_compare_with_semana5 "demos/demo_compare_with_semana5.cpp")
cc232_add_sem6_target(sem6_demo_bst_rotations "demos/demo_bst_rotations.cpp")
cc232_add_sem6_target(sem6_demo_treap_basico "demos/demo_treap_basico.cpp")
cc232_add_sem6_target(sem6_demo_capitulo6_panorama "demos/demo_capitulo6_panorama.cpp")
cc232_add_sem6_target(sem6_test_public "pruebas_publicas/test_public_week6.cpp")
cc232_add_sem6_target(sem6_test_internal "pruebas_internas/test_internal_week6.cpp")

add_test(NAME semana6_public COMMAND sem6_test_public)
add_test(NAME semana6_internal COMMAND sem6_test_internal)
