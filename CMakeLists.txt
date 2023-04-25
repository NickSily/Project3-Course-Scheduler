cmake_minimum_required(VERSION 3.21)
project(Gatorr)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Gatorr
        src/Graph.cpp
        src/Graph.h
        src/main.cpp)
