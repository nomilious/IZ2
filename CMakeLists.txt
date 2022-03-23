cmake_minimum_required(VERSION 3.0.0)
project(exec)

include_directories(include)
file(GLOB SOURCES src/*.c)

set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Werror -Wpedantic")
add_executable(${PROJECT_NAME} ${SOURCES})