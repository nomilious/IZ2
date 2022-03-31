cmake_minimum_required(VERSION 3.14)
project(test)

set(CMAKE_CXX_STANDARD 11)
if (V_HOW STREQUAL "Simple_off" OR V_HOW STREQUAL "Complicated_off")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -W -Werror -Wpedantic -g -O0 -fprofile-arcs -fPIC -ftest-coverage")
endif()
file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${HARDLIB_LIB_INCLUDE_DIRS} ${MYLIB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${HARDLIB_LIB_LIBRARIES} ${MYLIB_LIB_LIBRARIES} pthread GTest::Main)