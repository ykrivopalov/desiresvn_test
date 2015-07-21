set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Gui Quick)
find_package (Threads)

add_executable(integrator_gui main.cpp main.qrc integrator.cpp)
set_property(TARGET integrator_gui PROPERTY CXX_STANDARD 11)
target_link_libraries (integrator_gui eval Qt5::Gui Qt5::Quick ${CMAKE_THREAD_LIBS_INIT})
