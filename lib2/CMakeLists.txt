cmake_minimum_required(VERSION 3.0.0)
project(hardlib)


set(CMAKE_C_FLAGS "-g -O0 -Wall -W -Werror -Wpedantic -fprofile-arcs -fPIC -ftest-coverage")


file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set(HARDLIB_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(HARDLIB_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)


