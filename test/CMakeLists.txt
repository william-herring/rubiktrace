add_executable(cube_manip_tests EXCLUDE_FROM_ALL cube_manip_tests.cpp)
add_executable(test_suite EXCLUDE_FROM_ALL cube_manip_tests.cpp)

target_link_libraries(cube_manip_tests ${PROJECT_NAME})
target_link_libraries(test_suite ${PROJECT_NAME})