cmake_minimum_required (VERSION 3.2)

project (desiredvpn_test)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory (eval)
add_subdirectory (gui)
add_subdirectory (tests)
