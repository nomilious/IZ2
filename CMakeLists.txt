cmake_minimum_required(VERSION 3.0.0)
project(a.out)

set(CMAKE_C_STANDARD 99)
add_subdirectory(lib1)
if (simple)
    add_executable(${PROJECT_NAME} src/main1.c)
else()
    add_executable(${PROJECT_NAME} src/main2.c)
endif()


add_subdirectory(lib2)


set (CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Werror -Wpedantic")

target_include_directories(${PROJECT_NAME} PUBLIC ${MYLIB_LIB_INCLUDE_DIRS} PUBLIC ${HARDLIB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MYLIB_LIB_LIBRARIES} PRIVATE ${HARDLIB_LIB_LIBRARIES} dl)