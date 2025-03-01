cmake_minimum_required(VERSION 3.10)
project(EldenTreeEventHandler VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the library header files.
include_directories(${PROJECT_SOURCE_DIR}/include)

# Build the test executable.
add_executable(eldentree_tests tests/main.cpp)

# Build the benchmark executable.
add_executable(eldentree_benchmark benchmarks/benchmark.cpp)
