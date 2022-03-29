cmake_minimum_required(VERSION 3.0.0)
project(a.out)

add_subdirectory(lib1)
add_executable(${PROJECT_NAME} main.c)

# add_library(lib2)

set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Werror -Wpedantic")
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_LIBRARIES})