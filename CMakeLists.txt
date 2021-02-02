cmake_minimum_required(VERSION 3.18)
project(start_svm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20 -lstdc++fs")
set(CMAKE_C_COMPILER "gcc-10")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-10")

include_directories(./include)

add_executable(start_svm src/main.cpp)