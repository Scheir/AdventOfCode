cmake_minimum_required(VERSION 3.16)

# Set the C++ compiler explicitly
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(AdventOfCode LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O2 -std=c++20")


# Add the tools library
add_subdirectory(tools)

# Add the AoC25 directory
add_subdirectory(AoC24)

# Use FetchContent to download Google Benchmark
include(FetchContent)

set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE BOOL "Enable downloading dependencies (like Google Test)")

FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.0  # Use a specific version
)



# Fetch and build Google Benchmark
FetchContent_MakeAvailable(benchmark)

# Link Google Benchmark with the benchmark executable
target_link_libraries(benchmarks PRIVATE benchmark::benchmark)
