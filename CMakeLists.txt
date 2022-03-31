cmake_minimum_required(VERSION 3.0.0)
project(a.out)

# _time for TIME testing
# _on for FSANITIZER
# _off for user's or VALGRIND run or for TESTS
# Simple - simple, nonparallel run
# Complicated for parallel run

set(CMAKE_C_STANDARD 99)

add_subdirectory(lib1)
add_subdirectory(lib2)
if (V_HOW STREQUAL "Simple_off" OR V_HOW STREQUAL  "Simple_on" OR V_HOW STREQUAL  "Simple_time")
    add_executable(${PROJECT_NAME} mains/main1.c)  
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib1)
    target_link_libraries(${PROJECT_NAME} PRIVATE mylib)
else()
    add_executable(${PROJECT_NAME} mains/main2.c)
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/lib2)
    target_link_libraries(${PROJECT_NAME} PRIVATE hardlib dl)
endif()


if (V_HOW STREQUAL "Simple_on" OR V_HOW STREQUAL "Complicated_on")
    set(CMAKE_C_FLAGS "-g")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  -fsanitize=address,undefined -fno-sanitize-recover=all-fsanitize-undefined-trap-on-error" )    
elseif (V_HOW STREQUAL "Simple_off" OR V_HOW STREQUAL "Complicated_off")
    set(CMAKE_C_FLAGS "-Wall -W -Werror -Wpedantic -g -O0 -fprofile-arcs -fPIC -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif()

add_subdirectory(tests)