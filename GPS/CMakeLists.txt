cmake_minimum_required(VERSION 3.19)

project(GPS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


set(HEADERS CA_generator.h)

set(SOURCES CA_generator.cpp)

add_executable(main main.cpp ${HEADERS} ${SOURCES})