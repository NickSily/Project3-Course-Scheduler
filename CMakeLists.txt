cmake_minimum_required(VERSION 3.21)
project(Project3-Course-Scheduler)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project3-Course-Scheduler
        src/Graph.cpp
        src/Graph.h
        src/main.cpp)
