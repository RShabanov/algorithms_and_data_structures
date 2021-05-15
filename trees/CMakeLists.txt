cmake_minimum_required(VERSION 3.19)
project(trees)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        main.cpp)

set(SIMPLE_TREE
        simple_tree/Node.h
        simple_tree/SimpleTree.h
        )

add_executable(trees ${SOURCES} ${SIMPLE_TREE})