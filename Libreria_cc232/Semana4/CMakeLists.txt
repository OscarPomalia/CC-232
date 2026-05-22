cmake_minimum_required(VERSION 3.20)

project(Semana4 LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(sem4_headers INTERFACE)
target_include_directories(sem4_headers INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(sem4_headers INTERFACE cxx_std_17)

function(cc232_link_math_if_needed target_name)
    if(UNIX AND NOT APPLE)
        target_link_libraries(${target_name} PRIVATE m)
    endif()
endfunction()

function(cc232_add_sem4_target target_name source_file)
    add_executable(${target_name} "${source_file}")
    target_link_libraries(${target_name} PRIVATE sem4_headers)
    cc232_link_math_if_needed(${target_name})
endfunction()

cc232_add_sem4_target(sem4_demo_stack_queue "demos/demo_stack_queue.cpp")
cc232_add_sem4_target(sem4_demo_base_conversion "demos/demo_base_conversion.cpp")
cc232_add_sem4_target(sem4_demo_paren_rpn "demos/demo_paren_rpn.cpp")
cc232_add_sem4_target(sem4_demo_nqueens "demos/demo_nqueens.cpp")
cc232_add_sem4_target(sem4_demo_maze "demos/demo_maze.cpp")
cc232_add_sem4_target(sem4_demo_bank "demos/demo_bank.cpp")
cc232_add_sem4_target(sem4_demo_capitulo4_panorama "demos/demo_capitulo4_panorama.cpp")

cc232_add_sem4_target(sem4_test_public "pruebas_publicas/test_public_week4.cpp")
cc232_add_sem4_target(sem4_test_internal "pruebas_internas/test_internal_week4.cpp")

add_test(NAME semana4_public COMMAND sem4_test_public)
add_test(NAME semana4_internal COMMAND sem4_test_internal)
