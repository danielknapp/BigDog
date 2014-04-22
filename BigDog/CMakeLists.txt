cmake_minimum_required(VERSION 2.8.11)

project(BigDog)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_PREFIX_PATH "/home/madhav/Qt5.2.1/5.2.1/gcc_64/lib/cmake")

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(BigDog main.cpp maintab.cpp mainwindow.cpp model.cpp viewcontroller.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(BigDog Qt5::Widgets)
