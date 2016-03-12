cmake_minimum_required(VERSION 2.8.4)
project(oled_control)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES ext/oled-control/oled-control.c ext/oled-control/oled-control.h ext/oled-control/main.c)
add_executable(oled_control ${SOURCE_FILES})
set_property(TARGET oled_control PROPERTY C_STANDARD 99)