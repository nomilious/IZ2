cmake_minimum_required(VERSION 3.0.0)
project(a.out)

set(CMAKE_C_STANDARD 99)
add_subdirectory(lib1)
if (simple)
    add_executable(${PROJECT_NAME} mains/main1.c)
else()
    add_executable(${PROJECT_NAME} mains/main2.c)
endif()

add_subdirectory(lib2)

set(CMAKE_C_FLAGS "-g -O0 -Wall -W -Werror -Wpedantic -fprofile-arcs -fPIC -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
target_include_directories(${PROJECT_NAME} PUBLIC ${MYLIB_LIB_INCLUDE_DIRS} PUBLIC ${HARDLIB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MYLIB_LIB_LIBRARIES} PRIVATE ${HARDLIB_LIB_LIBRARIES} dl)
add_subdirectory(tests)