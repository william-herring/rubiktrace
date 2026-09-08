cmake_minimum_required(VERSION 4.2)
project(rubiktrace)

set(CMAKE_CXX_STANDARD 20)

add_library(rubiktrace_lib src/cube.cpp
        src/util.cpp
)

add_subdirectory(test)
enable_testing()
add_test(NAME cube_manip COMMAND cube_manip_tests)
add_test(NAME full COMMAND test_suite)

target_include_directories(rubiktrace_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
