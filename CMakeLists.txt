cmake_minimum_required(VERSION 2.8.4)
project(oled_control)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(oled_control ${SOURCE_FILES})