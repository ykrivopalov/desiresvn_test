set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Quick Core)
find_package(Qt5QuickCompiler)
add_executable(integrator_gui main.cpp main.qrc integrator.cpp)
qt5_use_modules(integrator_gui Quick Core)
target_link_libraries (integrator_gui eval ${CMAKE_THREAD_LIBS_INIT})
