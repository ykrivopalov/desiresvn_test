project (tests)

enable_testing()

# for mocs
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package (Qt5 REQUIRED COMPONENTS Test)
find_package (Threads)

add_executable (tests thread_pool.cpp integrator.cpp tests.cpp)
add_test (tests tests)
set_property(TARGET tests PROPERTY CXX_STANDARD 11)
target_link_libraries (tests Qt5::Test eval ${CMAKE_THREAD_LIBS_INIT})
