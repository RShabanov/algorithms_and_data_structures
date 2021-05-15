cmake_minimum_required(VERSION 3.19)
project(trees)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        main.cpp
        )

set(HEADERS
        Node.h
        SimpleTree.h)


add_executable(trees ${SOURCES} ${HEADERS})