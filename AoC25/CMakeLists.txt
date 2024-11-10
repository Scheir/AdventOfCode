set(DAY_SOURCES
    day1/day1.cpp
    day2/day2.cpp
)

# Main executable for AoC25
add_executable(runAoC main.cpp ${DAY_SOURCES})
target_link_libraries(runAoC PRIVATE tools)

# Add the benchmark executable
add_executable(benchmarks benchmarks/benchmarks.cpp ${DAY_SOURCES})


# TODO Potentially adding google tests aswell
# Tests and Benchmarks (commented out for now)
# enable_testing()
# add_executable(tests tests/tests.cpp)
# target_link_libraries(tests PRIVATE tools gtest gtest_main)
# add_test(NAME run_tests COMMAND tests)




