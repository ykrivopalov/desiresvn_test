# @todo why 3.2?
cmake_minimum_required (VERSION 3.2)

project (desiredvpn_test)

add_compile_options(-std=c++11)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory (eval)
add_subdirectory (tests)
