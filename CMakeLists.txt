#cmake_minimum_required(VERSION 2.8)
#PROJECT(BigDog)
#FIND_PACKAGE(Qt5Widgets REQUIRED)
#SET(BigDog_SOURCES main.cpp maintab.cpp mainwindow.cpp model.cpp
#	viewcontroller.cpp)
#SET(BigDog_HEADERS maintab.h mainwindow.h model.h viewcontroller.h)
#QT5_WRAP_CPP(BigDog_HEADERS_MOC ${BigDog_HEADERS})
#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_EXECUTABLE(BigDog ${BigDog_SOURCES} 
#    ${BigDog_HEADERS_MOC})
#TARGET_LINK_LIBRARIES(BigDog ${QT_LIBRARIES})

cmake_minimum_required(VERSION 2.8.11)

project(BigDog)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(BigDog WIN32 main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(BigDog Qt5::Widgets)