cmake_minimum_required(VERSION 3.0.0)
project(mylib)

if (V_HOW STREQUAL  "Simple_off" OR V_HOW STREQUAL "Complicated_off")
    set(CMAKE_C_FLAGS "-O0 -Wall -W -Werror -Wpedantic -fprofile-arcs -fPIC -ftest-coverage")
endif()

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set(MYLIB_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(MYLIB_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)