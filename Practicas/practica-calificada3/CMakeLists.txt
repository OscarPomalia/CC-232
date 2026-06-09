cmake_minimum_required(VERSION 3.10)
project(PC3_CC232)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Le decimos al compilador dónde buscar los .h
include_directories(include)

# Generamos el ejecutable principal
add_executable(pc3_main src/main.cpp)

# Habilitamos la herramienta de pruebas (ctest) que pide la rúbrica
enable_testing()