cmake_minimum_required(VERSION 4.2)
project(rubiktrace_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rubiktrace_lib
        src/cube.cpp
        src/inference.cpp
)

target_include_directories(rubiktrace_lib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

enable_testing()
add_subdirectory(test)