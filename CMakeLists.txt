cmake_minimum_required(VERSION 3.5)
project(Field)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR on)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_AUTOMOC on)
set(CMAKE_AUTORCC on)

find_package(Qt5 REQUIRED Core Widgets Sql Charts)
find_package(Eigen)

set(SOURCE_FILES main.cpp Field.cpp Field.h)
add_executable(Field ${SOURCE_FILES})
target_link_libraries(Field Qt5::Widgets Qt5::Sql Qt5::Charts)
