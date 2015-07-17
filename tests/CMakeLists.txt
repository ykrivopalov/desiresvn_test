project (tests)

enable_testing()

# for mocs
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package (Qt5Test REQUIRED)
find_package (Threads)

add_executable (tests thread_pool.cpp)
add_test (tests tests)

target_link_libraries (tests Qt5::Test eval ${CMAKE_THREAD_LIBS_INIT})
