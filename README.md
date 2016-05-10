# Task

Design and implement an application that contains the following components:

* Static library written in C++ (without third party libraries and frameworks) that implements the following functional:
  * parallel integration of sin(x) by trapezoidal rule with a possibility of the integration step setting;
  * thread pool with a possibility of threads count setting.

* Application with Qt/QML interface that uses integration library from the previous paragraph. This application should allow to perform or cancel integration and change integration step.

* Application should compile under Windows and Linux platforms. It's better to use features from the C++11 standard.

# How to build

## Linux

1. Install g++, Qt5
2. `cd build`
3. `cmake ..`
4. `make`
5. `./gui/integrator_gui`

## Windows

1. Install Visual Studio and Qt5
2. `cd build`
3. `cmake ..`. If cmake couldn't find Qt then specify Qt path in parameters.  
  Ex.: `cmake -DCMAKE_PREFIX_PATH="C:\Qt\5.5\msvc2012" ..`
4. Previous command creates visual studio solution file; so open it and build projects.
5. Before application execution make sure that Qt binaries in system path.  
  Ex.:

        set PATH=%PATH%;C:\Qt\5.5\msvc2012\bin
        gui\Release\integrator_gui.exe
