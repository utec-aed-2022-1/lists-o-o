cmake_minimum_required(VERSION 3.17)
project(lists_o_o)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lists_o_o
        circular.h
        double.h
        forward.h
        list.h
        main.cpp
        node.h
        tester.h)
