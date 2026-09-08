cmake_minimum_required(VERSION 4.2)
project(rubiktrace)

set(CMAKE_CXX_STANDARD 20)

add_library(rubiktrace_lib src/cube.cpp
        src/util.cpp)

target_include_directories(rubiktrace_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
